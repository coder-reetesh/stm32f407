/*-----------------------------------------UART-----------------------------------------*/
#include<stdio.h>
#include<stdint.h >
#include"stm32f4xx.h"
/*---------------MACRO---------------*/
#define GPIOAEN     (1<<0)
#define UART2EN     (1<<17)
#define CR1_TE 			(1U<<3)
#define CR1_UE 			(1U<<13)
#define SR_TXE 			(1U<<7)

#define SYS_FRQ						16000000
#define APB1_CLK					SYS_FRQ
#define UART_BAUDRATE			115200

/*------------------------------FUNCTION------------------------------*/

//	compute_uart_bd Function
static uint16_t compute_uart_bd(uint32_t PeriphClk,uint32_t BaudRate)
{
		return (PeriphClk + (BaudRate /2U)/BaudRate);
}

//	uart_set_baudrate Function
static void uart_set_baudrate(USART_TypeDef *USARTx , uint32_t PeriphClk , uint32_t BaudRate)
{
		USARTx->BRR = compute_uart_bd(PeriphClk , BaudRate);
}

//	uart2_write Function
void uart2_write(int ch) //	2nd part (Video)
{
				//		Make sure the transmit data register is empty
		while(!(USART2->SR & SR_TXE)){}
				//		write to transmit the data Register
		USART2->DR = (ch &0xFF);
}

//	usart2_tx_init Function
void usart2_tx_init(void)
{
	/*******************************Configure UART GPIO PIN*******************************/
	//	Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	//	Set PA2 as a alternate function mode.
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);
	//	Set  PA2 as a Alternate Function type to UART_TX(AF07)
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);
	
	/*******************************Configure UART module*******************************/
	/*------------------Enable clock access to UART2------------------*/
	RCC->APB1ENR |= UART2EN;
	/*------------------Configure Baudrate------------------*/
	uart_set_baudrate(USART2 , APB1_CLK , UART_BAUDRATE);
	/*------------------Configure transfer(TX) direction------------------*/
	USART2->CR1 = CR1_TE;
	/*------------------Enable Uart module------------------*/
	USART2->CR1 = CR1_UE;
	
}
int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}
int main()
{
		usart2_tx_init();
	while(1)
	{
			printf("Hello from STM32F4xx......\n\r");
	}
}
