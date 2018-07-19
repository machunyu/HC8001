#include <string.h>
#include "uart_driver.h"
#include "protocol.h"

extern uint8_t gRxFlag;
extern uint32_t RX_NUM;
extern uint8_t RxBuff[2000];

static uint8_t CalCRC8(uint8_t *vptr, uint32_t len)
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


void hs_uart_protocol()
{
	uint32_t i;
	uint32_t WriteData;
	uint32_t ReadData;
	uint32_t RegAddr;
	
	uint32_t RegType;
	uint32_t CmdType;
	
	uint32_t addr_0;
	uint32_t addr_1;
	uint32_t addr_2;
	uint32_t addr_3;

	uint32_t data_0;
	uint32_t data_1;
	uint32_t data_2;
	uint32_t data_3;

	uint16_t TempIndex;
	uint16_t ImagPackNum;
	uint8_t  TempPackNum;
	uint16_t TempLength;
	uint32_t ImagLength;
	uint32_t TempData;
	uint32_t ImagData;
		
	uint8_t ICAck[20];

	while(1)
	{	
		if(gRxFlag == 1)
		{
			if(RxBuff[0] == 0x5a)
			{	
				CmdType = RxBuff[1];

				switch(CmdType)
				{
					case WRITE_REG:
						
						if(RxBuff[12]==CalCRC8(RxBuff,12))
						{
							RegType = RxBuff[2]; 
							
							if(READ_ONLY!=RegType)
							{							
								addr_0 = RxBuff[3];
								addr_1 = RxBuff[4];
								addr_2 = RxBuff[5];
								addr_3 = RxBuff[6];
								
								data_0 = RxBuff[7];
								data_1 = RxBuff[8];
								data_2 = RxBuff[9];
								data_3 = RxBuff[10];
								
								RegAddr = (addr_0<<24)|(addr_1<<16)|(addr_2<<8)|addr_3;
								WriteData = (data_0<<24)|(data_1<<16)|(data_2<<8)|data_3;
								*((volatile uint32_t*)RegAddr) = WriteData;
								
								ICAck[0]=0x5a;
								ICAck[1]=CmdType;
								ICAck[2]=RegType;
								ICAck[3]=addr_0;
								ICAck[4]=addr_1;
								ICAck[5]=addr_2;
								ICAck[6]=addr_3;
								ICAck[7]=data_0;
								ICAck[8]=data_1;
								ICAck[9]=data_2;
								ICAck[10]=data_3;
								ICAck[11]=0x00;
								ICAck[12]=CalCRC8(ICAck,12);
								ICAck[13]=0x5a;
								ICAck[14]=0xF2;
								ICAck[15]=0x3D;
								ICAck[16]=0xa5;
								hs_uart_send_str(ICAck,17);									
							}
						}else{
							ICAck[0]=0x5a;
							ICAck[1]=0xff;
							ICAck[2]=0xff;
							ICAck[3]=0xff;
							ICAck[4]=CalCRC8(ICAck,4);
							ICAck[5]=0xa5;
							hs_uart_send_str(ICAck,6);
						}
						break;
						
					case READ_REG:
						if(RxBuff[12]==CalCRC8(RxBuff,12))
						{
						
							RegType = RxBuff[2];
						
							if(WRITE_ONLY!=RegType)
							{								
								addr_0 = RxBuff[3];
								addr_1 = RxBuff[4];
								addr_2 = RxBuff[5];
								addr_3 = RxBuff[6];

								RegAddr = (addr_0<<24)|(addr_1<<16)|(addr_2<<8)|addr_3;
								ReadData = *((volatile uint32_t*)RegAddr) ;
								data_0=ReadData>>24;
								data_1=ReadData>>16;
								data_2=ReadData>>8;
								data_3=ReadData;
															
								ICAck[0]=0x5a;
								ICAck[1]=CmdType;
								ICAck[2]=RegType;
								ICAck[3]=addr_0;
								ICAck[4]=addr_1;
								ICAck[5]=addr_2;
								ICAck[6]=addr_3;
								ICAck[7]=0x00;
								ICAck[8]=data_0;
								ICAck[9]=data_1;
								ICAck[10]=data_2;
								ICAck[11]=data_3;
								ICAck[12]=CalCRC8(ICAck,12);
								ICAck[13]=0x5a;
								ICAck[14]=0xF2;
								ICAck[15]=0x3D;
								ICAck[16]=0xa5;
								hs_uart_send_str(ICAck,17);								
							}
					    }else{
							ICAck[0]=0x5a;
							ICAck[1]=0xff;
							ICAck[2]=0xff;
							ICAck[3]=0xff;
							ICAck[4]=CalCRC8(ICAck,4);
							ICAck[5]=0xa5;
							hs_uart_send_str(ICAck,6);
						}						
						
						break;
						
					case DOWNLOAD_TEMP:
						TempIndex = (RxBuff[3]<<8)|RxBuff[2];
					
						TempLength = (RxBuff[5]<<8)|RxBuff[4];
						TempPackNum = RxBuff[6];
						//memcpy((void*)0x30090000,RxBuff+5,TempLength);
						for(i=0;i<TempLength/4;i++)
						{
							*((volatile uint32_t*)(0x30090000+4*i+TempPackNum*TempLength))=(RxBuff[7+4*i+3]<<24)|(RxBuff[7+4*i+2]<<16)|(RxBuff[7+4*i+1]<<8)|(RxBuff[7+4*i+0]);
						}		
						
						hs_uart_send(0x5a);
						hs_uart_send(CmdType);
						hs_uart_send(TempIndex/256);
						hs_uart_send(TempIndex%256);
						hs_uart_send(TempLength/256);
						hs_uart_send(TempLength%256);
						//hs_uart_send(TempPackNum);
						hs_uart_send(0x5a);
						hs_uart_send(0xF2);
						hs_uart_send(0x3D);
						hs_uart_send(0xa5);	
						break;
					
					case UPLOAD_TEMP:
						
						TempIndex = (RxBuff[3]<<8)|RxBuff[2];						
					
						TempLength = (RxBuff[5]<<8)|RxBuff[4];
											
						hs_uart_send(0x5a);
						hs_uart_send(CmdType);
						hs_uart_send(TempIndex/256);
						hs_uart_send(TempIndex%256);
						hs_uart_send(TempLength/256);
						hs_uart_send(TempLength%256);
					
						for(i=0;i<TempLength/4;i++)
						{
							TempData = *((volatile uint32_t*)(0x30090000+4*i));							
							hs_uart_send((uint8_t)TempData);
							hs_uart_send((uint8_t)(TempData>>8));
							hs_uart_send((uint8_t)(TempData>>16));
							hs_uart_send((uint8_t)(TempData>>24));
						}	

						hs_uart_send(0x5a);
						hs_uart_send(0xF2);
						hs_uart_send(0x3D);
						hs_uart_send(0xa5);						
						break;
						
					case UPLOAD_IMAG:
						
						ImagLength = (RxBuff[5]<<24)|(RxBuff[4]<<16)|(RxBuff[3]<<8)|RxBuff[2];
					
						hs_uart_send(0x5a);
						hs_uart_send(CmdType);
						hs_uart_send((uint8_t)(ImagLength>>24));
						hs_uart_send((uint8_t)(ImagLength>>16));
						hs_uart_send((uint8_t)(ImagLength>>8));
						hs_uart_send((uint8_t)ImagLength);	
						for(i=0;i<ImagLength/4;i++)
						{
							ImagData = *((volatile uint32_t*)(0x30000000+4*i));				
							hs_uart_send((uint8_t)ImagData);	
							hs_uart_send((uint8_t)(ImagData>>8));
							hs_uart_send((uint8_t)(ImagData>>16));
							hs_uart_send((uint8_t)(ImagData>>24));
						}
						hs_uart_send(0x5a);
						hs_uart_send(0xF2);
						hs_uart_send(0x3D);
						hs_uart_send(0xa5);	
						break;
					case DOWNLOAD_IMAG:
						ImagPackNum = (RxBuff[3]<<8)|RxBuff[2];
						ImagLength = (RxBuff[5]<<8)|RxBuff[4];
						for(i=0;i<ImagLength/4;i++)
						{
							*((volatile uint32_t*)(0x30000000+4*i+ImagPackNum*ImagLength))=(RxBuff[6+4*i+3]<<24)|(RxBuff[6+4*i+2]<<16)|(RxBuff[6+4*i+1]<<8)|(RxBuff[6+4*i+0]);
						}
						hs_uart_send(0x5a);
						hs_uart_send(CmdType);
						hs_uart_send(ImagPackNum/256);
						hs_uart_send(ImagPackNum%256);
						hs_uart_send(ImagLength/256);
						hs_uart_send(ImagLength%256);

						hs_uart_send(0x5a);
						hs_uart_send(0xF2);
						hs_uart_send(0x3D);
						hs_uart_send(0xa5);		
					default:
						
						break;	
				} 

			}else{
				gRxFlag = 0;
				RX_NUM = 0;
				memset(RxBuff,0,sizeof(RxBuff));				
			}
			gRxFlag = 0;	
			RX_NUM = 0;
			memset(RxBuff,0,sizeof(RxBuff));
		}
		
	}	
}
