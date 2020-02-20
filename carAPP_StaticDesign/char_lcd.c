/*
 * char_lcd.c
 *
 *  Author: Abdallah Heidar
 */ 


#include "char_lcd.h"
#include "softwareDelay.h"
#include "DIO.h"



void LCD_config_pins(void){

	/* set LCD RS pins as outputs */
	DIO_Cfg_s ST_dio = {0};
	ST_dio.GPIO = LCD_RS_PORT;
	ST_dio.dir = OUTPUT;
	ST_dio.pins = LCD_RS_PIN;
	DIO_init(&ST_dio);

	/* set LCD RW pins as outputs */
	ST_dio.GPIO = LCD_RW_PORT;
	ST_dio.pins = LCD_RW_PIN;
	DIO_init(&ST_dio);
	
	/* set LCD ENABLE pin as outputs */
	ST_dio.GPIO = LCD_EN_PORT;
	ST_dio.pins = LCD_EN_PIN;
	DIO_init(&ST_dio);


	/* set LCD RS pins as outputs */
	
	/*
	ST_dio.GPIO = LCD_D4_PORT;
	ST_dio.pins = LCD_D4_PIN|LCD_D5_PIN|LCD_D6_PIN|LCD_D7_PIN;
	DIO_init(&ST_dio);
	*/
	
	ST_dio.GPIO = LCD_D4_PORT;
	ST_dio.pins = LCD_D4_PIN;
	DIO_init(&ST_dio);

	ST_dio.GPIO = LCD_D5_PORT;
	ST_dio.pins = LCD_D5_PIN;
	DIO_init(&ST_dio);

	ST_dio.GPIO = LCD_D6_PORT;
	ST_dio.pins = LCD_D6_PIN;
	DIO_init(&ST_dio);

	ST_dio.GPIO = LCD_D7_PORT;
	ST_dio.pins = LCD_D7_PIN;
	DIO_init(&ST_dio);
}


void LCD_EN_pulse(void){
	
	DIO_Write(LCD_EN_PORT, LCD_EN_PIN, HIGH);
	softwareDelayMs(1);
	DIO_Write(LCD_EN_PORT, LCD_EN_PIN, LOW);
	softwareDelayMs(1);
}

void LCD_send_nibble(uint8_t data){
	uint8_t mask = 1;
	data >>= 4;
	if(data&mask)
	DIO_Write(LCD_D4_PORT, LCD_D4_PIN, HIGH);
	else
	DIO_Write(LCD_D4_PORT, LCD_D4_PIN, LOW);

	mask *= 2;
	if(data&mask)
	DIO_Write(LCD_D5_PORT, LCD_D5_PIN, HIGH);
	else
	DIO_Write(LCD_D5_PORT, LCD_D5_PIN, LOW);

	mask *= 2;
	if(data&mask)
	DIO_Write(LCD_D6_PORT, LCD_D6_PIN, HIGH);
	else
	DIO_Write(LCD_D6_PORT, LCD_D6_PIN, LOW);

	mask *= 2;
	if(data&mask)
	DIO_Write(LCD_D7_PORT, LCD_D7_PIN, HIGH);
	else
	DIO_Write(LCD_D7_PORT, LCD_D7_PIN, LOW);
}

void LCD_send_char(uint8_t data)		//Sends Char to LCD
{
	DIO_Write(LCD_RS_PORT, LCD_RS_PIN, HIGH);

	LCD_send_nibble(data); // Higher nibble first
	LCD_EN_pulse();

	LCD_send_nibble(data<<4);
	LCD_EN_pulse();
	softwareDelayMs(1);
}
void LCD_send_command(uint8_t data)	//Sends Command to LCD
{
	DIO_Write(LCD_RS_PORT, LCD_RS_PIN, LOW); /* RS is low to send cmd */

	LCD_send_nibble(data); // Higher nibble first
	LCD_EN_pulse();

	LCD_send_nibble(data<<4);
	LCD_EN_pulse();
	softwareDelayMs(1);
}
void LCD_init(void)//Initializes LCD
{
	LCD_config_pins();

	softwareDelayMs(20);
	//	LCD_send_nibble(0x00);
	//
	//	gpioPinWrite(LCD_RS_PORT, LCD_RS_PIN, LOW);
	//	gpioPinWrite(LCD_RW_PORT, LCD_RW_PIN, LOW);
	//	gpioPinWrite(LCD_EN_PORT, LCD_EN_PIN, LOW);

	LCD_send_command(0x33);
	LCD_send_command(0x32);
	LCD_send_command(Four_bit); // 4-bit
	LCD_send_command(Cursor_on);
	LCD_send_command(Lcd_clear);
	softwareDelayMs(10);
	LCD_send_command(Increment_cursor);
	LCD_send_command(Cursor_off); // Cursor off
}
void LCD_clear(void)				//Clears LCD
{
	LCD_send_command(Lcd_clear);
}

void LCD_send_string(uint8_t* data)	//Outputs string to LCD
{
	while(*data){
		LCD_send_char(*data++);
	}
}

void LCD_goto_xy(uint8_t x, uint8_t y)	//Cursor to X Y position
{
	uint8_t DDRAMAddr;
	// remap lines into proper order
	switch(y)
	{
		case 0: DDRAMAddr = LCD_LINE0_DDRAMADDR+x; break;
		case 1: DDRAMAddr = LCD_LINE1_DDRAMADDR+x; break;
		case 2: DDRAMAddr = LCD_LINE2_DDRAMADDR+x; break;
		case 3: DDRAMAddr = LCD_LINE3_DDRAMADDR+x; break;
		default: 
			DDRAMAddr = LCD_LINE0_DDRAMADDR+x;
	}
	// set data address
	LCD_send_command(1<<LCD_DDRAM | DDRAMAddr);

}
