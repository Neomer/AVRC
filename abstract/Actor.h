#ifndef ACTOR_H
#define ACTOR_H

#include "avr_types.h"
#include "Controller.h"

class IActor: public IObject
{
public:
	IActor(avr_bit_s pin, IController *controller)
	{
		_pin = pin;
		_controller = controller;
		_controller->setPinDirection(pin, IController::Write);
		_controller->registerObject(this);
	}

protected:
	avr_bit_s _pin;
	IController *_controller;
};

#endif // ACTOR_H
