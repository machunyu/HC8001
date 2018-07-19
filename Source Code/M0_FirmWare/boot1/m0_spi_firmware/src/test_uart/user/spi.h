#ifndef _SPI_H_
#define _SPI_H_

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include <stdint.h> 
	 
typedef struct
{

  uint16_t SPI_Mode;                /*!< Specifies the SPI operating mode.
                                         This parameter can be a value of @ref SPI_mode */

  uint16_t SPI_DataSize;            /*!< Specifies the SPI data size.
                                         This parameter can be a value of @ref SPI_data_size */

  uint16_t SPI_CPOL;                /*!< Specifies the serial clock steady state.
                                         This parameter can be a value of @ref SPI_Clock_Polarity */

  uint16_t SPI_CPHA;                /*!< Specifies the clock active edge for the bit capture.
                                         This parameter can be a value of @ref SPI_Clock_Phase */

  uint16_t SPI_NSS;                 /*!< Specifies whether the NSS signal is managed by
                                         hardware (NSS pin) or by software using the SSI bit.
                                         This parameter can be a value of @ref SPI_Slave_Select_management */
 
  uint16_t SPI_BaudRatePrescaler;   /*!< Specifies the Baud Rate prescaler value which will be
                                         used to configure the transmit and receive SCK clock.
                                         This parameter can be a value of @ref SPI_BaudRate_Prescaler
                                         @note The communication clock is derived from the master
                                               clock. The slave clock does not need to be set. */

  uint16_t SPI_FirstBit;            /*!< Specifies whether data transfers start from MSB or LSB bit.
                                         This parameter can be a value of @ref SPI_MSB_LSB_transmission */

}SPI_InitTypeDef;

#define rCTRLR0           			 *((volatile uint32_t*)0x40003000)
#define rCTRLR1           			 *((volatile uint32_t*)0x40003004)
#define rSSIENR           			 *((volatile uint32_t*)0x40003008)
#define rMWCR             			 *((volatile uint32_t*)0x4000300C)
#define rSER              			 *((volatile uint32_t*)0x40003010)
#define rBAUDR            			 *((volatile uint32_t*)0x40003014)
#define rTXFTLR           			 *((volatile uint32_t*)0x40003018)
#define rRXFTLR           			 *((volatile uint32_t*)0x4000301C)
#define rTXFLR            			 *((volatile uint32_t*)0x40003020)
#define rRXFLR            			 *((volatile uint32_t*)0x40003024)
#define rSR               			 *((volatile uint32_t*)0x40003028)
#define rIMR              			 *((volatile uint32_t*)0x4000302C)
#define rISR              			 *((volatile uint32_t*)0x40003030)
#define rRISR             			 *((volatile uint32_t*)0x40003034)
#define rTXOICR           			 *((volatile uint32_t*)0x40003038)
#define rRXOICR           			 *((volatile uint32_t*)0x4000303C)
#define rRXUICR           			 *((volatile uint32_t*)0x40003040)
#define rMSTICR           			 *((volatile uint32_t*)0x40003044)
#define rICR              			 *((volatile uint32_t*)0x40003048)
#define rDMACR            			 *((volatile uint32_t*)0x4000304C)
#define rDMATDLR          			 *((volatile uint32_t*)0x40003050)
#define rDMARDLR          			 *((volatile uint32_t*)0x40003054)
#define rIDR              			 *((volatile uint32_t*)0x40003058)
#define rSSI_COMP_VERSION            *((volatile uint32_t*)0x4000305C)
#define rDR                          *((volatile uint32_t*)0x40003060)
#define rRX_SAMPLE_DLY               *((volatile uint32_t*)0x400030f0)
	
	
#ifdef __cplusplus
}
#endif
	

#endif
