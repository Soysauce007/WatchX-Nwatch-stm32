#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "common.h"
//开发环境： keil5  ALIENTEK 探索者STM32F407开发板  2.4寸tft屏幕
//
//Nwatch已经成功移植到了Stm32啦，目前已经完成的移植内容为：
//                                                     RTC时钟、动画显示、断电flash模拟eeprom，及其自带的所有图标
//                                 待完成：             闹铃的flash存储，Sleep睡眠模式（低功耗模式），电压检测
//
//可实现的效果：闹钟、手电筒、秒表计时、3D动画演示、游戏（赛车、破坏小球）
//             设置->日期调整、（睡眠时间设置）、显示设置、版本信息查看、FPS显示
//感兴趣的小伙伴可以进群			
//                                                  
//主要的菜单界面可以阅读借鉴：setting.c 的迭代器函数  static void itemLoader(byte num)   同时注意 #define OPTION_COUNT	5中间的OPTION_COUNT 根据时间情况进行增加减少
//                          void setMenuOption_P(byte num, const char* name, const byte* icon, menu_f actionFunc)  中的actionFunc  根据输入的Go to Definition  of "xxxxx" 就可以进入对应的文件进行修改，也可以模仿进行添加文件
//                        
//还有一种菜单模式，可以借鉴 timedate.c 和 diag.c
//
//对于想将屏幕移植到oled 的小伙伴，只需要将void oled_flush(void)重写，oledBuffer[] 输出到oled屏幕上
//将因为手上还没有oled 我只是模拟了oled 的显示方式，无需修改其他位置
//
//对于想移植到其它stm32单片机上的小伙伴，需要特别注意appconfig.c中间的eepCheck_SAVE_ADDR 这个偏移地址，请适当调整
// EEPROM_CHECK_NUM这个值很玄学，我尝试了很久才出来
//
//移植和改动文件程序的时候需要主要：   common.h
//对于预编译不满意的可以修改：        config.h
//
//横屏显示的骚操作在 lcd.c LCD_Fast_DrawPoint 里面有一个倍数方便查找
//
//对了这个lcd.c是我简化过正点原子的库的，对你自己的屏幕需要你找个可以用的屏幕库修改一哈
//
//希望大家疫情期间玩的开心，保重身体！！！
//
//                                                   作者：YUMMY

void c_setup()
{
  SystemInit();	
 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);          //初始化延时函数
#if COMPILE_UART
		uart_init(UART_BAUD);		//初始化串口波特率为115200
#endif
 	LCD_Init();               //初始化LCD FSMC接口
	POINT_COLOR=BLACK;        //画笔颜色：红色
  // Everything else
	memset(&oledBuffer, 0x00, FRAME_BUFFER_SIZE);
	led_init();               //初始化LED
  buzzer_init();	
  global_init();
	appconfig_init();
	alarm_init();             //无法储存闹钟，每次重启以后需要自定义

  buttons_init();
  millis_init();
  time_init();
	rtc_init();
	LED0=!LED0;
	
	// Set watchface
	display_set(watchface_normal);

	display_load();
	
	//设置背景颜色
  if(	appConfig.invert)
	  LCD_Clear(WHITE);
  else   	
	  LCD_Clear(BLACK);
}

void c_loop()
{
    time_update();
//  if(pwrmgr_userActive())
//  {
//    battery_update();
//    buttons_update();
//  }
    
	  buttons_update();
  	buzzer_update();
    led_update();
	
	
#if COMPILE_STOPWATCH
  stopwatch_update();
#endif
//  global_update();

//  if(pwrmgr_userActive())
//  {
    alarm_update();
    display_update();
//  }

  // freeRAM();
//  wdt_update();
//  pwrmgr_update();

//显示完成后清除缓冲区
	  memset(&oledBuffer, 0x00, FRAME_BUFFER_SIZE);

}



int main(void)
{ 
	
	c_setup();	    //初始化

  while(1)
		{
	     c_loop(); //循环
	  }

}





