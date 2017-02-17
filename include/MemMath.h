#ifndef MEMMATH
#define MEMMATH

#define bitIsHigh(address, bit)		(address & (1 << bit))
#define bitIsLow(address, bit)		(address & (1 << bit)) == 0

#define setHigh(address, bit)		address |= 1 << bit
#define setLow(address, bit)		address &= ~(1 << bit)

#define  swapBit(address, bit)	address ^= (1<<(bit))

#define  waitHigh(address, bit)	while (bitIsLow(address, bit));
#define  waitLow(address, bit)	while (bitIsHigh(address, bit));

#endif // MEMMATH

