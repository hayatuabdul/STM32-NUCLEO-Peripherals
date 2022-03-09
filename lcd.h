#ifndef _LCD_H_
#define _LCD_H_  
#define LCD_PORT	GPIOD     //Defined LCD_PORT as GPIOD for convenience use in LCD.C
#define LCD_PORT2	GPIOB     //Defined LCD_PORT2 as GPIOB for convenience use in LCD.C
#define LCD_RS_pin	12      //Set control command to PB12
#define LCD_RW_pin	13      //Set Write command pin to PB13
#define LCD_E_pin		15      //Set enable pin to PB15

#define LCD_D0_pin	0



#define LCD_LINE1		0x80
#define LCD_LINE2		0xc0

#define set_LCD_RS()	LCD_PORT2->BSRR=(1u<<LCD_RS_pin)
#define clr_LCD_RS()	LCD_PORT2->BSRR=(1u<<(LCD_RS_pin+16))
#define set_LCD_RW()	LCD_PORT2->BSRR=(1u<<LCD_RW_pin)
#define clr_LCD_RW()	LCD_PORT2->BSRR=(1u<<(LCD_RW_pin+16))
#define set_LCD_E()		LCD_PORT2->BSRR=(1u<<LCD_E_pin)
#define clr_LCD_E()		LCD_PORT2->BSRR=(1u<<(LCD_E_pin+16))

#define LCD_CLR()		cmdLCD(0x01)

#define set_LCD_bus_input()		LCD_PORT->MODER&=~(0xffff<<(2*LCD_D0_pin))
#define set_LCD_bus_output()	LCD_PORT->MODER|=(0x5555<<(2*LCD_D0_pin))

#include <stm32f4xx.h>

void lcd_delayus(unsigned int us);
void WaitLcdBusy(void);                     //A function that waits for the LCD to be not busy
void set_LCD_data(unsigned char d);
void LCD_strobe(void);
void cmdLCD(unsigned char cmd);
void putLCD(unsigned char put);
void initLCD(void);
void custom_display (void);
void Lcd_Print_String(char *a);

#endif
