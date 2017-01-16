#ifndef BUTTONPULLUP
#define BUTTONPULLUP

/*************************************************** 
 * ButtonPullUp.h
 * 
 * Класс для работы с кнопкой замыкающей на землю
 ***************************************************/

#include "../abstract/Sensor.h"

class ButtonPullUp : public IDigitalSensor
{
public:
	ButtonPullUp(avr_bit_s pin, IController *controller) : 
		IDigitalSensor(pin, controller)
	{
		_controller->writeBit(pin._offset, pin._bit, 1);
	}
	
protected:
	void update()
	{
		
	}
};

#endif // BUTTONPULLUP

