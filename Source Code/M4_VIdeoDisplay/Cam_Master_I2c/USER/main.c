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
//变量定义
//===============================================================================================

 u8 ov2640_mode=0;						//工作模式:0,RGB565模式;1,JPEG模式

#define jpeg_dma_bufsize	5*1024    //定义JPEG DMA接收时数据缓存jpeg_buf0/1的大小(*4字节)
volatile u32 jpeg_data_len=0; 			//buf中的JPEG有效数据长度(*4字节)
volatile u8 jpeg_data_ok=0;				//JPEG数据采集完成标志 
										//0,数据没有采集完;
										//1,数据采集完了,但是还没处理;
										//2,数据已经处理完成了,可以开始下一帧接收
										
u32 *jpeg_buf0;							//JPEG数据缓存buf,通过malloc申请内存
u32 *jpeg_buf1;							//JPEG数据缓存buf,通过malloc申请内存
u32 *jpeg_data_buf;						//JPEG数据缓存buf,通过malloc申请内存


//===============================================================================================
// 主函数
//===============================================================================================
//切换为OV2640模式（GPIOC8/9/11切换为 DCMI接口）
void sw_ov2640_mode(void)
{
	OV2640_PWDN=0;//OV2640 Power Up
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_DCMI);  //PC8,AF13  DCMI_D2
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_DCMI);  //PC9,AF13  DCMI_D3
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_DCMI); //PC11,AF13 DCMI_D4  
 
} 

//jpeg数据接收回调函数
void jpeg_dcmi_rx_callback(void)
{ 
	u16 i;
	u32 *pbuf;
	pbuf=jpeg_data_buf/*+jpeg_data_len*/;//偏移到有效数据末尾
	//if(jpeg_data_len < 15* 1024)
	//{
	//if(DMA2_Stream1->CR&(1<<19))//buf0已满,正常处理buf1
	//{ 
		for(i=0;i<14400/*jpeg_dma_bufsize*/;i++)pbuf[i]=jpeg_buf0[i];//读取buf0里面的数据
		//jpeg_data_len+=jpeg_dma_bufsize;//偏移
		//jpeg_data_ok=1;
	//}
	#if 0
	else //buf1已满,正常处理buf0
	{
		for(i=0;i<jpeg_dma_bufsize;i++)pbuf[i]=jpeg_buf1[i];//读取buf1里面的数据
		jpeg_data_len+=jpeg_dma_bufsize;//偏移 
	} 
	//}	
	#endif
}


//处理JPEG数据
//当采集完一帧JPEG数据后,调用此函数,切换JPEG BUF.开始下一帧采集.
void jpeg_data_process(void)
{
	u16 i;
	u16 rlen;//剩余数据长度
	u32 *pbuf;
	if(ov2640_mode)//只有在JPEG格式下,才需要做处理.
	{
		if(jpeg_data_ok==0)	//jpeg数据还未采集完?
		{
			
			DMA_Cmd(DMA2_Stream1,DISABLE);		//停止当前传输
			while(DMA_GetCmdStatus(DMA2_Stream1) != DISABLE);	//等待DMA2_Stream1可配置 
			rlen=jpeg_dma_bufsize-DMA_GetCurrDataCounter(DMA2_Stream1);//得到剩余数据长度
				#if 0
			pbuf=jpeg_data_buf+jpeg_data_len;//偏移到有效数据末尾,继续添加
			if(DMA2_Stream1->CR&(1<<19))for(i=0;i<rlen;i++)pbuf[i]=jpeg_buf1[i];//读取buf1里面的剩余数据
			else for(i=0;i<rlen;i++)pbuf[i]=jpeg_buf0[i];//读取buf0里面的剩余数据 
			jpeg_data_len+=rlen;			//加上剩余长度
			#endif
			jpeg_data_ok=1; 				//标记JPEG数据采集完按成,等待其他函数处理
		}
		if(jpeg_data_ok==2)	//上一次的jpeg数据已经被处理了
		{ 
			DMA_SetCurrDataCounter(DMA2_Stream1,jpeg_dma_bufsize);//传输长度为jpeg_buf_size*4字节
			DMA_Cmd(DMA2_Stream1,ENABLE); //重新传输
			jpeg_data_ok=0;					//标记数据未采集
			jpeg_data_len=0;				//数据重新开始
		}
	}
}






//===============================================================================================
// 主函数
//===============================================================================================


int main(void)
{      
	u8 SendCmd[10]={0};	
	u32 i,j;
	u8* pbuf;
	u8 buff[5];
	u8 key,ret,state;           //保存键值
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200
	LED_Init();					//初始化LED 
	
	//TIM3_Int_Init(10000-1,8400-1);//10Khz计数,1秒钟中断一次
 	LCD_Init();					//LCD初始化  
	FSMC_SRAM_Init();			//初始化外部SRAM.
 	BEEP_Init();				//蜂鸣器初始化
 	KEY_Init();					//按键初始化 
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
	
	
	IIC_Stop();//产生一个停止条件
	printf("%d",ret);
}
#endif

	my_mem_init(SRAMIN);		//初始化内部内存池 
	my_mem_init(SRAMEX);		//初始化内部内存池  
	my_mem_init(SRAMCCM);		//初始化CCM内存池 

	POINT_COLOR=RED;      	 	
	jpeg_buf0=mymalloc(SRAMIN,/*jpeg_dma_bufsize*/13600*4);	//为jpeg dma接收申请内存	
	jpeg_buf1=mymalloc(SRAMIN,jpeg_dma_bufsize*4);	//为jpeg dma接收申请内存	
	jpeg_data_buf=mymalloc(SRAMEX,300*1024);		//为jpeg文件申请内存(最大300KB)

	ov2640_mode=1;
	My_DCMI_Init();			//DCMI配置
	dcmi_rx_callback=jpeg_dcmi_rx_callback;//回调函数
	DCMI_DMA_Init((u32)jpeg_buf0,0/*(u32)jpeg_buf1*/,14400/*jpeg_dma_bufsize*/,DMA_MemoryDataSize_Word,DMA_MemoryInc_Enable);//DCMI DMA配置(双缓冲模式)

	DCMI_Set_Window(0,0,320,180);
		 
 	while(1)
	{	

		DCMI_Start(); 
		while(jpeg_data_ok!=1);	//等待第一帧图片采集完
		
		DCMI_Stop(); //停止显示
		pbuf=(u8*)jpeg_data_buf;
	
		for(i=0;i<180;i++)
		{
			LCD_SetCursor(0,i);   	//设置光标位置 
			LCD_WriteRAM_Prepare();     //开始写入GRAM
			for(j=0;j<320;j++)
			{	
				LCD->LCD_RAM= ((pbuf[i*320+j]&0xf8)<<8)|((pbuf[i*320+j]&0xfC)<<3)|((pbuf[i*320+j]&0xf8)>>3);				
			}
			
		}

		key=KEY_Scan(0);		//得到键值
	   	if(key)
		{	
			BEEP_On();	
			switch(key)
			{				 
				case KEY3_PRES:	//注册
					SendCmd[0]=0x5a;
					SendCmd[1]=ENCODE;	
					SendCmd[2] = CalCRC8(SendCmd,2);
					SendCmd[3] = 0xa5;
					IIC_SendStr(SendCmd,4);	

					break;
				case KEY0_PRES:	//识别
					SendCmd[0]=0x5a;
					SendCmd[1]=MATCH;	
					SendCmd[2] = CalCRC8(SendCmd,2);
					SendCmd[3] = 0xa5;
					IIC_SendStr(SendCmd,4);	

					break;
				case KEY1_PRES:	//删除单个模板
					SendCmd[0]=0x5a;
					SendCmd[1]=ERASER_ONE_TEMP;	
					SendCmd[2] = CalCRC8(SendCmd,2);
					SendCmd[3] = 0xa5;
					IIC_SendStr(SendCmd,4);			

					break;
				case KEY2_PRES:	 //删除全部模板
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








