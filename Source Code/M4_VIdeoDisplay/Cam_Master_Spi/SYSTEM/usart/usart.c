#include "sys.h"
#include "usart.h"	
#include <string.h>
#include "lcd.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F4̽���߿�����
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/6/10
//�汾��V1.5
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
//V1.5�޸�˵��
//1,�����˶�UCOSII��֧��
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB

#define HS_HAL_OK                            0x00
#define HS_HAL_ERROR                         0x01
#define HS_HAL_BUSY                          0x02
#define HS_HAL_TIMEOUT                       0x04


#define WRITE_READ_FLASH_TIMEOUT             0x05
#define WRITE_READ_FLASH_MATCH_ERROR         0x06
#define TEMPLATE_INDEX_OVER                  0x07
#define ENCODE_TIMEOUT                       0x08
#define MATCH_TIMEOUT                        0x09
#define MATCH_ERROR                          0x0A

#define FLAG1                                0x21
#define FLAG2                                0x22
#define BEEP                                 0x23

#define ENCODE_OK                            0x11
#define MATCH_OK                             0x12
#define ERASER_ONE_TEMP_OK                   0x13
#define ERASER_ALL_TEMP_OK                   0x14

uint8_t CalCRC8(uint8_t *vptr, uint32_t len)
{
    const uint8_t *dat = vptr;
    uint16_t crc = 0;
    uint32_t i, j;
    
    for (j = len; j; j--, dat++) {
        crc ^= (*dat << 8);
        for (i = 8; i; i--) {
            if (crc & 0x8000)
                crc ^= (uint16_t)(0x1070 << 3);
            crc <<= 1;
        }
    }
    return (uint8_t)(crc >> 8);
}

#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif
 
void Send_Char(u8 ch)
{
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
}

void uart_send_str(uint8_t *pStr, uint32_t ulStrLength)
{
	while(ulStrLength--)
	{
		Send_Char(*pStr);
		pStr++;
	}
}
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	

//��ʼ��IO ����1 
//bound:������
void uart_init(u32 bound){
   //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��USART1ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10����ΪUSART1
	
	//USART1�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA9��PA10

   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	
 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	
#if EN_USART1_RX	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

#endif
	 USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
	
}


void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 i,Res,state;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�
	{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
		USART_RX_BUF[USART_RX_STA]=Res ;
		USART_RX_STA++;

		if((USART_RX_BUF[0]==0x5a)&&(Res==0xa5))
		{
			if(USART_RX_BUF[3]==CalCRC8(USART_RX_BUF,3))
			{
				state = USART_RX_BUF[2];
				switch (state)
				{

					case ENCODE_OK:
						LCD_ShowString(30,40,210,24,24,"Encode OK");
						delay_ms(1000);
						break;
					case MATCH_OK:
						LCD_ShowString(30,40,210,24,24,"Match OK");
						delay_ms(1000);
						break;
					case ERASER_ONE_TEMP_OK:
						LCD_ShowString(30,40,210,24,24,"Eraser one temp OK");
						delay_ms(1000);
						break;
					case ERASER_ALL_TEMP_OK:
						LCD_ShowString(30,40,210,24,24,"Eraser all temp OK");
						delay_ms(1000);
						break;
					case WRITE_READ_FLASH_TIMEOUT:
						LCD_ShowString(30,40,210,24,24,"WRITE READ FLASH TIMEOUT ");
						delay_ms(1000);
						break;
					case WRITE_READ_FLASH_MATCH_ERROR:
						LCD_ShowString(30,40,210,24,24,"WRITE READ FLASH MATCH ERROR");
						delay_ms(1000);
						break;
					case TEMPLATE_INDEX_OVER:
						LCD_ShowString(30,40,210,24,24,"TEMPLATE INDEX OVER");
						delay_ms(1000);
						break;
					case ENCODE_TIMEOUT:
						LCD_ShowString(30,40,210,24,24,"ENCODE TIMEOUT");
						delay_ms(1000);
						break;
					case MATCH_TIMEOUT:
						LCD_ShowString(30,40,210,24,24,"MATCH TIMEOUT");
						delay_ms(1000);
						break;
					case MATCH_ERROR:
						LCD_ShowString(30,40,210,24,24,"MATCH ERROR");
						delay_ms(1000);
						break;

					case FLAG1:
						if(USART_RX_BUF[1]==0x01)
						{
							POINT_COLOR = GREEN;
						}
						if(USART_RX_BUF[1]==0x02)
						{
							POINT_COLOR = YELLOW;
						}						
						LCD_DrawLine(20,20,40,20);
						LCD_DrawLine(280,20,300,20);
						LCD_DrawLine(20,160,40,160);
						LCD_DrawLine(280,160,300,160);
						LCD_DrawLine(20,20,20,40);
						LCD_DrawLine(300,20,300,40);
						LCD_DrawLine(20,140,20,160);
						LCD_DrawLine(300,140,300,160);
						break;
					case FLAG2:
						POINT_COLOR = GREEN;
						LCD_DrawRectangle(20,20,300,160);
						break;
					
					case BEEP:
						#if 0
						for(i=0;i<2;i++)
						{
							GPIO_SetBits(GPIOF,GPIO_Pin_8);  //��������Ӧ����GPIOF8���ߣ�
							delay_ms(100);
							GPIO_ResetBits(GPIOF,GPIO_Pin_8);  //��������Ӧ����GPIOF8���ߣ�
							delay_ms(100);
						}	
						#endif
						break;
					default:
						break;
					
				}
				USART_RX_STA = 0;
				memset(USART_RX_BUF,0,USART_REC_LEN);
			}else{
				USART_RX_STA = 0;
				memset(USART_RX_BUF,0,USART_REC_LEN);
			}

		}

  } 

} 
#endif	

 



