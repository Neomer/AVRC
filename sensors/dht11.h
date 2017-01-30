#ifndef DHT11_H
#define DHT11_H

#include "../abstract/avr_types.h"
#include "../abstract/Controller.h"

class DHT11
{
public:
	DHT11(avr_bit_s port, IController * controller)
	{
		_port = port;
		_controller = controller;
	}

private:
	avr_bit_s _port;
	IController *_controller;
};

#endif // DHT11_H
