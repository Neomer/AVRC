#ifndef ACTOR_H
#define ACTOR_H

#include "avr_types.h"
#include "Controller.h"

class IActor
{
public:
	IActor(avr_bit_s pin, IController *controller)
	{
		_pin = pin;
		_controller = controller;
		_port.setOffset(pin._offset);
		_controller->setPinDirection(_port._ddr, pin._bit, IController::Write);
	}


protected:
	avr_port_s _port;
	avr_bit_s _pin;
	IController *_controller;
};

#endif // ACTOR_H
