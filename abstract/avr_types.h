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

#endif // AVR_TYPES

