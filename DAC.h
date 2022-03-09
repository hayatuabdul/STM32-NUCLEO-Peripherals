#ifndef _DAC_H
#define _DAC_H
#include <stm32f4xx.h>

#define DAC_port	GPIOA
#define DAC_pin		5         //This pin is used to output the signal. Waveforms in this case

void init_DAC(void);          //Initalizes the DAC function
void output_dac(unsigned short d);   //This function writes data byte to DAC 2 output register



#endif
