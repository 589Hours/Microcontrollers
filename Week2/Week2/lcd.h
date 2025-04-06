/*
 * lcd.h
 *
 * Created: 14-2-2025 13:59:38
 *  Author: rikva
 */ 
void init();
void write_data(unsigned char byte);
void write_command(unsigned char byte);
void display_text(char *str);
void lcd_write_integer(int data);
void clear();
void set_cursor(int position);
