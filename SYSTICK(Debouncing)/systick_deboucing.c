#include "stm32f4xx.h"

/*****************PORT*****************/
#define 		GPIOAEN   		(1<<0)
#define 		GPIODEN   		(1<<3)
/*****************LED*****************/
#define LED_GREEN_PIN   	    (1<<12)
#define LED_ORANGE_PIN  	    (1<<13)
#define LED_RED_PIN     		(1<<14)
#define LED_BLUE_PIN    		(1<<15)
/**********************SYSTICK**********************/
#define SYSTICK_LOAD_VAL 				    16000000
#define CTRL_ENABLE									(1U<<0)
#define CTRL_CLKSRC									(1U<<2)
#define CTRL_COUNTFLAG					    (1U<<16)
#define CTRL_TICKINT                 (1<<1)


typedef enum {OFF =0, ON = 1}BTN_STATE;
uint32_t push_btn_count=0;

/************BTN_STATE************/
BTN_STATE key_pressed()
{
	return (BTN_STATE)(GPIOA->IDR & 0x01UL);
}

/************debounce function************/

uint8_t debounce()
{
	static uint8_t btn_state = OFF;
    static uint8_t btn_debounce_state = OFF;

	btn_state = btn_state << 1 | key_pressed();
	// 25ms systick, stable for 160ms

	if(btn_state == 0xf)
	{
		btn_debounce_state = ON;
	}
	else 
	{
		btn_debounce_state = OFF;
	}
	return btn_debounce_state;
}

/*--------------------SysTick Function--------------------*/
void systick(int MS)
{
		/*Reload with number of clocks per milisecond*/
		SysTick->LOAD = (SYSTICK_LOAD_VAL/1000)*MS;			// SYSTICK_LOAD_VAL 				16000000
		
		/*Clear Systick Current Value register*/
		SysTick->VAL=0;
		
		/*Enable Systick and select internal clock source*/
		SysTick->CTRL=(CTRL_ENABLE | CTRL_CLKSRC | CTRL_TICKINT);       //	CTRL_ENABLE	(1U<<0)
		                                                                //	CTRL_CLKSRC	(1U<<2)		
		//SysTick->CTRL=0;
}

/*--------------------LED_Process--------------------*/

void LED_Process(uint32_t push_btn_count)
{
    if(push_btn_count == 1)
			{
					GPIOD->ODR = LED_GREEN_PIN;
			}
		else if(push_btn_count == 2)
			{
			    GPIOD->ODR &= ~LED_GREEN_PIN;
					GPIOD->ODR = LED_ORANGE_PIN;
			}
		else if(push_btn_count == 3)
			{
					GPIOD->ODR &= ~LED_ORANGE_PIN;
					GPIOD->ODR = LED_RED_PIN;
			}
		else if(push_btn_count == 4)
			{
			    GPIOD->ODR &= ~LED_RED_PIN;
				GPIOD->ODR = LED_BLUE_PIN;
      		}
			else
			{
					GPIOD->ODR &=~ (LED_BLUE_PIN | LED_RED_PIN | LED_ORANGE_PIN | LED_GREEN_PIN);
			}
}


/*--------------------SysTick Handler--------------------*/

void SysTick_Handler(void)
{
		if(debounce()==ON)
		{
			if(push_btn_count>=4)
			{
					push_btn_count=0;
			}
			else
			{
					++push_btn_count;
			}
		}
}
