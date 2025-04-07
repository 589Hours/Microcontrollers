

#include "spi.h"

#include <avr/io.h>

int main()
{
	// inilialize
	DDRB=0x01;					  	// Set PB0 pin as output for display select
	spi_masterInit();              	// Initialize spi module
	displayDriverInit();            // Initialize display chip

	
	wait(1000);
	
	writeNegLedDisplay(1234);		// opdracht 5B
	writeNegLedDisplay(-202);		// opdracht 5B
	
	
	writeLedDisplay(9876);			// opdracht 5A
	writeLedDisplay(11);			// opdracht 5A
	writeLedDisplay(1000);			// opdracht 5A

	// write 4-digit data
	
	wait(1000);

	return (1);
}