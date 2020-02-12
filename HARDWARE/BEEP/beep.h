#ifndef __BEEP_H
#define __BEEP_H	 
#include "sys.h" 
#include "typedefs.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//蜂鸣器驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 



// TONE_VALUE = F_CPU / TONE_FREQ / 16
// TONE_VALUE should be kept below 256 (1960Hz) otherwise the datatype will be bumped up from char to int
typedef enum
{
	TONE_STOP = 0,
	TONE_PAUSE = 1,
	TONE_REPEAT = 2,
	TONE_2KHZ = 250,
	TONE_2_5KHZ = 200,
	TONE_3KHZ = 166,
	TONE_3_5KHZ = 143,
	TONE_4KHZ = 125,
	TONE_4_5KHZ = 111,
	TONE_5KHZ = 100,
} tone_t;

typedef enum
{
	VOL_OTHER = 0,
	VOL_UI = 1,
	VOL_ALARM = 2,
	VOL_HOUR = 3
} vol_t;

typedef enum
{
	PRIO_MIN = 0,
	PRIO_LOW = 1,
	PRIO_NML = 2,
	PRIO_HIGH = 3,
	PRIO_MAX = 255
} tonePrio_t;

#define PRIO_UI		PRIO_LOW
#define PRIO_ALARM	PRIO_HIGH
#define PRIO_HOUR	PRIO_NML

typedef void (*buzzFinish_f)(void);

#define buzzer_stop()	(buzzer_buzz(0, TONE_STOP, PRIO_MAX, NULL))

void buzzer_init(void);//初始化	
void buzzer_buzz(byte, tone_t, vol_t, tonePrio_t, buzzFinish_f);
//void buzzer_buzzb(byte, tone_t, vol_t);
bool buzzer_buzzing(void);
void buzzer_update(void);



//LED端口定义
#define BEEP PFout(8)	// 蜂鸣器控制IO 





#endif















