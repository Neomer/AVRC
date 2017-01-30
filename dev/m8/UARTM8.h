#ifndef UARTM8_H
#define UARTM8_H


#ifdef __AVRC_INTERRUPTION_ENABLED__


#include "../../abstract/UART.h"

class UART : public iUART
{
public:
	UART(IController *controller) : 
		iUART(controller)
	{
	}
	
protected:
	void setupPort()
	{
	}
};


#endif

#endif // UARTM8_H
