#ifndef LED_C
#define LED_C

#include "../MemMath.h"

#define led(DDR, BIT)					setHigh(DDR, BIT)
#define led_turn_on(PORT, BIT)			setHigh(PORT, BIT)
#define led_turn_off(PORT, BIT)			setLow(PORT, BIT)

#endif // LED_C

