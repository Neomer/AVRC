#ifndef UART_H
#define UART_H

#ifdef __AVRC_INTERRUPTION_ENABLED__

#include "avr_types.h"
#include "Object.h"
#include "Controller.h"

extern "C" void USART_TX_vect(void) __attribute__ ((signal));
extern "C" void USART_RX_vect(void) __attribute__ ((signal));

class iUART
{
	friend void USART_TX_vect(void);
	friend void USART_RX_vect(void);
	
public:
	explicit iUART(IController *controller)
	{
		_controller = controller;
		_interface = this;
	}
	
	iUART *getInstance() { return _interface; }
	
	void send() {}
	void receive() {}

protected:
	virtual void setupPort() = 0;
	
	IController *_controller;
	avr_char_a _buffer_tx, _buffer_rx;
	static iUART *_interface;
	
};
	
#endif

#endif // UART_H
