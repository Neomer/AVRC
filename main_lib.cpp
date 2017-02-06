#define F_CPU	8000000UL

#include "abstract/Controller.h"
#include "dev/m8/MemoryM8.h"
#include "actors/LED.h"
#include "sensors/dht11.h"


#include <avr/iom8.h>
#include "stdlib.h"
#include "abstract/Queue.h"

static QUEUE(30) uart_rx;
static QUEUE(30) uart_tx;

ISR(USART_RXC_vect)
{
	QUEUE_ADD(uart_rx, UDR);
}

ISR(USART_UDRE_vect)
{
	UDR = QUEUE_GET(uart_tx);
}

int main()
{
	while (1) 
	{
	}
}
