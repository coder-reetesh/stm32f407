#include "stm32f4xx.h"
#include "systick_debouncing.h"
int main()
{
    int MS=25;
    //RCC->AHB1ENR ;
		RCC->APB2ENR;
    RCC->AHB1ENR = GPIODEN | GPIOAEN;
    
    GPIOD->MODER |=  ((1U<<24)|(1U << 26)|(1U<<28)|(1U<<30));
		GPIOD->MODER &= ~((1U<<25)|(1U << 27)|(1U<<29)|(1U<<31));
	
		systick(MS);
//	volatile unsigned int val =0;


	while(1)
	{
			LED_Process(push_btn_count);
	}
	return 0;
}