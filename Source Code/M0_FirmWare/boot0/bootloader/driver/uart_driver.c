#include <stdint.h>
#include "uart.h"

uint8_t gRxFlag = 0;
uint32_t RX_NUM = 0;
uint8_t RxBuff[1200]={0};

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





