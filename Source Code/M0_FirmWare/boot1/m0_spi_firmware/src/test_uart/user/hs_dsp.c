#include <stdint.h>
#include "dsp_cfg.h"
#include "gpio.h"
//#include "uart_driver.h"
#include "spi0_driver.h"

uint8_t IrisEncoded(uint16_t index,EyeType eye,EncodeQuaulityLevel level,EncodeType type,RamType ram)
{
	if(DSP_CURRNET_STATUS == 0x81)//�ж�DSP�Ƿ�ready
	{
		if (eye==RightEye)
		{
			DSP_TMPL_ENCODE_CTRL |= (1<<1);
			DSP_TMPL_ENCODE_CTRL &=~ 0x01;
		}else{
			DSP_TMPL_ENCODE_CTRL &=~ (1<<1);
			DSP_TMPL_ENCODE_CTRL |= 0x01;
		}
		if(type==LocalAndReserveRawPic)
		{
			DSP_TMPL_ENCODE_CTRL &=~ (1<<2);
		}else{
			DSP_TMPL_ENCODE_CTRL |= (1<<2);
		}
		if(level == LowQuaulity)
		{
			DSP_TMPL_ENCODE_CTRL |= (1<<3);
			DSP_TMPL_ENCODE_CTRL &=~ (1<<4);
		}else if(type==MidQuaulity)
		{
			DSP_TMPL_ENCODE_CTRL &=~ (1<<3);
			DSP_TMPL_ENCODE_CTRL |= (1<<4);
		}else{
			DSP_TMPL_ENCODE_CTRL |= (1<<3);
			DSP_TMPL_ENCODE_CTRL |= (1<<4);
		}
		
		if(ram==BRAM_A)
		{
			DSP_RX_TMPL_INDEX &=~(1<<16);//select template BRAM A
		}else{
			DSP_RX_TMPL_INDEX |=(1<<16);//select template BRAM B
		}
		//DSP_TMPL_ENCODE_CTRL |= 0x19;//���ñ���ģʽΪLocation & Encode
		DSP_CMD |= 0x07;//��ʼ����		
		while(!(DSP_CMD_STATUS&(1<<3)))//�ȴ���Ĥ���������ģ����Ч
		{
			rGPIO0DATA |= 0x01;
			if(DSP_ERR_STATUS&(1<<3))
			{
				return ENCODE_TIMEOUT;
			}
		}
		while(DSP_CURRNET_STATUS != 0x81);//�ȴ�DSP ready
		DSP_RX_TMPL_INDEX = index;//���ñ�������

		DSP_CMD |= 0x08;//��ģ��д�뵽FLASH
		if(DSP_ERR_STATUS&(1<<2))//�ж������Ƿ����
		{
			return TEMPLATE_INDEX_OVER;	
		}
		while(!(DSP_CMD_STATUS&(1<<8)))//�ȴ�ģ��д�����
		{
			rGPIO0DATA |= 0x01;
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

uint8_t IrisMatch(uint16_t index,EyeType eye,EncodeQuaulityLevel level,EncodeType type,RamType ram,TempMatchMode mode)
{
	
	if(DSP_CURRNET_STATUS == 0x81)//�ж�DSP�Ƿ�ready
	{
		IrisEncoded(index,eye,level,type,ram);
		while(DSP_CURRNET_STATUS != 0x81);//�ȴ�DSP ready
		if(mode==NormalMode)
		{
			DSP_TMPL_MATCH_CTRL |= 0x01;
			DSP_TMPL_MATCH_CTRL &=~ (1<<1);
		}else{
			DSP_TMPL_MATCH_CTRL &=~ 0x01;
			DSP_TMPL_MATCH_CTRL |= (1<<1);
		}
		
		DSP_CMD |= 0x0D;//��ʼʶ��
		while(!(DSP_CMD_STATUS&(1<<5)))//�ȴ�ʶ��ɹ�
		{
			rGPIO0DATA |= 0x01;
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
    if(DSP_CURRNET_STATUS == 0x81)//�ж�DSP�Ƿ�ready
	{
		DSP_RX_CTRL |= 0x01;//ɾ��/����ģ��ʱ��ͬʱ������־������
		DSP_RX_TMPL_INDEX = index;//����ɾ������

		DSP_CMD |= 0x0E;//ɾ��ָ��ģ��
		if(DSP_ERR_STATUS&(1<<2))//�ж������Ƿ����
		{
			return TEMPLATE_INDEX_OVER;	
		}
		DSP_CMD |= 0x08;//��ģ��д�뵽FLASH
		while(!(DSP_CMD_STATUS&(1<<7)))//�ȴ�ģ��ɾ�����
		{
			rGPIO0DATA |= 0x01;
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
	uint8_t Ack[20]={0};
    if(DSP_CURRNET_STATUS == 0x81)//�ж�DSP�Ƿ�ready
	{
		DSP_RX_CTRL |= 0x01;//ɾ��/����ģ��ʱ��ͬʱ������־������

		DSP_CMD |= 0x0B;//ɾ��ȫ��ģ��

		DSP_CMD |= 0x08;//��ģ��д�뵽FLASH
		while(!(DSP_CMD_STATUS&(1<<7)))//�ȴ�ģ��ɾ�����
		{
			rGPIO0DATA |= 0x01;
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
	if(DSP_ERR_STATUS&(1<<3))//�жϱ����Ƿ�ʱ
	{
		gEncodeTimeOut = 1;
	}
}

