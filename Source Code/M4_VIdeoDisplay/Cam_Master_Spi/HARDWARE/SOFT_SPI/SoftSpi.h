#ifndef __SOFT_SPI_H
#define __SOFT_SPI_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h" 
#include "stm32f4xx_gpio.h"

#define SPI_SCK_PIN                     GPIO_Pin_13
#define SPI_SCK_GPIO_PORT               GPIOB
#define SPI_MOSI_PIN                    GPIO_Pin_14
#define SPI_MOSI_GPIO_PORT              GPIOB
#define SPI_MISO_PIN                    GPIO_Pin_4
#define SPI_MISO_GPIO_PORT              GPIOB
#define SPI_NSS_PIN                     GPIO_Pin_12
#define SPI_NSS_GPIO_PORT               GPIOB
#define SPI_RESET_PIN                   GPIO_Pin_5
#define SPI_RESET_GPIO_PORT             GPIOB

#define SPI_SCK_GPIO_CLK_ENABLE()       RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE)//使能GPIOB时钟
#define SPI_MISO_GPIO_CLK_ENABLE()      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE)//使能GPIOB时钟
#define SPI_MOSI_GPIO_CLK_ENABLE()      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE)//使能GPIOB时钟
#define SPI_NSS_GPIO_CLK_ENABLE()       RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE)//使能GPIOB时钟
#define SPI_RESET_GPIO_CLK_ENABLE()     RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE)//使能GPIOB时钟

#define MOSI_H  GPIO_SetBits(SPI_MOSI_GPIO_PORT, SPI_MOSI_PIN)  
#define MOSI_L  GPIO_ResetBits(SPI_MOSI_GPIO_PORT, SPI_MOSI_PIN)  
#define SCK_H   GPIO_SetBits(SPI_SCK_GPIO_PORT, SPI_SCK_PIN)  
#define SCK_L   GPIO_ResetBits(SPI_SCK_GPIO_PORT, SPI_SCK_PIN)  
#define MISO    GPIO_ReadInputDataBit(SPI_MISO_GPIO_PORT, SPI_MISO_PIN)
#define NSS_H   GPIO_SetBits(SPI_NSS_GPIO_PORT, SPI_NSS_PIN)  
#define NSS_L   GPIO_ResetBits(SPI_NSS_GPIO_PORT, SPI_NSS_PIN)



void Soft_SPI_Init(void);
uint16_t SPI_ReadWrite_Byte(uint8_t cmd_addr, uint16_t data);
void SPI_WriteByte(uint8_t ch);
uint8_t SPI_ReadByte();
void SPI_SendStr(uint8_t *pStr, uint32_t ulStrLength);
void SPI_RecvStr(uint8_t *buf,uint32_t num);

#endif
