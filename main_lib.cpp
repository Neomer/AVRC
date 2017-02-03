#define F_CPU	8000000UL

#include "abstract/Controller.h"
#include "dev/m8/MemoryM8.h"
#include "actors/LED.h"
#include "sensors/dht11.h"

#define FIXPOINT_FRAC_MASK	0x7f
#define FIXPOINT_FRAC_BITS	7
#define FIXPOINT_INT_MASK	0xff80
#define FIXPOINT_INT_BITS	9

class fix_point_t
{
public:
	fix_point_t(uint8_t natural, uint8_t fractional)
	{
		_buf = ((natural << FIXPOINT_INT_BITS) & FIXPOINT_INT_MASK) | (fractional) & FIXPOINT_FRAC_BITS;
	}
	
	fix_point_t()
	{
		_buf = 0x00;
	}
	
	template<typename T>
	fix_point_t operator + (T &value)
	{
		uint8_t frac = (_buf & FIXPOINT_FRAC_MASK) + (value & FIXPOINT_FRAC_MASK);
		uint8_t nat = (_buf & FIXPOINT_INT_MASK) + (value & FIXPOINT_INT_MASK) + (frac - 100); 
		
		return fix_point_t(nat, frac);
	}
	
	template<typename T>
	fix_point_t operator + (T value)
	{
		uint8_t frac = (_buf & FIXPOINT_FRAC_MASK) + (value & FIXPOINT_FRAC_MASK);
		uint8_t nat = (_buf & FIXPOINT_INT_MASK) + (value & FIXPOINT_INT_MASK) + (frac - 100); 
		
		return fix_point_t(nat, frac);
	}
	
private:
	uint16_t _buf;
};


int main()
{
	IController c;
	//DHT11 dht(avr_bit_s(iPB, 0), &c);
	
	fix_point_t fp(1, 2);
	fp = fp + 3;
	
	while (1) 
	{
//		dht.read();
	}
}
