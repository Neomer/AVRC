#ifndef PWMM8_H
#define PWMM8_H

#include "../../abstract/PWM.h"
#include "MemoryM8.h"

class PWMM8 : public IPWM
{
public:
	PWMM8(IPWM::pwm_number number, IController *controller) :
		IPWM(number, controller)
	{
		
	}
	
protected:
	// Проверяет наличие ШИМ порта в текущей версии контроллера
	bool PWM_available(pwm_number number)
	{
		if (number == IPWM::PWM_OC0)
			return false;
		
		return true;
	}

	// Возвращает адрес OCR 
	avr_mem_t PWM_getOCRaddress(pwm_number number)
	{
		switch (number) {
			case IPWM::PWM_OC1:
				return iOCR1A;
				break;
				
			default:
				return iOCR2;
				break;
		}
	}

	// TRUE, если ШИМ 8-битный
	avr_bit_t PWM_is8bit(pwm_number number)
	{
		if (number == IPWM::PWM_OC1)
			return false;
		
		return true;
	}

public:
	// Устанавливает настройки порта
	void PWM_setupPort(pwm_number number)
	{
		if (!PWM_available(number))
		{
			return;
		}

		switch (number)
		{
			case  IPWM::PWM_OC0:
			return;
			
			case IPWM::PWM_OC1:
//				TCCR1A |= (1 << COM1A1) | (1 << WGM11);
//				TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS10);
//				TCNT1 = 0x00;
//				ICR1 = 0xFF;
//				OCR1A = 0x00;
				break;
				
			case IPWM::PWM_OC2:
				_controller->setHigh(iDDRB, 3);
				_controller->writeMem<avr_uint8_t>(iTCCR2, 0b01101001);
				_controller->writeMem<avr_uint8_t>(iTCNT2, 0);
				_controller->writeMem<avr_uint8_t>(iOCR2, 0);
				break;
		}
		_ocr = PWM_getOCRaddress(number);
	}	
};

#endif // PWMM8_H
