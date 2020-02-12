/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */

#include "common.h"
#include "lcd.h"
#include "led.h"

#define OPTION_COUNT	5

static prev_menu_s prevMenuData;

static void mSelect(void);
static void itemLoader(byte);
static void setBrightness(void);
static void setInvert(void);
static void setRotate(void);
#if COMPILE_ANIMATIONS
static void setAnimations(void);
#endif
static void setMenuOptions(void);

void mDisplayOpen()
{
	setMenuInfo(OPTION_COUNT, MENU_TYPE_ICON, PSTR(STR_DISPLAYMENU));
	setMenuFuncs(MENUFUNC_NEXT, mSelect, MENUFUNC_PREV, itemLoader);

	setMenuOptions();

	setPrevMenuOpen(&prevMenuData, mDisplayOpen);

	beginAnimation2(NULL);
}

static void mSelect()
{
	bool isExiting = exitSelected();
	if(isExiting)
		appconfig_save();
	setPrevMenuExit(&prevMenuData);
	doAction(exitSelected());
	
	
}

static void itemLoader(byte num)
{
	UNUSED(num);
	setMenuOptions();
	addBackOption();
}

static void setBrightness()
{
 	byte brightness = appConfig.brightness;;
	if(brightness > 3)
		brightness = 0;
		brightness++;
	appConfig.brightness = brightness;
	switch(brightness)           //ÉèÖÃ»­±ÊÑÕÉ«
	{
		case 0:	POINT_COLOR= GREEN; break;
		case 1:	POINT_COLOR= BLUE; break;
		case 2:	POINT_COLOR= YELLOW; break;
	}	

 
}

static void setInvert()
{
	bool invert = !appConfig.invert;
	appConfig.invert = invert;
	
	if(invert)
	{ 
		POINT_COLOR=BLACK;	//»­±ÊÑÕÉ«
    BACK_COLOR=WHITE;  //±³¾°É« 
	}
	else
	{
		POINT_COLOR=WHITE;	//»­±ÊÑÕÉ«
    BACK_COLOR=BLACK;  //±³¾°É« 
	}

//	oled_setInvert(invert);
}

static void setRotate() 
{
	bool rotate = !appConfig.display180;
	appConfig.display180 = rotate;

//	oled_set180(rotate);
	
	display_dir=rotate;
	
	LCD_Clear(WHITE);//ÇåÆÁ

}

static void setLEDs() {
  appConfig.CTRL_LEDs = !appConfig.CTRL_LEDs;
}

#if COMPILE_ANIMATIONS
static void setAnimations()
{
	bool anims = !appConfig.animations;
	appConfig.animations = anims;
}
#endif

static void setMenuOptions()
{
//	setMenuOption_P(0, PSTR(STR_BRIGHTNESS), menu_brightness[appConfig.brightness], setBrightness);
//	setMenuOption_P(1, PSTR(STR_INVERT), menu_invert, setInvert);
//	setMenuOption_P(2, PSTR(STR_ROTATE), menu_rotate, setRotate);
//#if COMPILE_ANIMATIONS
//	setMenuOption_P(3, PSTR(STR_ANIMATIONS), menu_anim[appConfig.animations], setAnimations);
//#endif
//  setMenuOption_P(4, PSTR(STR_LEDS), menu_LEDs[appConfig.CTRL_LEDs], setLEDs);
//	

	
	setMenuOption_P(0, PSTR(STR_BRIGHTNESS), menu_brightness[appConfig.brightness], setBrightness);
	setMenuOption_P(1, PSTR(STR_INVERT), menu_invert, setInvert);
	setMenuOption_P(2, PSTR(STR_ROTATE), menu_rotate, setRotate);
#if COMPILE_ANIMATIONS
	setMenuOption_P(3, PSTR(STR_ANIMATIONS), menu_anim[appConfig.animations], setAnimations);
#endif
  setMenuOption_P(4, PSTR(STR_LEDS), menu_LEDs[appConfig.CTRL_LEDs], setLEDs);
	

}
