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

#define nrf24_ce_low		setLow(SPI_PORT_CE, SPI_CE)
#define nrf24_ce_high		setHigh(SPI_PORT_CE, SPI_CE)
#define nrf24_irq			bitIsHigh(SPI_PIN_IRQ, SPI_IRQ)



//регистры
#define NRF24_REGISTER_CONFIG			0x00
#define		NRF24_MASK_RX_DR			6 //вкл/откл прерывание от бита RX_DR в рег. STATUS. 0-вкл, 1-выкл.
#define		NRF24_MASK_TX_DS			5 //вкл/откл прерывание от бита TX_DS в рег. STATUS. 0-вкл, 1-выкл.
#define		NRF24_MASK_MAX_RT			4 //вкл/откл прерывание от бита MAX_RT в рег. STATUS. 0-вкл, 1-выкл.
#define		NRF24_EN_CRC				3 //включение CRC. ѕо умолчанию вкл. если один из битов регистра EN_AA включен.
#define		NRF24_CRCO					2 //режим CRC. 0-1 байт, 1-2 байта.
#define		NRF24_PWR_UP			    1 //1-POWER UP, 0-POWER DOWN, по умолчанию 0.
#define		NRF24_PRIM_RX				0 //0-режим передачи, 1-режим приема.

#define NRF24_REGISTER_EN_AA			0x01
#define NRF24_REGISTER_EN_RXADDR		0x02  // Enabled RX Addresses
#define		NRF24_EN_PIPE_P0			0
#define		NRF24_EN_PIPE_P1			2
#define		NRF24_EN_PIPE_P2			4
#define		NRF24_EN_PIPE_P3			8
#define		NRF24_EN_PIPE_P4			16
#define		NRF24_EN_PIPE_P5			32
#define NRF24_REGISTER_SETUP_AW			0x03  // Setup of Address Widths (common for all data pipes)
#define		NRF24_AW_3					1
#define		NRF24_AW_4					2
#define		NRF24_AW_5					3
#define NRF24_REGISTER_SETUP_RETR		0x04  // Setup of Automatic Retransmission (переотправка в случае фейла)
#define		NRF24_AR_DELAY				4
#define		NRF24_AR_CNT				0
#define NRF24_REGISTER_RF_CH			0x05  // RF Channel
#define NRF24_REGISTER_RF_SETUP			0x06  // RF Setup Register
#define		NRF24_CONT_WAVE				7	  // Enables continuous carrier transmit when high.
#define		NRF24_RF_DR_LOW				5	  // Set RF Data Rate to 250kbps.
#define		NRF24_PLL_LOCK				4	  // Force PLL lock signal. Only used in test
#define		NRF24_RF_DR_HIGH			3	  // [RF_DR_LOW, RF_DR_HIGH]: С00Т Ц 1Mbps С01Т Ц 2Mbps С10Т Ц 250kbps С11Т Ц Reserved
#define		NRF24_RF_PWR				1	  // Set RF output power in TX mode 
											  //	'00' Ц  -18dBm 
											  //	'01' Ц  -12dBm 
											  //	'10' Ц    -6dBm 
											  //	'11' Ц     0dBm
#define		NRF24_RF_PWR_0db			0x03
#define		NRF24_RF_PWR_6db			0x02
#define		NRF24_RF_PWR_12db			0x01
#define		NRF24_RF_PWR_18db			0x00
#define		NRF24_RF_PWR_MASK			0x03

#define		NRF24_RF_DR_1MBPS			0x00
#define		NRF24_RF_DR_2MBPS			0x01
#define		NRF24_RF_DR_250KBPS			0x02

#define NRF24_REGISTER_STATUS			0x07
#define		NRF24_RX_DR					6 /*прерывание: данные получены. ƒл€ сброса записать 1.*/
#define		NRF24_TX_DS					5 /*прерывание: данные переданы. ƒл€ сброса записать 1.*/
#define		NRF24_MAX_RT				4 /*прерывание: данные не переданы. ƒл€ сброса записать 1.*/
#define		NRF24_CLEAR_INT				0xE0
#define		NRF24_RX_PIPE				1		// —мещение статуса буффера RX
#define		NRF24_RX_PIPE_MASK			0x0E	
#define		NRF24_RX_EMPTY				0x07	// RX пуст
#define		NRF24_TX_FULL0				0 /*флаг переполнени€ TX FIFO буфера передачи. 1-переполнен, 0-есть еще место.*/
#define NRF24_REGISTER_OBSERVE_TX		0x08
#define NRF24_PLOS_CNT_MASK				0xF0 // Count lost packets
#define NRF24_ARC_CNT_MASK				0x0F // Count retransmitted packets
#define NRF24_REGISTER_RPD				0x09
#define NRF24_REGISTER_RX_ADDR_P0		0x0A
#define NRF24_REGISTER_RX_ADDR_P1		0x0B
#define NRF24_REGISTER_RX_ADDR_P2		0x0C
#define NRF24_REGISTER_RX_ADDR_P3		0x0D
#define NRF24_REGISTER_RX_ADDR_P4		0x0E
#define NRF24_REGISTER_RX_ADDR_P5		0x0F
#define NRF24_REGISTER_TX_ADDR			0x10
#define NRF24_REGISTER_RX_PW_P0         0x11 // Number of bytes in RX payload in data pipe 0
#define NRF24_REGISTER_RX_PW_P1         0x12 // Number of bytes in RX payload in data pipe 1
#define NRF24_REGISTER_RX_PW_P2         0x13 // Number of bytes in RX payload in data pipe 2
#define NRF24_REGISTER_RX_PW_P3         0x14 // Number of bytes in RX payload in data pipe 3
#define NRF24_REGISTER_RX_PW_P4         0x15 // Number of bytes in RX payload in data pipe 4
#define NRF24_REGISTER_RX_PW_P5         0x16 // Number of bytes in RX payload in data pipe 5
#define NRF24_REGISTER_FIFO_STATUS		0x17 // FIFO Status Register
#define		NRF24_FIFO_STATUSTX_REUSE	6
#define		NRF24_FIFO_STATUSTX_FULL	5
#define		NRF24_FIFO_STATUSTX_EMPTY	4
#define		NRF24_FIFO_STATUSRX_FULL	1
#define		NRF24_FIFO_STATUSRX_EMPTY	0
#define NRF24_REGISTER_DYNPD			0x1C // Enable dynamic payload length
#define NRF24_DPL_P0					0
#define NRF24_DPL_P1					1
#define NRF24_DPL_P2					2
#define NRF24_DPL_P3					3
#define NRF24_DPL_P4					4
#define NRF24_DPL_P5					5
#define NRF24_REGISTER_FEATURE			0x1D // Feature Register
#define NRF24_EN_DPL					2	 // Enables Dynamic Payload Length
#define NRF24_EN_ACK_PAY				1    // Enables Payload with ACK
#define NRF24_EN_DYN_ACK				0	 // Enables the W_TX_PAYLOAD_NOACK command


#if 1 //ќписание команд
#define NRF24_R_REGISTER                      0x00 //читаем регистр
#define NRF24_W_REGISTER                      0x20 //пишем в регистр
#define NRF24_REGISTER_MASK					  0x1F
#define NRF24_R_RX_PAYLOAD                    0x61 //считывание из буфера прин€тых данных из космоса
#define NRF24_W_TX_PAYLOAD                    0xA0 //запись данных в буфер дл€ отправки в космос
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
#include "../interface/spi.h"
#include "../interface/uart.h"

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
inline void nrf24_set_retransmission_count(uint8_t delay, uint8_t count);
inline void nrf24_set_address_width(uint8_t length);
inline void nrf24_set_data_rate(uint8_t rate);
inline void nrf24_set_output_power(uint8_t power);
inline void nrf24_set_rx_enable(uint8_t pipes);
inline void nrf24_set_auto_ack(uint8_t pipes);
inline void nrf24_set_data_length(uint8_t pipe, uint8_t length);
inline void nrf24_set_channel(uint8_t channel);
inline void nrf24_clear_status();
inline void nrf24_flush_tx();
inline void nrf24_flush_rx();

inline uint8_t nrf24_read_status()
{
	spi_ss_low;
	_delay_ms(1000);
	uint8_t ret = spi_fast_exchage(NRF24_NOP);
	
	spi_ss_high;
	return ret;
}

uint8_t nrf24_read_register(uint8_t address)
{
	spi_ss_low;
	spi_fast_exchage(NRF24_R_REGISTER | (address & NRF24_REGISTER_MASK));
	uint8_t ret = spi_fast_exchage(NRF24_NOP);
	spi_ss_high;
	return ret;
}

inline void nrf24_write_register(uint8_t address, uint8_t value)
{
	spi_ss_low;
	spi_fast_exchage(NRF24_W_REGISTER | (address & NRF24_REGISTER_MASK));
	spi_fast_exchage(value);
	spi_ss_high;
}

inline void nrf24_prepare_tx()
{
	nrf24_write_register(NRF24_REGISTER_CONFIG, 
										(1 << NRF24_PWR_UP) | 
										(1 << NRF24_EN_CRC) | 
										(0 << NRF24_PRIM_RX) | 
										(1 << NRF24_MASK_TX_DS) | 
										(1 << NRF24_MASK_RX_DR) |
										(1 << NRF24_MASK_MAX_RT));
	nrf24_clear_status();
	nrf24_write_register(NRF24_REGISTER_STATUS, NRF24_CLEAR_INT);
	_delay_us(150);
}

inline void nrf24_prepare_rx()
{
	nrf24_write_register(NRF24_REGISTER_CONFIG, 
										(1 << NRF24_PWR_UP) | 
										(1 << NRF24_EN_CRC) | 
										(1 << NRF24_PRIM_RX) | 
										(1 << NRF24_MASK_TX_DS) | 
										(1 << NRF24_MASK_RX_DR) |
										(1 << NRF24_MASK_MAX_RT));
	nrf24_clear_status();
	nrf24_flush_rx();
	nrf24_ce_high;
	
	_delay_us(135);
}

inline void nrf24_clear_status()
{
	nrf24_write_register(NRF24_REGISTER_STATUS, NRF24_CLEAR_INT);
}

inline void nrf24_send_char(uint8_t data)
{
	nrf24_ce_low;
	
	nrf24_prepare_tx();
	nrf24_flush_tx();	
	
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
	nrf24_flush_tx();	
	
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
	nrf24_flush_tx();	
	
	_delay_us(32);
	
	spi_ss_low;
	spi_fast_exchage(NRF24_W_TX_PAYLOAD);
	spi_write_string(data);
	spi_ss_high;
	
	nrf24_ce_high;
}

inline uint8_t nrf24_read_char( void )
{
	spi_ss_low;
    uint8_t status = spi_fast_exchage( NRF24_R_RX_PAYLOAD );
	uint8_t ret = spi_fast_exchage(NRF24_NOP);
    spi_ss_high;
	return ret;
}

inline void nrf24_read_array( uint8_t *buffer, uint8_t length)
{
	spi_ss_low;
    spi_fast_exchage( NRF24_R_RX_PAYLOAD );
	spi_read_data(buffer, length);
    spi_ss_high;
}


inline bool nrf24_has_data( void )
{	
	uint8_t st = nrf24_read_status();
	return bitIsHigh(st, NRF24_RX_DR) || (((st & NRF24_RX_PIPE_MASK) >> NRF24_RX_PIPE) != NRF24_RX_EMPTY);
}

inline void nrf24_flush_tx()
{
	spi_ss_low;
	spi_fast_exchage(NRF24_FLUSH_TX);
	spi_ss_high;
}

inline void nrf24_flush_rx()
{
	spi_ss_low;
	spi_fast_exchage(NRF24_FLUSH_RX);
	spi_ss_high;
}

inline void nrf24_init()
{
	spi_init_master();
	
	setHigh(SPI_DDR_CE, SPI_CE);
	setLow(SPI_DDR_IRQ, SPI_IRQ);
	
	nrf24_ce_low;

	nrf24_set_rx_enable(NRF24_EN_PIPE_P0 | NRF24_EN_PIPE_P1 | NRF24_EN_PIPE_P2 | NRF24_EN_PIPE_P3 | NRF24_EN_PIPE_P4 | NRF24_EN_PIPE_P5);
	nrf24_set_auto_ack(NRF24_EN_PIPE_P0 | NRF24_EN_PIPE_P1 | NRF24_EN_PIPE_P2 | NRF24_EN_PIPE_P3 | NRF24_EN_PIPE_P4 | NRF24_EN_PIPE_P5);
	nrf24_set_data_rate(NRF24_RF_DR_1MBPS);
	nrf24_set_channel(74);
	nrf24_set_address_width(NRF24_AW_5);
	nrf24_set_retransmission_count(10, 5);
	
	nrf24_write_register(NRF24_REGISTER_STATUS, NRF24_RX_DR | NRF24_TX_DS | NRF24_MAX_RT);
	nrf24_write_register(NRF24_REGISTER_RX_ADDR_P0, 43);
	nrf24_write_register(NRF24_REGISTER_TX_ADDR, 43);
}

inline void nrf24_set_channel(uint8_t channel)
{
	nrf24_write_register(NRF24_REGISTER_RF_CH, channel);
	_delay_ms(5);
}

inline void nrf24_set_data_length(uint8_t pipe, uint8_t length)
{
	nrf24_write_register(NRF24_REGISTER_RX_PW_P0 + pipe, length);
	_delay_ms(5);
}

inline void nrf24_set_auto_ack(uint8_t pipes)
{
	nrf24_write_register(NRF24_REGISTER_EN_AA, pipes);
}

inline void nrf24_set_rx_enable(uint8_t pipes)
{
	nrf24_write_register(NRF24_REGISTER_EN_RXADDR, pipes);
}

inline void nrf24_set_output_power(uint8_t power)
{
	uint8_t rf = nrf24_read_register(NRF24_REGISTER_RF_SETUP);
	rf |= (power & NRF24_RF_PWR_MASK) << NRF24_RF_PWR;
	nrf24_write_register(NRF24_REGISTER_RF_SETUP, rf);
}

inline void nrf24_set_data_rate(uint8_t rate)
{
	uint8_t rf = nrf24_read_register(NRF24_REGISTER_RF_SETUP);
	rf |= (((rate & 0x02) >> 1) << NRF24_RF_DR_LOW) | ((rate & 0x01) << NRF24_RF_DR_HIGH);
	nrf24_write_register(NRF24_REGISTER_RF_SETUP, rf);
}


///
/// \brief nrf24_set_address_width Setup address width for all pipes
/// \param length Takes value (NRF24_AW_3, NRF24_AW_4, NRF24_AW_5).
///
inline void nrf24_set_address_width(uint8_t length)
{
	nrf24_write_register(NRF24_REGISTER_SETUP_AW, length);
}

///
/// \brief nrf24_set_retransmission_count Setup retransmission settings
/// \param delay Time of delay between retransmissions. max = 15. Res = 250us * (<delay> + 1)
/// \param count Count of retransmissons. max = 15;
///
inline void nrf24_set_retransmission_count(uint8_t delay, uint8_t count)
{
	nrf24_write_register(NRF24_REGISTER_SETUP_RETR, ((count & 0x0F) << NRF24_AR_CNT)  | ((delay & 0x0F) << NRF24_AR_DELAY));
}

inline void nrf24_set()
{
	
}


#endif // NRF24L01_H
