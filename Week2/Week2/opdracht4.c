/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** lookup.c
**
** Beschrijving:	Ledpatroon op PORTD dmv table lookup (scheiding logica en data)    
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c switch.c
**					avr-gcc -g -mmcu=atmega128 -o lookup.elf lookup.o
**					avr-objcopy -O ihex lookup.elf lookup.hex 
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/
/*
#include <avr/io.h>
#include <avr/interrupt.h>
#include "seven_segment.h"


int main( void ) {
	DDRB = 0xff;					// PORTB all output 
	
	// Init Interrupt hardware
	EICRA |= 0x0B;			// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x03;			// Enable INT1 & INT0
	
	// Enable global interrupt system
	sei();
	
	while (1) {
		for (int i = 0; i < 54; i++)
		{
			PORTB = SHOW[i];
			wait(250);
			if (i == 53){
				i = 0;
			}
		}
	}

	return 1;
}
*/