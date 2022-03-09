#include "LED.h"
#include "UART.h"
#include "DELAY.h"
#include "ADC.h"

void Init_LED(void)
{
	
	//Initializing GPIO
	//ENABLE PORT(S)
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;		//GPIO B clock enable
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOCEN;		//GPIO C clock enable
	
	//CONFIGURE PORT PIN FUNCTIONS FOR ONBOARD LEDS
	//CONFIGURE PORT:GPIOB  PIN:0 TO OUTPUT for LED1
	GPIOB->MODER |= 1<<(2*0);					//ONLY set  GPIOB0
	GPIOB->MODER |= 1<<(2*7);				//ONLY set  GPIOB7
	GPIOB->MODER |= 1<<(2*14);			//ONLY set  GPIOB14
	GPIOB->OTYPER|=(0u<<(2*0));					//set new pin functions on GPIOC
	GPIOB->OTYPER|=(0u<<(1*7));					//set new pin functions on GPIOC
	GPIOB->OTYPER|=(0u<<(1*14));					//set new pin functions on GPIOC
	GPIOB->OSPEEDR|=(2u<<(2*0));
	GPIOB->OSPEEDR|=(2u<<(2*7));
	GPIOB->OSPEEDR|=(2u<<(2*14));
	GPIOB->PUPDR|=(0u<<(2*0));
	GPIOB->PUPDR|=(0u<<(2*7));
	GPIOB->PUPDR|=(0u<<(2*14));
	
	// the above assumes that bit 1 is to zero
	GPIOB->MODER |= 0<<(2*0);				//ONLY clear GPIOB0
	GPIOB->MODER |= 0<<(2*7);				//ONLY clear  GPIOB7
	GPIOB->MODER |= 0<<(2*14);			//ONLY clear  GPIOB14
	GPIOB->OTYPER&=~(0u<<(1*0));							//clear pin functions on GPIOB
	GPIOB->OTYPER&=~(0u<<(1*14));					    //Clear pin functions on GPIOB
	GPIOB->OTYPER&=~(0u<<(1*7));							//clear pin functions on GPIOB
	GPIOB->OSPEEDR&=~(1<<(2*0));
	GPIOB->OSPEEDR&=~(1<<(2*7));
	GPIOB->OSPEEDR&=~(1<<(2*14));
	GPIOB->PUPDR&=~(3u<<(2*0));
	GPIOB->PUPDR&=~(3u<<(2*7));
	GPIOB->PUPDR&=~(3u<<(2*14));
	
	//CONFIGURE PORT PIN FUNCTIONS FOR EXTERNAL LEDS
	GPIOC->MODER |= 1<<(2*8);				//ONLY set  GPIOC8
	GPIOC->MODER |= 1<<(2*9);				//ONLY set  GPIOC9
	GPIOC->MODER |= 1<<(2*10);			//ONLY set  GPIOC10
	GPIOC->MODER |= 1<<(2*11);			//ONLY set  GPIOC11
	
	// the above assumes that bit 1 is to zero
	GPIOC->MODER |= 0<<(2*8);				//ONLY clear GPIOC8
	GPIOC->MODER |= 0<<(2*9);				//ONLY clear  GPIOC9
	GPIOC->MODER |= 0<<(2*10);			//ONLY clear  GPIOC10
	GPIOC->MODER |= 0<<(2*11);			//ONLY clear  GPIOC11
	
	
	GPIOE->OTYPER&=~(0u<<(10*2));							//clear pin functions on GPIOC
	GPIOE->OTYPER|=(0u<<(10*2));							//set new pin functions on GPIOC
	GPIOE->OSPEEDR|=(2u<<(10*2));
	GPIOE->OSPEEDR&=~(1<<(10*2));
	GPIOE->PUPDR&=~(3u<<(10*2));							//clear pin functions on GPIOC
	GPIOE->PUPDR|=(0u<<(10*2));
	
}	
	
//Toggle functions for the onboard LEDs
void Toggle_LED (void)
	{
	
	GPIOB->ODR^=(1u<<0);								//XOR GPIOB output data register to invert the selected pin
}
void Toggle_LED2 (void)
	{
	
	GPIOB->ODR^=(1u<<7);								//XOR GPIOB output data register to invert the selected pin

}
void Toggle_LED3 (void)
{
	
	GPIOB->ODR^=(1u<<14);								//XOR GPIOB output data register to invert the selected pin
}


//Toggle functions for the External LEDs
void Toggle_exLED (void)
	{
	
	GPIOC->ODR^=(1u<<8);								//XOR GPIOC output data register to invert the selected pin
}
void Toggle_exLED2 (void)
	{
	
	GPIOC->ODR^=(1u<<9);
}
void Toggle_exLED3 (void)
{
	
	GPIOC->ODR^=(1u<<10);								//XOR GPIOC output data register to invert the selected pin
}

void Toggle_exLED4 (void)
{
	
	GPIOC->ODR^=(1u<<11);								//XOR GPIOC output data register to invert the selected pin
}


void exLEDs (void)
{
	float lcd_voltage;
	int ADC_DATA;
	ADC_DATA = read_adc();
	
	lcd_voltage = (3.3f/4095)*ADC_DATA;
		 if (lcd_voltage >0.0f && lcd_voltage <0.406f)                      // 3.3/16 = 0.2. Bottom LCD
		{
	ex_LED1_on;
	ex_LED2_on;
	ex_LED3_on;
	ex_LED4_on;
  tickdelayMs(500);
  ex_LED1_off;
	ex_LED2_off;
  ex_LED3_off;
  ex_LED4_off;			
	
		}
	  else if (lcd_voltage >0.4f && lcd_voltage <0.806f)
		{
	ex_LED1_on;
	ex_LED2_on;
	ex_LED3_on;
	ex_LED4_on;
  tickdelayMs(300);
  ex_LED1_off;
	ex_LED2_off;
  ex_LED3_off;
  ex_LED4_off;	
		}
		
		 else if (lcd_voltage >0.8f && lcd_voltage <1.206f)
		 {
	ex_LED1_on;
	ex_LED2_on;
	ex_LED3_on;
	ex_LED4_on;
  tickdelayMs(150);
  ex_LED1_off;
	ex_LED2_off;
  ex_LED3_off;
  ex_LED4_off;	
		 }
		 
		 else if (lcd_voltage >1.2f && lcd_voltage <1.606f)
		 {
	ex_LED1_on;
	ex_LED2_on;
	ex_LED3_on;
	ex_LED4_on;
  tickdelayMs(100);
  ex_LED1_off;
	ex_LED2_off;
  ex_LED3_off;
  ex_LED4_off;	
	
		 }
		 else if (lcd_voltage >1.6f && lcd_voltage <2.06f)
		 {
		
	ex_LED1_on;
	ex_LED2_on;
	ex_LED3_on;
	ex_LED4_on;
  tickdelayMs(70);
  ex_LED1_off;
	ex_LED2_off;
  ex_LED3_off;
  ex_LED4_off;			
		 }
		 		 else if (lcd_voltage >2.0f && lcd_voltage <2.406f)
		 {
	ex_LED1_on;
	ex_LED2_on;
	ex_LED3_on;
	ex_LED4_on;
  tickdelayMs(50);
  ex_LED1_off;
	ex_LED2_off;
  ex_LED3_off;
  ex_LED4_off;	
		 }
		 
		 else if (lcd_voltage >2.4f && lcd_voltage <2.806f)
		 {
	ex_LED1_on;
	ex_LED2_on;
	ex_LED3_on;
	ex_LED4_on;
  tickdelayMs(25);
  ex_LED1_off;
	ex_LED2_off;
  ex_LED3_off;
  ex_LED4_off;	
	
		 }
		 else if (lcd_voltage >2.8f && lcd_voltage <=3.3f)
		 {
		
	ex_LED1_on;
	ex_LED2_on;
	ex_LED3_on;
	ex_LED4_on;
  tickdelayMs(10);
  ex_LED1_off;
	ex_LED2_off;
  ex_LED3_off;
  ex_LED4_off;			
		 }
}

	
void Morse(int duration)
{
  Blue_led_on;
  tickdelayMs(duration);              //Assign duration to a delay function
  Blue_led_off;
  tickdelayMs(duration);              //Assign duration to a delay function
}

void Init_Morse(void)
{
    	  //The Morse code slows down LCD when using a lot of delays
//	  Morse(200); Morse(200); Morse(200); // S
//    Wait3(300); // otherwise the Morses run together
//    Morse(500); Morse(500); Morse(500); // O
//    Morse(200); Morse(200); Morse(200); // S
//    Wait3(1000);
//    
	  Morse(20); Morse(50); // A (.-)
    Wait3(30); // Otherwise the Morses run together
    Morse(50); Morse(20); Morse(20); // D (-..)
    Morse(50); Morse(20); Morse(50); Morse(20); // C (-.-.)
    tickdelayMs(100);
}