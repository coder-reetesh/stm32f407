#ifndef systick_debouncing_H
#define systick_debouncing_H

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
#define CTRL_ENABLE							(1U<<0)
#define CTRL_CLKSRC							(1U<<2)
#define CTRL_COUNTFLAG					    (1U<<16)
#define CTRL_TICKINT                         (1<<1)



uint32_t BTN_STATE_key_pressed();
void systick(int MS);
void LED_Process(uint32_t push_btn_count);

typedef enum {OFF =0, ON = 1}BTN_STATE;
extern uint32_t push_btn_count;

#endif