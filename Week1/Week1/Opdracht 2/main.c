/*
 * main.c
 *
 * Created: 4/7/2025 5:05:48 PM
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
	DDRD = 0xFF; // PORTD als output

	while (1)
	{
		PORTD = 0b01000000; // PORTD.6 aan
		wait(500);
		PORTD = 0b10000000; // PORTD.7 aan
		wait(500);
	}
}
