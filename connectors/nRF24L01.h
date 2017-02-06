#ifndef NRF24L01_H
#define NRF24L01_H

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
#endif

#include <abstract/spi.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <MemMath.h>
#include <util/delay.h>

inline uint8_t nrf24_read_register(uint8_t address)
{
	__setLow(__SPI_PORT__, __SPI_SS__);
	SPDR = address;
	while(__bitIsLow(SPSR, SPIF));
	if (address == NRF24_STATUS)
	{
		__setHigh(__SPI_PORT__, __SPI_SS__);
		return SPDR;
	}
	SPDR = NRF24_NOP;
	while(__bitIsLow(SPSR, SPIF));
	__setHigh(__SPI_PORT__, __SPI_SS__);
	return SPDR;
}

inline void nrf24_write_register(uint8_t address, uint8_t value)
{
	address |= NRF24_W_REGISTER;
	__setLow(__SPI_PORT__, __SPI_SS__);
	SPDR = address;
	__waitHigh(SPSR, SPIF);
	SPDR = value;
	__waitHigh(SPSR, SPIF);
	address = SPDR;
	__setHigh(__SPI_PORT__, __SPI_SS__);	
}

inline void nrf24_prepare_tx()
{
	nrf24_write_register(NRF24_CONFIG, (1 << NRF24_PWR_UP) | (1 << NRF24_EN_CRC) | (0 << NRF24_PRIM_RX));
	_delay_ms(2);
	nrf24_write_register(NRF24_CONFIG, (1 << NRF24_PWR_UP) | (1 << NRF24_EN_CRC) | (1 << NRF24_PRIM_RX));
	__setHigh(__SPI_PORT__, __SPI_CE__);
	_delay_us(135);
}

inline void nrf24_prepare_rx()
{
	__setLow(__SPI_PORT__, __SPI_CE__);
	nrf24_write_register(NRF24_CONFIG, (1 << NRF24_PWR_UP) | (1 << NRF24_EN_CRC) | (0 << NRF24_PRIM_RX));
	_delay_us(135);
	nrf24_write_register(NRF24_RX_PW_P0, 1);
}

inline void nrf24_send_char(uint8_t data)
{
	nrf24_write_register(NRF24_W_TX_PAYLOAD, data);
	nrf24_prepare_tx();
	__waitLow(PIND, 6);
	uint8_t status = nrf24_read_register(NRF24_STATUS);
	nrf24_write_register(NRF24_STATUS, status);
	nrf24_prepare_rx();
}

inline bool nrf24_has_data(uint8_t *buffer)
{
	if (__bitIsLow(PIND, 6))
	{
		uint8_t status = nrf24_read_register(NRF24_STATUS);
		nrf24_write_register(NRF24_STATUS, status);
		if (__bitIsHigh(status, NRF24_RX_DR))
		{
			*buffer = nrf24_read_register(NRF24_R_RX_PAYLOAD);
			return true;
		}
	}
	return false;
}

#endif // NRF24L01_H
