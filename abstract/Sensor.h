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
		_port.setOffset(pin._offset);
		_controller->setPinDirection(_port._ddr, pin._bit, IController::Read);
		
#ifndef __AVRC_OBJECT_DONT_AUTOUPDATE__
		_controller->registerObject(this);
#endif
	}
	
	avr_bit_t state()
	{
		return _controller->readBit(_pin);
	}
	
protected:
	avr_bit_s _pin;
	IController *_controller;
	avr_port_s _port;
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

	avr_bit_s _pin;
	IController *_controller;
};

#endif // SENSOR

