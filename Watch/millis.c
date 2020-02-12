/*
 * Project: Lightweight millisecond tracking library
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/millisecond-tracking-library-for-avr/
 */

#ifndef ARDUINO


#include "common.h"
#include "sys.h"
#include "led.h"
//#include "misc.h"

 millis_t milliseconds;


//static inline bool millis_interrupt_off(void)
//{
//	TIM_Cmd(TIM2,DISABLE);//开启时钟
//	return true;
//}

//static inline bool millis_interrupt_on(void)
//{
//	TIM_Cmd(TIM2,ENABLE);//开启时钟
//	return false;
//}

////// NEED TO DO A RESTORE THING! if paused then millis() is called it will unpause
//#define MILLIS_ATOMIC() for(bool cs = millis_interrupt_off(); cs; cs = millis_interrupt_on())


// Initialise library
void millis_init()
{
	// Timer settings
	  //1、配置嵌套中断控制器NVIC
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//优先级分组
     NVIC_InitTypeDef nvic;
     nvic.NVIC_IRQChannel=TIM2_IRQn;
     nvic.NVIC_IRQChannelCmd=ENABLE;
     nvic.NVIC_IRQChannelPreemptionPriority=0;
     nvic.NVIC_IRQChannelSubPriority=0;
     NVIC_Init(&nvic);

	 //2、定时器初始化配置
     TIM_TimeBaseInitTypeDef tim;//结构体
     //优先级函数调用
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//开启时钟
     TIM_DeInit(TIM2);//？？？？？
     tim.TIM_ClockDivision=TIM_CKD_DIV1;//采样分频
     tim.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
     tim.TIM_Period=1000;//自动重装载寄存器的值
     tim.TIM_Prescaler=35;//时钟预分频
     //tim.TIM_RepetitionCounter=
     TIM_TimeBaseInit(TIM2,&tim);//初始化结构体
     TIM_ClearFlag(TIM2,TIM_FLAG_Update);//清除溢出中断标志
     TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
     TIM_Cmd(TIM2,ENABLE);//开启时钟
     
	
}

// Get current milliseconds
millis_t millis_get()
{
	millis_t ms;
		ms = milliseconds;
	return ms;
}




 //定时器中断函数处理。 //TIM2通用定时器
 void TIM2_IRQHandler(void)
{
		if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)//判断中断标志是否发生
		{
				milliseconds++;		
				update = true;
			
			#ifdef RTC_SRC
			  update = true;
			#else
			if(milliseconds%3600==0)
			{
				update = true;
				++timeDate.time.secs;   //每秒钟标志位+1;
				 LED1=!LED1;	
			}
			#endif
			
	 }
	 TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);     //手动清除中断标志位
}










#endif
