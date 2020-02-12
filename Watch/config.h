/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */

// Fuses for ATmega328/328P
// Internal RC 8MHz 6 CK/14CK + 4.1ms startup
// Serial program (SPI) enabled
// Brown-out at 1.8V
// High:		0xDF
// Low:			0xD2
// Extended:	0xFE

#ifndef CONFIG_H_
#define CONFIG_H_

//#define CPU_DIV clock_div_1

// Hardware version
// 1 = PCB 1.0 - 1.1
// 2 = PCB 1.2
// 3 = PCB 1.3 - 1.4
#define HW_VERSION	3

#define USER_NAME "   Yummy"

// Firmware version
#define FW_VERSION	"  2.8 T2020" // maybe use some __DATE__ __TIME__ stuff?

// Language
// 0 = English
// 1 = German (not done)
// 2 = Russian
#define LANGUAGE 0


// 编译选项
#define COMPILE_GAME1      1 // 游戏Breakout    
#define COMPILE_GAME2      1 // 游戏Car dodge
#define COMPILE_GAME3      1 // 游戏Flappy thing (not finished) 有bug  未完成，实在做不来
#define COMPILE_ANIMATIONS 1 //动画
#define COMPILE_STOPWATCH  1 //秒表
#define COMPILE_TORCH      1 //手电筒
#define COMPILE_TUNEMAKER  1 //3D滚动


//这个两个开启后可以串口打印调试信息
#define COMPILE_UART       0
#define DEBUG_MSGS		     0
#define UART_BAUD          115200



#define RTC_SRC   ///在无外部时钟时间 请注销这里          这里有BUG ，需要配合修改millis.c里面的z中断计时软件


#endif /* CONFIG_H_ */
