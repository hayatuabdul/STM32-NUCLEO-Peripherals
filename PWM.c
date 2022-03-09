#include <stm32f4xx.h>
#include "DELAY.h"

//Timer 4 is used to enable the PWM below. The PWM is tested by setting a frequency to it
void Init_Timer4(void)
{
	TIM4->CCMR1=0X0060;                 //Enable PWM 
	TIM4->CCER=1;                       //Enable PWM CH1
	TIM4->CCR1=8889-1;                  //Pulse width is 1/3 of period

	RCC->APB1ENR|=RCC_APB1ENR_TIM4EN;		//timer 4 clock enabled
	TIM4->DIER|=TIM_DIER_UIE;						//timer uptdate interrupt enabled
	
	//PWM FREQ = Fclk/PSC/ARR. My clock is 16MHz. To get 1KHz frequncy, clock/freq should be set in the PSC and ARR.
	//PWM DUTY = CCR4/ARR
	TIM4->PSC=16;										    //Clock speed as prescaler
	TIM4->ARR=1000;                     //(ARR)1000 as ARR because of freq. 16 * 1000 was our result when divded from clock speed
	TIM4->CCR4=50;                      //Percentage of duty cycle
	TIM4->CNT=0;												//zero timer counter
	NVIC->ISER[0]|=(1u<<30);						//timer 4 global interrupt enabled
	TIM4->CR1|=TIM_CR1_CEN;							//start timer counter
}