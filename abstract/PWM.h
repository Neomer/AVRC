#ifndef PWM_H
#define PWM_H

#ifdef __AVRC_PWM_ENABLED__

#include "avr_types.h"
#include "Object.h"
#include "Controller.h"

#define AVRC_PWM_8BIT_MAXVALUE		0xff
#define AVRC_PWM_16BIT_MAXVALUE		0xffff

class IPWM : public IObject
{
public:

	enum pwm_number
	{
		PWM_OC0,
		PWM_OC1,
		PWM_OC2
	};
	
	IPWM(pwm_number number, IController *controller)
	{
		_controller = controller;
		_pwm_number = number;
		_step = 1;
		
#ifndef __AVRC_OBJECT_DONT_AUTOUPDATE__
		controller->registerObject(this);
#endif		
	}
	
	// Устанавливаем настройки порта
	virtual void PWM_setupPort(pwm_number number) = 0;
		
	void setStep(avr_uint8_t step)
	{
		_step = step;
	}
	
	void up()
	{
		if (PWM_is8bit(_pwm_number))
		{
			avr_uint8_t ocr = _controller->readMem<avr_uint8_t>(_ocr);
			if (ocr + _step <= AVRC_PWM_8BIT_MAXVALUE)
			{
				_controller->writeMem<avr_uint8_t>(_ocr, ocr + _step);
			}
		}
		else
		{
			avr_uint16_t ocr = _controller->readMem<avr_uint16_t>(_ocr);
			if (ocr + _step <= AVRC_PWM_16BIT_MAXVALUE)
			{
				_controller->writeMem<avr_uint16_t>(_ocr, ocr + _step);
			}
		}
	}
	
	void down()
	{
		if (PWM_is8bit(_pwm_number))
		{
			avr_uint8_t ocr = _controller->readMem<avr_uint8_t>(_ocr);
			if (ocr  >= _step)
			{
				_controller->writeMem<avr_uint8_t>(_ocr, ocr - _step);
			}
		}
		else
		{
			avr_uint16_t ocr = _controller->readMem<avr_uint16_t>(_ocr);
			if (ocr  >= _step)
			{
				_controller->writeMem<avr_uint16_t>(_ocr, ocr - _step);
			}
		}
	}

	void upTo(avr_uint8_t step)
	{
		if (PWM_is8bit(_pwm_number))
		{
			avr_uint8_t ocr = _controller->readMem<avr_uint8_t>(_ocr);
			if (ocr + step <= AVRC_PWM_8BIT_MAXVALUE)
			{
				_controller->writeMem<avr_uint8_t>(_ocr, ocr + step);
			}
		}
		else
		{
			avr_uint16_t ocr = _controller->readMem<avr_uint16_t>(_ocr);
			if (ocr + step <= AVRC_PWM_16BIT_MAXVALUE)
			{
				_controller->writeMem<avr_uint16_t>(_ocr, ocr + step);
			}
		}
	}
	
	void downTo(avr_uint8_t step)
	{
		if (PWM_is8bit(_pwm_number))
		{
			avr_uint8_t ocr = _controller->readMem<avr_uint8_t>(_ocr);
			if (ocr  >= step)
			{
				_controller->writeMem<avr_uint8_t>(_ocr, ocr - step);
			}
		}
		else
		{
			avr_uint16_t ocr = _controller->readMem<avr_uint16_t>(_ocr);
			if (ocr  >= step)
			{
				_controller->writeMem<avr_uint16_t>(_ocr, ocr - step);
			}
		}
	}
	
	bool isMax()
	{
		if (PWM_is8bit(_pwm_number))
		{
			return _controller->readMem<avr_uint8_t>(_ocr) + _step >= AVRC_PWM_8BIT_MAXVALUE;
		}
		else
		{
			return _controller->readMem<avr_uint16_t>(_ocr) + _step >= AVRC_PWM_16BIT_MAXVALUE;
		}
		
	}
	
	bool isMin()
	{
		if (PWM_is8bit(_pwm_number))
		{
			return _controller->readMem<avr_uint8_t>(_ocr) - _step <= 0;
		}
		else
		{
			return _controller->readMem<avr_uint16_t>(_ocr) - _step <= 0;
		}
		
	}
	
	void update()
	{
#ifndef __AVRC_OBJECT_DONT_AUTOUPDATE__
		up();
#endif
	}	
	
	// Задержка при увеличении
	avr_float32_t delayUp()
	{
		return _delay_up;
	}
	
	// Установить задержку при увеличении
	void setDelayUp(avr_float32_t value)
	{
		_delay_up = value;
	}
	
	// Задержка при уменьшении
	avr_float32_t delayDown()
	{
		return _delay_down;
	}
	
	// Установить задержку при уменьшении 
	void setDelayDown(avr_float32_t value)
	{
		_delay_down = value;
	}
	
private:
	avr_uint8_t _step;
	pwm_number _pwm_number;
	avr_float32_t _delay_up, _delay_down;
	
protected:
	avr_mem_t _ocr;

	// Проверяет наличие ШИМ порта в текущей версии контроллера
	virtual bool PWM_available(pwm_number number) = 0;
	// Возвращает адрес OCR 
	virtual avr_mem_t PWM_getOCRaddress(pwm_number number) = 0;
	// TRUE, если ШИМ 8-битный
	virtual avr_bit_t PWM_is8bit(pwm_number number) = 0;
	
	IController *_controller;
};

#endif

#endif // PWM_H

