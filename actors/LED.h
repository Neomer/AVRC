#ifndef LED_H
#define LED_H

#include "../abstract/Actor.h"

class LED : public IActor
{
public:
	LED(avr_bit_s pin, IController *controller) :
		IActor(pin, controller)
	{
		controller->setLow(_port._port, _pin._bit);
	}
	
	//����������� ��������� ���������
	void swap()
	{
		_controller->swapBit(_port._port, _pin._bit);
	}
	
	//�������� ���������
	inline void turnOn()
	{
		_controller->setHigh(_port._port, _pin._bit);
	}
	
	//��������� ���������
	inline void turnOff()
	{
		_controller->setLow(_port._port, _pin._bit);
	}
	
	//TRUE, ���� ��������
	avr_bit_t isLight()
	{
		return _controller->bitIsHigh(_port._pin, _pin._bit);
	}
	
	//TRUE, ���� ���������
	avr_bit_t isDark()
	{
		return _controller->bitIsHigh(_port._pin, _pin._bit);
	}
};

#endif // LED_H
