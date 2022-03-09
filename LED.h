#include <stm32f4xx.h>

#define Green_led_on		GPIOB->BSRR^=(1u<<0)
#define Green_led_off		GPIOB->BSRR^=(1u<<16)      //+16 to clear BSRR pin

#define Blue_led_on			GPIOB->BSRR^=(1u<<7)
#define Blue_led_off		GPIOB->BSRR^=(1u<<23)

#define Red_led_on			GPIOB->BSRR^=(1u<<14)
#define Red_led_off		  GPIOB->BSRR^=(1u<<30)

//External LEDs definition
#define ex_LED1_on		  GPIOC->BSRR^=(1u<<8)
#define ex_LED1_off		  GPIOC->BSRR^=(1u<<24)

#define ex_LED2_on			GPIOC->BSRR^=(1u<<9)
#define ex_LED2_off		  GPIOC->BSRR^=(1u<<25)

#define ex_LED3_on			GPIOC->BSRR^=(1u<<10)
#define ex_LED3_off		  GPIOC->BSRR^=(1u<<26)

#define ex_LED4_on			GPIOC->BSRR^=(1u<<11)
#define ex_LED4_off		  GPIOC->BSRR^=(1u<<27)




void Toggle_LED (void);        //Toggles Green LED with ODR
void Toggle_LED2 (void);       //Toggles Blue LED with ODR
void Toggle_LED3 (void);       //Toggles Red LED with ODR
void Toggle_exLED (void);
void Toggle_exLED2 (void);
void Toggle_exLED3 (void);
void Toggle_exLED4 (void);
void delay_ms(int time_ms);
void Morse(int duration);      //A function that transmits characters in Morse code to the Blue LED. 
void exLEDs (void);	           //Funtion that dsplays and change LEDs depedning on ADC voltage
void Init_Morse(void);	       //Starts the Morse function
void Init_LED(void);