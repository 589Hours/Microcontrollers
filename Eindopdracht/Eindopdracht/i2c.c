/*
 * i2c.c
 *
 * Created: 4-4-2025 17:25:03
 *  Author: rikva
 *	followed example: https://github.com/ExploreEmbedded/oneMicro-ATmega128/blob/master/Code%20Library/Tutorial%20Examples/00-libfiles/i2c.c
	for i2c
 */
#define F_CPU 10e6

#include <avr/io.h>
#include <util/delay.h>

#include "i2c.h"

void i2c_init() {
	DDRD &= ~((1 << PD0) | (1 << PD1)); // set SCL and SDA to input
	TWSR = 0x00; //prescaler to 1
	TWBR = 0x42; // SCL freq 42 so we get 100k hz 
	TWCR = 0x04; // start TWI module
}

void i2c_start() {
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT))); // wait for flag to be set, start condition has been send.
}

void i2c_stop() {
	TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWSTO));
	_delay_us(100); //wait for a short time
}

void i2c_write(uint8_t data) {
	TWDR = data; // set the data in the data register
	TWCR = ((1 << TWINT) | (1 << TWEN));
	while (!(TWCR & (1 << TWINT)));
}

void i2c_write_address() {
	i2c_write(((uint8_t) SLAVE_ADDR << 1));
}