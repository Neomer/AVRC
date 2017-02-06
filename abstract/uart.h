#ifndef UART_H
#define UART_H

#include <avr/io.h>

#define UART_READY_TO_SEND		UDRE
#define UART_READY_TO_READ		RXC
//bool uart_ready_read;

enum UART_Parity
{
	UART_Parity_None = 0,
	UART_Parity_Even = 2,
	UART_Parity_Odd  = 3
};

enum UART_StopBits
{
	UART_StopBits_1 = 0,
	UART_StopBits_2 = 1
};

//	FORMULA:  (F_CPU / ( baudRate * 16)) - 1;
#define UART_BAUD_8MHz_115200	3	 // ~3.34
#define UART_BAUD_8MHz_57600	8	 // ~7.68
#define UART_BAUD_8MHz_38400	12	 // ~12.02
#define UART_BAUD_8MHz_19200	25	 // ~25.04
#define UART_BAUD_8MHz_9600		51   // ~51.08
#define UART_BAUD_8MHz_4800		103  // ~103.16
#define UART_BAUD_8MHz_2400		207  // ~207.33

#define UART_BAUD_16MHz_115200		7	 // ~6.68
#define UART_BAUD_16MHz_57600		8	 // ~15.36
#define UART_BAUD_16MHz_38400		24	 // ~24.04
#define UART_BAUD_16MHz_19200		50	 // ~50.08
#define UART_BAUD_16MHz_9600		102  // ~102.16
#define UART_BAUD_16MHz_4800		206  // ~206.32
#define UART_BAUD_16MHz_2400		415  // ~414.66

inline void uart_init( uint16_t baudRate, 
				 uint8_t dataBits = 8, 
				 UART_Parity parity = UART_Parity_None, 
				 UART_StopBits stopBits = UART_StopBits_1)
{
	uint8_t  internalDataBits = ((dataBits - 5) & 3) << UCSZ0;
	uint8_t internalParity = (((uint8_t)parity) & 3) << UPM0;
	uint8_t internalStopBits = (((uint8_t)stopBits) & 1) << USBS;
	
	UBRRH = (baudRate & 0xFF00) >> 8;
	UBRRL = baudRate & 0x00FF;
	UCSRC = (0 << USBS) | (1 << URSEL) | internalDataBits | internalParity | internalStopBits; 
	UCSRB = (1 << RXEN) | (1 << TXEN);
}

inline void uart_send_char(char data)
{
	while (__bitIsLow(UCSRA, UART_READY_TO_SEND));
	UDR = data;
}

inline void uart_send_array(const char *data, uint8_t size)
{
	for (uint8_t p = 0 ; p < size; p++)
	{	
		while (__bitIsLow(UCSRA, UART_READY_TO_SEND));
		UDR = data[p];
	}
}

inline void uart_send_str(const char *data)
{
	for (uint8_t p = 0 ; data[p] != 0; p++)
	{	
		while (__bitIsLow(UCSRA, UART_READY_TO_SEND));
		UDR = data[p];
	}
}

inline void uart_send_int(int data)
{
	char buf[6];
	itoa(data, buf, 10);
	uart_send_str(buf);
}

inline char uart_read_char()
{
	while (__bitIsLow(UCSRA, RXC));
	return UDR;
}

#endif // UART_H

