/*
 * main.c
 *
 * Created: 4/7/2025 5:09:23 PM
 *  Author: luukb
 */ 

#define F_CPU 10e6
#include <avr/io.h>
#include <util/delay.h>

typedef struct {
	unsigned char actieveLEDS;
	unsigned int delay;
	} PATTERN;
	
PATTERN pattern [] = {
	{0x00, 100},{0x01, 100}, {0x03, 100}, {0x07, 100}, {0x0F, 100}, {0x1F, 100}, {0x3F, 100}, {0x7F, 100}, {0xFF, 100}, 
	{0xFE, 100}, {0xFC, 100}, {0xF8, 100}, {0xF0, 100}, {0xE0, 100}, {0xC0, 100}, {0x80, 100}, {0x00, 100},
	{0xA5, 125}, {0x5A, 125},
	{0xA5, 125}, {0x5A, 125},
	{0xA5, 125}, {0x5A, 125},
	{0xFE, 100}, {0xFC, 100}, {0xF8, 100}, {0xF0, 100}, {0xE0, 100}, {0xC0, 100}, {0x80, 100}, {0x00, 100},
	{0x00, 100},{0x01, 100}, {0x03, 100}, {0x07, 100}, {0x0F, 100}, {0x1F, 100}, {0x3F, 100}, {0x7F, 100}, {0xFF, 100},
	{0x00, 100}
};

void wait(int ms)
{
	for (int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}

int main( void )
{
	DDRA = 0xff;
	
	while(1)
	{
		int index = 0;
		
		while(pattern[index].delay != 0){
			//Write data to PORTA
			PORTA = pattern[index].actieveLEDS;
			//wait
			wait(pattern[index].delay);
			//increment for next round
			index++;
		}
	}
}