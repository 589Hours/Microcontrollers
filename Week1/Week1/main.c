/*
 * MicrocontrollerLesVoorbeeld.c
 *
 * Created: 7-2-2025 10:41:46
 * Author : rikva
 */ 

#define F_CPU 10000000UL
#define BUTTON_FIVE 0x20
#define BUTTON_SIX 0x40
#define BUTTON_SEVEN 0x80

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

enum state {Start, S1, S2, S3, End};

enum state currentState = Start;

void moveFromStart(){
	if (PIND & BUTTON_FIVE)
	{
		currentState = S2;
	} else if (PIND & BUTTON_SIX)
	{
		currentState = S1;
	}
}

void moveFromS1(){
	
	if (PIND & BUTTON_FIVE)
	{
		currentState = S2;
	} else if (PIND & BUTTON_SEVEN)
	{
		currentState = Start;
	}
}

void moveFromS2(){
	if (PIND & BUTTON_FIVE)
	{
		currentState = S3;
	} else if (PIND & BUTTON_SIX) 
	{
		currentState = S1;
	} else if (PIND & BUTTON_SEVEN)
	{
		currentState = Start;
	}
}

void moveFromS3()
{
	if (PIND & BUTTON_FIVE || PIND & BUTTON_SIX)
	{
		currentState = End;
	} else if (PIND & BUTTON_SEVEN) 
	{
		currentState = Start;
	}
}

void moveFromEnd()
{
	if (PIND & BUTTON_SEVEN)
	{
		currentState = Start;
	}
}


void wait (int ms){
	for (int i = 0; i<ms; i++){
		_delay_ms(1); // Library function (max 30ms at 8 MHZ)
	}
}

int main(void)
{
	DDRA = 0xff;
	DDRD = 0x00;
	
    while (1) 
    {
		switch (currentState)
		{
			case Start:
			PORTA = 0x01;
			moveFromStart();
			break;
			case S1:
			PORTA = 0x02;
			moveFromS1();
			break;
			case S2:
			PORTA = 0x04;
			moveFromS2();
			break;
			case S3:
			PORTA = 0x08;
			moveFromS3();
			break;
			case End:
			PORTA = 0x10;
			moveFromEnd();
			break;
		}
		wait(500);
    }
	

}