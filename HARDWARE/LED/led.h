#ifndef __LED_H
#define __LED_H
#include "sys.h"
#include "typedefs.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */






typedef enum
{
	LED_RED,
	LED_GREEN
} led_t;

//#define LED_FLASH_INFINITE	0
//#define LED_ALL				255
#define LED_FLASH_FAST	50
#define LED_BRIGHTNESS_MAX	255

//LED端口定义
#define LED0 PFout(9)	// DS0
#define LED1 PFout(10)	// DS1	 



void led_init(void);//初始化	
void led_flash(led_t, byte, byte);
BOOL led_flashing(void);
void led_update(void);
void led_stop(void);

 




#endif


