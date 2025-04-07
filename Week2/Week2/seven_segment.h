/*
 * seven_segment.h
 *
 * Created: 4/7/2025 3:40:14 PM
 *  Author: luukb
 */ 


#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_

const int SHOW[53];

void display(int digits);
ISR( INT0_vect );
ISR( INT1_vect );
void wait( int ms );


#endif /* SEVEN_SEGMENT_H_ */