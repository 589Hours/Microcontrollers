/*
 * seven_segment.c
 *
 * Created: 4/7/2025 3:40:01 PM
 *  Author: luukb
 */ 

#define F_CPU 10e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "seven_segment.h"

int count = 0;

const int SHOW[53] = { // opdracht 4
	0b00000100, 0b01000000, 0b00000010, 0b00000001, 0b00100000, 0b01000000, 0b00010000, 0b01110111, 0b01110111, 0b01110111, // A
	0b00001000, 0b00000100, 0b01000000, 0b00000010, 0b00000001, 0b00100000, 0b01000000, 0b00010000,0b01111111,0b01111111,0b01111111, // B
	0b00000001,0b00100000,0b00010000,0b00001000,0b00111001,0b00111001,0b00111001, // C
	0b00001000,0b00000100,0b00000000,0b00000010,0b00000001,0b00100000,0b00010000,0b00111111,0b00111111,0b00111111, // D
	0b00000001,0b00100000,0b01000000,0b00010000,	0b00001000,	0b01111001,	0b01111001,	0b01111001, // E
	0b00000001,	0b00100000,	0b01000000,	0b00010000,	0b01110001,	0b01110001,	0b01110001 // F
};

// 7 seg
const int NUMBERS[17] = { // opdracht 3
	//DP gfe dcba
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
	0b01110111, // A
	0b01111111, // B
	0b00111001, // C
	0b00111111, // D
	0b01111001, // E
	0b01110001, // F
	0b11111001  // E. for error
};

void display(int digits){ //opdracht 3
	
	PORTB = NUMBERS[digits];
}

// Should return 1 on true and 0 on false
int checkIfOtherButtonIsPressed(int digit){ //opdracht 4
	if (PIND & digit)
	{
		count = 0;
		display(count);
		return 1;
	}
	return 0;
}
/*
ISR( INT0_vect ) { //opdracht 4
	if (checkIfOtherButtonIsPressed(0x02))
	{
		return;
	}
	
	if (count > 0)
	{
		count--;
	}
	display(count);
}


ISR( INT1_vect ) { //opdracht 4
	
	if (checkIfOtherButtonIsPressed(0x1))
	{
		return;
	}
	
	if (count > 15){
		display(16);
		} else {
		count++;
	}
	
	display(count);
}
*/

void wait( int ms ) { // opdracht 3
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}