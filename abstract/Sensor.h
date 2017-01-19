#ifndef SENSOR
#define SENSOR

#include "avr_types.h"
#include "Controller.h"

#include <util/delay.h>

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

#define AVRC_ANALOGSENSOR_DEFAULT_HYSTERESIS	100
#define AVRC_ANALOGSENSOR_MAXVALUE				0x3FF
#define AVRC_ANALOGSENSOR_HALFVALUE	  		    511
#define	AVRC_ANALOGSENSOR_VOLTAGE				0.0048828125

class IAnalogSensor: public IObject
{
public:
	IAnalogSensor(avr_bit_s pin, IController *controller)
	{
		_pin = pin;
		_controller = controller;
		_port.setOffset(pin._offset);
		_hysteresis = AVRC_ANALOGSENSOR_DEFAULT_HYSTERESIS;
		
#ifndef __AVRC_OBJECT_DONT_AUTOUPDATE__
		_controller->registerObject(this);
#endif
		_controller->writeMem(iACSR, (avr_uint8_t)0x80);
		_controller->writeMem(iSFIOR, (avr_uint8_t)0x00);
		_controller->writeMem(iADCSR, (avr_uint8_t)0b10000101);
		_controller->writeMem(iADMUX, (avr_uint8_t)0b11000000 | pin._bit);
	}
	
	void setHysteresis(avr_uint8_t value)
	{
		_hysteresis = value;
	}

	//TRUE, если значение больше половины + гистерезис
	avr_bit_t half()
	{
		return read() >= AVRC_ANALOGSENSOR_HALFVALUE;
	}
	
	avr_float32_t voltage()
	{
		return read() * AVRC_ANALOGSENSOR_VOLTAGE;
	}
	
	avr_float32_t percent()
	{
		return read() / AVRC_ANALOGSENSOR_MAXVALUE;
	}

private:
	avr_uint8_t _hysteresis;

protected:
	volatile avr_uint16_t read()
	{
		_controller->writeMem(iADMUX, (avr_uint8_t) (_pin._bit | (_controller->readMem<avr_uint16_t>(iADMUX) & 0xF0)));
		_delay_ms(10);
		_controller->setHigh(iADCSR, 6);
		while (_controller->bitIsLow(iADCSR, 4));
		_controller->setHigh(iADCSR, 4);
		return _controller->readMem<avr_uint16_t>(iADCW);
	}

	avr_bit_s _pin;
	IController *_controller;
	avr_port_s _port;
};

#endif // SENSOR

