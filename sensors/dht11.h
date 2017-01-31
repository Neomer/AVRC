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
	
	avr_bit_t read()
	{
		avr_uint8_t data[5];
		
		_controller->setPinDirection(iDDRD, 6, IController::Write);
		_controller->setLow(iPORTD, 6);
		_delay_ms (50);
		_controller->setHigh(iPORTD, 6);
		_controller->setPinDirection(iDDRD, 6, IController::Read);
		_controller->waitForLow(iPIND, 6);
		while (_controller->bitIsLow(iPIND, 6));
		while (_controller->bitIsHigh(iPIND, 6));
		for (int b = 0; b < 5; b++)
		{
			for (int bit = 0; bit < 8; bit++)
			{
				while (_controller->bitIsLow(iPIND, 6));
				_delay_us (50);
				if (_controller->bitIsHigh(iPIND, 6));
				data[b] |= 1 << (7 - bit);
				while (_controller->bitIsHigh(iPIND, 6));
			}
		}
		_delay_us(70);
		_controller->setPinDirection(iDDRD, 6, IController::Write);
		_controller->setHigh(iPORTD, 6);
			
		if (data[0] + data[1] + data[2] + data[3] != data[4])
		{
			return false;
		}
			
		_humidity = data[0] + data[1] * 0.01,
		_temperature = data[2] + data[3] * 0.01;
		return true;
	}
	
	avr_float32_t temperature()	{ return _temperature; }
	avr_float32_t humidity() { return _humidity; }

private:
	avr_bit_s _port;
	IController *_controller;
	avr_float32_t _humidity, _temperature;
};

#endif // DHT11_H
