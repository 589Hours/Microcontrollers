/*
 * opdracht3.c
 *
 * Created: 28-2-2025 12:51:15
 *  Author: rikva
 */ 
#include <avr/io.h>
#include <stdbool.h>

#define F_CPU 10e6
#include <util/delay.h>

void wait(int ms){
	for(int i=0; i<ms;i++){
		_delay_ms(1);
	}
}

int main(void)
{
	ADCSRA = 0b10000110; // adc setup, no free running, devision 64
	ADMUX = 0b01100011; // setup VCC-VREF met ADLAR = 1 (leftsided) met kanaal F3
	
	DDRF = 0x00;
	DDRD = 0xff; //all output
	
	/* Replace with your application code */
	while (1)
	{
		ADCSRA |= (1<<6); // start adc
		while ( ADCSRA & 0b01000000);
		PORTD = ADCH;
		wait(1000);
	}
}