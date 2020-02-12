/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 
 
#define eeprom_busy_wait() do {} while (!eeprom_is_ready())//等待EEPROM操作完成

extern uint8_t eeprom_read_byte (const uint8_t *addr);//读取指定地址的一个字节8bit的EEPROM数据

extern uint16_t eeprom_read_word (const uint16_t *addr);//读取指定地址的一个字16bit的EEPROM数据

extern void eeprom_read_block (void *buf, const void *addr, size_t n);//读取由指定地址开始的指定长度的EEPROM数据

extern void eeprom_write_byte (uint8_t *addr, uint8_t val);//向指定地址写入一个字节8bit的EEPROM数据

extern void eeprom_write_word (uint16_t *addr, uint16_t val);//向指定地址写入一个字16bit的EEPROM数据
 
 
 */

#include "common.h"
#include "stmflash.h"



#define LENTH(Buffer) sizeof(Buffer)	 		  	//数组长度	
#define SIZE(buff) LENTH(buff)/4+((LENTH(buff)%4)?1:0)

#define EEPROM_CHECK_NUM 0xFF // Any 8 bit number that isn't 0 or 255

#define eepCheck_SAVE_ADDR   0X080E0000 	//设置FLASH 保存地址(必须为偶数，且所在扇区,要大于本代码所占用到的扇区.
										//否则,写操作的时候,可能会导致擦除整个扇区,从而引起部分程序丢失.引起死机.
#define appConfig_SAVE_ADDR  eepCheck_SAVE_ADDR +16 	//设置FLASH 保存地址(必须为偶数，且所在扇区,要大于本代码所占用到的扇区.
										//否则,写操作的时候,可能会导致擦除整个扇区,从而引起部分程序丢失.引起死机.


appconfig_s appConfig;     //appconfig_s的长度为8

static byte eepCheck EEMEM ;//= EEPROM_CHECK_NUM;

//static appconfig_s eepConfig EEMEM = {
//	0, // sleep timeout (this value * 5 = sleep timeout in secs)
//	false, // invert
//#if COMPILE_ANIMATIONS
//	true, // animations
//#endif
//	true, // 180 rotate
//	false, // FPS
//	TIMEMODE_24HR,
//	{
//		255 // volume + brightness (all max)
//	}
//};

void appconfig_init()
{

	 STMFLASH_Read(eepCheck_SAVE_ADDR,(u32*)(&eepCheck),LENTH(byte));
//   appConfig = (appconfig_s *) malloc(sizeof(appconfig_s));
	     memset(&appConfig, 0x00, LENTH(appconfig_s));

	
	
	 if(eepCheck == EEPROM_CHECK_NUM)
	
		 STMFLASH_Read(appConfig_SAVE_ADDR,(u32*)(&appConfig),LENTH(appconfig_s));
	else
	{
    eepCheck = EEPROM_CHECK_NUM;
		STMFLASH_Write(eepCheck_SAVE_ADDR,(u32*)(&eepCheck),LENTH(byte));

		appconfig_reset();
	}

	if(appConfig.sleepTimeout > 12)
		appConfig.sleepTimeout = 0;
}

void appconfig_save()
{			   

  	STMFLASH_Write(appConfig_SAVE_ADDR,(u32*)(&appConfig),LENTH(appconfig_s));

}

void appconfig_reset()
{
	appConfig.sleepTimeout = 1;
	appConfig.invert = false;
#if COMPILE_ANIMATIONS
	appConfig.animations = true;
#endif
	appConfig.display180 = true;
  appConfig.CTRL_LEDs = false;
	appConfig.showFPS = true;
	appConfig.timeMode = TIMEMODE_24HR;
	appConfig.volumes = 255;
	
	appconfig_save();

//	alarm_reset();
}
