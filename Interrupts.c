#include <stm32f4xx.h>
#include "ADC.h"
#include "DAC.h"
#include "lcd.h"
#include "LED.h"
#include "UART.h"
#include "DELAY.h"


void TIM3_IRQHandler(void)			//TIMER 3 INTERRUPT SERVICE ROUTINE
{
	TIM3->SR&=~TIM_SR_UIF;				//clear interrupt flag in status register
	
	unsigned char myText[]=" Press any Key to display ADC voltage and it's progress bar";       //Array to make sentences. More conveniant than recurring strings
	int i;                                          
	for (i=0; i<60; i++)                            //For loop that counts the array characters
	{
	                         
		send_usart(myText[i]);         //Print Text from Array
		

	}
	send_usart('\r');
	
	char ch;
	
	ch = receive_usart();       //Receive Usart when keyboard pressed
	usart_char(ch);             //When button is pressed, transmit ADC voltage and progress bar.
	send_usart('\r');           //New row

}

void TIM4_IRQHandler(void)			//TIMER 4 INTERRUPT SERVICE ROUTINE
{
	
  int myTick=0;
	myTick++;
	TIM4->SR&=~TIM_SR_UIF;				//clear interrupt flag in status register
}


void TIM6_DAC_IRQHandler(void)			//TIMER 7 INTERRUPT SERVICE ROUTINE
{
	unsigned short ADC_DATA;       
	TIM6->SR&=~TIM_SR_UIF;				   //clear interrupt flag in status register
	ADC_DATA = read_adc();           //Runs the ADC at 12 bit sampling. I used timer 6 because of its DAC properties
	int sample = 0;
	sample++;
	if (sample == 10000)
	{
		Toggle_LED3();                //Red LED flashing at 4.8Hz sampling rate
		sample=0;
	}

}

void TIM7_IRQHandler(void)			//TIMER 4 INTERRUPT SERVICE ROUTINE
{

	TIM7->SR&=~TIM_SR_UIF;				//clear interrupt flag in status register


}