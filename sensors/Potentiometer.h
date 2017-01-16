#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "../abstract/Sensor.h"

class Potentiometer : public IAnalogSensor
{
public:
	Potentiometer(avr_bit_s pin, IController *controller) : 
		IAnalogSensor(pin, controller)
	{
		
	}
	
	
#ifndef __AVRC_OBJECT_DONT_AUTOUPDATE__
protected:
#else
public:
#endif
	void update()
	{
		
	}
};

#endif // POTENTIOMETER_H
