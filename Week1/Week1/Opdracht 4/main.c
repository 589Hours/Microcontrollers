/*
 * main.c
 *
 * Created: 4/7/2025 5:09:00 PM
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
	DDRA = 0xFF; // PORTA als output (voor de 8 LEDs)

	while (1)
	{
		for (int i = 0; i < 8; i++)
		{
			PORTA = 0b00000001 << i; // Shift LED één plek naar links
			wait(50);
		}
	}
}
