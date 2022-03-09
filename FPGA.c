#include "FPGA.h"
#include "LED.h"

void Init_FPGA(void)
{
	//ENABLE PORT(S)
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;		//GPIO B clock enable
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOEEN;		//GPIO E clock enable
	
	//CONFIGURE PORT PIN FUNCTIONS
	
	//Configure port pins for FPGA
	
	GPIOB->MODER |= 1<<(2*10);				//ONLY set  GPIOB10
	GPIOB->MODER |= 1<<(2*11);			 //ONLY set  GPIOB11
	GPIOE->MODER |= 1<<(2*2);				 //ONLY set  GPIOE2
	GPIOE->MODER |= 1<<(2*10);			 //ONLY set  GPIOB28
	GPIOE->MODER |= 1<<(2*12);		 	//ONLY set  GPIOE12
	GPIOE->MODER |= 1<<(2*15);			//ONLY set  GPIOE15
	
	// the above assumes that bit 1 is to zero
	
	
	GPIOB->MODER |= 0<<(2*10);			//ONLY set  GPIOB10
	GPIOB->MODER |= 0<<(2*11);			//ONLY set  GPIOB11
	GPIOE->MODER |= 0<<(2*2);				//ONLY set  GPIOE2
	GPIOE->MODER |= 0<<(2*10);			//ONLY set  GPIOE10
	GPIOE->MODER |= 0<<(2*12);			//ONLY set  GPIOE12
	GPIOE->MODER |= 0<<(2*15);			//ONLY set  GPIOE15
}

void FPGA_LED (void)
{
	
	GPIOB->ODR^=(1u<<10);								//XOR GPIOB output data register 
	GPIOB->ODR^=(1u<<11);								//XOR GPIOB output data register 
	GPIOE->ODR^=(1u<<2);								//XOR GPIOB output data register 
	GPIOE->ODR^=(1u<<10);								//XOR GPIOB output data register 
	GPIOE->ODR^=(1u<<12);								//XOR GPIOB output data register 
	GPIOE->ODR^=(1u<<15);								//XOR GPIOB output data register 
}
	
void FPGA_Comm (void)
{
	//Evidence of functional 4-bit communication with FPGA and C code. This function makes it possible to interact with the FPGA board and can also make changes that affect the output
	FPGA_sel0_on;       //Control line 1
	//Wait3(500);
	//FPGA_sel0_off;
	
	FPGA_sel1_on;       //Control line 2
	//Wait3(300);
	//FPGA_sel1_off;
	
  FPGA_data0_on;		  //Data bus 0
	FPGA_data1_on;	    //Data bus 1
	FPGA_data2_on;	    //Data bus 2
	FPGA_data3_on;	    //Data bus 3
}