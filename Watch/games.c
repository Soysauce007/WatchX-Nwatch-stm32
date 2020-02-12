/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */

#include "common.h"

#define OPTION_COUNT	getItemCount()

static prev_menu_s prevMenuData;

static void mSelect(void);
static void itemLoader(byte);

static uint8_t getItemCount()
{
  uint8_t cnt = 0;
#if COMPILE_GAME1
  ++cnt;
#endif
#if COMPILE_GAME2
  ++cnt;
#endif
#if COMPILE_GAME3
  ++cnt;
#endif
  return cnt;
}

void mGamesOpen()
{
	setMenuInfo(OPTION_COUNT, MENU_TYPE_STR, PSTR(STR_GAMESMENU));
	setMenuFuncs(MENUFUNC_NEXT, mSelect, MENUFUNC_PREV, itemLoader);

	setPrevMenuOpen(&prevMenuData, mGamesOpen);
	
	beginAnimation2(NULL);
}

static void mSelect()
{
	setPrevMenuExit(&prevMenuData);
	doAction(true);
}

static void itemLoader(byte num)
{
	num = 0;
#if COMPILE_GAME1
	setMenuOption_P(num++, PSTR(GAME1_NAME), NULL, game1_start);
#endif
#if COMPILE_GAME2
	setMenuOption_P(num++, PSTR(GAME2_NAME), NULL, game2_start);
#endif
#if COMPILE_GAME3
	setMenuOption_P(num++, PSTR(GAME3_NAME), NULL, game3_start);
#endif
	addBackOption();
}
