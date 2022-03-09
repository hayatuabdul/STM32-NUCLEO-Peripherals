#include <stm32f4xx.h>
#include "DELAY.h"

void tickdelayMs (int n)
{
	SysTick ->LOAD = 16000;     //Reload with number of clock per milliseconds. 16 now because of 16Mhz
	SysTick ->VAL = 0;          //Clears the current value register
	SysTick ->CTRL = 0X5;       //Enables the SysTick
	
	for (int i=0; i<n; i++)     //Waits until the count flag is set
	{
		while((SysTick ->CTRL & 0x10000) == 0){}
		}
	SysTick ->CTRL = 0;
	
}
	
void delay_us(int time_us){	
	unsigned char i;
	while(time_us--)
	{
		for(i=0; i<SystemCoreClock/((int)(4000000.0*11.25)); i++){
			__nop();
		}
	}	
}

void delay_ms(int time_ms){
	unsigned int i;																						//increment a variable to waste time
	for(i=0; i<(int)((SystemCoreClock/180)/100)*time_ms; i++){//incrementing a variable from 0 to 4,500,000 takes 100ms when MCU speed is 180MHz
		__nop();							
	}
}


void Wait3 (int delay_us)
{
  unsigned int value;
	unsigned int start;
	start = (TIM3->CNT);                    //Increment start to the counter
	value=(TIM3->CNT) - (start & 0x0ffff);  //Subtract start by the value 
	while (value < delay_us)                //A loop where it's always subtracting start by the value 
	{
	  value=(TIM3->CNT) - start;            //Value is now the timer count - the start count
	}
	
}

void wait_us(uint32_t n) 
	{
   uint32_t start, cnt;
   start = DWT->CYCCNT;
  cnt = n * (SystemCoreClock/1000000);
while (((DWT->CYCCNT - start)) < cnt);
 }
	
 
void initTIM2 (int time_s)
{
	//Inline conditional to prevent 32-bit register overflow.
	int ARR = (time_s*10000 > 429496729) ? 429496729 :time_s*10000 ;                      //In Line Conditions
	//if timer > max time, set max time else stick to original time
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	//Timer 2, set dierection to count upwards
	TIM2->DIER |= TIM_DIER_UIE;
	//Timer 2, set prescaler to 9000
	TIM2->PSC = 9000;                                         //9000 because 90 Mhz/9000 = 10000 which is our ARR. 10K/10K = 1 second.
	TIM2->ARR = ARR;
	TIM2->CNT = 0;
	NVIC->ISER[0] |=(1u << 28);
	TIM2->CR1 |= TIM_CR1_CEN;
	
}
 
void Init_Timer2(void)
{
	RCC->APB1ENR|=RCC_APB1ENR_TIM2EN;		//timer 2 clock enabled
	TIM2->DIER|=TIM_DIER_UIE;						//timer uptdate interrupt enabled
																			//APB clock is Fcy/2 = 180MHz/2 = 90MHz
	TIM2->PSC=2-1;	   			          	//divide APB clock by 256 = 90MHz/256 = 351kHz
	TIM2->ARR=80;                       //Set to 80 to run waveforms at 1000Hz
	TIM2->CNT=0;												//zero timer counter
	NVIC->ISER[0]|=(1u<<28);						//timer 2 global interrupt enabled
	TIM2->CR1|=TIM_CR1_CEN;							//start timer counter
}

void Init_Timer3(void)
{
	RCC->APB1ENR|=RCC_APB1ENR_TIM3EN;		//timer 3 clock enabled
	TIM3->DIER|=TIM_DIER_UIE;						//timer uptdate interrupt enabled
																			//APB clock is Fcy/2 = 180MHz/2 = 90MHz
	TIM3->PSC=5000-1;				             //divide APB clock by 256 = 90MHz/256 = 351kHz
	TIM3->ARR=1000-1;                    //Random speed derived from above calculation
	TIM3->CNT=0;												//zero timer counter
	NVIC->ISER[0]|=(1u<<29);					 //timer 3 global interrupt enabled
	TIM3->CR1|=TIM_CR1_CEN;							//start timer counter
}

void Init_Timer5(void)
{
	RCC->APB1ENR|=RCC_APB1ENR_TIM5EN;		//timer 4 clock enabled
	TIM5->DIER|=TIM_DIER_UIE;						//timer uptdate interrupt enabled
																			//APB clock is Fcy/2 = 180MHz/2 = 90MHz
	TIM5->PSC=80;										    //(90Mhz/62500*80) = this displays the red led at 0.2 ms which is 4.8Hz
	TIM5->ARR=62500-1;                  //(ARR)/(90mHZ/PSC) = 1/5 which is 4.8 Hz
	TIM5->CNT=0;												//zero timer counter
	NVIC_EnableIRQ(TIM5_IRQn);					//timer 5 global interrupt enabled
	TIM5->CR1|=TIM_CR1_CEN;							//start timer counter
}

void Init_Timer6(void)
{
	RCC->APB1ENR|=RCC_APB1ENR_TIM6EN;		//timer 4 clock enabled
	TIM6->DIER|=TIM_DIER_UIE;						//timer uptdate interrupt enabled
																			//APB clock is Fcy/2 = 180MHz/2 = 90MHz
	TIM6->PSC=8;										    //(90Mhz/234*8) = 48KHz
	TIM6->ARR=234-1;                   //90MHz/(234*8) = 48KHz
	TIM6->CNT=0;												//zero timer counter
	NVIC->ISER[1]|=(1u<<22);						//timer 4 global interrupt enabled
	TIM6->CR1|=TIM_CR1_CEN;							//start timer counter
}

void Init_Timer7(void)
{
	RCC->APB1ENR|=RCC_APB1ENR_TIM7EN;		//timer 4 clock enabled
	TIM7->DIER|=TIM_DIER_UIE;						//timer uptdate interrupt enabled
																			//APB clock is Fcy/2 = 180MHz/2 = 90MHz
	TIM7->PSC=80;										    //(90Mhz/234*8) = 48KHz
	TIM7->ARR=23400-1;                   //(ARR)/(90mHZ/PSC) = 1/5 which is 4.8 hz
	TIM7->CNT=0;												//zero timer counter
	NVIC->ISER[1]|=(1u<<23);						//timer 4 global interrupt enabled
	TIM7->CR1|=TIM_CR1_CEN;							//start timer counter
}

	
void deinitTIM2(void)
{
	__disable_irq();
	TIM2->CR1 &= ~TIM_CR1_CEN;
	__enable_irq();                         //This prevents the timers and interrupts to be in dilemma
	
}

void deinitTIM3(void)
{
	__disable_irq();
	TIM3->CR1 &= ~TIM_CR1_CEN;
	__enable_irq();                         //This prevents the timers and interrupts to be in dilemma
	
}

void deinitTIM4(void)
{
	__disable_irq();
	TIM4->CR1 &= ~TIM_CR1_CEN;
	__enable_irq();                         //This prevents the timers and interrupts to be in dilemma
	
}

void deinitTIM5(void)
{
	__disable_irq();
	TIM5->CR1 &= ~TIM_CR1_CEN;
	__enable_irq();                         //This prevents the timers and interrupts to be in dilemma
	
}

void deinitTIM6(void)
{
	__disable_irq();
	TIM6->CR1 &= ~TIM_CR1_CEN;
	__enable_irq();                         //This prevents the timers and interrupts to be in dilemma
	
}

void deinitTIM7(void)
{
	__disable_irq();
	TIM7->CR1 &= ~TIM_CR1_CEN;
	__enable_irq();                         //This prevents the timers and interrupts to be in dilemma
	
}

static void TIM2_IRQHandler(void)                 //This overwrites pre-extisitng functions. Static(Functions belongs to this C file alone.
{
	//Operation here
	TIM2->SR &= ~TIM_SR_UIF;
}


	