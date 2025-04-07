/*
 * spi.h
 *
 * Created: 4/7/2025 2:30:20 PM
 *  Author: luukb
 */ 


#ifndef SPI_H_
#define SPI_H_

void wait(int ms);
void spi_masterInit(void);
void displayDriverInit();
void writeLedDisplay ( int value );
void writeNegLedDisplay ( int value );
void clearDisplay();
void spi_writeword ( unsigned char adress, unsigned char data );

#endif /* SPI_H_ */