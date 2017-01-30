#ifndef TIMER_H
#define TIMER_H

#include "Controller.h"

class iTimer8bit
{
public:
	enum TimerScaling
	{
		ScalingNone = 1,
		Scaling8 = 2,
		Scaling64 = 3,
		Scaling256 = 4,
		Scaling1024 = 5,
		ExternalSourceUp = 6,
		ExternalSourceDown = 7
	};

	enum TimerScalingEx
	{
		ScalingExNone = 1,
		ScalingEx8 = 2,
		ScalingEx32 = 3,
		ScalingEx64 = 4,
		ScalingEx128 = 5,
		ScalingEx256 = 6,
		ScalingEx1024 = 7,
	};

	iTimer8bit(avr_mem_t TCCR, 
		   avr_mem_t OCR, 
		   avr_mem_t TCNT,
		   IController *controller) :
		_tccr(TCCR),
		_ocr(OCR),
		_tcnt(TCNT)
	{
		_controller = controller;
	}
	
	// Установка значения регистра сравнения
	void setCompare(avr_uint8_t value) { _controller->writeMem<avr_uint8_t>(_ocr, value); }
	// Установка начального значения
	void setBegin(avr_uint8_t value) { _controller->writeMem<avr_uint8_t>(_tcnt, value); }
	// Возвращает значение счетного регистра
	avr_uint8_t getCounter() { return _controller->readMem<avr_uint8_t>(_tcnt); }
	// Останавливает таймер
	void stop() { _controller->andMask<avr_uint8_t>(_tccr, 0xF8); }
	// Устанавливает предделитель для таймера
	void setSourceScaling(TimerScaling value) { _controller->xorMask<avr_uint8_t>(_tccr, value); }
	void setSourceScalingEx(TimerScalingEx value) { _controller->xorMask<avr_uint8_t>(_tccr, value); }
	
private:
	
protected:
	IController *_controller;
	avr_mem_t _tccr,	// Регистр настроек
			  _ocr,		// Регистр сравнения
			  _tcnt;	// Счетный регистр
};




#endif // TIMER_H
