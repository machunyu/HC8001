#include <stdint.h>
#include <string.h>
#include "uart.h"
#include "cfg.h"
#include "hs_dsp.h"

uint8_t gRxFlag = 0;
uint32_t RX_NUM = 0;
uint8_t RxBuff[1200]={0};

#define ICER                           *((volatile uint32_t*)0xE000E180)
	
	





void hs_uart_init(void)
{
	//rUARTCR &=~0x01;//����UART
	//rUARTLCR_H &=~(1<<4);//���FIFO
	//��ʼ����������
	//���ò�����Ϊ115200����Ƶ26M��
	//Baud rate divisor BAUDDIV = (FUARTCLK/(16��Baud rate))
	rUARTIBRD = 0x0e;//�����ʷ�Ƶ��������
	rUARTFBRD = 0x06;//�����ʷ�ƵС������
	//rUARTLCR_H |= (1<<5);
	//rUARTLCR_H |= (1<<6);//8λ����λ
	//rUARTLCR_H &=~(1<<3);//1λֹͣλ
	//rUARTLCR_H &=~(1<<1);//��У��λ
	//rUARTLCR_H &=~0x01;
	//rUARTCR &=~(1<<14);
	//rUARTCR &=~(1<<15);//��Ӳ������
	//rUARTCR |= (1<<8);//ʹ��TX
	//rUARTCR |= (1<<9);//ʹ��RX
	
	rUARTCR = 0x300;
	rUARTIFLS = 0x24;
	rUARTLCR_H = 0x60;
	
	rUARTIMSC = (1<<4);//ʹ�ܽ����ж�
	
	rUARTCR |= 0x01; //ʹ��UART
}

void hs_uart_send(uint8_t ch)
{	
	rUARTDR = ch;
	while((rUARTFR&(1<<7))==0);
}

void hs_uart_send_str(uint8_t *pStr, uint32_t ulStrLength)
{
	while(ulStrLength--)
	{
		hs_uart_send(*pStr);
		pStr++;
	}
}

void UART0_IRQHandler(void)
{
	uint8_t res;
	uint8_t ret;
	uint8_t Ack[20]={0};
	uint8_t CmdType;
	res=(uint8_t)rUARTDR;
    RxBuff[RX_NUM] = res;
	RX_NUM++;
	if((RxBuff[0]==0x5a)&&(res==0xa5))
	{
		CmdType = RxBuff[1];

		switch(CmdType)
		{
			case ENCODE:
				
				if(RxBuff[2]==CalCRC8(RxBuff,2))
				{
					ret=IrisEncoded(56,LeftEye,LowQuaulity,LocalAndReserveRawPic,BRAM_A);//���۵�һ��
					Ack[0]=0x5a;
					Ack[1]=CmdType;
					Ack[2]=ret;
					Ack[3]=CalCRC8(Ack,3);
					Ack[4]=0xa5;
					hs_uart_send_str(Ack,5);
					//delay(4000*1000);
					
					ret=IrisEncoded(57,LeftEye,LowQuaulity,LocalAndReserveRawPic,BRAM_A);//���۵ڶ���
					Ack[0]=0x5a;
					Ack[1]=CmdType;
					Ack[2]=ret;
					Ack[3]=CalCRC8(Ack,3);
					Ack[4]=0xa5;
					hs_uart_send_str(Ack,5);
					//delay(4000*1000);
					
					ret=IrisEncoded(58,LeftEye,LowQuaulity,LocalAndReserveRawPic,BRAM_A);//���۵�һ��
					Ack[0]=0x5a;
					Ack[1]=CmdType;
					Ack[2]=ret;
					Ack[3]=CalCRC8(Ack,3);
					Ack[4]=0xa5;
					hs_uart_send_str(Ack,5);
					//delay(4000*1000);
					
					ret=IrisEncoded(59,LeftEye,LowQuaulity,LocalAndReserveRawPic,BRAM_A);//���۵ڶ���
					Ack[0]=0x5a;
					Ack[1]=CmdType;
					Ack[2]=ret;
					Ack[3]=CalCRC8(Ack,3);
					Ack[4]=0xa5;
					hs_uart_send_str(Ack,5);
					//delay(4000*1000);
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
					ret=IrisMatch(59,LeftEye,LowQuaulity,LocalAndReserveRawPic,BRAM_A,NormalMode);//ʶ��
					Ack[0]=0x5a;
					Ack[1]=CmdType;
					Ack[2]=ret;
					Ack[3]=CalCRC8(Ack,3);
					Ack[4]=0xa5;
					hs_uart_send_str(Ack,5);
					//delay(4000*1000);

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
					ret=IrisEraseOneTemp(56);//ɾ����һģ��
					Ack[0]=0x5a;
					Ack[1]=CmdType;
					Ack[2]=ret;
					Ack[3]=CalCRC8(Ack,3);
					Ack[4]=0xa5;
					hs_uart_send_str(Ack,5);
					//delay(4000*1000);

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
					ret=IrisEraseAllTemp();//ɾ��ȫ��ģ��
					Ack[0]=0x5a;
					Ack[1]=CmdType;
					Ack[2]=ret;
					Ack[3]=CalCRC8(Ack,3);
					Ack[4]=0xa5;
					hs_uart_send_str(Ack,5);
					//delay(4000*1000);

				}else{
					Ack[0]=0x5a;
					Ack[1]=0xff;
					Ack[2]=0xff;
					Ack[3]=CalCRC8(Ack,3);
					Ack[4]=0xa5;
					hs_uart_send_str(Ack,5);
				}							
				break;
				
			default:
				
				break;	
		}
		RX_NUM = 0;
		memset(RxBuff,0,1200);
	}
	rUARTICR|=(1<<4);
}



