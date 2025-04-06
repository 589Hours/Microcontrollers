#define F_CPU 10e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile int state = 0; //0 voor laag, 1 voor hoog


ISR(TIMER1_COMPA_vect){
	if (state == 0)
	{
		OCR1A = 146; //146 ticks voor hoog oftewel 15 ms
		PORTD |= 0b10000000;
		state = 1;
		
	} else {
		OCR1A = 244; //244 ticks voor laag oftewel 25 ms
		PORTD &= ~(0b11000000);
		state = 0;
	}
}

void timerInit(){
	OCR1A = 146; // 146 ticks because start on low
	TIMSK |= 0b00001000; // enable compare
	TCCR1A = 0; // timer, compare output at OCR1A
	TCCR1B = 0b00000101; //	prescaler to 1024
}

int main(){
	DDRD |= 0b11000000;
	
	sei();
	timerInit();
	
	while (1)
	{
		_delay_ms(100);
	}
	
	return 0;
}