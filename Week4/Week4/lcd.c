#define F_CPU 10e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>

#include "lcd.h"

#define LCD_E 	6  // RA6 UNI-6
#define LCD_RS	4  // RA4 UNI-6

void lcd_strobe_lcd_e(void) {
	PORTA |= (1<<LCD_E);	// E high
	_delay_ms(1);			// nodig
	PORTA &= ~(1<<LCD_E);  	// E low
	_delay_ms(1);			
}

void lcd_init(void) {
	// PORTC output mode and all low (also E and RS pin)
	DDRC = 0xFF;
	DDRA = 0xFF;
	PORTC = 0x00;
	PORTA = 0x00;

	// Step 2 
	PORTC = 0x20;	// function set
	lcd_strobe_lcd_e();

	// Step 3 
	PORTC = 0x20;   // function set
	lcd_strobe_lcd_e();
	PORTC = 0x80;
	lcd_strobe_lcd_e();

	// Step 4 
	PORTC = 0x00;   // Display on/off control
	lcd_strobe_lcd_e();
	PORTC = 0xF0;
	lcd_strobe_lcd_e();

	// Step 4 
	PORTC = 0x00;   // Entry mode set
	lcd_strobe_lcd_e();
	PORTC = 0x60;
	lcd_strobe_lcd_e();
}

void lcd_write_integer(int data)
{
	char data_out[16];
	memset(data_out, 0, sizeof(data_out[0]) * 16);
	sprintf(data_out, "%s %u", "Counter: " , data);
	display_text(data_out);
}

void display_text(char *str) {
	for(;*str; str++){
		write_data(*str);
	}
}


void write_data(unsigned char byte) {
	// First nibble.
	PORTC = byte;
	PORTA |= (1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTA |= (1<<LCD_RS);
	lcd_strobe_lcd_e();
}

void write_command(unsigned char byte) {
	// First nibble.
	PORTC = byte;
	PORTA &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTA &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();
}


void clear() {
	write_command (0x01);	//Leeg display
	_delay_ms(2);
	write_command (0x80);	//Cursor terug naar start
}
