#ifndef UART_H_
#define UART_H_
#include <stdint.h >
#include "stm32f4xx.h"

void usart2_tx_init(void);
void usart2_rxtx_init(void);
void delayMs(int n);



#endif