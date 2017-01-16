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
	
	void setPinDirection(avr_bit_s bit, PortDirection direction)
	{
		writeBit(bit._offset, bit._bit, direction);
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
	
	avr_bit_t readBit(avr_bit_s &bit)
	{
		avr_int8_t * link = (avr_int8_t *) bit._offset;

		return (((*link) & (1 << bit._bit)) >> bit._bit);
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
		
	avr_uint8_t * link(avr_mem_t address)
	{
		return (avr_uint8_t *) address;
	}
	
	avr_int32_t exec()
	{
		while (1) 
		{
			update();
		}
	}
	
	virtual void initPWM(avr_uint8_t pwm_num) = 0;
	
protected:
	virtual void update();
	
	
private:
};

#endif // CONTROLLER

