#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "key.h"  
#include "sram.h"   
#include "malloc.h" 
#include "usmart.h"  
#include "sdio_sdcard.h"    
#include "malloc.h" 
   
#include "ff.h"  
#include "exfuns.h"    
#include "fontupd.h"
#include "text.h"	
#include "piclib.h"	
#include "string.h"	
#include "math.h"	
#include "dcmi.h"	
#include "ov2640.h"	
#include "beep.h"	
#include "timer.h"
#include "spi.h"
#include "myiic.h"
#include "delay.h"




#define WRITE_READ_FLASH_TIMEOUT             0x05
#define WRITE_READ_FLASH_MATCH_ERROR         0x06
#define TEMPLATE_INDEX_OVER                  0x07
#define ENCODE_TIMEOUT                       0x08
#define MATCH_TIMEOUT                        0x09
#define MATCH_ERROR                          0x0A

#define FLAG1                                0x21
#define FLAG2                                0x22


#define ENCODE_OK                            0x11
#define MATCH_OK                             0x12
#define ERASER_ONE_TEMP_OK                   0x13
#define ERASER_ALL_TEMP_OK                   0x14

#define ENCODE             0x01
#define MATCH              0x02
#define ERASER_ONE_TEMP    0x03
#define ERASER_ALL_TEMP    0x04
//===============================================================================================
//��������
//===============================================================================================

 u8 ov2640_mode=0;						//����ģʽ:0,RGB565ģʽ;1,JPEGģʽ

#define jpeg_dma_bufsize	5*1024    //����JPEG DMA����ʱ���ݻ���jpeg_buf0/1�Ĵ�С(*4�ֽ�)
volatile u32 jpeg_data_len=0; 			//buf�е�JPEG��Ч���ݳ���(*4�ֽ�)
volatile u8 jpeg_data_ok=0;				//JPEG���ݲɼ���ɱ�־ 
										//0,����û�вɼ���;
										//1,���ݲɼ�����,���ǻ�û����;
										//2,�����Ѿ����������,���Կ�ʼ��һ֡����
										
u32 *jpeg_buf0;							//JPEG���ݻ���buf,ͨ��malloc�����ڴ�
u32 *jpeg_buf1;							//JPEG���ݻ���buf,ͨ��malloc�����ڴ�
u32 *jpeg_data_buf;						//JPEG���ݻ���buf,ͨ��malloc�����ڴ�


//===============================================================================================
// ������
//===============================================================================================
//�л�ΪOV2640ģʽ��GPIOC8/9/11�л�Ϊ DCMI�ӿڣ�
void sw_ov2640_mode(void)
{
	OV2640_PWDN=0;//OV2640 Power Up
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_DCMI);  //PC8,AF13  DCMI_D2
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_DCMI);  //PC9,AF13  DCMI_D3
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_DCMI); //PC11,AF13 DCMI_D4  
 
} 

//jpeg���ݽ��ջص�����
void jpeg_dcmi_rx_callback(void)
{ 
	u16 i;
	u32 *pbuf;
	pbuf=jpeg_data_buf/*+jpeg_data_len*/;//ƫ�Ƶ���Ч����ĩβ
	//if(jpeg_data_len < 15* 1024)
	//{
	//if(DMA2_Stream1->CR&(1<<19))//buf0����,��������buf1
	//{ 
		for(i=0;i<14400/*jpeg_dma_bufsize*/;i++)pbuf[i]=jpeg_buf0[i];//��ȡbuf0���������
		//jpeg_data_len+=jpeg_dma_bufsize;//ƫ��
		//jpeg_data_ok=1;
	//}
	#if 0
	else //buf1����,��������buf0
	{
		for(i=0;i<jpeg_dma_bufsize;i++)pbuf[i]=jpeg_buf1[i];//��ȡbuf1���������
		jpeg_data_len+=jpeg_dma_bufsize;//ƫ�� 
	} 
	//}	
	#endif
}


//����JPEG����
//���ɼ���һ֡JPEG���ݺ�,���ô˺���,�л�JPEG BUF.��ʼ��һ֡�ɼ�.
void jpeg_data_process(void)
{
	u16 i;
	u16 rlen;//ʣ�����ݳ���
	u32 *pbuf;
	if(ov2640_mode)//ֻ����JPEG��ʽ��,����Ҫ������.
	{
		if(jpeg_data_ok==0)	//jpeg���ݻ�δ�ɼ���?
		{
			
			DMA_Cmd(DMA2_Stream1,DISABLE);		//ֹͣ��ǰ����
			while(DMA_GetCmdStatus(DMA2_Stream1) != DISABLE);	//�ȴ�DMA2_Stream1������ 
			rlen=jpeg_dma_bufsize-DMA_GetCurrDataCounter(DMA2_Stream1);//�õ�ʣ�����ݳ���
				#if 0
			pbuf=jpeg_data_buf+jpeg_data_len;//ƫ�Ƶ���Ч����ĩβ,�������
			if(DMA2_Stream1->CR&(1<<19))for(i=0;i<rlen;i++)pbuf[i]=jpeg_buf1[i];//��ȡbuf1�����ʣ������
			else for(i=0;i<rlen;i++)pbuf[i]=jpeg_buf0[i];//��ȡbuf0�����ʣ������ 
			jpeg_data_len+=rlen;			//����ʣ�೤��
			#endif
			jpeg_data_ok=1; 				//���JPEG���ݲɼ��갴��,�ȴ�������������
		}
		if(jpeg_data_ok==2)	//��һ�ε�jpeg�����Ѿ���������
		{ 
			DMA_SetCurrDataCounter(DMA2_Stream1,jpeg_dma_bufsize);//���䳤��Ϊjpeg_buf_size*4�ֽ�
			DMA_Cmd(DMA2_Stream1,ENABLE); //���´���
			jpeg_data_ok=0;					//�������δ�ɼ�
			jpeg_data_len=0;				//�������¿�ʼ
		}
	}
}






//===============================================================================================
// ������
//===============================================================================================


int main(void)
{      
	u8 SendCmd[10]={0};	
	u32 i,j;
	u8* pbuf;
	u8 buff[5];
	u8 key,ret,state;           //�����ֵ
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	LED_Init();					//��ʼ��LED 
	
	//TIM3_Int_Init(10000-1,8400-1);//10Khz����,1�����ж�һ��
 	LCD_Init();					//LCD��ʼ��  
	FSMC_SRAM_Init();			//��ʼ���ⲿSRAM.
 	BEEP_Init();				//��������ʼ��
 	KEY_Init();					//������ʼ�� 
	IRIS_Int_Init();
	IIC_Init();
#if 0	
while(1){	
	
	//SDA_OUT();
	IIC_Start();
	IIC_Send_Byte(0x31);
	
	IIC_Wait_Ack();	
	ret = IIC_Read_Byte(1);
	//delay_ms(1);
	
	
	IIC_Stop();//����һ��ֹͣ����
	printf("%d",ret);
}
#endif

	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ�� 
	my_mem_init(SRAMEX);		//��ʼ���ڲ��ڴ��  
	my_mem_init(SRAMCCM);		//��ʼ��CCM�ڴ�� 

	POINT_COLOR=RED;      	 	
	jpeg_buf0=mymalloc(SRAMIN,/*jpeg_dma_bufsize*/13600*4);	//Ϊjpeg dma���������ڴ�	
	jpeg_buf1=mymalloc(SRAMIN,jpeg_dma_bufsize*4);	//Ϊjpeg dma���������ڴ�	
	jpeg_data_buf=mymalloc(SRAMEX,300*1024);		//Ϊjpeg�ļ������ڴ�(���300KB)

	ov2640_mode=1;
	My_DCMI_Init();			//DCMI����
	dcmi_rx_callback=jpeg_dcmi_rx_callback;//�ص�����
	DCMI_DMA_Init((u32)jpeg_buf0,0/*(u32)jpeg_buf1*/,14400/*jpeg_dma_bufsize*/,DMA_MemoryDataSize_Word,DMA_MemoryInc_Enable);//DCMI DMA����(˫����ģʽ)

	DCMI_Set_Window(0,0,320,180);
		 
 	while(1)
	{	

		DCMI_Start(); 
		while(jpeg_data_ok!=1);	//�ȴ���һ֡ͼƬ�ɼ���
		
		DCMI_Stop(); //ֹͣ��ʾ
		pbuf=(u8*)jpeg_data_buf;
	
		for(i=0;i<180;i++)
		{
			LCD_SetCursor(0,i);   	//���ù��λ�� 
			LCD_WriteRAM_Prepare();     //��ʼд��GRAM
			for(j=0;j<320;j++)
			{	
				LCD->LCD_RAM= ((pbuf[i*320+j]&0xf8)<<8)|((pbuf[i*320+j]&0xfC)<<3)|((pbuf[i*320+j]&0xf8)>>3);				
			}
			
		}

		key=KEY_Scan(0);		//�õ���ֵ
	   	if(key)
		{	
			BEEP_On();	
			switch(key)
			{				 
				case KEY3_PRES:	//ע��
					SendCmd[0]=0x5a;
					SendCmd[1]=ENCODE;	
					SendCmd[2] = CalCRC8(SendCmd,2);
					SendCmd[3] = 0xa5;
					IIC_SendStr(SendCmd,4);	

					break;
				case KEY0_PRES:	//ʶ��
					SendCmd[0]=0x5a;
					SendCmd[1]=MATCH;	
					SendCmd[2] = CalCRC8(SendCmd,2);
					SendCmd[3] = 0xa5;
					IIC_SendStr(SendCmd,4);	

					break;
				case KEY1_PRES:	//ɾ������ģ��
					SendCmd[0]=0x5a;
					SendCmd[1]=ERASER_ONE_TEMP;	
					SendCmd[2] = CalCRC8(SendCmd,2);
					SendCmd[3] = 0xa5;
					IIC_SendStr(SendCmd,4);			

					break;
				case KEY2_PRES:	 //ɾ��ȫ��ģ��
					SendCmd[0]=0x5a;
					SendCmd[1]=ERASER_ALL_TEMP;	
					SendCmd[2] = CalCRC8(SendCmd,2);
					SendCmd[3] = 0xa5;
					IIC_SendStr(SendCmd,4);	
					
					break;
			}
		}
		delay_ms(50);
		BEEP_Off();		
		#if 1
		if(!IRIS_Int_Scan())
		{
			IIC_ReadStr(buff,5);
			if((buff[0]==0x5a)&&(buff[4]==0xa5))
			{
				if(USART_RX_BUF[3]==CalCRC8(USART_RX_BUF,3))
				{
					state = buff[2];
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
		#endif
		jpeg_data_len=0;			
	}
}








