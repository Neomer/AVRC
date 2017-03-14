#ifndef I2C_SOFT
#define I2C_SOFT

#include <avr/io.h>
#include <util/delay.h>
#include <MemMath.h>
#include <interface/uart.h>

#ifndef I2C_PORT
	#warning "SOFTWARE I2C PORT PARAMETERS NOT SET! SETUP BY DEFAULT."
	#define I2C_PORT		PORTC
	#define I2C_DDR			DDRC
	#define I2C_PIN			PINC
	#define I2C_SCL			1
	#define I2C_SDA			0
// (1 / SPEED) * 1000000
	#define I2C_TIMEOUT		10			
#endif

#define i2c_delay			_delay_us(I2C_TIMEOUT)
#define i2c_delay_state		_delay_us(I2C_TIMEOUT << 1)

#define i2c_scl_rx			setLow(I2C_DDR, I2C_SCL)
#define i2c_scl_tx			setHigh(I2C_DDR, I2C_SCL)
#define i2c_scl_down		setLow(I2C_PORT, I2C_SCL)
#define i2c_scl_up			setHigh(I2C_PORT, I2C_SCL)

#define i2c_sda_rx			setLow(I2C_DDR, I2C_SDA)
#define i2c_sda_tx			setHigh(I2C_DDR, I2C_SDA)
#define i2c_sda_down		setLow(I2C_PORT, I2C_SDA)
#define i2c_sda_up			setHigh(I2C_PORT, I2C_SDA)


inline void i2csoft_init_master()
{
	i2c_sda_rx;
	i2c_scl_rx;
}

inline void i2csoft_start()
{
	i2c_sda_tx;
	i2c_sda_down;
	i2c_delay;
	
	i2c_scl_tx;
	i2c_scl_down;
	i2c_delay;
}

inline void i2csoft_stop()
{
	i2c_sda_tx;
    i2c_sda_down;
    i2c_delay;
	
    i2c_scl_rx;
    i2c_delay;
    i2c_sda_rx;
}

inline bool i2csoft_write_byte(uint8_t data)
{
	bool ret = true;
	
	for (int i = 8; i; i--)
	{
		if (!(data & 0x80))
		{
			i2c_sda_tx;
			i2c_sda_down;
			i2c_delay;
		}
		else
		{
			i2c_sda_rx;
		}
		i2c_scl_tx; 
	    i2c_scl_down;
	    i2c_delay;
	    data <<= 1; 
	    i2c_scl_rx;
	    i2c_delay_state;
	    i2c_scl_tx;
	    i2c_scl_down;
	    i2c_delay;
	}
	i2c_scl_rx;
    i2c_delay;
    i2c_sda_rx;
    if (bitIsHigh(I2C_PIN, I2C_SDA))
    { 
		ret = false;
    }
    i2c_delay; 
    i2c_scl_tx;
    i2c_scl_down;
	i2c_delay_state;
	
	return ret;
}

inline uint8_t i2csoft_read_byte(bool ack = true)
{
	uint8_t ret = 0;

	i2c_sda_rx; // настраиваем sda на чтение
	for (uint8_t i = 7; i >= 0; i--) // цикл приема бит
	{
		i2c_scl_tx;// выдаем такт на SCL
		i2c_scl_down;
		i2c_delay;
		i2c_scl_rx;
		i2c_delay;
		if (bitIsHigh(I2C_PIN, I2C_SDA))
		{ 
			setHigh(ret, i); // если считали единицу - устанавливаем соответствующий бит
		};
		i2c_delay;
		i2c_scl_tx;
		i2c_scl_down;
		i2c_delay;
	};
	if(ack==1)  //выдаем или не выдаем ACK на шину
	{
		i2c_sda_tx;
		i2c_sda_down;
	}
	else
	{
		i2c_sda_rx;
	};
	i2c_scl_tx;
	i2c_scl_down;
	i2c_delay;
	i2c_scl_rx;
	i2c_delay_state;
	i2c_scl_tx;
	i2c_scl_down;
	i2c_delay;
	
	return ret;
}

inline void i2csoft_write_array(uint8_t *data, uint8_t length)
{
	while (length--)
	{
		uart_send_char('>');
		uart_send_int(*data);
		i2csoft_write_byte(*(data++));
	}
}


#endif // I2C_SOFT

