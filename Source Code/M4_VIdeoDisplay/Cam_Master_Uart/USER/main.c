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
#include "w25qxx.h"    
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
	u8 key,a,b,beep;           //�����ֵ
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200

 	LCD_Init();					//LCD��ʼ��  
	FSMC_SRAM_Init();			//��ʼ���ⲿSRAM.
 	BEEP_Init();				//��������ʼ��
 	KEY_Init();					//������ʼ��   

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
			switch(key)
			{				 
				case WKUP_PRES:	//ע��
					SendCmd[0]=0x5a;
					SendCmd[1]=ENCODE;	
					SendCmd[2] = CalCRC8(SendCmd,2);
					SendCmd[3] = 0xa5;
					uart_send_str(SendCmd,4);	

					break;
				case KEY0_PRES:	//ʶ��
					SendCmd[0]=0x5a;
					SendCmd[1]=MATCH;	
					SendCmd[2] = CalCRC8(SendCmd,2);
					SendCmd[3] = 0xa5;
					uart_send_str(SendCmd,4);	

					break;
				case KEY1_PRES:	//ɾ������ģ��
					SendCmd[0]=0x5a;
					SendCmd[1]=ERASER_ONE_TEMP;	
					SendCmd[2] = CalCRC8(SendCmd,2);
					SendCmd[3] = 0xa5;
					uart_send_str(SendCmd,4);			

					break;
				case KEY2_PRES:	 //ɾ��ȫ��ģ��
					SendCmd[0]=0x5a;
					SendCmd[1]=ERASER_ALL_TEMP;	
					SendCmd[2] = CalCRC8(SendCmd,2);
					SendCmd[3] = 0xa5;
					uart_send_str(SendCmd,4);						
					break;
			}
		} 
		jpeg_data_len=0;			
	}
}








