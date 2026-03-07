#include "stm32f4xx.h"

/*Tested with ARM Compiler : version 5*/



void delayMs(int delay); 
/*
void configureLed(uint32_t pin){
	RCC->AHB1ENR |= (1<<3); 
	GPIOD->MODER |=(1<< (pin*2));
	GPIOD->MODER &=~(1<< ((pin*2) +1) );
}

void onLedGreen(){
	GPIOD->ODR |=(1<<12);	//GREEN
}

void offLedGreen(){
	GPIOD->ODR &=~(1<<12);	//GREEN
}

unsigned int count = 3;
*/
int main(void) 
{
	
		  RCC->AHB1ENR |= (1<<0);  //Refference manual (page - 182 )
		  GPIOA->MODER &=((0<<1) & (0<<0));
		  /*--------------------------------------------------------*/		  
		  RCC->AHB1ENR |= (1<<3);   
          GPIOD->MODER |=((1<<24) & ~(1<<25)); 
	
		  RCC->AHB1ENR |= (1<<3);   
          GPIOD->MODER |=((1<<26) & ~(1<<27)); 

          RCC->AHB1ENR |= (1<<3);   
          GPIOD->MODER |=((1<<28) & ~(1<<29));
	
		  RCC->AHB1ENR |= (1<<3);   
          GPIOD->MODER |=((1<<30) & ~(1<<31)); 
 //configureLed(13); 
		  
	  while(1)
	  {
			GPIOD->ODR ^=(1<<12);	//GREEN
			delayMs(30);
			//GPIOD->ODR ^=(1<<13);	//ORANGE
			//delayMs(60);
			GPIOD->ODR ^=(1<<14);	//RED
			delayMs(30);
			GPIOD->ODR ^=(1<<15);	//BLUE
			delayMs(60);
			
			
			if((GPIOA->IDR & (1<<0))==1) 
			{
						
					GPIOD->ODR |=(1<<13);	//ORANGE
					delayMs(90);
					break;
						
			}
			else if(GPIOA->IDR==0x00){
					//`GPIOD->ODR &=(1<<13);	//ORANGE
			}
	
				//delayMs(20);
/*					count--;
					if(count ==0){
						offLedGreen();
					}
*/
	  }
}
void delayMs(int n) {
    int i;
    for (; n > 0; n--)
        for (i = 0; i < 3195; i++) ;
}

