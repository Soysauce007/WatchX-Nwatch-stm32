/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2014 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */

#ifndef RTC_H_
#define RTC_H_
#include "typedefs.h"
#include "m_rtc.h"


typedef enum
{
	RTC_SQW_OFF = 0,
	RTC_SQW_ON = 1
} rtc_sqw_t;

typedef struct
{
	signed char whole;
	byte frac;
}rtc_temperature_s;


void rtc_init(void);
void rtc_tempUpdate(void);
void rtc_tempGet(rtc_temperature_s*);
void rtc_save(timeDate_s *timeDate); 
void rtc_get(timeDate_s *timeDate); 
void rtc_sqw(rtc_sqw_t sqw); 
void rtc_setUserAlarmWake(alarm_s *alarm); 
void rtc_setSystemAlarmWake(alarm_s *alarm); 
bool rtc_userAlarmState(void);
bool rtc_systemAlarmState(void);

//#define rtc_sqw(enable)					EMPTY_FUNC
//#define rtc_get(timeData)				EMPTY_FUNC
//#define rtc_save(timeData)				EMPTY_FUNC
//#define rtc_setUserAlarmWake(alarm)		EMPTY_FUNC
//#define rtc_setSystemAlarmWake(alarm)	EMPTY_FUNC
//#define rtc_userAlarmState()			(false)
//#define rtc_systemAlarmState()			(false)





#endif /* RTC_H_ */
