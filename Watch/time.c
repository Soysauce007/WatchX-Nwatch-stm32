/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */

#include "common.h"

#define SECONDS_IN_MIN	60
#define SECONDS_IN_HOUR	(60 * SECONDS_IN_MIN)
#define SECONDS_IN_DAY	(((uint32_t)24) * SECONDS_IN_HOUR)

#define FEB_LEAP_YEAR	29
static const byte monthDayCount[] PROGMEM = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

timeDate_s timeDate;
//static timestamp_t timestamp;
 bool update;

static void getRtcTime(void);

void time_init()
{
	time_wake();
}

void time_sleep()
{
////	TCCR2B = _BV(CS22)|_BV(CS20);
////	while(ASSR & (_BV(OCR2BUB)|_BV(TCR2AUB)|_BV(TCR2BUB)));

//#if RTC_SRC != RTC_SRC_INTERNAL
//	// Turn off square wave
//	rtc_sqw(RTC_SQW_OFF);

//	alarm_s alarm;

//	// Set next alarm
//	if(alarm_getNext(&alarm))
//	{
//		alarm.days = alarm_getNextDay() + 1;
//		rtc_setUserAlarmWake(&alarm);
//	}
//	else // No next alarm
//		rtc_setUserAlarmWake(NULL);

//	// Set up hour beeps
//	if(appConfig.volHour)
//	{
//		alarm.min = 0;
//		alarm.hour = 0;
//		alarm.days = 0;
//		rtc_setSystemAlarmWake(&alarm);
//	}
//	else // Hour beep volume set to minimum, so don't bother with the system alarm
//		rtc_setSystemAlarmWake(NULL);
//#endif

	update = false;
}

void time_shutdown()
{
//#if RTC_SRC != RTC_SRC_INTERNAL
//	rtc_sqw(RTC_SQW_OFF);
//	rtc_setUserAlarmWake(NULL);
//	rtc_setSystemAlarmWake(NULL);
//#endif

	update = false;
}

rtcwake_t time_wake()
{
//#if RTC_SRC != RTC_SRC_INTERNAL
	getRtcTime();

	// Turn on square wave
//	rtc_sqw(RTC_SQW_ON);

//	update = false;

	// Check alarms
	bool userAlarm = rtc_userAlarmState();
	bool systemAlarm = rtc_systemAlarmState();

	if(userAlarm && systemAlarm)
		return RTCWAKE_USER_SYSTEM;
	else if(userAlarm)
		return RTCWAKE_USER;
	else if(systemAlarm)
		return RTCWAKE_SYSTEM;
	return RTCWAKE_NONE;
}

void time_set(timeDate_s* newTimeDate)
{

	memcpy(&timeDate, newTimeDate, sizeof(timeDate_s));

	timeDate.time.secs = 0;
	time_timeMode(&timeDate.time, appConfig.timeMode);

	rtc_save(&timeDate);
//	getRtcTime();

	alarm_updateNextAlarm();
}

bool time_isLeapYear(byte year)
{
// Watch only supports years 2000 - 2099, so no need to do the full calculation

	return (year % 4 == 0);

	//uint fullYear = year + 2000;
	//return ((fullYear & 3) == 0 && ((fullYear % 25) != 0 || (fullYear & 15) == 0));
}

// Workout day of week from year, month and date
// http://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week
day_t time_dow(byte yy, month_t m, byte d)
{
	//static byte t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
	//y -= m < 3;
	//byte dow = (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;

  m =(month_t)(m + (month_t)1);
	int y = yy + 2000;
	byte dow = (d+=m<3?y--:y-2,23*m/9+d+4+y/4-y/100+y/400)%7 ;

	// 0 = Sunday, 1 = Monday, but Monday should be 0
	dow--;
	if(dow == 255) // Overflowed, must have been 0 which is Sunday
		dow = 6;
	return (day_t)dow;
}

byte time_monthDayCount(month_t month, byte year)
{
//	byte numDays = pgm_read_byte(&monthDayCount[month]);
		byte numDays = monthDayCount[month];

	if(month == MONTH_FEB && time_isLeapYear(year))
		numDays = FEB_LEAP_YEAR;
	return numDays;
}


char* time_timeStr()
{
	static char buff[BUFFSIZE_TIME_FORMAT_SMALL];
	sprintf_P(buff, PSTR(TIME_FORMAT_SMALL), timeDate.time.hour, timeDate.time.mins, timeDate.time.ampm);
	return buff;
}

void time_timeMode(time_s* time, timemode_t mode)
{
	byte hour = time->hour;
	if(mode == TIMEMODE_12HR)
	{
		if(time->ampm != CHAR_24) // Already 12hr
			return;
		else if(hour >= 12)
		{
			if(hour > 12)
				hour -= 12;
			time->ampm = CHAR_PM;
		}
		else
		{
			if(hour == 0)
				hour = 12;
			time->ampm = CHAR_AM;
		}
	}
	else // 24 hour
	{
		if(time->ampm == CHAR_AM && hour == 12) // Midnight 12AM = 00:00
			hour = 0;
		else if(time->ampm == CHAR_PM && hour < 12) // No change for 12PM (midday)
			hour += 12;
		time->ampm = CHAR_24;
	}
	
	time->hour = hour;
}

void time_update()
{
	if(!update)
		return;
	update = false;
#ifdef RTC_SRC 
	getRtcTime();
	
	if(timeDate.time.secs == 0 && timeDate.time.mins == 0)
		tune_play(tuneHour, VOL_HOUR, PRIO_HOUR);
#else
	
	// Slightly modified code from AVR134            
	if(timeDate.time.secs == 60)
	{
		timeDate.time.secs = 0;
		if(++timeDate.time.mins == 60)
		{
			timeDate.time.mins = 0;
			if(++timeDate.time.hour == 24) // What about 12 hr?
			{
				byte numDays = time_monthDayCount(timeDate.date.month, timeDate.date.year);

				timeDate.time.hour = 0;
				if (++timeDate.date.date == numDays + 1)
				{
					timeDate.date.month++;
					timeDate.date.date = 1;
				}

				if (timeDate.date.month == 13)
				{
					timeDate.date.month = (month_t)1;
					timeDate.date.year++;
					if(timeDate.date.year == 100)
						timeDate.date.year = 0;
				}

				if(++timeDate.date.day == 7)
					timeDate.date.day = (day_t)0;
			}

//			tune_play(tuneHour, VOL_HOUR, PRIO_HOUR);
		}
	}
#endif

	debug_printf("%02hhu:%02hhu:%02hhu\n", timeDate.time.hour, timeDate.time.mins, timeDate.time.secs);
	//debug_printf("T: %hhuC\n",rtc_temp());
}

static void getRtcTime()
{
	
	    #ifdef RTC_SRC
	
	     rtc_get(&timeDate);
	
			#else
	
    	timeDate.date.year='0'-28;
	    timeDate.date.month=(month_t)1;
	    timeDate.date.day=(day_t)5;
	    timeDate.date.date=7;
    	timeDate.time.hour=milliseconds/3600;
	    timeDate.time.mins=(milliseconds%3600)/60;
    	timeDate.time.secs= milliseconds%3600%60;
 
			#endif
	

	
	
	timeDate.time.ampm = CHAR_24;
//	timestamp = time_timeDate2TimeStamp(&timeDate);

	// Convert to correct time mode
		time_timeMode(&timeDate.time, appConfig.timeMode);

	
}

//#if RTC_SRC == RTC_SRC_INTERNAL
//ISR(TIMER2_OVF_vect)
//#else
//#ifdef __AVR_ATmega32U4__
//ISR(INT3_vect)
//#else
//ISR(INT0_vect)
//#endif
//#endif
//{
//	update = true;
//}
