/*
 * Week4.c
 *
 * Created: 28-2-2025 09:25:39
 * Author : rikva
 */ 

#include <avr/io.h>
#include <stdbool.h>

#define F_CPU 10e6
#include <util/delay.h>

//om een frequentie tussen de 50khz en 200khz te krijgen moeten wij de 10e6 (10 Mhz) delen door 50 t/m 200
//wij kiezen ervoor om ook de deling door 64 uit de tabel te doen

int main(void)
{
	ADCSRA = 0b11100110; // adc setup, free running, devision 64
	//ADMUX = 0b01100001; // setup VCC-VREF met ADLAR = 1 (leftsided) met kanaal F1
	ADMUX = 0b01000001; // setup VCC-VREF met ADLAR = 0 (rightsided) met kanaal F1
	
	DDRB = 0xff; //all output
	DDRD = 0xff; //all output
	
    /* Replace with your application code */
    while (1) 
    {
		PORTB = ADCL;
		PORTD = ADCH;
		_delay_ms(200);
    }
}

