#ifndef CONTROLLER
#define CONTROLLER

#include "avr_types.h"
#include "Object.h"

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

	void setPinDirection(avr_mem_t address, avr_int8_t bit, PortDirection direction)
	{
		writeBit(address, bit, direction);
	}

	template<typename T>
	void writeMem(avr_mem_t address, T value)
	{
		T * link = (T *) address;
		*link = value;
	}
	
	void writeBit(avr_mem_t address, avr_int8_t bit, avr_bit_t value)
	{
		volatile avr_int8_t * link = (avr_int8_t *) address;
		if (value)
		{
			*link |= 1 << bit;
		}
		else
		{
			*link &= ~(1 << bit);
		}
	}
	
	void setHigh(avr_mem_t address, avr_int8_t bit)
	{
		volatile avr_int8_t * link = (avr_int8_t *) address;
		*link |= 1 << bit;
	}
	
	void setHigh(avr_bit_s &pin)
	{
		volatile avr_int8_t * link = (avr_int8_t *) pin._offset;
		*link |= 1 << pin._bit;
	}
	
	void setLow(avr_mem_t address, avr_int8_t bit)
	{
		volatile avr_int8_t * link = (avr_int8_t *) address;
		*link &= ~(1 << bit);
	}
	
	void setLow(avr_bit_s &pin)
	{
		volatile avr_int8_t * link = (avr_int8_t *) pin._offset;
		*link &= ~(1 << pin._bit);
	}
	
	void swapBit(avr_mem_t address, avr_int8_t bit)
	{
		volatile avr_int8_t * link = (avr_int8_t *) address;

		*link ^= 1 << bit;
	}
	
	avr_bit_t readBit(avr_mem_t address, avr_int8_t bit)
	{
		volatile avr_int8_t * link = (avr_int8_t *) address;

		return (((*link) & (1 << bit)) >> bit);
	}
	
	avr_bit_t readBit(avr_bit_s &bit)
	{
		volatile avr_int8_t * link = (avr_int8_t *) bit._offset;

		return (((*link) & (1 << bit._bit)) >> bit._bit);
	}
	
	avr_bit_t maskBit(avr_mem_t address, avr_uint8_t mask)
	{
		volatile avr_int8_t * link = (avr_int8_t *) address;

		return (*link) & mask;
	}
	
	template<typename T>
	T readMem(avr_mem_t address)
	{
		volatile T * link = (T *) address;

		return *link;
	}
	
	avr_bit_t bitIsLow(avr_mem_t address, avr_uint8_t bit)
	{
		volatile avr_uint8_t * link = (avr_uint8_t *) address;
		return ((*link) & (1 << bit)) == 0;
	}

	avr_bit_t bitIsLow(avr_bit_s &pin)
	{
		volatile avr_uint8_t * link = (avr_uint8_t *) pin._offset;
		return ((*link) & (1 << pin._bit)) == 0;
	}
		
	avr_bit_t bitIsHigh(avr_mem_t address, avr_uint8_t bit)
	{
		volatile avr_uint8_t * link = (avr_uint8_t *) address;
		return ((*link) & (1 << bit)) != 0;
	}
		
	avr_bit_t bitIsHigh(avr_bit_s &pin)
	{
		avr_uint8_t * link = (avr_uint8_t *) pin._offset;
		return ((*link) & (1 << pin._bit)) != 0;
	}
	
	volatile avr_uint8_t * link(avr_mem_t address)
	{
		return (volatile avr_uint8_t *) address;
	}
	
	virtual void initPWM(avr_uint8_t pwm_num) = 0;

#ifndef __AVRC_OBJECT_DONT_AUTOUPDATE__
	void registerObject(IObject *obj)
	{
		_objects.append(obj);
	}
	

	void update()
	{
		for (int i = 0; i < _objects.count(); i++)
		{
			_objects.at(i)->update();
		}
	}
#endif
	
protected:

private:
#ifndef __AVRC_OBJECT_DONT_AUTOUPDATE__
	avr_array_s<IObject *> _objects;
#endif
};

#endif // CONTROLLER

