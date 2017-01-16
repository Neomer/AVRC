#ifndef CONTROLLERM8
#define CONTROLLERM8

#include <avr/io.h>
#include "../../Controller.h"
#include "MemoryM8.h"

class ControllerM8 : public  IController
{
public:
	void initPWM(avr_uint8_t pwm_num)
	{	
		switch (pwm_num)
		{
			case 0:
				return;
				
			case 1:
				
				break;
				
			case 2:
				break;
				
			default:
				return;
		}
	}
	
	
private:
};


#endif // CONTROLLERM8

