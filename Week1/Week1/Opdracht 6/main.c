/*
 * main.c
 *
 * Created: 4/7/2025 5:14:28 PM
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


int main (void)
{
	int ms = 1000;
	DDRD = 0xff;
	
	DDRC = 0x00;
	PORTC = 0x01;
	
	while(1)
	{
		if (PINC & 0x01)
		{
			if(ms == 1000){
				ms = 250;
				} else {
				ms = 1000;
			}
		}
		
		PORTD = 0xff;
		wait(ms);
		PORTD = 0x0;
		wait(ms);
		
	}	
}