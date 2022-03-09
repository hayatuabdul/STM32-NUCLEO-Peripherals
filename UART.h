#ifndef _USART_H_
#define _USART_H_
#include <stm32f4xx.h>

#define USART_MODULE	USART3
#define USART_PORT		GPIOD      //Set USART_PORT as GPIOD
#define USART_TX_pin	8
#define USART_RX_pin	9
#define BAUDRATE	115200


void myPrintf (const char* format,...);          //Our own written printf. Prints out to USART 
void send_usart(unsigned char d);                //A function that transmits character to USART
void init_USART(void);                           //Funtion that initializes USART
unsigned char receive_usart( void);              //Function that receives character from USART
static void USART3_IRQHandler(void);             //An interrput that triggers when action is taken form keyboard
void usart_char (char value);                   //A char funtion that activates when keyboard is pressed from USART terminal
int usart_write(int ch);                        //A function that 

#endif