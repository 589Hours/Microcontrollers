/*
 * Eindopdracht.c
 *
 * Created: 20-3-2025 10:53:02
 * Author : rikva
 */ 

#define F_CPU 10e6

#include <math.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "i2c.h"

#define RISING_EDGE 1
#define FALLING_EDGE 0
#define MAX_DISTANCE 150

volatile double pulse_width = 0;
volatile int previous_edge = FALLING_EDGE;

void i2c_write_ultrasonic_distance(uint8_t distance);

void wait(int ms) {
	for(int i = 0; i < ms; i++) {
		_delay_ms(1);
	}
}

void timer1_init(){
	TCCR1A = 0x00; //normal mode
	TCCR1B = 0b00000011; // prescaler 64
}

// Distance kan berekend worden door: (high level time x velocity of sound = 340 m/s) / 2
double get_distance() {
	// 340 m/s -> 340 000 cm / 1 000 000 us -> 0.034 cm/us --> 0.3 mm/us
	return (pulse_width * 0.0343) / 2;
}

void trigger_ultrasonic() {
	// first low, then atleast 10 micro sec high signal for measure signal, return to low
	PORTE &= ~(1<<5);
	_delay_us(2);
	PORTE |= (1<<5);
	_delay_us(10);
	PORTE &= ~(1<<5);
}

ISR(INT4_vect) {
	switch (previous_edge) {
		case FALLING_EDGE:
			TCNT1 = 0; //reset when going to rising edge
			previous_edge = RISING_EDGE;
		break;
		case RISING_EDGE:
			// Capture the time difference - times 6.4 because 1 tick is 6.4 us
			pulse_width = (double) TCNT1 * 6.4;
			previous_edge = FALLING_EDGE;
			double distance = get_distance();
			
			clear();
			if (distance > MAX_DISTANCE) {
				display_text("out of range");
				return;
			}
			lcd_write_double(distance);
			i2c_write_ultrasonic_distance((uint8_t) round(get_distance()));
		break;
	}
}

void i2c_write_ultrasonic_distance(uint8_t distance) {
	i2c_start();
	i2c_write_address();
	i2c_write(distance);
	i2c_stop();
}

void i2c_demo() {
	i2c_start();
	i2c_write((uint8_t) SLAVE_ADDR << 1); //end bit has to be 0 for write, the rest is for the address
	i2c_write((uint8_t) 155);
	i2c_stop();
}

int main(void)
{
	//setup i2c
	i2c_init();
	
	// Setup lcd
	lcd_init();
	
	// timer init
	timer1_init();
	
	// Setup interrupts
	DDRE &= ~(1<<4); // set E4 to input for ultrasonic
	DDRE |= (1<<5); // setup E5 pin for output/start signal ultrasonic sensor
	EICRB |= 1; // last 2 bits 0 1 for interrupt on ANY logical change
	EIMSK |= (1<<4); // set interrupt on E4 active
	sei(); //enable interrupt
	
    /* Replace with your application code */
    while (1) 
    {
		trigger_ultrasonic(); // Trigger ultrasonic
		wait(500);
		
		/* I2C test bit
		clear();
		display_text("demo start");
		i2c_demo();
		wait(2000);
		clear();
		display_text("demo done");
		wait(2000);
		*/
    }
}
