#include "ADC.h"



void init_ADC(void)
{
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOCEN;	//GPIOC clock enable
	ADC_input_port->MODER|=(3u<<(2*ADC_input_pin));	//ADC input pin is analogue mode
	
	RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;		//ADC clock enable
	ADC1->SQR1&=~ADC_SQR1_L;						//set number of conversions per sequence to 1
	ADC1->SQR3&=~ADC_SQR3_SQ1;					//clear channel select bits
	ADC1->SQR3|=ADC_Channel;						//set channel
	ADC1->CR2|=ADC_CR2_ADON;						//enable ADC
	
}


unsigned short read_adc(void)
{
	ADC1->CR2|=ADC_CR2_SWSTART;				//start ADC conversion
	while((ADC1->SR&ADC_SR_EOC)==0){__NOP();}	//wait for ADC conversion complete
	return ADC1->DR;									//return converted value
}


//void meter(void)
//{
//	ADC_DATA = read_adc();
//	
//	lcd_voltage = (3.3f/4095)*ADC_DATA;
//	
//	  if (lcd_voltage >0.0f && lcd_voltage <0.206f)                      // 3.3/16 = 0.2. Bottom LCD
//		{
//		putLCD('-');
//	
//		}
//	  else if (lcd_voltage >0.2f && lcd_voltage <0.406f)
//		{
//		putLCD('-');
//	  putLCD('-');
//		}
//		
//		 else if (lcd_voltage >0.4f && lcd_voltage <0.606f)
//		 {
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		 }
//		 
//		 else if (lcd_voltage >0.6f && lcd_voltage <0.806f)
//		 {
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		putLCD('-');
//	
//		 }
//		 else if (lcd_voltage >0.8f && lcd_voltage <1.06f)
//		 {
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		putLCD('-');
//	  putLCD('-');
//		
//		 }
//		 else if (lcd_voltage >1.06f && lcd_voltage <1.206f)
//		 {
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');

//		 }
//		 	  else if (lcd_voltage >1.2f && lcd_voltage <1.406f)
//		{
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		}
//		
//		 else if (lcd_voltage >1.4f && lcd_voltage <1.606f)
//		 {
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		 }
//		 
//		 else if (lcd_voltage >1.6f && lcd_voltage <1.806f)
//		 {
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		 }
//		 else if (lcd_voltage >1.8f && lcd_voltage <2.06f)
//		 {
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//	  putLCD('-');
//			 
//		 }
//		 else if (lcd_voltage >2.06f && lcd_voltage <2.206f)
//		 {
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//	  putLCD('-');	 
//		 }
//		 	  else if (lcd_voltage >2.2f && lcd_voltage <2.406f)
//		{
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//	  putLCD('-');		
//		}
//		
//		 else if (lcd_voltage >2.4f && lcd_voltage <2.606f)
//		 {
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//	  putLCD('-');	 
//		 }
//		 
//		 else if (lcd_voltage >2.6f && lcd_voltage <2.806f)
//		 {
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//	  putLCD('-');
//		 }
//		 else if (lcd_voltage >2.8f && lcd_voltage <3.06f)
//		 {
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//	  putLCD('-');	 
//		 }
//	   else if (lcd_voltage >3.0f && lcd_voltage <=3.3f)
//		 {
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//	  putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//		putLCD('-');
//	  putLCD('-');
//    putLCD('-');				 
//		 }
	

//	int j = 0;
//	
//	while(Modulus[j] !='\0')                        //While string is not empty, Display.
//	{
//		putLCD(Modulus[j]);
//		j++;
//	}
//	
//	
//}