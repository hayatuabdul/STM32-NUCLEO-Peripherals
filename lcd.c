#include "lcd.h"

void lcd_delayus(unsigned int us)		//blocking delay for LCD, argument is approximate number of micro-seconds to delay
{
	unsigned char i;
	while(us--)
	{
		for(i=0; i<SystemCoreClock/4000000; i++){__NOP();}
	}
}

void WaitLcdBusy(void)
{
	
	unsigned int port;       //Initialized port
	set_LCD_bus_input();
	set_LCD_RW();            //Read
	clr_LCD_RS();            //Command
	do{
		set_LCD_E();    
	lcd_delayus(10);
	
	port =  LCD_PORT->IDR & (1u<<7);  //Only set bit 7 to port. Bit 7 is the busy flag
	clr_LCD_E();
	}
	while (port);            //Keep looping as long as port is high
	set_LCD_bus_output();    
}

void set_LCD_data(unsigned char d)
{
	LCD_PORT->BSRR=(0xff<<(LCD_D0_pin+16));	//clear data lines
	LCD_PORT->BSRR=(d<<LCD_D0_pin);					//put data on lines
}

void LCD_strobe(void)		//10us high pulse on LCD enable line
{
	lcd_delayus(10);
	set_LCD_E();
	lcd_delayus(10);
	clr_LCD_E();
}


void cmdLCD8(unsigned char cmd)		//sends a byte to the LCD control register
{
	WaitLcdBusy();				//wait for LCD to be not busy
	clr_LCD_RS();					//control command
	clr_LCD_RW();					//write command
	set_LCD_data(cmd);		//set data on bus
	LCD_strobe();					//apply command
}

void cmdLCD(unsigned char cmd)		//sends a byte to the LCD control register
{
	WaitLcdBusy();			          	//wait for LCD to be not busy
	clr_LCD_RS();					          //control command
	clr_LCD_RW();					          //write command
	set_LCD_data(cmd & 0xF0);       //Set upper bit only
  LCD_strobe();
  set_LCD_data((cmd & 0x0F)<<4); //Set lower bit only
  LCD_strobe();
}


void putLCD(unsigned char put)	//sends a char to the LCD display
{
	WaitLcdBusy();				        //wait for LCD to be not busy
	set_LCD_RS();					        //text command
	clr_LCD_RW();				        	//write command
  set_LCD_data(put & 0xF0);     //Set upper bit only
  LCD_strobe();
  set_LCD_data((put & 0x0F)<<4);//Set lower bit only
  LCD_strobe();                 //apply command
	
}

void initLCD(void)
{
		SystemCoreClockUpdate();
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;	//enable LCD port clock
	  RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;	//GPIO B clock enable
	
	
			//CONFIG LCD GPIO PINS
	LCD_PORT2->MODER&=~(					//clear pin direction settings. LCD_PORT2 is for RS, RW AND E pin only
			(3u<<(2*LCD_RS_pin))
			|(3u<<(2*LCD_RW_pin))
			|(3u<<(2*LCD_E_pin))
			);
	
	LCD_PORT->MODER&=~(					//clear pin direction settings. LCD_PORT is for the D0 pins. This is so I have space for the FPGA pins.
			(0xffff<<(2*LCD_D0_pin))
			);
	
	
	LCD_PORT2->MODER|=(				//reset pin direction settings to digital outputs
			(1u<<(2*LCD_RS_pin))
			|(1u<<(2*LCD_RW_pin))
			|(1u<<(2*LCD_E_pin))
			
		);

  LCD_PORT->MODER|=(				//reset pin direction settings to digital outputs
			(0x5555<<(2*LCD_D0_pin))
		);
	
			//LCD INIT COMMANDS
		
	clr_LCD_RS();					//all lines default low
	lcd_delayus(40000);		//40ms startup delay

  cmdLCD8(0x30);         //Run in 4-bit mode
	
	
	lcd_delayus(40);
	
	cmdLCD(0x28);	//Function set: 2 Line, 8-bit, 5x7 dots
	lcd_delayus(40);
	cmdLCD(0x28);	//Function set: 2 Line, 8-bit, 5x7 dots
	lcd_delayus(40);
	cmdLCD(0x28);	//Function set: 2 Line, 8-bit, 5x7 dots
	lcd_delayus(40);
	cmdLCD(0x0c);	//Display on, Cursor blinking command
	lcd_delayus(40);
	cmdLCD(0x01);	//Clear LCD
	lcd_delayus(1600);
	cmdLCD(0x06);	//Entry mode, auto increment with no shift
	lcd_delayus(40);
}




	char customChar[8] = 
 {
  0x04,
  0x0E,
  0x0E,
  0x0F,
  0x0F,
  0x0E,
  0x0E,
  0x04,
	 
  };
 
int k;
	
	
                       //Print Text from Array
//	cmdLCD(0X40);
//	cmdLCD(0X00);
//		for (k=0; k>8; k++) { 
//			putLCD(customChar[k]);
		
	//}

	
void Lcd_Print_String(char *a)
{
    int i;
    for(i=0;a[i]!='\0';i++)
       putLCD(a[i]);  //Split the string using pointers and call the Char function 
}
	
