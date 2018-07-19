#include <stdint.h>
#include "i2c.h"

void i2c1_init(void)
{
	rIC1_ENABLE &=~0x01;//½ûÄÜIIC
	rIC1_CON = 0x45;
	rIC1_TAR = 0x10;
	rIC1_SS_SCL_LCNT = 35;
	rIC1_SS_SCL_HCNT = 21;

    rIC1_INTR_MASK = 0x00; 

    rIC1_RX_TL = 4;

    rIC1_TX_TL = 4;	
	
	rIC1_ENABLE |= 0x01;//Ê¹ÄÜIIC
}


void i2c1_wr_data(uint16_t sub_addr,uint16_t wr_dat)
{
    int j;

    rIC1_DATA_CMD = 0x000 |(char)(sub_addr/256);   
	rIC1_DATA_CMD = 0x000 |(char)(sub_addr%256);
    rIC1_DATA_CMD = 0x000 |(char)(wr_dat/256);      
	rIC1_DATA_CMD = 0x200 |(char)(wr_dat%256);
    //wait 70us
    for(j=0;j<5000;j++); //wait

}
void i2c1_wr_8data(uint16_t sub_addr,uint8_t wr_dat)
{
    int j;

    rIC1_DATA_CMD = 0x000 |(char)(sub_addr/256);   
	rIC1_DATA_CMD = 0x000 |(char)(sub_addr%256);
	rIC1_DATA_CMD = 0x200 |wr_dat;
    //wait 70us
    for(j=0;j<5000;j++); //wait

}
uint8_t i2c1_rd_data(uint16_t sub_addr)
{
    char rd_dat=0;
    int j; 
    rIC1_DATA_CMD = 0x000 |(char)sub_addr; 
    rIC1_DATA_CMD = 0x7aa ; 

    //wait 70us
    for(j=0;j<500;j++);
    rd_dat = rIC1_DATA_CMD  ; 
    return   rd_dat;
}

