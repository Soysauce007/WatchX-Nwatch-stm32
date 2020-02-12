/*
 * Project: Lightweight millisecond tracking library
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/millisecond-tracking-library-for-avr/
 */

#ifndef MILLIS_H_
#define MILLIS_H_

#include "typedefs.h"


#define millis() millis_get()

extern  millis_t milliseconds;

millis_t millis_get(void);

void millis_init(void);

#endif /* MILLIS_H_ */
