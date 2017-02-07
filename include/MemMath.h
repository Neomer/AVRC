#ifndef MEMMATH
#define MEMMATH

#define __bitIsHigh(address, bit)		(address & (1 << bit))
#define __bitIsLow(address, bit)		(address & (1 << bit)) == 0

#define __setHigh(address, bit)		address |= 1 << bit
#define __setLow(address, bit)		address &= ~(1 << bit)

#define  __swapBit(address, bit)	address ^= (1<<(bit))

#define  __waitHigh(address, bit)	while (__bitIsLow(address, bit));
#define  __waitLow(address, bit)	while (__bitIsHigh(address, bit));

#endif // MEMMATH

