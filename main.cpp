#define F_CPU	8000000UL

#include <avr/io.h>
#include <avr/iom8.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "MemMath.h"
#include "abstract/uart.h"
#include "abstract/Queue.h"



int main()
{
	uart_init(UART_BAUD_8MHz_9600);
	while (1)
	{
		uart_send_char(uart_read_char() + 1);
	}
}
