#include <stm32f4xx.h>
#include "UART.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "ADC.h"

void init_USART(void)
{
	unsigned char i1,i2;
	SystemCoreClockUpdate();	
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;		//usart port clock enable
	
	USART_PORT->MODER&=~(				//clear pin function bits
		(3u<<(2*USART_TX_pin))
		|(3u<<(2*USART_RX_pin))
			);
	USART_PORT->MODER|=(			//reset pin function bits (alternate function)
		(2u<<(2*USART_TX_pin))
		|(2u<<(2*USART_RX_pin))
			);
	
	i1=USART_TX_pin/8;
	i2=USART_RX_pin/8;

		// ALTERNATE FUNCTION SELECT BITS - SET TO UART
	USART_PORT->AFR[i1]&=~(0x0f<<(4*(USART_TX_pin-(i1*8))));
	USART_PORT->AFR[i1]|=(0x07<<(4*(USART_TX_pin-(i1*8))));
	USART_PORT->AFR[i2]&=~(0x0f<<(4*(USART_RX_pin-(i2*8))));
	USART_PORT->AFR[i2]|=(0x07<<(4*(USART_RX_pin-(i2*8))));
	
	RCC->APB1ENR|=RCC_APB1ENR_USART3EN;		//usart clock enable
	USART_MODULE->CR1|=(		//USART CONFIG
			USART_CR1_TE		//transmit enable
			|USART_CR1_RE		//receive enable
			|USART_CR1_UE		//usart main enable bit
			|USART_CR1_RXNEIE);


USART_MODULE->BRR = 0X008B;   //Set baudrate to 115200
CLEAR_BIT(USART_MODULE ->CR2, (1<<12|1<<13)); // Clear STOP bits = 1 STOP BIT
CLEAR_BIT(USART_MODULE ->CR1, 1<<15); // 16 bit oversampling
CLEAR_BIT(USART_MODULE ->CR1, 1<<12); // 1 start bit 8 Data bits
//CLEAR_BIT(USART_MODULE ->CR1, 1<<10); // Disable PARITY
CLEAR_BIT(USART_MODULE ->CR1, 1<<9); // EVEN Parity
;
				
				
//	USART_MODULE->BRR=SystemCoreClock/(BAUDRATE);		//set baud rate
//																									//this is not an accurate way to set the baudrate
//																									//and only works for 16Mhz system clock.
																									
}

unsigned char receive_usart(void)
{
	char recieved = USART_MODULE->DR;              //Only take action when char is recieved (Type something on the keyboard
	while(!(USART_MODULE->SR&=~USART_SR_RXNE));    //While Usart is triggered, return data
	return USART_MODULE->DR;											//write byte to usart data register
	
}

void send_usart(unsigned char d)
{
	while(!(USART_MODULE->SR&USART_SR_TC));		//wait for transmission complete
	USART_MODULE->DR=d;		//write byte to usart data register
}

static void USART3_IRQHandler(void)       //Not called
{
	char recieved = USART_MODULE->DR;
	
	//Do something
	USART_MODULE->SR&=~USART_SR_RXNE;       //This function gets triggered when something is typed on the keyboard
}


int usart_write(int ch)
	{
	while(!(USART_MODULE->SR&=~USART_SR_RXNE));    //While Usart is triggered, return data
	USART_MODULE->DR = ch;											   //write byte to usart data register
	return ch;
	}		

int usart_read(void) 
{
while(!(USART2->SR & 0x0020))
{}return USART2->DR; 
} 

void usart_char (char value)
{
	
unsigned char Modulus[] = "V V";  //A string that displays the voltage unitfloat lcd_voltage;
		
float lcd_voltage;
int ADC_DATA;
ADC_DATA = read_adc();
lcd_voltage = (3.3f/4095)*ADC_DATA; 	
		
	unsigned int a = (ADC_DATA*3300/4095);         //ADC_DATA used here to output a much bigger number when divided by 4095. 3300(3.3 in a way LCD understands).
	
	Modulus[0] = (a/1000 + 0x30);                //Output the value in ASCII MODE
	
	a %= 1000;
	Modulus[1] = (a/100 + 0x30);                 //Same sequence for the second digit
	
	a %= 100;
	Modulus[2] = (a/10 + 0x30);
	
	a %= 10;
	Modulus[3] = (a/1 + 0x30);
		
		value %=16;
	
		for (; value>0;value--)
		{
  send_usart(Modulus[0]);                            //First digit of ADC voltage
	send_usart(0x2E);                                  //Perioid character in ASCII
	send_usart(Modulus[1]);                            //Second digit of ADC voltage
	send_usart(Modulus[2]);                            //Third digit of ADC voltage
	send_usart(Modulus[3]);                            //Fourth digit of ADC voltage
  send_usart('V');	
  send_usart('\r');
			
  float
	Vlevel = lcd_voltage *10;               //Vlevel is the voltage multiplied by 10 because 35/3.3 = 10. 35 because 16*2
	for (int i=0; i<=Vlevel; i++)          //As long as the ADC is below the Vlevel, the code loops
	{
		//send_usart('<');                         //Display character to imitate a level symbol on the USART
		send_usart('.');                         //Display character to imitate a level symbol on the USART
		send_usart('.');                         //Display character to imitate a level symbol on the USART
		
	}
	send_usart('_');                          //Display character to imitate a level symbol on the USART
	send_usart('_');                          //Display character to imitate a level symbol on the USART
	send_usart('\n');                         //Display character to imitate a level symbol on the USART
	send_usart('\n');                         //Display character to imitate a level symbol on the USART
	send_usart('\n');                         //Display character to imitate a level symbol on the USART
	send_usart('\n');                         //Display character to imitate a level symbol on the USART
	
   }
}

//USART interface connected to stdio library
//struct _FILE{int handle;};
//FILE _stdin = {0}; 
//FILE _stdout = {1}; 
//FILE _stderr = {2}; 

//int fgetc(FILE *f) 
//{ int c; 
//		 c = usart_read();
// if (c == '\r')
// {
//	 usart_write(c);
//	 c = '\n';
// }	
//   usart_write(c); 
//   return c;
//}
//int fputc(int c, FILE *f)
//{
//	return  usart_write(c);
//}


////Re-write printf
//#define BUFFER_SIZE 255
//char transmit_buffer[255];
//void myPrintf (const char* format,...)         //Like const [char], but not proper. Three dots means various arguments not yet specified
//{
//	va_list args;
//	va_start (args, format);
//	vsprintf(transmit_buffer,format,args);
//	va_end(args);
//	
//	for (unsigned int i = 0; i < BUFFER_SIZE; i++)
//	{
//		send_usart(transmit_buffer[i]);
//	}
//}


