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
		IDigitalSensor(pin, controller),
		_pressed(false),
		_released(true)
	{
		_controller->setHigh(_port._port, _pin._bit);
		_controller->setLow(_port._ddr, pin._bit);
	}
	
	//True, если кнопка нажата
	avr_bit_t isPressed()
	{
		return _controller->bitIsLow(_pin);
	}
	
	// True, если кнопка отжата
	avr_bit_t isReleased()
	{
		return _controller->bitIsHigh(_pin);
	}
	
	// True, если кнопка была нажата с момента прошлого вызова этой функциями
	avr_bit_t onPress()
	{
		avr_bit_t ret = _pressed;
		_pressed = false;
		return ret;
	}
	
private:
	avr_bit_t _pressed, _released;

#ifndef __AVRC_OBJECT_DONT_AUTOUPDATE__
protected:
#else
public:
#endif
	void update()
	{
		if (isPressed())
		{
			if (_released)
			{
				_pressed = true;
				_released = false;
			}
		}
		else
		{
			_released = true;
		}
	}
};

#endif // BUTTONPULLUP

