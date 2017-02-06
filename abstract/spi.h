#ifndef SPI_H
#define SPI_H

#include <avr/io.h>

#ifndef __SPI_MOSI__
	#define  __SPI_PORT__		0
	#define  __SPI_PIN__		0
	#define  __SPI_MOSI__		0
	#define  __SPI_SCK__		0
	#define  __SPI_SS__			0
	#define  __SPI_MISO__		0
	#define  __SPI_CE__			0
#endif

inline void spi_init_master( void )
{
   DDRB |= (1<<__SPI_MOSI__)|(1<<__SPI_SCK__)|(1<<__SPI_SS__)|(0<<__SPI_MISO__);
   PORTB |= (1<<__SPI_MOSI__)|(1<<__SPI_SCK__)|(1<<__SPI_SS__)|(1<<__SPI_MISO__);
   SPCR = (1<<SPE)|(0<<DORD)|(1<<MSTR)|(0<<CPOL)|(0<<CPHA)|(1<<SPR1)|(0<<SPR0);
   SPSR = (0<<SPI2X);
}

inline void spi_init_slave( void )
{
	DDRB |= (1<<__SPI_MOSI__)|(1<<__SPI_SCK__)|(1<<__SPI_SS__)|(0<<__SPI_MISO__);
	PORTB |= (1<<__SPI_MOSI__)|(1<<__SPI_SCK__)|(1<<__SPI_SS__)|(1<<__SPI_MISO__);
	SPCR = (1<<SPE)|(0<<DORD)|(1<<MSTR)|(0<<CPOL)|(0<<CPHA)|(1<<SPR1)|(0<<SPR0);
	SPSR = (0<<SPI2X);
}

inline void spi_write_byte( uint8_t data )
{
	PORTB &= ~(1<<__SPI_SS__);
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	PORTB |= (1<<__SPI_SS__);
}


inline uint8_t spi_read_byte( uint8_t data )
{
	uint8_t report;
	PORTB &= ~(1<<__SPI_SS__);
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	report = SPDR;
	PORTB |= (1<<__SPI_SS__);
	return report;
}

#endif // SPI_H
