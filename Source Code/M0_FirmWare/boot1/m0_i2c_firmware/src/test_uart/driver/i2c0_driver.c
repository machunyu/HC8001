#include <stdint.h>
#include <string.h>
#include "i2c.h"
#include "dsp_cfg.h"
#include "hs_dsp.h"

uint8_t gI2cRxFlag = 0;
uint32_t RX_NUM = 0;
uint8_t I2cRxBuff[2000]={0};

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

void i2c0_init(void)
{
	rIC0_ENABLE &=~0x01;//禁能IIC
	rIC0_SAR = 0x018;//设置从机地址0x18
	rIC0_CON &=~(1<<3);//设置从机地址为7bit
	rIC0_CON &=~(1<<2);
	rIC0_CON |= (1<<1);//设置速度为standard mode（0~100k）
	
	rIC0_CON &=~ 0x01;//禁能master mode
	rIC0_CON &=~(1<<6);//使能slave mode
	rIC0_CON = 0x02;
	rIC0_RX_TL = 0;
	rIC0_TX_TL = 0;
	rIC0_INTR_MASK = 0x024;

	rIC0_ENABLE |= 0x01;//使能IIC
}

void hs_i2c0_send(uint8_t ch)
{
	
	while(!(rIC0_RAW_INTR_STAT&(1<<5)));
	
	rIC0_DATA_CMD = 0x000 |ch;
	
}

void hs_i2c0_send_str(uint8_t *pStr, uint32_t ulStrLength)
{
	while(ulStrLength--)
	{
		hs_i2c0_send(*pStr);
		pStr++;
	}
}

void I2C0_IRQHandler(void)
{ 
	uint8_t status;
	//status =rIC0_RAW_INTR_STAT;
	if(rIC0_RAW_INTR_STAT&(1<<5))
	{		
		rIC0_DATA_CMD =0xa5;		
		//rIC0_DATA_CMD =0x5a;
	    //rIC0_DATA_CMD =0x11;
		//rIC0_DATA_CMD =0x22;
		//rIC0_DATA_CMD =0x33;
		status=rIC0_CLR_RD_REQ;
	}
	if(rIC0_RAW_INTR_STAT&(1<<2))
	{
		uint8_t res;
		uint8_t ret;
		uint8_t CmdType;
		uint8_t Ack[20]={0};
		res=(uint8_t)rIC0_DATA_CMD;
		I2cRxBuff[RX_NUM] = res;
		RX_NUM++;
		if((I2cRxBuff[0]==0x5a)&&(res==0xa5))
		{
			CmdType = I2cRxBuff[1];

			switch(CmdType)
			{
				case ENCODE:
					
					if(I2cRxBuff[2]==CalCRC8(I2cRxBuff,2))
					{
						ret=IrisEncoded(56);//左眼第一次
						Ack[0]=0x5a;
						Ack[1]=CmdType;
						Ack[2]=ret;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_i2c0_send_str(Ack,5);	
						
					}else{
						Ack[0]=0x5a;
						Ack[1]=0xff;
						Ack[2]=0xff;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_i2c0_send_str(Ack,5);
					}
					break;
					
				case MATCH:
					if(I2cRxBuff[2]==CalCRC8(I2cRxBuff,2))
					{
						ret=IrisMatch();//识别
						Ack[0]=0x5a;
						Ack[1]=CmdType;
						Ack[2]=ret;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_i2c0_send_str(Ack,5);
					

					}else{
						Ack[0]=0x5a;
						Ack[1]=0xff;
						Ack[2]=0xff;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_i2c0_send_str(Ack,5);
					}						
					
					break;
					
				case ERASER_ONE_TEMP:
					if(I2cRxBuff[2]==CalCRC8(I2cRxBuff,2))
					{
						ret=IrisEraseOneTemp(56);//删除单一模板
						Ack[0]=0x5a;
						Ack[1]=CmdType;
						Ack[2]=ret;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_i2c0_send_str(Ack,5);
					

					}else{
						Ack[0]=0x5a;
						Ack[1]=0xff;
						Ack[2]=0xff;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_i2c0_send_str(Ack,5);
					}															
					break;
				
				case ERASER_ALL_TEMP:
					
					if(I2cRxBuff[2]==CalCRC8(I2cRxBuff,2))
					{
						ret=IrisEraseAllTemp();//删除全部模板
						Ack[0]=0x5a;
						Ack[1]=CmdType;
						Ack[2]=ret;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_i2c0_send_str(Ack,5);
				

					}else{
						Ack[0]=0x5a;
						Ack[1]=0xff;
						Ack[2]=0xff;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_i2c0_send_str(Ack,5);
					}							
					break;
					
				default:
					
					break;	
			}
			RX_NUM = 0;
			memset(I2cRxBuff,0,1200);
		}
	}
}

