/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */

#ifndef UTIL_H_
#define UTIL_H_



//#define BLACK	0
//#define WHITE	1
//#define INVERT	2
#define NOINVERT	false
#define INVERT		true

#define F_CPU  168000000
#define sprintf_P  sprintf
#define PSTR(a)  a

#define max(a,b) \
({ __typeof__ (a) _a = (a); \
	__typeof__ (b) _b = (b); \
_a > _b ? _a : _b; })

#define UNUSED(var) ((void)(var))
	
#define EMPTY_FUNC	((void)(0))

#define noinline __attribute__ ((__noinline__))

#define M_PI 3.14

// Quick and easy macro for a for loop
#define LOOP(count, var) for(byte var=0;var<count;var++)

// Reverse loop sometimes produces smaller/faster code
#define LOOPR(count, var) for(byte var=count;var--;)

#define CONCAT(a, b) a ## b

#define PROGMEM   //卵用，在Arduino中间需要将数据保存在flash中间，但是stm32应该直接储存在flash
#define EEMEM
#define FRAME_WIDTH			128
#define FRAME_HEIGHT		64
#define FRAME_BUFFER_SIZE	((FRAME_WIDTH * FRAME_HEIGHT) / 8)





// http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&t=60729&postdays=0&postorder=asc&start=20
#define BITS7(arg, bits...) ((arg>=0)? (1 << (arg)):0)
#define BITS6(arg, bits...) ((arg>=0)? (1 << (arg)):0) | \
BITS7(bits, -1)
#define BITS5(arg, bits...) ((arg>=0)? (1 << (arg)):0) | \
BITS6(bits, -1)
#define BITS4(arg, bits...) ((arg>=0)? (1 << (arg)):0) | \
BITS5(bits, -1)
#define BITS3(arg, bits...) ((arg>=0)? (1 << (arg)):0) | \
BITS4(bits, -1)
#define BITS2(arg, bits...) ((arg>=0)? (1 << (arg)):0) | \
BITS3(bits, -1)
#define BITS1(arg, bits...) ((arg>=0)? (1 << (arg)):0) | \
BITS2(bits, -1)
#define BITS0(arg, bits...) ((arg>=0)? (1 << (arg)):0) | \
BITS1(bits, -1)

#define SET_BITS(var, bits...)   var |=   BITS0(bits, -1)
#define CLEAR_BITS(var, bits...) var &= ~(BITS0(bits, -1))
#define LOAD_BITS(var, bits...)  var =    BITS0(bits, -1)



#endif /* UTIL_H_ */
