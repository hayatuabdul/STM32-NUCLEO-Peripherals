#include <stm32f4xx.h>
#include "ADC.h"
#include "DAC.h"
#include "lcd.h"
#include "LED.h"
#include "DELAY.h"
#include "Switch.h"


void TIM5_IRQHandler(void)			//TIMER 5 INTERRUPT SERVICE ROUTINE
{
	uint16_t tdelay =250;       //Delay to pulse Green LED at different rates
	//GPIOC->MODER |= 1<<(2*13);				 	//ONLY set  GPIOB0
	GPIOC->MODER |= 0<<(2*13);					 //ONLY clear  GPIOD13

	TIM5->SR&=~TIM_SR_UIF;				//clear interrupt flag in status register
			
		Toggle_LED3();                //Red LED flashing at 4.8Hz sampling rate using timer 5
}

void switch_led(void)			
{
		uint16_t tdelay =250;       //Delay to pulse Green LED at different rates
	 if(short_press) 
		{
	 
      if(tdelay==150)
				tdelay = 700;
			else
	  	tdelay = 350;
		}
		Toggle_LED();
	  tickdelayMs(tdelay);
}

void user_button_hold(void)			
{
	for (int s=0; s<=2500; s++)    //How long the hold function waits for. 10 seconds in this case
	{
	Red_led_off;        //Disable LEDs while on hold mode
	Blue_led_off;
	Green_led_off;
	deinitTIM2();       //Disable Timer 2
	deinitTIM3();       //Disable Timer 3
	deinitTIM4();       //Disable Timer 4
	deinitTIM5();       //Disable Timer 5
	deinitTIM6();       //Disable Timer 6
	 cmdLCD(0x01);     //Clears the LCD
		
	char HOLD[]="     HOLD MODE";   //An empty char consisting of 16 levels that clears the second lind of the LCD so the progress bar decreases
	for (int h=0; h<=14; h++)             //A loop that accounts for the emplty char above
	{
		putLCD(HOLD[h]);               //Displays 'HOLD MODE' on the LCD
	}
}
		cmdLCD(LCD_LINE1);
	char cleanline1[]="                ";   //An empty char consisting of 16 levels that clears the second lind of the LCD so the progress bar decreases
	for (int p=0; p<=16; p++)             //A loop that accounts for the emplty char above
	{
		putLCD(cleanline1[p]);               //Display the empty char on the LCD right before a progress bar change
	}
}

