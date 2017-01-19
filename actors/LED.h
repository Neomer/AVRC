#ifndef LED_H
#define LED_H

#include "../abstract/Actor.h"
#include "../abstract/PWM.h"

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
	void turnOn(IPWM *pwm = 0)
	{
#ifdef __AVRC_PWM_ENABLED__
		if (pwm)
		{
			while (!pwm->isMax())
			{
				pwm->up();
				delay_ms(pwm->delayUp());
			}
		}
		else
		{
#endif
			_controller->setHigh(_port._port, _pin._bit);
#ifdef __AVRC_PWM_ENABLED__
		}
#endif
	}
	
	//��������� ���������
	void turnOff(IPWM *pwm = 0)
	{
#ifdef __AVRC_PWM_ENABLED__
		if (pwm)
		{
			while (!pwm->isMin())
			{
				pwm->down();
				delay_ms(pwm->delayDown());
			}
		}
		else
		{
#endif
			_controller->setLow(_port._port, _pin._bit);
#ifdef __AVRC_PWM_ENABLED__
		}
#endif
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
	
private:
	
protected:
	void update()
	{
		
	}
};

#endif // LED_H
