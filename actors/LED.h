#ifndef LED_H
#define LED_H

#include "../abstract/Actor.h"

class LED : public IActor
{
public:
	LED(avr_bit_s pin, IController *controller) :
		IActor(pin, controller)
	{
		controller->setLow(pin);
	}
	
	//Переключает состояние светодида
	void swap()
	{
		_controller->swapBit(_pin._offset, _pin._bit);
	}
	
	//Включает светодиод
	void turnOn()
	{
		_controller->setHigh(_pin);
	}
	
	//Выключает светодиод
	void turnOff()
	{
		_controller->setLow(_pin);
	}
	
	//TRUE, если включена
	avr_bit_t isLight()
	{
		return _controller->bitIsHigh(_pin);
	}
	
	//TRUE, если выключена
	avr_bit_t isDark()
	{
		return _controller->bitIsLow(_pin);
	}
	
private:
	
protected:
	void update()
	{
		
	}
};

#endif // LED_H
