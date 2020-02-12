/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */

#include "common.h"

#define OPTION_COUNT		2

static prev_menu_s prevMenuData;

static void mSelect(void);
static void itemLoader(byte);
static void setTimeout(void);
static void setMenuOptions(void);


static display_t mDraw(void);



void mSleepOpen()
{
	setMenuInfo(OPTION_COUNT, MENU_TYPE_ICON, PSTR(STR_SLEEPMENU));
	setMenuFuncs(MENUFUNC_NEXT, mSelect, MENUFUNC_PREV, itemLoader);

  menuData.func.draw = mDraw;
	setPrevMenuOpen(&prevMenuData, mSleepOpen);

	beginAnimation2(NULL);
}

static void mSelect()
{
	bool isExiting = exitSelected();
	
	if(isExiting)

	appconfig_save();

	setPrevMenuExit(&prevMenuData);

	doAction(isExiting);
}

static void itemLoader(byte num)
{
	UNUSED(num);
	setMenuOptions();
//	setMenuOption_P(1, menuBack, menu_exit, back);
	addBackOption();
}

static void setTimeout()
{
	byte timeout = appConfig.sleepTimeout;
	timeout++;
	if(timeout > 12)
		timeout = 0;
	appConfig.sleepTimeout = timeout;
}


static void setMenuOptions()
{

	setMenuOption_P(0, PSTR(STR_TIMEOUT), menu_sleeptimeout, setTimeout);

}


static display_t mDraw()
{
	if(menuData.selected == 0)
	{
		char buff[4];
		sprintf_P(buff, PSTR("%hhuS"), (unsigned char)(appConfig.sleepTimeout * 5));
		draw_string(buff, NOINVERT, 56, 40);
	}
	return DISPLAY_DONE;
}

