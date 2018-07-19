#include <stdint.h>

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


void delay(volatile uint32_t nCount)
{
	for(;nCount!=0;nCount--);
}

