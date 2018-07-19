#include <stdint.h>
#include <string.h>
#include "spi.h"
#include "cfg.h"
#include "dsp_cfg.h"
#include "hs_dsp.h"

uint8_t gSpiRxFlag = 0;
uint32_t RX_NUM = 0;
uint8_t SpiRxBuff[3000]={0};

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

void spi0_init(void)
{
	rSSIENR &=~0x01;//禁止SPI
	rCTRLR0 = 0x07;
	//rMWCR = 0x00;
	rTXFTLR = 0;
	rRXFTLR = 0;
	rIMR = 0x14;
	rSSIENR |= 0x01;//开启SPI
}

void hs_spi0_send(uint8_t ch)
{
	rDR = 0x0000|ch;
    while((rRISR&0x01)!=0x01);
}

void hs_spi0_send_str(uint8_t *pStr, uint32_t ulStrLength)
{
	while(ulStrLength--)
	{
		hs_spi0_send(*pStr);
		pStr++;
	}
}

void SPI0_IRQHandler(void)
{ 
	uint8_t res,status;
	uint8_t ret;
	uint8_t Ack[20]={0};
	uint8_t CmdType;
	if((rRISR&(1<<4))==0x10)
	{
		res=(uint8_t)rDR;
		SpiRxBuff[RX_NUM] = res;
		if(SpiRxBuff[0]==0xff)
		{
			RX_NUM =0;
		}else{
			RX_NUM++;
		}
		status= rICR;
		if((SpiRxBuff[0]==0x5a)&&(res==0xa5))
		{
			CmdType = SpiRxBuff[1];

			switch(CmdType)
			{
				case ENCODE:
					
					if(SpiRxBuff[2]==CalCRC8(SpiRxBuff,2))
					{
						ret=IrisEncoded(56,LeftEye,LowQuaulity,LocalAndReserveRawPic,BRAM_A);//左眼第一次
						Ack[0]=0x5a;
						Ack[1]=CmdType;
						Ack[2]=ret;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_spi0_send_str(Ack,5);
						//delay(4000*1000);
						
						ret=IrisEncoded(57,LeftEye,LowQuaulity,LocalAndReserveRawPic,BRAM_A);//左眼第二次
						Ack[0]=0x5a;
						Ack[1]=CmdType;
						Ack[2]=ret;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_spi0_send_str(Ack,5);
						//delay(4000*1000);
						
						ret=IrisEncoded(58,LeftEye,LowQuaulity,LocalAndReserveRawPic,BRAM_A);//右眼第一次
						Ack[0]=0x5a;
						Ack[1]=CmdType;
						Ack[2]=ret;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_spi0_send_str(Ack,5);
						//delay(4000*1000);
						
						ret=IrisEncoded(59,LeftEye,LowQuaulity,LocalAndReserveRawPic,BRAM_A);//右眼第二次
						Ack[0]=0x5a;
						Ack[1]=CmdType;
						Ack[2]=ret;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_spi0_send_str(Ack,5);
						//delay(4000*1000);
					}else{
						Ack[0]=0x5a;
						Ack[1]=0xff;
						Ack[2]=0xff;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_spi0_send_str(Ack,5);
					}
					break;
					
				case MATCH:
					if(SpiRxBuff[2]==CalCRC8(SpiRxBuff,2))
					{
						ret=IrisMatch(59,LeftEye,LowQuaulity,LocalAndReserveRawPic,BRAM_A,NormalMode);//识别
						Ack[0]=0x5a;
						Ack[1]=CmdType;
						Ack[2]=ret;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_spi0_send_str(Ack,5);
						//delay(4000*1000);

					}else{
						Ack[0]=0x5a;
						Ack[1]=0xff;
						Ack[2]=0xff;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_spi0_send_str(Ack,5);
					}						
					
					break;
					
				case ERASER_ONE_TEMP:
					if(SpiRxBuff[2]==CalCRC8(SpiRxBuff,2))
					{
						ret=IrisEraseOneTemp(56);//删除单一模板
						Ack[0]=0x5a;
						Ack[1]=CmdType;
						Ack[2]=ret;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_spi0_send_str(Ack,5);
						//delay(4000*1000);

					}else{
						Ack[0]=0x5a;
						Ack[1]=0xff;
						Ack[2]=0xff;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_spi0_send_str(Ack,5);
					}															
					break;
				
				case ERASER_ALL_TEMP:
					
					if(SpiRxBuff[2]==CalCRC8(SpiRxBuff,2))
					{
						ret=IrisEraseAllTemp();//删除全部模板
						Ack[0]=0x5a;
						Ack[1]=CmdType;
						Ack[2]=ret;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_spi0_send_str(Ack,5);
						//delay(4000*1000);

					}else{
						Ack[0]=0x5a;
						Ack[1]=0xff;
						Ack[2]=0xff;
						Ack[3]=CalCRC8(Ack,3);
						Ack[4]=0xa5;
						hs_spi0_send_str(Ack,5);
					}							
					break;
					
				default:
					
					break;	
			}
			RX_NUM = 0;
			memset(SpiRxBuff,0,1200);
		}
	}
	if((rRISR&0x01)==0x01)
	{
		status= rICR;
	}		
}
