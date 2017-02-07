#ifndef NRF24L01_H
#define NRF24L01_H

#ifndef SPI_CE
	#error "NRF24 needs CE and IRQ defines!"
	#define SPI_CE				0
	#define SPI_PIN_CE			0
	#define SPI_PORT_CE			0
	#define SPI_DDR_CE			0

	#define SPI_IRQ				0
	#define SPI_PIN_IRQ			0
	#define SPI_PORT_IRQ		0
	#define SPI_DDR_IRQ			0
#endif

#define nrf24_ce_low		__setLow(SPI_PORT_CE, SPI_CE)
#define nrf24_ce_high		__setHigh(SPI_PORT_CE, SPI_CE)
#define nrf24_irq			__bitIsHigh(SPI_PORT_IRQ, SPI_IRQ)


/*регистр STATUS*/
#define NRF24_STATUS          0x07
#define NRF24_RX_DR           6 /*прерывание: данные получены. Для сброса записать 1.*/
#define NRF24_TX_DS           5 /*прерывание: данные переданы. Для сброса записать 1.*/
#define NRF24_MAX_RT          4 /*прерывание: данные не переданы. Для сброса записать 1.*/
#define NRF24_RX_P_NO2        3
#define NRF24_RX_P_NO1        2
#define NRF24_RX_P_NO0        1
#define NRF24_TX_FULL0        0 /*флаг переполнения TX FIFO буфера передачи. 1-переполнен, 0-есть еще место.*/

/*регистр CONFIG*/    //Конфигурационный регистр
#define NRF24_CONFIG          0x00
#define NRF24_MASK_RX_DR  6 //вкл/откл прерывание от бита RX_DR в рег. STATUS. 0-вкл, 1-выкл.
#define NRF24_MASK_TX_DS  5 //вкл/откл прерывание от бита TX_DS в рег. STATUS. 0-вкл, 1-выкл.
#define NRF24_MASK_MAX_RT 4 //вкл/откл прерывание от бита MAX_RT в рег. STATUS. 0-вкл, 1-выкл.
#define NRF24_EN_CRC      3 //включение CRC. По умолчанию вкл. если один из битов регистра EN_AA включен.
#define NRF24_CRCO        2 //режим CRC. 0-1 байт, 1-2 байта.
#define NRF24_PWR_UP      1 //1-POWER UP, 0-POWER DOWN, по умолчанию 0.
#define NRF24_PRIM_RX     0 //0-режим передачи, 1-режим приема.

#define NRF24_RX_PW_P0        0x11//указываем в нем из скольких байт будет состоять наше поле данных для отправки.

#if 1 //Описание команд
#define NRF24_R_REGISTER                      0x00 //читаем регистр
#define NRF24_W_REGISTER                      0x20 //пишем в регистр
#define NRF24_REGISTER_MASK					  0x1F
#define NRF24_R_RX_PAYLOAD                    0x61 //считывание из буфера принятых данных из космоса
#define NRF24_W_TX_PAYLOAD                    0xA0 //запись данных в буфер для отправки в космос
#define NRF24_FLUSH_TX                        0xE1 //очистка буфера отправки
#define NRF24_FLUSH_RX                        0xE2 //очистка буфера приема
#define NRF24_REUSE_TX_PL                     0xE3
#define NRF24_ACTIVATE                        0x50
#define NRF24_R_RX_PL_WID                     0x60
#define NRF24_W_ACK_PAYLOAD                   0xA8
#define NRF24_W_TX_PAYLOAD_NOACK              0x58
#define NRF24_NOP                             0xFF //команда заглушка, ничего не делает.
#define NRF24_RF_CH							  0x05
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../MemMath.h"
#include "../abstract/spi.h"

inline void nrf24_init();
inline void nrf24_config(uint8_t dataLength, uint8_t channel);
inline uint8_t nrf24_read_register(uint8_t address);
inline void nrf24_write_register(uint8_t address, uint8_t value);
inline void nrf24_prepare_tx();
inline void nrf24_prepare_rx();
inline void nrf24_send_char(uint8_t data);
inline bool nrf24_has_data(void);
inline void nrf24_config_register( uint8_t address, uint8_t data );
inline uint8_t nrf24_read_status();
inline void nrf24_send_data(uint8_t *data, uint8_t length);
inline void nrf24_read_char( uint8_t *buffer);
inline void nrf24_read_array( uint8_t *buffer, uint8_t length);


inline uint8_t nrf24_read_status()
{
	spi_ss_low;
	uint8_t ret = spi_fast_exchage(NRF24_NOP);
	spi_ss_high;
	return ret;
}

inline void nrf24_config_register( uint8_t address, uint8_t data )
{
	spi_ss_low;
	spi_fast_exchage(NRF24_W_REGISTER | (address & NRF24_REGISTER_MASK));
	spi_fast_exchage(data);
	spi_ss_high;
}

inline uint8_t nrf24_read_register(uint8_t address)
{
	spi_ss_low;
	spi_fast_exchage(NRF24_R_REGISTER | (address & NRF24_REGISTER_MASK));
	uint8_t ret = spi_read_byte();
	spi_ss_high;
	return ret;
}

inline void nrf24_write_register(uint8_t address, uint8_t value)
{
	spi_ss_low;
	spi_fast_exchage(NRF24_W_REGISTER | (address & NRF24_REGISTER_MASK));
	spi_write_byte(value);
	spi_ss_high;
}

inline void nrf24_prepare_tx()
{
	nrf24_write_register(NRF24_CONFIG, (1 << NRF24_PWR_UP) | (1 << NRF24_EN_CRC) | (1 << NRF24_PRIM_RX));
	_delay_us(135);
}

inline void nrf24_prepare_rx()
{
	nrf24_write_register(NRF24_CONFIG, (1 << NRF24_PWR_UP) | (1 << NRF24_EN_CRC) | (0 << NRF24_PRIM_RX));
	_delay_us(135);
}

inline void nrf24_send_char(uint8_t data)
{
	nrf24_ce_low;
	
	nrf24_prepare_tx();
	
	spi_ss_low;
	spi_fast_exchage(NRF24_FLUSH_TX);
	spi_ss_high;
	
	_delay_us(32);
	
	spi_ss_low;
	spi_fast_exchage(NRF24_W_TX_PAYLOAD);
	spi_write_byte(data);
	spi_ss_high;
	
	nrf24_ce_high;
}

inline void nrf24_send_array(uint8_t *data, uint8_t length)
{
	nrf24_ce_low;
	
	nrf24_prepare_tx();
	
	spi_ss_low;
	spi_fast_exchage(NRF24_FLUSH_TX);
	spi_ss_high;
	
	_delay_us(32);
	
	spi_ss_low;
	spi_fast_exchage(NRF24_W_TX_PAYLOAD);
	spi_write_data(data, length);
	spi_ss_high;
	
	nrf24_ce_high;
}

inline void nrf24_send_string(const char *data)
{
	nrf24_ce_low;
	
	nrf24_prepare_tx();
	
	spi_ss_low;
	spi_fast_exchage(NRF24_FLUSH_TX);
	spi_ss_high;
	
	_delay_us(32);
	
	spi_ss_low;
	spi_fast_exchage(NRF24_W_TX_PAYLOAD);
	spi_write_string(data);
	spi_ss_high;
	
	nrf24_ce_high;
}



inline bool nrf24_has_data( void )
{	
	return __bitIsHigh(nrf24_read_status(), NRF24_RX_DR);
}

inline void nrf24_init()
{
	spi_init_master();
	
	__setHigh(SPI_DDR_CE, SPI_CE);
	__setLow(SPI_DDR_IRQ, SPI_IRQ);
	
	nrf24_ce_low;
}

inline void nrf24_config(uint8_t dataLength, uint8_t channel)
{
	nrf24_write_register(NRF24_RF_CH, channel);
	nrf24_write_register(NRF24_RX_PW_P0, dataLength);
	
	nrf24_prepare_rx();
	nrf24_ce_high;
}

inline void nrf24_read_char( uint8_t *buffer)
{
	spi_ss_low;
    spi_fast_exchage( NRF24_R_RX_PAYLOAD );
	*buffer = spi_read_byte();
    spi_ss_high;
	nrf24_config_register(NRF24_STATUS, (1 << NRF24_RX_DR));
}

inline void nrf24_read_array( uint8_t *buffer, uint8_t length)
{
	spi_ss_low;
    spi_fast_exchage( NRF24_R_RX_PAYLOAD );
	spi_read_data(buffer, length);
    spi_ss_high;
	nrf24_config_register(NRF24_STATUS, (1 << NRF24_RX_DR));
}

#endif // NRF24L01_H
