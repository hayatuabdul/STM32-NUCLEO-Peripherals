#define FPGA_sel0_on		GPIOB->BSRR^=(1u<<10);   //Set BSRR register for control 1
#define FPGA_sel0_off	  GPIOB->BSRR^=(1u<<26);	 //Reset BSRR register for control 1

#define FPGA_sel1_on 		GPIOB->BSRR^=(1u<<11);   //Set BSRR register for control 2
#define FPGA_sel1_off		GPIOB->BSRR^=(1u<<27);   //Reset BSRR register for control 2

#define FPGA_data0_on		GPIOE->BSRR^=(1u<<15);   //Set BSRR register for data bus 0
#define FPGA_data0_off	GPIOE->BSRR^=(1u<<31);	 //Reset BSRR register for data bus 0

#define FPGA_data1_on 	GPIOE->BSRR^=(1u<<12);	 //Set BSRR register for data bus 1
#define FPGA_data1_off	GPIOE->BSRR^=(1u<<28);   //Reset BSRR register for data bus 1

#define FPGA_data2_on		GPIOE->BSRR^=(1u<<10);   //Set BSRR register for data bus 2
#define FPGA_data2_off	GPIOE->BSRR^=(1u<<26);	 //Reset BSRR register for data bus 2

#define FPGA_data3_on 	GPIOE->BSRR^=(1u<<2);    //Set BSRR register for data bus 3
#define FPGA_data3_off	GPIOE->BSRR^=(1u<<18);   //Reset BSRR register for data bus 3


void Init_FPGA(void);    //Initializes FPGA by setting and clearing the MODER direction of the pins
void FPGA_LED (void);    //This is a fucntion for the Output Data register of the FPGA pins
void FPGA_Comm (void);   //Evidence of 4-Bit mode communication by toggling the LEDS on the FPGA board