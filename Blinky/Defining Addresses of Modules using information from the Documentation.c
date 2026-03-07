/******************************************************************************************
																				NOTES
-------------------------------------------------------------------------------------------
APB (BUS) : Stands for Advance Peripheral Bus
 AHB (BUS) : Stands for Advance High-performance Bus

Diffrece between AHB & APB bus is - 
				AHB bus is faster than APB Bus.
in some micro controller design you could have connected with bith AHB & AFB bus , 
so this mean if you want to access GPIOA in two clock cycles, you go through AHB. 
But if you need to access it a bit slower ,let's say like six cycles, you can use the APB.

 RCC  : Stands for Resetting Clock Control
******************************************************************************************/

/*
Where is LED Connected
PORT : 	A
PIN	 :	5
*/

#define PERIPH_BASE				(0x40000000UL)
#define AHB1PERIPH_OFFSET		(0x00020000UL)
#define AHB1PERIPH_BASE			(PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOA_OFFSET			(0x0000UL)
#dedine GPIOA_BASE				(PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET				(0x3800UL)
#define RCC_BASE					(AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1EN_R_OFFSET		(0x30UL)
#define RCC_AHB1EN_R			(*(volatile unsigned int*)(RCC_BASE + AHB1EN_R_OFFSET))

#define GPIOAEN						(1U<<0) //shift 1 at position 0

#define MODE_R_OFFSET			(0x00UL)
#define GPIOA_MODE_R			(*(volatile unsigned int*)(GPIOA_BASE + MODE_R_OFFSET))

#define OD_R_OFFSET				(0x14UL)
#define GPIO_OD_R					(*(volatile unsigned int*)(GPIOA_BASE + OD_R_OFFSET))

#define PIN5							(1U<<5)
#define LED_PIN						(PIN5)


//
int main()
{
	/*	1. Enable clock access to GPIOA		*/
		RCC_AHB1EN_R = GPIOAEN;
		
	/*	2. Set PA5 as output pin				*/
		GPIOA_MODE_R |=(1U<<10);
		GPIOA_MODE_R &= ~(1U<<11);
	while(1)
	{
		/*	3.	Set PA5 HIGh*/
		GPIO_OD_R |= LED_PIN;
		/*	4.	Toggle PA5 HIGh*/
		GPIO_OD_R ^= LED_PIN;
		for(int i=0;i<100000;i++){}
	}
}