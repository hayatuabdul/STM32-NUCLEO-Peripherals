#define short_press GPIOC->IDR & 1<<13    //If the input data register AND bit 13 is true, take action while still true. IDR is value of entiire register
#define long_press  GPIOC->IDR & 1<<13

void switch_led(void);   //A funtion that switches LED frequency upon user button press

void user_button_hold(void);  //A function that enables hold mode while disabling the hardware peripherals such as timer and LEDs