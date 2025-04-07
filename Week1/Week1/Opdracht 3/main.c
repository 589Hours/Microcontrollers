/*
 * main.c
 *
 * Created: 4/7/2025 5:07:19 PM
 *  Author: luukb
 */ 

#define F_CPU 10e6
#include <avr/io.h>
#include <util/delay.h>

void wait(int ms)
{
	for (int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}

int main(void)
{
	DDRD = 0xFF;  // PORTD als output (LED)
	DDRC = 0x00;  // PORTC als input (knop)
	PORTC = 0x01; // Pull-up resistor aan op PC0

	while (1)
	{
		if (!(PINC & 0x01)) // Knop ingedrukt (laag)
		{
			PORTD = 0x80; // PORTD.7 aan
			wait(500);
			PORTD = 0x00; // LED uit
			wait(500);
		}
		else
		{
			PORTD = 0x00; // LED blijft uit
		}
	}
}
