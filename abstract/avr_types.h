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


 
template <typename T>
class avr_array_s
{
public:
	avr_array_s() : 
		_cnt(0)
	{
	}
	
	void append(T &item)
	{
		if (_cnt < AVRC_ARRAY_MAX_LENGTH)
		{
			_el[_cnt++] = item;
		}
	}
	
	avr_uint8_t count()
	{
		return _cnt;
	}
	
	const T at(avr_uint8_t index)
	{
#ifndef __AVRC_ARRAY_DONT_CONTROL_RANGE__
		if ((index >= 0) && (index < _cnt))
		{
			return _el[index];
		}
#else
		return _el[index];
#endif
	}

private:
	avr_uint8_t _cnt;
	T _el[AVRC_ARRAY_MAX_LENGTH];	
} ;

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

#endif // AVR_TYPES

