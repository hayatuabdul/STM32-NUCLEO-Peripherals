#ifndef timers_h
#define timers_h

void delay_us(int time_us);      //Timer set in Microseconds
void delay_ms(int time_ms);      //Timer set in Milliseconds
void tickdelayMs (int n);        //A system Tick timer that utilizes the SysTick

/*

@param time_s = the amount of time between interrupt calls.
*/
void initTIM2 (int time_s);      //An advanced timer to uses a fucntion to stay accurate

//@Brief  deinitalizes of Timer 2 to prevent it running again
void deinitTIM2(void);         //Disables the timer whilst on hold mode
void deinitTIM3(void);
void deinitTIM4(void);
void deinitTIM5(void);
void deinitTIM6(void);

void Wait3 (int delay_us);
void wait_us(uint32_t n);
void Init_Timer2(void);         //Used for an interrupt do display waveforms
void Init_Timer3(void);         //Used to transmit characters to USART
void Init_Timer4(void);         //Used for PWM
void Init_Timer5(void);         //Used as an inteerupt for the switch
void Init_Timer6(void);         //Used for ADC
void Init_Timer7(void);






#endif