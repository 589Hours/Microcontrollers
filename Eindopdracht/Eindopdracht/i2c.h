/*
 * i2c.h
 *
 * Created: 4-4-2025 17:25:17
 *  Author: rikva
 */ 

#define SLAVE_ADDR 0x55

void i2c_init();
void i2c_start();
void i2c_stop();
void i2c_write(uint8_t data);
void i2c_write_address();
