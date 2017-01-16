#ifndef CONTROLLER
#define CONTROLLER

#include "avr_types.h"

class IController
{
public:
	enum PortDirection
	{
		Read = 0,
		Write = 1
	};
	
	void setPinDirection(avr_mem_t port, avr_int8_t pin, PortDirection direction)
	{
		writeBit(port, pin, direction);
	}

	template<typename T>
	void writeMem(avr_mem_t address, T value)
	{
		T * link = (T *) address;
		*link = value;
	}
	
	void writeBit(avr_mem_t address, avr_int8_t bit, avr_bit_t value)
	{
		avr_int8_t * link = (avr_int8_t *) address;
		if (value)
		{
			*link |= 1 << bit;
		}
		else
		{
			* link &= ~(1 << bit);
		}
	}

	void swapBit(avr_mem_t address, avr_int8_t bit)
	{
		avr_int8_t * link = (avr_int8_t *) address;

		*link ^= 1 << bit;
	}
	
	avr_bit_t readBit(avr_mem_t address, avr_int8_t bit)
	{
		avr_int8_t * link = (avr_int8_t *) address;

		return (((*link) & (1 << bit)) >> bit);
	}
	
	avr_bit_t maskBit(avr_mem_t address, avr_uint8_t mask)
	{
		avr_int8_t * link = (avr_int8_t *) address;

		return (*link) & mask;
	}
	
	template<typename T>
	T readMem(avr_mem_t address)
	{
		T * link = (T *) address;

		return *link;
	}
	
	avr_bit_t bitIsLow(avr_mem_t address, avr_uint8_t bit)
	{
		avr_uint8_t * link = (avr_uint8_t *) address;
		return (*link) & (1 << bit) == 0;
	}
		
	avr_bit_t bitIsHigh(avr_mem_t address, avr_uint8_t bit)
	{
		avr_uint8_t * link = (avr_uint8_t *) address;
		return (*link) & (1 << bit) != 0;
	}
		
	avr_int8_t * link(avr_mem_t address)
	{
		return (avr_uint8_t *) address;
	}
	
	virtual void initPWM(avr_uint8_t pwm_num) = 0;
	
	
private:
};

#endif // CONTROLLER

