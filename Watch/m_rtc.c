/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2014 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */

#include "common.h"
#include "delay.h"
#include "sys.h"
#include "rtc.h"
#include "led.h"

RTC_TimeTypeDef RTC_TimeStruct;
RTC_DateTypeDef RTC_DateStruct;

//#if RTC_SRC == RTC_SRC_INTERNAL

void rtc_init()
{
	delay_ms(1000);

	My_RTC_Init();
}

// dont forget about millis()!
// square wave
// should tick twice per sec
// 1 per sec when in sleep

void rtc_tempUpdate()
{
	// read internal temperature sensor
}

void rtc_tempGet(rtc_temperature_s* temp)
{
	temp->whole = 0;
	temp->frac = 0;
}


void rtc_save(timeDate_s *timeDate)
{
	int ret=0;
		u16 retry=0X1FFF; 
	RTC_InitTypeDef RTC_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);//使能PWR时钟
	PWR_BackupAccessCmd(ENABLE);	//使能后备寄存器访问 
			RCC_LSEConfig(RCC_LSE_ON);//LSE 开启    
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)	//检查指定的RCC标志位设置与否,等待低速晶振就绪
			{
			retry++;
			delay_ms(10);
			}
		if(retry==0)return ;		//LSE 开启失败. 
			
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);		//设置RTC时钟(RTCCLK),选择LSE作为RTC时钟    
		RCC_RTCCLKCmd(ENABLE);	//使能RTC时钟 

    RTC_InitStructure.RTC_AsynchPrediv = 0x7F;//RTC异步分频系数(1~0X7F)
    RTC_InitStructure.RTC_SynchPrediv  = 0xFF;//RTC同步分频系数(0~7FFF)
    RTC_InitStructure.RTC_HourFormat   = RTC_HourFormat_24;//RTC设置为,24小时格式
    RTC_Init(&RTC_InitStructure);
	
	
	ret=RTC_Set_Date(timeDate->date.year,(month_t)(timeDate->date.month+1),timeDate->date.date,(day_t)(timeDate->date.day+1));
	ret=RTC_Set_Time(timeDate->time.hour,timeDate->time.mins,timeDate->time.secs,timeDate->time.ampm);
	if(ret)LED0=!LED0;
}	
void rtc_get(timeDate_s *timeDate)
{
	
	RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
	RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
		
			
	timeDate->date.year=RTC_DateStruct.RTC_Year;
	timeDate->date.month=(month_t)(RTC_DateStruct.RTC_Month-1);
	timeDate->date.date=RTC_DateStruct.RTC_Date;
	timeDate->date.day=(day_t)(RTC_DateStruct.RTC_WeekDay-1);
	

	timeDate->time.hour=RTC_TimeStruct.RTC_Hours;
	timeDate->time.mins=RTC_TimeStruct.RTC_Minutes;
	timeDate->time.secs=RTC_TimeStruct.RTC_Seconds;
	timeDate->time.ampm=0;
	
	
	
}
void rtc_sqw(rtc_sqw_t sqw)
{

}	

void rtc_setUserAlarmWake(alarm_s *alarm)
{
  RTC_Set_AlarmA(  alarm->days,alarm->hour,alarm->min,0);
}	

void rtc_setSystemAlarmWake(alarm_s *alarm)
{
  RTC_Set_AlarmA(  alarm->days,alarm->hour,alarm->min,0);
}

bool rtc_userAlarmState()
{
 return RTC_GetFlagStatus(RTC_FLAG_ALRAF);
}

bool rtc_systemAlarmState()
{
  return RTC_GetFlagStatus(RTC_FLAG_ALRAF);
}


//	RTC_AlarmCmd(RTC_Alarm_A,DISABLE);//关闭闹钟A 




//#endif
