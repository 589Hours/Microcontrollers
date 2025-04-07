/*
 * opdracht2.c
 *
 * Created: 4/7/2025 4:05:21 PM
 *  Author: luukb
 */ 

static int i = 0;

#include <avr/io.h>
#include <avr/interrupt.h>


ISR( INT0_vect ) { 
	PORTA |= ~(1<<i);
	i++;
	if ( i > 7)
	{
		i = 0;
	}
	PORTA &= (1<<i);
}


ISR( INT1_vect ) { 
	PORTA |= ~(1<<i);
	i--;
	if ( i < 0)
	{
		i = 7;
	}
	PORTA &= (1<<i);
}

int main ( void ){
	//Init IO
	DDRA = 0xff;		//PORTD(7:4) output, PORTD(3:0) input
	
	//Init Interrupt hardware
	EICRA |= 0x0B;		// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x03;		// Enable INT1 & INT 0
	
	//Enable global interupt system
	//SREG = 0x80			// Of direct vai SREG of via wrapper
	sei();
	
	while (1){
	}
	
	return 1;
} 