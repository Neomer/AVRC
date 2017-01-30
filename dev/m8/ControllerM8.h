#ifndef CONTROLLERM8
#define CONTROLLERM8

#include <avr/io.h>
#include <avr/iom8.h>
#include "../../abstract/Controller.h"
#include "MemoryM8.h"

class ControllerM8 : public  IController
{
public:
	void initPWM(avr_uint8_t pwm_num)
	{	
	}

	void update()
	{
		
	}	
	
	void initInterruptions()
	{
		sei();
	}
	
	avr_uint8_t getVectorINT0()
	{
		return 0;
	}

	avr_uint8_t getVectorINT1()
	{
		return 0;
	}

	avr_uint8_t getVectorINT2()
	{
		return 0;
	}

};


#endif // CONTROLLERM8

