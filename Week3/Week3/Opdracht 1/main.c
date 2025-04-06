#define F_CPU 10e6

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LCD_E 	6  // RA6 UNI-6
#define LCD_RS	4  // RA4 UNI-6

void lcd_strobe_lcd_e(void);
void init(void);
void display_text(char *str);
void display_number(int num);
void write_data(unsigned char byte);
void write_command(unsigned char byte);
void clear();

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main(void)
{
	// Init I/O
	DDRC = 0xFF;
	PORTC = 0xFF;
	
	DDRD &= 0b01111111;
	DDRE |= 0b11111111;
	
	//init lcd
	init();
	
	write_data('A');
	
	wait(2000);
	
	display_text("LCD Started!");
	
	//init timer stuff
	TCCR2 = 0b00001111; // Set timer into normal mode on T2
	TCNT2 = 0x00; // count to 0x00

    /* Replace with your application code */
    while (1) 
    {
		PORTE = TCNT2;
		write_command(0x02);
		display_text("Teller: ");
		display_number(TCNT2);
		_delay_ms(250);
    }
}

void lcd_strobe_lcd_e(void) {
	PORTA |= (1<<LCD_E);	// E high
	_delay_ms(1);			// nodig
	PORTA &= ~(1<<LCD_E);  	// E low
	_delay_ms(1);
}

void init(void) {
	// PORTC output mode and all low (also E and RS pin)
	DDRD = 0xFF;
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

void display_text(char *str) {
	for(;*str; str++){
		write_data(*str);
	}
}

void display_number(int num){
	char buffer[10];
	sprintf(buffer, "%d", num);
	display_text(buffer);
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