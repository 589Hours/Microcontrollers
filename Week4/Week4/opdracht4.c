/*
 * opdracht4.c
 *
 * Created: 28-2-2025 13:08:19
 *  Author: rikva
 */ 
#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>

#define F_CPU 10e6
#include <util/delay.h>
#include <avr/interrupt.h>

#include "lcd.h"

void wait(int ms){
	for(int i=0; i<ms;i++){
		_delay_ms(1);
	}
}

int main(void)
{
	ADCSRA = 0b10000110; // adc setup, no free running, devision 64
	ADMUX = 0b11100011; // setup 2.56V internal met ADLAR = 1 (leftsided) met kanaal F3, 8 bit
	
	DDRF = 0x00;
	DDRD = 0xff; //all output
	
	lcd_init();
	clear();
	sei();
	
	display_text("hallo");
	
	/* Replace with your application code */
	while (1)
	{
		ADCSRA |= (1<<6); // start adc
		while ( ADCSRA & 0b01000000);
		PORTD = ADCH;
		clear();
		lcd_write_integer(ADCH);
		wait(1000);
	}
}
