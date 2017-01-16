#ifndef SENSOR
#define SENSOR

#include "avr_types.h"
#include "Controller.h"

class IDigitalSensor: public IObject
{
public:
	IDigitalSensor(avr_bit_s pin, IController *controller)
	{
		_pin = pin;
		_controller = controller;
		_controller->setPinDirection(pin, IController::Read);
		_controller->registerObject(this);
	}
	
	avr_bit_t state()
	{
		return _controller->readBit(_pin);
	}
	
protected:
	avr_bit_s _pin;
	IController *_controller;
};

class IAnalogSensor
{
public:
	IAnalogSensor(avr_bit_s pin, IController *controller)
	{
		_pin = pin;
		_controller = controller;
	}
	
	avr_uint8_t read()
	{
		return 0;
	}
	
protected:
	virtual void update() = 0;

	avr_bit_s _pin;
	IController *_controller;
};

#endif // SENSOR

