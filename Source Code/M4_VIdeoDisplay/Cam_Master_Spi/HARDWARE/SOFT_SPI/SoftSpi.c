#include "SoftSpi.h"
#include "delay.h"

void Soft_SPI_Init(void)
{  
	/*##-1- Enable peripherals and GPIO Clocks #################################*/
	/* Enable GPIO TX/RX clock */
	GPIO_InitTypeDef GPIO_InitStruct;

	SPI_SCK_GPIO_CLK_ENABLE();
	SPI_MISO_GPIO_CLK_ENABLE();
	SPI_MOSI_GPIO_CLK_ENABLE();
	SPI_NSS_GPIO_CLK_ENABLE();
	SPI_RESET_GPIO_CLK_ENABLE();

	/*##-2- Configure peripheral GPIO ##########################################*/
	/* SPI SCK GPIO pin configuration  */
	
	GPIO_InitStruct.GPIO_Pin = SPI_SCK_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//复用功能
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_100MHz;
	GPIO_Init(SPI_SCK_GPIO_PORT, &GPIO_InitStruct);
	GPIO_SetBits(SPI_SCK_GPIO_PORT, SPI_SCK_PIN);

	/* SPI MISO GPIO pin configuration  */
	GPIO_InitStruct.GPIO_Pin = SPI_MISO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(SPI_MISO_GPIO_PORT, &GPIO_InitStruct);

	/* SPI MOSI GPIO pin configuration  */
	GPIO_InitStruct.GPIO_Pin = SPI_MOSI_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//复用功能
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_100MHz;
	GPIO_Init(SPI_MOSI_GPIO_PORT, &GPIO_InitStruct);
	GPIO_SetBits(SPI_MOSI_GPIO_PORT, SPI_MOSI_PIN);

	GPIO_InitStruct.GPIO_Pin = SPI_NSS_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//复用功能
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_100MHz;
	GPIO_Init(SPI_NSS_GPIO_PORT, &GPIO_InitStruct);
	GPIO_SetBits(SPI_NSS_GPIO_PORT, SPI_NSS_PIN);

	GPIO_InitStruct.GPIO_Pin = SPI_RESET_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//复用功能
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_100MHz;
	GPIO_Init(SPI_RESET_GPIO_PORT, &GPIO_InitStruct);
	GPIO_SetBits(SPI_RESET_GPIO_PORT, SPI_RESET_PIN);
}



void SPI_WriteByte(uint8_t ch)
{
	uint8_t i;
	NSS_L;  
	delay_us(2);
	SCK_L;
	delay_us(1);
	//__NOP();             /*读取第一bit数据 等待数据稳定 根据实际时钟调整*/
	//delay_us(1);
	
	for(i=0;i<8;i++)
	{   
		if(ch&0x80)
		{
		  MOSI_H;          /*若最高位为高，则输出高*/
		}
		else
		{
		  MOSI_L;          /*若最高位为低，则输出低*/   
		}   
		//__NOP();
		SCK_L;
		delay_us(1);
		ch <<= 1;        /*数据左移*/
		SCK_H;
		delay_us(1);
	}
	SCK_L;
	delay_us(1);
	NSS_H;
	delay_us(2);
}

uint8_t SPI_ReadByte(void)
{
	u8 i,dat,temp;
	NSS_L;  
	delay_us(2);
	SCK_L;
	delay_us(1);
	
    dat =0; 
    temp =0x80;
  
    for (i=0;i<8;i++)
    {
        SCK_H;
        delay_us(1);
        if (MISO)
		dat|= temp;					    
        SCK_L;
		delay_us(1);
        temp >>= 1;		
    }
	
	SCK_L;
	delay_us(1);
	NSS_H;
	delay_us(2);
   return dat;

}

void SPI_SendStr(uint8_t *pStr, uint32_t ulStrLength)
{
	while(ulStrLength--)
	{
		SPI_WriteByte(*pStr);
		pStr++;
	}
}

void SPI_RecvStr(uint8_t *buf,uint32_t num)
{
	if (num == 0) 		
    num= 0x100;
    while(num--)
    {
		*buf++ = SPI_ReadByte();
    }
}
