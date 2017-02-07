#ifndef LED_C
#define LED_C

#include "../MemMath.h"

#define led(DDR, BIT)					__setHigh(DDR, BIT)
#define led_turn_on(PORT, BIT)			__setHigh(PORT, BIT)
#define led_turn_off(PORT, BIT)			__setLow(PORT, BIT)

#endif // LED_C

