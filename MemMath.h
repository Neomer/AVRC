#ifndef MEMMATH
#define MEMMATH

#define bitIsHigh(address, bit)		address & (1 << bit)
#define bitIsLow(address, bit)		address & (1 << bit) == 0

#define setHigh(address, bit)		address |= 1 << bit
#define setLow(address, bit)		address &= ~(1 << bit)

#endif // MEMMATH

