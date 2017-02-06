/*
DHT11 Library 0x01

copyright (c) Davide Gironi, 2011

Released under GPLv3.
Please refer to LICENSE file for licensing information.
*/


#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>

#include "dht11.h"

#define DHT11_ERROR 255

/*
 * get data from dht11
 */
uint8_t dht11_getdata(uint8_t select) {
	uint8_t bits[5];
	uint8_t i,j = 0;

	memset(bits, 0, sizeof(bits));

	//reset port
	DHT11_DDR |= (1<<DHT11_INPUTPIN); //output
	DHT11_PORT |= (1<<DHT11_INPUTPIN); //high
	_delay_ms(100);

	//send request
	DHT11_PORT &= ~(1<<DHT11_INPUTPIN); //low
	_delay_ms(18);
	DHT11_PORT |= (1<<DHT11_INPUTPIN); //high
	_delay_us(1);
	DHT11_DDR &= ~(1<<DHT11_INPUTPIN); //input
	_delay_us(39);

	//check start condition 1
	if((DHT11_PIN & (1<<DHT11_INPUTPIN))) {
		return DHT11_ERROR;
	}
	_delay_us(80);
	//check start condition 2
	if(!(DHT11_PIN & (1<<DHT11_INPUTPIN))) {
		return DHT11_ERROR;
	}
	_delay_us(80);

	//read the data
	for (j=0; j<5; j++) { //read 5 byte
		uint8_t result=0;
		for(i=0; i<8; i++) {//read every bit
			while(!(DHT11_PIN & (1<<DHT11_INPUTPIN))); //wait for an high input
			_delay_us(30);
			if(DHT11_PIN & (1<<DHT11_INPUTPIN)) //if input is high after 30 us, get result
				result |= (1<<(7-i));
			while(DHT11_PIN & (1<<DHT11_INPUTPIN)); //wait until input get low
		}
		bits[j] = result;
	}

	//reset port
	DHT11_DDR |= (1<<DHT11_INPUTPIN); //output
	DHT11_PORT |= (1<<DHT11_INPUTPIN); //low
	_delay_ms(100);

	//check checksum
	if (bits[0] + bits[1] + bits[2] + bits[3] == bits[4]) {
		if (select == 0) { //return temperature
			return(bits[2]);
		} else if(select == 1){ //return humidity
			return(bits[0]);
		}
	}

	return DHT11_ERROR;
}

/*
 * get temperature (0..50C)
 */
int8_t dht11_gettemperature() {
	uint8_t ret = dht11_getdata(0);
	if(ret == DHT11_ERROR)
		return -1;
	else
		return ret;
}

/*
 * get humidity (20..90%)
 */
int8_t dht11_gethumidity() {
	uint8_t ret = dht11_getdata(1);
	if(ret == DHT11_ERROR)
		return -1;
	else
		return ret;
}



