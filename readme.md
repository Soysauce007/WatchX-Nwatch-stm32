移植到Stm32的NWatch

首先感谢zkemble在2015年提供的NWatch，真的是太棒了

![NWatch](https://blog.zakkemble.net/wp-content/uploads/2013/09/PICT2254-300x225.jpg)

https://github.com/zkemble/NWatch
其次是crystaledm提供的c语言库
https://github.com/crystaledm/watchX

##### 开发环境： 

keil5  ALIENTEK 探索者STM32F407开发板  2.4寸tft屏幕

##### 目前已经完成的移植内容为：

RTC时钟、动画显示、断电flash模拟eeprom，及其自带的所以图标

##### 待完成：             

闹铃的flash存储，Sleep睡眠模式（低功耗模式），电压检测，音调，音量调节

##### 可实现的效果：

闹钟、手电筒、秒表计时、3D动画演示、游戏（赛车、破坏小球）
             设置->日期调整、（睡眠时间设置）、显示设置、版本信息查看、FPS显示

##### 感兴趣的小伙伴可以进群：

我还没创，你自己建吧！		
                                                  

##### 主要的菜单界面可以阅读借鉴：

setting.c 的迭代器函数  

```
static void itemLoader(byte num)   
```

同时注意

```
 #define OPTION_COUNT	5
```

中间的OPTION_COUNT 根据实际情况进行增加减少 

```
  void setMenuOption_P(byte num, const char* name, const b yte* icon, menu_f actionFunc) 
```

 中的actionFunc  根据Go to Definition  of "xxxxx" 就可以进入对应的文件进行修改，也可以模仿进行添加文件

还有一种菜单模式，可以借鉴 timedate.c 和 diag.c。

##### 屏幕移植到oled ：

对于想将屏幕移植到oled 的小伙伴，只需要将void oled_flush(void)重写，将oledBuffer[]数组输出到oled屏幕上，将因为手上还没有oled 我在TFT屏幕上模拟了oled 的显示方式，无需修改其他位置。

##### 移植到其它stm32单片机：

对于想移植到其它stm32单片机上的小伙伴，需要特别注意appconfig.c中间的eepCheck_SAVE_ADDR 这个偏移地址，请适当调整。
 EEPROM_CHECK_NUM这个值很玄学，我尝试了很久才出来

移植和改动文件程序的时候需要主要：  common.h
对部分预编译效果不满意的可以修改：       config.h

##### 其它：

横屏显示的骚操作在 lcd.c LCD_Fast_DrawPoint 里面随便乘以了一个倍数。

对了这个lcd.c是我简化过正点原子的库的，对你自己的屏幕需要你找个可以用的屏幕库修改一哈

希望大家疫情期间玩的开心，保重身体！！！

​      