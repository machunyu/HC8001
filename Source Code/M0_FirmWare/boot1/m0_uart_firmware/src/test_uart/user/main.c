#include <string.h>
#include <stdint.h>
#include "cfg.h"
#include "gpio.h"
#include "uart_driver.h"
#include "protocol.h"
#include "i2c1_driver.h"
#include "ar0237_driver.h"
#include "dsp_cfg.h"
#include "cfg.h"
#include "hs_dsp.h"
#include "sys.h"


#define ISP_IMAGE_W_H                   *((volatile uint32_t*)0x4000912C)
#define ISP_IMAGE_OUT_W_H               *((volatile uint32_t*)0x40009130)
	
#define SENSOR_SEL                      *((volatile uint32_t*)0x40009154)	
	
#define ICPR                           *((volatile uint32_t*)0xE000E280)	

#define ISER                           *((volatile uint32_t*)0xE000E100)	
	
#define IPR0                           *((volatile uint32_t*)0xE000E400)
#define IPR1                           *((volatile uint32_t*)0xE000E404)	
#define IPR2                           *((volatile uint32_t*)0xE000E408)	
#define IPR3                           *((volatile uint32_t*)0xE000E40C)	
#define IPR4                           *((volatile uint32_t*)0xE000E410)	
#define IPR5                           *((volatile uint32_t*)0xE000E414)	
#define IPR6                           *((volatile uint32_t*)0xE000E418)	
#define IPR7                           *((volatile uint32_t*)0xE000E41C)

extern uint8_t gRxFlag;
extern uint32_t RX_NUM;
extern uint8_t RxBuff[1200];



int main(void)
{
	
	uint8_t ret;
	uint8_t Ack[20]={0};
	uint8_t CmdType;
	
	DSP_CTRL|=0x01;//dsp enable
	INT_CTRL|= 0xff ;//enable cm0 int
	UART0_CTRL |= 0x01;//enable uart0
	SW_BOOTLINK_EN |= 0x01;//enable bootlink
	
	while(DSP_CUR_STA!=0x81);
	INT_CTRL|=0xff ;//enable cm0 int
	
	IPR0 |= (1<<14); //Set dsp2 interrupt priority 
	I2C1_CTRL |= 0x01;//enable i2c1
	hs_uart_init();

	
	DSP_WR_EN1 = 0x77686873;
	TMPL_ENCODE_RX_PARA_FAKE_CHK = 0x03d400c8;//关闭活体检测 
	DSP_WR_EN1 = 0x00;
	
	DSP_WR_EN3 = 0x77686873;
	WRITE_TEMP_TIMEOUT = 0xffffffff;//设置注册超时时间	
	DSP_WR_EN3 = 0x00;
	ISP_IMAGE_W_H = 0x04380780;
	ISP_IMAGE_OUT_W_H = 0x00b40140; 
	
	MIPI_CSI_CTRL|=0x02; 
	
	SENSOR_SEL = 0x03;//sensor选择
		
	i2c1_init();

	ar0237_init();	
		
	while(1)
	{
		if (gRxFlag)
		{
			CmdType = RxBuff[1];

			switch(CmdType)
			{
				case ENCODE:
					
					if(RxBuff[2]==CalCRC8(RxBuff,2))
					{
						ret=IrisEncoded(56);//左眼第一次
						Ack[0]=0x5a;
						Ack[1]=CmdType;
						Ack[2]=ret;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_uart_send_str(Ack,5);
						delay(4000*1000);
	
					}else{
						Ack[0]=0x5a;
						Ack[1]=0xff;
						Ack[2]=0xff;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_uart_send_str(Ack,5);
					}
					break;
					
				case MATCH:
					if(RxBuff[2]==CalCRC8(RxBuff,2))
					{
						ret=IrisMatch();//识别
						Ack[0]=0x5a;
						Ack[1]=CmdType;
						Ack[2]=ret;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_uart_send_str(Ack,5);
						delay(4000*1000);

					}else{
						Ack[0]=0x5a;
						Ack[1]=0xff;
						Ack[2]=0xff;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_uart_send_str(Ack,5);
					}						
					
					break;
					
				case ERASER_ONE_TEMP:
					if(RxBuff[2]==CalCRC8(RxBuff,2))
					{
						ret=IrisEraseOneTemp(56);//删除单一模板
						Ack[0]=0x5a;
						Ack[1]=CmdType;
						Ack[2]=ret;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_uart_send_str(Ack,5);
						delay(4000*1000);

					}else{
						Ack[0]=0x5a;
						Ack[1]=0xff;
						Ack[2]=0xff;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_uart_send_str(Ack,5);
					}															
					break;
				
				case ERASER_ALL_TEMP:
					
					if(RxBuff[2]==CalCRC8(RxBuff,2))
					{
						ret=IrisEraseAllTemp();//删除全部模板
						Ack[0]=0x5a;
						Ack[1]=CmdType;
						Ack[2]=ret;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_uart_send_str(Ack,5);
						delay(4000*1000);

					}else{
						Ack[0]=0x5a;
						Ack[1]=0xff;
						Ack[2]=0xff;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_uart_send_str(Ack,5);
					}							
					break;
				case UPLOAD_TEMPLATE:
						
					
				default:
					
					break;	
			}
			gRxFlag = 0;
			RX_NUM = 0;
			memset(RxBuff,0,1200);
		}

	}
	
}


