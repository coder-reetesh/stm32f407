#include "stm32f4xx.h"

/*Tested with ARM Compiler : version 5*/

void delayMs(int delay); 

void onLedGreen(){
	GPIOD->ODR |=(1<<12);	//GREEN
}

void offLedGreen(){
	GPIOD->ODR &=~(1<<12);	//GREEN
}

int main(void) {

	RCC->AHB1ENR |= (1<<3);   
	GPIOD->MODER |=((1<<24) & ~(1<<25)); 
	
	RCC->AHB1ENR |= (1<<3);   
	GPIOD->MODER |=((1<<26) & ~(1<<27)); 
	
	RCC->AHB1ENR |= (1<<3);   
	GPIOD->MODER |=((1<<28) & ~(1<<29));
	
	RCC->AHB1ENR |= (1<<3);   
	GPIOD->MODER |=((1<<30) & ~(1<<31)); 
	
	RCC->AHB1ENR |= (1<<3);   
	GPIOD->MODER |=((1<<18) & ~(1<<19));

	RCC->AHB1ENR |= (1<<3);   
	GPIOD->MODER |=((1<<10) & ~(1<<11));
	
	int count = 10000000;
	
	while (1) {
		//GPIOD->ODR ^=(1<<12);	//GREEN
		onLedGreen();
		delayMs(30);
		GPIOD->ODR ^=(1<<13);	//ORANGE
		delayMs(60);
		GPIOD->ODR ^=(1<<14);	//RED
		delayMs(30);
		GPIOD->ODR ^=(1<<15);	//BLUE
		delayMs(60);
		GPIOD->ODR ^=(1<<9);	//GREEN
		delayMs(30);
		GPIOD->ODR ^=(1<<5);	//RED
		delayMs(60);
		count--;
		if(count ==0){
			offLedGreen();
		}
	}
}

void delayMs(int n) {
    int i;
    for (; n > 0; n--)
        for (i = 0; i < 3195; i++) ;
}

