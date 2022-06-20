#include <stm32f4xx.h>
#include "math.h"
#include "stdio.h"
#include "ADC.h"
#include "DAC.h"
#include "lcd.h"
#include "LED.h"
#include "UART.h"
#include "DELAY.h"
#include "FPGA.h"
#include "Switch.h"

//By Abdullahi Hayatu.   Student ID: 10614230

extern void PLL_Config(void);

float lcd_voltage;

unsigned int Wave1[100];       //Sawtoothe Wave Array definition

unsigned int Wave2[100];       //Tirangular Wave Array definition

unsigned int Wave3[50];        //Sine Wave Array definition

float pi = 3.142;     //Set pi as a float

int ADC_DATA;

unsigned char Modulus[] = "V V";  //A string that displays the voltage unit


uint16_t tdelay =250;

int main(void)
{
	
	//PLL_Config();              //Disabled because it doesn't interface well with my LCD
	SystemCoreClockUpdate();
	
	init_ADC();		//config ADC
	init_DAC();		//config DAC
	Init_Timer2();								// Initialise Timer 2
	Init_Timer3();								// Initialise Timer 3
	//Init_Timer4();							// Initialise Timer 4
	Init_Timer5();								// Initialise Timer 5
	Init_Timer6();								// Initialise Timer 6
	//Init_Timer7();							// Initialise Timer 7
	init_USART();                 // Initialise USART
	initLCD();                    // Initialise LCD
	Init_LED();                   // Initialise LED
	Init_FPGA();                  // Initialise FPGA
	char ch;
	
	
	//Waveforms below
  //These below functions trigger waveforms based on the counts and samples being used. They are later called using an interrupt so it doesn't interfere with the LCD
	
	//Sawtoothe Wave
	int n=0;
	for(n=0;n<100;++n){
		Wave1[n]=n*40;              //Multiplied by 40 because 40*100 = 4000. 4096 for a wave cycle
	}
	//Triangular Wave
	for(n=0;n<50;++n){
		Wave2[n]=n*80;              //Counts to 4000 for first half of wave
	}
	for(n=0;n<50;++n){
		Wave2[n+50]=4000-n*80;      //Counts down from 4000 to 0
	}
	//Sine Wave
	for(n=0;n<100;++n){
		Wave3[n]=((1.0f+sin(n/(pi*5)))*2000.0f);   //A formula for sinewave with a sample of 50 and counts to 4000
	}
	
while(1)
{

	//HOLD mode is activated by the user button. The function below activates
	if(long_press)             //if user button pressed
		{
	    user_button_hold();     //Activate this function
		}
		else                      //Else reinitalise the timers and proceed with the loop
		{
	Init_Timer2();								// Initialise Timer 2
	Init_Timer3();								// Initialise Timer 3
	Init_Timer4();								// Initialise Timer 4
	Init_Timer5();								// Initialise Timer 5
	Init_Timer6();								// Initialise Timer 6
	Init_Timer7();								// Initialise Timer 7
			
		
	
	FPGA_Comm();            //Evidence of functional 4-bit communication with FPGA and C code

	  
	Init_Morse();    //Transmitting 'ADC' in morse via Blue LED. I used smaller time frames because longer delays lag out the LCD
    
	exLEDs();    //Using if and else statments to display External LEDs propoertional to the ADC voltage. This is done by changing the speed of the toggles
	
	switch_led();	
	
	//LCD below
	//I used the modulus formula to obtain the ADC voltage and display it on the LCD. The formual below is required because the LCD doesn't undertstand floats or doubles
	//lcd_delayus(1000);
	ADC_DATA = read_adc();
	unsigned int a = (ADC_DATA*3300/4095);         //ADC_DATA used here to output a much bigger number when divided by 4095. 3300(3.3 in a way LCD understands). LCD doesn't get floats
	
	Modulus[0] = (a/1000 + 0x30);                //Output the value in ASCII MODE . 0x30 is equivalent to a '0' in ASCII code.
	//This method works by dividing the digits by 1000 first(four digits) to get the first digit before the decimal, then it moves to the second digit by the right and divides by 100 and so on. 
	a %= 1000;
	Modulus[1] = (a/100 + 0x30);                 //Same sequence for the second digit
	
	a %= 100;
	Modulus[2] = (a/10 + 0x30);
	
	a %= 10;
	Modulus[3] = (a/1 + 0x30);
	
	output_dac(ADC_DATA);
	
	cmdLCD(LCD_LINE1+10);
	putLCD(Modulus[0]);                            //First digit of ADC voltage
	putLCD(0x2E);                                  //Perioid character in ASCII
	putLCD(Modulus[1]);                            //Second digit of ADC voltage
	putLCD(Modulus[2]);                            //Third digit of ADC voltage
	putLCD(Modulus[3]);                            //Fourth digit of ADC voltage
	
  putLCD('V');
	
	
	lcd_voltage = (3.3f/4095)*ADC_DATA;    //3.3 because of the max voltage divided by 4095 because of 4096 cycles then multiplied by the ADC data read from A1.
	
	cmdLCD(LCD_LINE2);
	char cleanline[]="                ";   //An empty char consisting of 16 levels that clears the second lind of the LCD so the progress bar decreases
	for (int p=0; p<=16; p++)             //A loop that accounts for the emplty char above
	{
		putLCD(cleanline[p]);               //Display the empty char on the LCD right before a progress bar change
	}
	cmdLCD(LCD_LINE2);
	float                                  //Float because the ADC voltage is in decimal
	Vlevel = lcd_voltage *5;               //Vlevel is the voltage multiplied by 5 because 16/3.3 = 5.
	for (int i=0; i<=Vlevel; i++)          //As long as the ADC is below the Vlevel, the code loops
	{
		putLCD(255);                         //Display character to imitate a level symbol on the LCD. 255 is a character in ASCII that fills up the entire slot of a level on the LCD.
	}
	

}	

}
}

void TIM2_IRQHandler(void)			//TIMER 2 INTERRUPT SERVICE ROUTINE. Runs the Sine wave at 1KHz Frequency
{

	static int i=0;               //Set i to an integer that doesn't change
	TIM2->SR&=~TIM_SR_UIF;				//clear interrupt flag in status register
	i++;                          //Increment i
	if (i>=100)                   //Restart the cycle of samples
	{
		i=0;                        //Go back to 0
	}
	output_dac(Wave3[i]);  //Displays Sine Waveform at 1KHz freq
    
   
}
	






