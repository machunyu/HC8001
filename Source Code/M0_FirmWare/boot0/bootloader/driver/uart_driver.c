#include <stdint.h>
#include "uart.h"

uint8_t gRxFlag = 0;
uint32_t RX_NUM = 0;
uint8_t RxBuff[1200]={0};

void hs_uart_init(void)
{
	//rUARTCR &=~0x01;//禁能UART
	//rUARTLCR_H &=~(1<<4);//清空FIFO
	//初始化串口配置
	//设置波特率为115200（主频26M）
	//Baud rate divisor BAUDDIV = (FUARTCLK/(16×Baud rate))
	rUARTIBRD = 0x0e;//波特率分频整数部分
	rUARTFBRD = 0x06;//波特率分频小数部分
	//rUARTLCR_H |= (1<<5);
	//rUARTLCR_H |= (1<<6);//8位数据位
	//rUARTLCR_H &=~(1<<3);//1位停止位
	//rUARTLCR_H &=~(1<<1);//无校验位
	//rUARTLCR_H &=~0x01;
	//rUARTCR &=~(1<<14);
	//rUARTCR &=~(1<<15);//无硬件流控
	//rUARTCR |= (1<<8);//使能TX
	//rUARTCR |= (1<<9);//使能RX
	
	rUARTCR = 0x300;
	rUARTIFLS = 0x24;
	rUARTLCR_H = 0x60;
	
	rUARTIMSC = (1<<4);//使能接收中断
	
	rUARTCR |= 0x01; //使能UART
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





