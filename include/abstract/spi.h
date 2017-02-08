#ifndef SPI_H
#define SPI_H

#include <avr/io.h>
#include <util/delay.h>
#include "../MemMath.h"

// DEFINES!
#ifndef SPI_MOSI
	#warning "You should define SPI pins first! SPI interface disabled!"
#else
#define AVRC_SPI

inline void spi_init_master( void );
inline void spi_init_slave( void );
inline void spi_write_byte( uint8_t data );
// Sends 1 byte of data and receive answer
inline uint8_t spi_fast_exchage( uint8_t data );
inline uint8_t spi_read_byte( void );
inline void spi_read_data( uint8_t *buffer, uint8_t length );
inline void spi_write_data( uint8_t *buffer, uint8_t length );
inline void spi_write_string( const char *data );

// Переводит порт в режим чтения/записи
#define spi_ss_low			__setLow(SPI_PORT, SPI_SS)
#define spi_ss_high			__setHigh(SPI_PORT, SPI_SS)
#define spi_wait_status		__waitHigh(SPSR, SPIF);


inline void spi_init_master( void )
{
	__setLow(SPI_DDR, SPI_MISO);
	SPI_DDR |= (1<<SPI_MOSI)|(1<<SPI_SCK)|(1<<SPI_SS);
	SPI_PORT |= (1<<SPI_MOSI)|(1<<SPI_SCK)|(1<<SPI_SS)|(1<<SPI_MISO);
	SPCR = (1<<SPE)|(0<<DORD)|(1<<MSTR)|(0<<CPOL)|(0<<CPHA)|(1<<SPR1)|(0<<SPR0);
	SPSR = (0<<SPI2X);
}

inline void spi_init_slave( void )
{
	SPI_DDR |= (1<<SPI_MOSI)|(1<<SPI_SCK)|(1<<SPI_SS)|(0<<SPI_MISO);
	SPI_PORT |= (1<<SPI_MOSI)|(1<<SPI_SCK)|(1<<SPI_SS)|(1<<SPI_MISO);
	SPCR = (1<<SPE)|(0<<DORD)|(1<<MSTR)|(0<<CPOL)|(0<<CPHA)|(1<<SPR1)|(0<<SPR0);
	SPSR = (0<<SPI2X);
}

inline void spi_write_byte( uint8_t data )
{
	SPDR = data;
	spi_wait_status;
}

inline uint8_t spi_exchange(uint8_t data)
{
	uint8_t reply = 0;
	for (int i=7; i>=0; i--) {
	  reply <<= 1;
	  __setLow(SPI_PORT, SPI_SCK);
	  if (data & (1<<i))
		  __setHigh(SPI_PORT, SPI_MOSI);
	  else
		  __setLow(SPI_PORT, SPI_MOSI);
	  __setHigh(SPI_PORT, SPI_SCK);
	  if (__bitIsHigh(SPI_PORT, SPI_MISO))
		reply |= 1;
	}
	return reply;

}

inline uint8_t spi_fast_exchage( uint8_t data )
{
	SPDR = data;
	spi_wait_status;
	_delay_ms(10);
	return SPDR;
}

inline uint8_t spi_read_byte( void )
{
	return SPDR;
}

inline void spi_read_data( uint8_t *buffer, uint8_t length )
{
	for (uint8_t i = 0; i < length; i++)
	{
		SPDR = buffer[i];
		spi_wait_status;
		buffer[i] = SPDR;
	}
}

inline void spi_write_data( uint8_t *buffer, uint8_t length )
{
	for (uint8_t i = 0; i < length; i++)
	{
		SPDR = buffer[i];
		spi_wait_status;
	}
}

inline void spi_write_string( const char *data )
{
	for (uint8_t i = 0; data[i] != 0; i++)
	{
		SPDR = data[i];
		spi_wait_status;
	}
}

#endif


#endif // SPI_H
