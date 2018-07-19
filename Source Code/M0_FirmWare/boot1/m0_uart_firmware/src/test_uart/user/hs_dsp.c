#include <stdint.h>
#include "dsp_cfg.h"
#include "gpio.h"
#include "uart_driver.h"
#include "sys.h"

extern uint8_t SensorReady;

uint8_t IrisEncoded(uint32_t index)
{
	while(!SensorReady);
	if(DSP_CURRNET_STATUS == 0x81)//判断DSP是否ready
	{
		#if 0
		if (encodeInfo.eye==RightEye)
		{
			DSP_TMPL_ENCODE_CTRL |= (1<<1);
			DSP_TMPL_ENCODE_CTRL &=~ 0x01;
		}else{
			DSP_TMPL_ENCODE_CTRL &=~ (1<<1);
			DSP_TMPL_ENCODE_CTRL |= 0x01;
		}
		if(encodeInfo.encode_type==LocalAndReserveRawPic)
		{
			DSP_TMPL_ENCODE_CTRL &=~ (1<<2);
		}else{
			DSP_TMPL_ENCODE_CTRL |= (1<<2);
		}
		if(encodeInfo.level == LowQuaulity)
		{
			DSP_TMPL_ENCODE_CTRL |= (1<<3);
			DSP_TMPL_ENCODE_CTRL &=~ (1<<4);
		}else if(encodeInfo.level==MidQuaulity)
		{
			DSP_TMPL_ENCODE_CTRL &=~ (1<<3);
			DSP_TMPL_ENCODE_CTRL |= (1<<4);
		}else{
			DSP_TMPL_ENCODE_CTRL |= (1<<3);
			DSP_TMPL_ENCODE_CTRL |= (1<<4);
		}
		
		if(encodeInfo.ram_type==BRAM_A)
		{
			DSP_RX_TMPL_INDEX &=~(1<<16);//select template BRAM A
		}else{
			DSP_RX_TMPL_INDEX |=(1<<16);//select template BRAM B
		}
		#endif
		DSP_TMPL_ENCODE_CTRL |= 0x19;//设置编码模式为Location & Encode
		DSP_CMD |= 0x07;//开始编码		
		while(!(DSP_CMD_STATUS&(1<<3)))//等待虹膜编码结束且模板有效
		{
			#if 0
			if(encodeInfo.level == LowQuaulity)
			{
				if(((uint16_t)DSP_ENCODE_RESULT_20)>((uint16_t)(TMPL_ENCODE_RX_PARA_20)))
				{
					Ack[0]=0x5a;
					Ack[1]=0x01;
					Ack[2]=0x21;
					Ack[3]=CalCRC8(Ack,3);
					Ack[4]=0xa5;
					hs_uart_send_str(Ack,5);
				}else{
					Ack[0]=0x5a;
					Ack[1]=0x02;
					Ack[2]=0x21;
					Ack[3]=CalCRC8(Ack,3);
					Ack[4]=0xa5;
					hs_uart_send_str(Ack,5);
				}	
			}else if(encodeInfo.level==MidQuaulity){
				if(((uint16_t)DSP_ENCODE_RESULT_20)>((uint16_t)(TMPL_ENCODE_RX_PARA_20>>16)))
				{
					Ack[0]=0x5a;
					Ack[1]=0x01;
					Ack[2]=0x21;
					Ack[3]=CalCRC8(Ack,3);
					Ack[4]=0xa5;
					hs_uart_send_str(Ack,5);
				}else{
					Ack[0]=0x5a;
					Ack[1]=0x02;
					Ack[2]=0x21;
					Ack[3]=CalCRC8(Ack,3);
					Ack[4]=0xa5;
					hs_uart_send_str(Ack,5);
				}	
			}else{
				if(((uint16_t)DSP_ENCODE_RESULT_20)>((uint16_t)(TMPL_ENCODE_RX_PARA_21)))
				{
					Ack[0]=0x5a;
					Ack[1]=0x01;
					Ack[2]=0x21;
					Ack[3]=CalCRC8(Ack,3);
					Ack[4]=0xa5;
					hs_uart_send_str(Ack,5);
				}else{
					Ack[0]=0x5a;
					Ack[1]=0x02;
					Ack[2]=0x21;
					Ack[3]=CalCRC8(Ack,3);
					Ack[4]=0xa5;
					hs_uart_send_str(Ack,5);
				}	
			}	
			#endif
			if(DSP_ERR_STATUS&(1<<3))
			{

				return ENCODE_TIMEOUT;
			}
		}

		while(DSP_CURRNET_STATUS != 0x81);//等待DSP ready
		DSP_RX_TMPL_INDEX = index;//设置编码索引
		DSP_RX_TMPL_INDEX &=~(1<<16);//select template BRAM A
		DSP_CMD |= 0x08;//将模板写入到FLASH
		if(DSP_ERR_STATUS&(1<<2))//判断索引是否溢出
		{
			return TEMPLATE_INDEX_OVER;	
		}
		while(!(DSP_CMD_STATUS&(1<<8)))//等待模板写入完成
		{
			if(DSP_ERR_STATUS&0x01)
			{
				return WRITE_READ_FLASH_TIMEOUT;
			}
		}
		if(DSP_ERR_STATUS&(1<<1))
		{
			return WRITE_READ_FLASH_MATCH_ERROR;
		}
		
		return ENCODE_OK;
		
	}else{	
		
		return HS_HAL_BUSY;
	}
}

uint8_t IrisMatch(void)
{
	while(!SensorReady);
	if(DSP_CURRNET_STATUS == 0x81)//判断DSP是否ready
	{
		#if 0
		if (machInfo.eye==RightEye)
		{
			DSP_TMPL_ENCODE_CTRL |= (1<<1);
			DSP_TMPL_ENCODE_CTRL &=~ 0x01;
		}else{
			DSP_TMPL_ENCODE_CTRL &=~ (1<<1);
			DSP_TMPL_ENCODE_CTRL |= 0x01;
		}
		if(machInfo.encode_type==LocalAndReserveRawPic)
		{
			DSP_TMPL_ENCODE_CTRL &=~ (1<<2);
		}else{
			DSP_TMPL_ENCODE_CTRL |= (1<<2);
		}
		if(machInfo.level == LowQuaulity)
		{
			DSP_TMPL_ENCODE_CTRL |= (1<<3);
			DSP_TMPL_ENCODE_CTRL &=~ (1<<4);
		}else if(machInfo.level==MidQuaulity)
		{
			DSP_TMPL_ENCODE_CTRL &=~ (1<<3);
			DSP_TMPL_ENCODE_CTRL |= (1<<4);
		}else{
			DSP_TMPL_ENCODE_CTRL |= (1<<3);
			DSP_TMPL_ENCODE_CTRL |= (1<<4);
		}
		
		if(machInfo.ram_type==BRAM_A)
		{
			DSP_RX_TMPL_INDEX &=~(1<<16);//select template BRAM A
		}else{
			DSP_RX_TMPL_INDEX |=(1<<16);//select template BRAM B
		}
		#endif
		DSP_TMPL_ENCODE_CTRL |= 0x19;//设置编码模式为Location & Encode
		DSP_CMD |= 0x07;//开始编码		
		while(!(DSP_CMD_STATUS&(1<<3)))//等待虹膜编码结束且模板有效
		{
			#if 0
			if(machInfo.level == LowQuaulity)
			{
				if(((uint16_t)DSP_ENCODE_RESULT_20)>((uint16_t)(TMPL_ENCODE_RX_PARA_20)))
				{
					Ack[0]=0x5a;
					Ack[1]=0x01;
					Ack[2]=0x21;
					Ack[3]=CalCRC8(Ack,3);
					Ack[4]=0xa5;
					hs_uart_send_str(Ack,5);
				}else{
					Ack[0]=0x5a;
					Ack[1]=0x02;
					Ack[2]=0x21;
					Ack[3]=CalCRC8(Ack,3);
					Ack[4]=0xa5;
					hs_uart_send_str(Ack,5);
				}	
			}else if(machInfo.level==MidQuaulity){
				if(((uint16_t)DSP_ENCODE_RESULT_20)>((uint16_t)(TMPL_ENCODE_RX_PARA_20>>16)))
				{
					Ack[0]=0x5a;
					Ack[1]=0x01;
					Ack[2]=0x21;
					Ack[3]=CalCRC8(Ack,3);
					Ack[4]=0xa5;
					hs_uart_send_str(Ack,5);
				}else{
					Ack[0]=0x5a;
					Ack[1]=0x02;
					Ack[2]=0x21;
					Ack[3]=CalCRC8(Ack,3);
					Ack[4]=0xa5;
					hs_uart_send_str(Ack,5);
				}	
			}else{
				if(((uint16_t)DSP_ENCODE_RESULT_20)>((uint16_t)(TMPL_ENCODE_RX_PARA_21)))
				{
					Ack[0]=0x5a;
					Ack[1]=0x01;
					Ack[2]=0x21;
					Ack[3]=CalCRC8(Ack,3);
					Ack[4]=0xa5;
					hs_uart_send_str(Ack,5);
				}else{
					Ack[0]=0x5a;
					Ack[1]=0x02;
					Ack[2]=0x21;
					Ack[3]=CalCRC8(Ack,3);
					Ack[4]=0xa5;
					hs_uart_send_str(Ack,5);
				}	
			}	
			#endif
			if(DSP_ERR_STATUS&(1<<3))
			{
				return ENCODE_TIMEOUT;
			}
		}
		while(DSP_CURRNET_STATUS != 0x81);//等待DSP ready
		//if(machInfo.mode==NormalMode)
		//{
			DSP_TMPL_MATCH_CTRL |= 0x01;
			DSP_TMPL_MATCH_CTRL &=~ (1<<1);
		//}else{
			//DSP_TMPL_MATCH_CTRL &=~ 0x01;
			//DSP_TMPL_MATCH_CTRL |= (1<<1);
		//}	
		DSP_CMD |= 0x0D;//开始识别
		while(!(DSP_CMD_STATUS&(1<<5)))//等待识别成功
		{
			if(DSP_ERR_STATUS&(1<<4))
			{

				return MATCH_TIMEOUT;
			}
			else if(DSP_CMD_STATUS&(1<<6))
			{
				return MATCH_ERROR;
			}
		}

		return MATCH_OK;
		
	}else{
		
		return HS_HAL_BUSY;		
	}	
}

uint8_t IrisEraseOneTemp(uint16_t index)
{
    if(DSP_CURRNET_STATUS == 0x81)//判断DSP是否ready
	{
		DSP_RX_CTRL |= 0x01;//删除/擦除模板时，同时擦除标志和数据
		DSP_RX_TMPL_INDEX = index;//设置删除索引
		DSP_CMD |= 0x0E;//删除指定模板
		if(DSP_ERR_STATUS&(1<<2))//判断索引是否溢出
		{
			return TEMPLATE_INDEX_OVER;	
		}
		DSP_CMD |= 0x08;//将模板写入到FLASH
		while(!(DSP_CMD_STATUS&(1<<7)))//等待模板删除完成
		{

			if(DSP_ERR_STATUS&0x01)
			{
				return WRITE_READ_FLASH_TIMEOUT;
			}
		}
		if(DSP_ERR_STATUS&(1<<1))
		{
			return WRITE_READ_FLASH_MATCH_ERROR;
		}
		return ERASER_ONE_TEMP_OK;
		
	}else{	
		
		return HS_HAL_BUSY;
	}
}

uint8_t IrisEraseAllTemp(void)
{
    if(DSP_CURRNET_STATUS == 0x81)//判断DSP是否ready
	{
		DSP_RX_CTRL |= 0x01;//删除/擦除模板时，同时擦除标志和数据

		DSP_CMD |= 0x0B;//删除全部模板

		DSP_CMD |= 0x08;//将模板写入到FLASH
		while(!(DSP_CMD_STATUS&(1<<7)))//等待模板删除完成
		{
			if(DSP_ERR_STATUS&0x01)
			{
				return WRITE_READ_FLASH_TIMEOUT;
			}
		}
		if(DSP_ERR_STATUS&(1<<1))
		{
			return WRITE_READ_FLASH_MATCH_ERROR;
		}
		return ERASER_ALL_TEMP_OK;
		
	}else{	
		
		return HS_HAL_BUSY;
	}
}


uint8_t gEncodeTimeOut = 0;

void DSP1_IRQHandler(void)
{
	if(DSP_ERR_STATUS&(1<<3))//判断编码是否超时
	{
		
	}
	DSP_CMD |= 0x10000;
}
