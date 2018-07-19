#ifndef _DSP_CFG_H_
#define _DSP_CFG_H_
#include <stdint.h>

typedef enum 
{
	LeftEye=0,
	RightEye
}EyeType;

typedef enum
{
	LowQuaulity=0,	
	MidQuaulity,
	HighQuaulity
}EncodeQuaulityLevel;

typedef enum
{
	LocalAndReserveRawPic=0,
	ReserveEncodePic
}EncodeType;

typedef enum
{
	BRAM_A=0,
	BRAM_B	
}RamType;

typedef enum
{
	NormalMode=0,
	DownloadMode
}TempMatchMode;


#define ENCODE             0x01
#define MATCH              0x02
#define ERASER_ONE_TEMP    0x03
#define ERASER_ALL_TEMP    0x04
//#define CRC8_FAIL          0x05	

#define HS_HAL_OK                            0x00
#define HS_HAL_ERROR                         0x01
#define HS_HAL_BUSY                          0x02
#define HS_HAL_TIMEOUT                       0x04


#define WRITE_READ_FLASH_TIMEOUT             0x05
#define WRITE_READ_FLASH_MATCH_ERROR         0x06
#define TEMPLATE_INDEX_OVER                  0x07
#define ENCODE_TIMEOUT                       0x08
#define MATCH_TIMEOUT                        0x09
#define MATCH_ERROR                          0x0A

#define ENCODE_OK                            0x11
#define MATCH_OK                             0x12
#define ERASER_ONE_TEMP_OK                   0x13
#define ERASER_ALL_TEMP_OK                   0x14

#define STATUS_IDLE                          0x10
#define STATUS_WRITE_FLASH_INFO_AREA         0x11
#define STATUS_WRITE_FLASH_USER_CODE         0x12
#define STATUS_ENCODE                        0x13
#define STATUS_ENCODE_FINISHED               0x14
#define STATUS_MATCH                         0x15
#define STATUS_DELETE_ONE_TEMPLATE           0x16
#define STATUS_DELETE_ALL_TEMPLATE           0x17
#define WRITE_SPECIFIED_TEMPLATE             0x18
#define READ_SPECIFIED_TEMPLATE              0x19

  
#define ISP_GAIN_CTRL                           *((volatile uint32_t*)0x400093E8)
#define ISP_SHUTTLE_CTRL                        *((volatile uint32_t*)0x400093EC)
	                                            
#define TMPL_FLAG0                              *((volatile uint32_t*)0x40009000)
#define TMPL_FLAG1                              *((volatile uint32_t*)0x40009004)
#define TMPL_FLAG2                              *((volatile uint32_t*)0x40009008)
#define TMPL_FLAG3                              *((volatile uint32_t*)0x4000900c)
#define TMPL_FLAG4                              *((volatile uint32_t*)0x40009010)
#define TMPL_FLAG5                              *((volatile uint32_t*)0x40009014)
#define TMPL_FLAG6                              *((volatile uint32_t*)0x40009018)	
#define TMPL_FLAG7                              *((volatile uint32_t*)0x4000901c)
#define TMPL_EncryptKey_31_0	                *((volatile uint32_t*)0x40009100)
#define TMPL_EncryptKey_63_32	                *((volatile uint32_t*)0x40009104)	
#define TMPL_EncryptKey_95_64	                *((volatile uint32_t*)0x40009108)	
#define TMPL_EncryptKey_127_96	                *((volatile uint32_t*)0x4000910c)	
#define TMPL_EncryptKey_159_128	                *((volatile uint32_t*)0x40009110)
#define TMPL_EncryptKey_191_160	                *((volatile uint32_t*)0x40009114)	
#define TMPL_EncryptKey_223_192	                *((volatile uint32_t*)0x40009118)	
#define TMPL_EncryptKey_255_224	                *((volatile uint32_t*)0x4000911c)	
#define TMPL_Encrypt_en                         *((volatile uint32_t*)0x40009120)
#define USR_CODE_SIZE                           *((volatile uint32_t*)0x40009124)
#define TMPL_INDEX_MAX_TH                       *((volatile uint32_t*)0x40009128)	
#define ISP_IMG_IN_SIZE                         *((volatile uint32_t*)0x4000912c)	
#define ISP_IMG_OUT_SIZE                        *((volatile uint32_t*)0x40009130)
#define ISP_IMG_LEFT_EYE_WIN0                   *((volatile uint32_t*)0x40009134)	
#define ISP_IMG_LEFT_EYE_WIN1                   *((volatile uint32_t*)0x40009138)
#define ISP_IMG_RIGHT_EYE_WIN0                  *((volatile uint32_t*)0x4000913c)	
#define ISP_IMG_RIGHT_EYE_WIN1                  *((volatile uint32_t*)0x40009140)		
#define ISP_RX_TOTAL_NUM                        *((volatile uint32_t*)0x40009144)  
#define ISP_RX_TH_MIN                           *((volatile uint32_t*)0x40009148)	
#define ISP_RX_TH_MID                           *((volatile uint32_t*)0x4000914C)  
#define ISP_RX_TH_MAX                           *((volatile uint32_t*)0x40009150)
#define ISP_RX_SET_MID                          *((volatile uint32_t*)0x40009154)
#define ISP_RX_CAL_MIX                          *((volatile uint32_t*)0x40009158)	
#define ISP_RX_GAIN                             *((volatile uint32_t*)0x4000915c)
#define ISP_RX_GAIN_ID                          *((volatile uint32_t*)0x40009160)
#define ISP_RX_SHUTTER                          *((volatile uint32_t*)0x40009164)
#define ISP_RX_HL                               *((volatile uint32_t*)0x40009168)
#define ISP_RX_SAMPLE_FACTOR                    *((volatile uint32_t*)0x4000916c)
#define ISP_RX_MAX_RATIO                        *((volatile uint32_t*)0x40009170)	
#define ISP_RX_STATISTICAL_MAX                  *((volatile uint32_t*)0x40009174)	
#define ISP_RX_STATISTICAL_MIN                  *((volatile uint32_t*)0x40009178)
#define ISP_RX_STATISTICAL_MID                  *((volatile uint32_t*)0x4000917c)
	
#define TMPL_ENCODE_RX_PUPIL_RADIU              *((volatile uint32_t*)0x40009190)
#define TMPL_ENCODE_RX_IRIS_RADIU               *((volatile uint32_t*)0x40009194)
#define TMPL_ENCODE_RX_MEDIAN0                  *((volatile uint32_t*)0x40009198)
#define TMPL_ENCODE_RX_MEDIAN1                  *((volatile uint32_t*)0x4000919c)
#define TMPL_ENCODE_RX_MEDIAN2                  *((volatile uint32_t*)0x400091a0)
#define TMPL_ENCODE_RX_PARA_FAKE_CHK            *((volatile uint32_t*)0x400091a4)
#define TMPL_ENCODE_RX_PARA_INTEFRATOR          *((volatile uint32_t*)0x400091a8)
#define TMPL_ENCODE_RX_PARA_PUPIL               *((volatile uint32_t*)0x400091ac)
#define TMPL_ENCODE_RX_PARA_DS_GM_RANGE         *((volatile uint32_t*)0x400091b0)	
#define TMPL_ENCODE_RX_PARA_DS_MARGIN           *((volatile uint32_t*)0x400091b4)
#define TMPL_ENCODE_RX_PARA_DS_RANGE            *((volatile uint32_t*)0x400091b8)
#define TMPL_ENCODE_RX_PARA_FS_GM_RANGE         *((volatile uint32_t*)0x400091bc)	
#define TMPL_ENCODE_RX_PARA_FS_MARGIN           *((volatile uint32_t*)0x400091c0)
#define TMPL_ENCODE_RX_PARA_FS_RANGE            *((volatile uint32_t*)0x400091c4)	
#define TMPL_ENCODE_RX_PARA_IRIS_DM_SM          *((volatile uint32_t*)0x400091c8)
#define TMPL_ENCODE_RX_PARA_IRIS_EYE_PIX_TH     *((volatile uint32_t*)0x400091cc)	
#define TMPL_ENCODE_RX_PARA_IRIS_GARY_RANGE     *((volatile uint32_t*)0x400091d0)
	
#define TMPL_ENCODE_RX_PARA_1                   *((volatile uint32_t*)0x400091d4)	
#define TMPL_ENCODE_RX_PARA_2                   *((volatile uint32_t*)0x400091d8)	
#define TMPL_ENCODE_RX_PARA_3                   *((volatile uint32_t*)0x400091dc)
#define TMPL_ENCODE_RX_PARA_4                   *((volatile uint32_t*)0x400091e0)
#define TMPL_ENCODE_RX_PARA_5                   *((volatile uint32_t*)0x400091e4)
#define TMPL_ENCODE_RX_PARA_6                   *((volatile uint32_t*)0x400091e8)
#define TMPL_ENCODE_RX_PARA_7                   *((volatile uint32_t*)0x400091ec)
#define TMPL_ENCODE_RX_PARA_8                   *((volatile uint32_t*)0x400091f0)
#define TMPL_ENCODE_RX_PARA_9                   *((volatile uint32_t*)0x400091f4)	
#define TMPL_ENCODE_RX_PARA_10                  *((volatile uint32_t*)0x400091f8)
#define TMPL_ENCODE_RX_PARA_11                  *((volatile uint32_t*)0x400091fc)
#define TMPL_ENCODE_RX_PARA_12                  *((volatile uint32_t*)0x40009200)
#define TMPL_ENCODE_RX_PARA_13                  *((volatile uint32_t*)0x40009204)	
#define TMPL_ENCODE_RX_PARA_14                  *((volatile uint32_t*)0x40009208)
#define TMPL_ENCODE_RX_PARA_15                  *((volatile uint32_t*)0x4000920c)
#define TMPL_ENCODE_RX_PARA_16                  *((volatile uint32_t*)0x40009210)
#define TMPL_ENCODE_RX_PARA_17                  *((volatile uint32_t*)0x40009214)
#define TMPL_ENCODE_RX_PARA_18                  *((volatile uint32_t*)0x40009218)
#define TMPL_ENCODE_RX_PARA_19                  *((volatile uint32_t*)0x4000921c)
#define TMPL_ENCODE_RX_PARA_20                  *((volatile uint32_t*)0x40009220)
#define TMPL_ENCODE_RX_PARA_21                  *((volatile uint32_t*)0x40009224)	
#define TMPL_ENCODE_RX_PARA_22                  *((volatile uint32_t*)0x40009228)
#define TMPL_ENCODE_RX_PARA_23                  *((volatile uint32_t*)0x4000922c)
#define TMPL_ENCODE_RX_PARA_24                  *((volatile uint32_t*)0x40009230)
#define TMPL_ENCODE_RX_PARA_25                  *((volatile uint32_t*)0x40009234)
#define TMPL_ENCODE_RX_PARA_26                  *((volatile uint32_t*)0x40009238)
#define TMPL_ENCODE_RX_PARA_27                  *((volatile uint32_t*)0x4000923c)
#define TMPL_ENCODE_RX_PARA_28                  *((volatile uint32_t*)0x40009240)
#define TMPL_ENCODE_RX_PARA_29                  *((volatile uint32_t*)0x40009244)
#define TMPL_ENCODE_RX_PARA_30                  *((volatile uint32_t*)0x40009248)
#define TMPL_ENCODE_RX_PARA_31                  *((volatile uint32_t*)0x4000924c)
#define TMPL_ENCODE_RX_PARA_32                  *((volatile uint32_t*)0x40009250)
#define TMPL_ENCODE_RX_PARA_33                  *((volatile uint32_t*)0x40009254)
#define TMPL_ENCODE_RX_PARA_34                  *((volatile uint32_t*)0x40009258)
#define TMPL_ENCODE_RX_PARA_35                  *((volatile uint32_t*)0x4000925c)
#define TMPL_ENCODE_RX_PARA_36                  *((volatile uint32_t*)0x40009260)
#define TMPL_ENCODE_RX_PARA_37                  *((volatile uint32_t*)0x40009264)
#define TMPL_ENCODE_RX_PARA_38                  *((volatile uint32_t*)0x40009268)
#define TMPL_ENCODE_RX_PARA_39                  *((volatile uint32_t*)0x4000926c)
#define TMPL_ENCODE_RX_PARA_40                  *((volatile uint32_t*)0x40009270)
#define TMPL_ENCODE_RX_PARA_41                  *((volatile uint32_t*)0x40009274)
	                                                                                           
#define TMPL_Match_RX_PARA_1                    *((volatile uint32_t*)0x40009280)
#define TMPL_Match_RX_PARA_2                    *((volatile uint32_t*)0x40009284)
#define TMPL_Match_RX_PARA_3                    *((volatile uint32_t*)0x40009288)
	
#define WRITE_TEMP_TIMEOUT						*((volatile uint32_t*)0x400092ac)			
                                                
#define DSP_CMD                                 *((volatile uint32_t*)0x40009300)
#define DSP_CURRNET_STATUS                      *((volatile uint32_t*)0x40009304)
#define DSP_CMD_STATUS                          *((volatile uint32_t*)0x40009308)	
#define DSP_ERR_STATUS                          *((volatile uint32_t*)0x4000930c)
#define DSP_RX_CTRL                             *((volatile uint32_t*)0x40009310)
#define DSP_RX_TMPL_INDEX                       *((volatile uint32_t*)0x40009314)
#define DSP_TMPL_ENCODE_CTRL                    *((volatile uint32_t*)0x40009318)	
#define DSP_TMPL_MATCH_CTRL                     *((volatile uint32_t*)0x4000931c)	
#define DSP_WR_EN0                              *((volatile uint32_t*)0x40009320)
#define DSP_WR_EN1                              *((volatile uint32_t*)0x40009324)
#define DSP_WR_EN2                              *((volatile uint32_t*)0x40009328)
#define DSP_WR_EN3                              *((volatile uint32_t*)0x4000932c)	
#define DSP_WR_EN4                              *((volatile uint32_t*)0x40009330)

#define DSP_ENCODE_RESULT_1                     *((volatile uint32_t*)0x40009348)
#define DSP_ENCODE_RESULT_2                     *((volatile uint32_t*)0x4000934c)
#define DSP_ENCODE_RESULT_3                     *((volatile uint32_t*)0x40009350)
#define DSP_ENCODE_RESULT_4                     *((volatile uint32_t*)0x40009354)
#define DSP_ENCODE_RESULT_5                     *((volatile uint32_t*)0x40009358)
#define DSP_ENCODE_RESULT_6                     *((volatile uint32_t*)0x4000935c)
#define DSP_ENCODE_RESULT_7                     *((volatile uint32_t*)0x40009360)
#define DSP_ENCODE_RESULT_8                     *((volatile uint32_t*)0x40009364)
#define DSP_ENCODE_RESULT_9                     *((volatile uint32_t*)0x40009368)
#define DSP_ENCODE_RESULT_10                    *((volatile uint32_t*)0x4000936c)
#define DSP_ENCODE_RESULT_11                    *((volatile uint32_t*)0x40009370)
#define DSP_ENCODE_RESULT_12                    *((volatile uint32_t*)0x40009374)
#define DSP_ENCODE_RESULT_13                    *((volatile uint32_t*)0x40009378)
#define DSP_ENCODE_RESULT_14                    *((volatile uint32_t*)0x4000937c)
#define DSP_ENCODE_RESULT_15                    *((volatile uint32_t*)0x40009380)
#define DSP_ENCODE_RESULT_16                    *((volatile uint32_t*)0x40009384)
#define DSP_ENCODE_RESULT_17                    *((volatile uint32_t*)0x40009388)
#define DSP_ENCODE_RESULT_18                    *((volatile uint32_t*)0x4000938c)
#define DSP_ENCODE_RESULT_19                    *((volatile uint32_t*)0x40009390)
#define DSP_ENCODE_RESULT_20                    *((volatile uint32_t*)0x40009394)
#define DSP_ENCODE_RESULT_21                    *((volatile uint32_t*)0x40009398)
#define DSP_ENCODE_RESULT_22                    *((volatile uint32_t*)0x4000939c)
#define DSP_ENCODE_RESULT_23                    *((volatile uint32_t*)0x400093a0)
#define DSP_ENCODE_RESULT_24                    *((volatile uint32_t*)0x400093a4)
#define DSP_ENCODE_RESULT_25                    *((volatile uint32_t*)0x400093a8)
#define DSP_ENCODE_RESULT_26                    *((volatile uint32_t*)0x400093ac)
	                                                                                            
#define DSP_ENCODE_RESULT_27                    *((volatile uint32_t*)0x400093c0)
#define DSP_ENCODE_RESULT_28                    *((volatile uint32_t*)0x400093c4)
#define DSP_ENCODE_RESULT_29                    *((volatile uint32_t*)0x400093c8)
#define DSP_ENCODE_RESULT_30                    *((volatile uint32_t*)0x400093d0)
	                                            
#define DSP_ENCODE_RESULT_31                    *((volatile uint32_t*)0x400093e8)
#define DSP_ENCODE_RESULT_32                    *((volatile uint32_t*)0x400093ec)
	


#endif
