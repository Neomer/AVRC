#ifndef AVR_TYPES
#define AVR_TYPES

#define HIGH		1
#define LOW			0

typedef unsigned short		avr_mem_t;
typedef bool				avr_bit_t;
typedef unsigned char		avr_uint8_t;
typedef unsigned short		avr_uint16_t;
typedef unsigned int		avr_uint32_t;
typedef unsigned long long	avr_uint64_t;

typedef char		avr_int8_t;
typedef short		avr_int16_t;
typedef int			avr_int32_t;
typedef long long	avr_int64_t;

typedef float		avr_float32_t;
typedef double		avr_float64_t;

typedef class AVR_BIT 
{ 
public:
	
	AVR_BIT() 
	{
		_offset = 0;
		_bit = 0;
	}
	
	AVR_BIT(avr_mem_t offset, avr_uint8_t bit)
	{
		_offset = offset;
		_bit = bit;
	}

	avr_mem_t _offset; 
	avr_uint8_t _bit; 
} avr_bit_s;

#define AVRC_ARRAY_MAX_LENGTH	50


 
template <typename T, avr_uint8_t SIZE>
class avr_array_s
{
public:
	avr_array_s() : 
		_cnt(0)
	{
	}
	
	void clear()
	{
		_cnt = 0;
	}
	
	avr_bit_t isFull()
	{
		return _cnt >= SIZE;
	}
	
	avr_bit_t isEmpty()
	{
		return _cnt == 0;
	}
	
// 	void append(const T &item)
// 	{
// #ifndef __AVRC_ARRAY_DONT_CONTROL_RANGE__
// 		if (_cnt < AVRC_ARRAY_MAX_LENGTH)
// 		{
// 			_el[_cnt++] = item;
// 		}
// #else
// 		_el[_cnt++] = item;
// #endif
// 	}
	
	void append(T item)
	{
#ifndef __AVRC_ARRAY_DONT_CONTROL_RANGE__
		if (_cnt < SIZE)
		{
			_el[_cnt++] = item;
		}
#else
		_el[_cnt++] = item;
#endif
	}

	void append(avr_array_s<T, SIZE> &other)
	{
#ifndef __AVRC_ARRAY_DONT_CONTROL_RANGE__
		if (_cnt + other.count() < SIZE)
		{
			for (int i = 0; i < other.count(); i++)
			{
				append(other.at(i));
			}
		}
#else
		for (int i = 0; i < other.count(); i++)
		{
			append(other.at(i));
		}
#endif
	}
	
	avr_uint8_t count()
	{
		return _cnt;
	}
	
	const T at(avr_uint8_t index)
	{
#ifndef __AVRC_ARRAY_DONT_CONTROL_RANGE__
		if ((index >= 0) && (index < SIZE))
		{
			return _el[index];
		}
		return _el[SIZE - 1];
#else
		return _el[index];
#endif
	}

	void operator += (T item)
	{
		append(item);
	}

	void operator += (avr_array_s<T, SIZE> &other)
	{
		append(other);
	}
	
	void set(avr_uint8_t index, T value)
	{
#ifndef __AVRC_ARRAY_DONT_CONTROL_RANGE__
		if ((index >= 0) && (index < SIZE))
		{
			_el[index] = value;
		}
#else
		_el[index] = value;
#endif
	}
	
	avr_uint16_t summ(avr_uint8_t count)
	{
		avr_uint16_t ret = 0;
// 		avr_uint8_t idx = 0;
// 		while (count--)
// 		{
// 			ret += _el[idx++];
// 		}

		for (int idx = 0; idx < count; idx++)
			ret += _el[idx];
		return ret;
	}

private:
	avr_uint8_t _cnt;
	T _el[SIZE];	
} ;

typedef avr_array_s<avr_uint8_t, 5>  avr_char_a;

typedef class AVR_PORT
{
public:
	AVR_PORT()
	{
		_port = _ddr = _pin = 0;
	}

	AVR_PORT(avr_uint16_t offset)
	{
		_pin = offset;
		_ddr = offset + 1;
		_port = offset + 2;
	}
	
	void setOffset(avr_uint16_t offset)
	{
		_pin = offset;
		_ddr = offset + 1;
		_port = offset + 2;
	}
	
	avr_uint8_t _pin;
	avr_uint8_t _ddr;
	avr_uint8_t _port;
} avr_port_s;

#include <util/delay.h>

void delay_ms(uint16_t n) 
{
	while (n--) 
	{
		_delay_ms(1);
	}
}

avr_float32_t fromNF(avr_uint8_t natural, avr_uint8_t frac)
{
	return  natural + frac * 0.01;
}

// typedef class AVR_FLOAT16
// {
// public:
// 	AVR_FLOAT16(avr_int16_t value)
// 	{
// 		_value = value;
// 	}
// 	
// 	AVR_FLOAT16(avr_uint8_t natural, avr_uint8_t frac)
// 	{
// 		_value = 1 & (natural << 8) & frac;
// 	}
// 	
// 	operator avr_float32_t() 
// 	{
// 		avr_float32_t ret;
// 		ret = _value
// 	}
// 	
// 	operator avr_float64_t()
// 	{
// 		avr_float64_t ret;
// 	}
// 	
// private:
// 	avr_int8_t ;
// } avr_float16_s;
#endif // AVR_TYPES

