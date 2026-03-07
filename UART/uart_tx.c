/*
SR = Status Register
CR = Control Register
SYS_FRQ = System Frequency for APB1_CLK enable
CR1_UE = USART enable
SR_TXE = Interrupt enable [ Transfer (TX) ]
SR_RXNE = Interrupt enable [ Receover (RX) ]

===================================WORK INSTRUCTION===================================
//	Compute_uart_bd Function
//	uart_set_baudrate Function
//	uart2_write Function
//	usart2_tx_init Function
	{
			1.	Enable clock access to GPIOA.
			2.	Set PA2 as a alternate function mode.
			3.	Set  PA2 as  	a Alternate Function type to UART_TX(AF07).
			4.	Configure UART module
					A)	Enable clock access to UART2
					B)	Configure Baudrate
					C)	Configure transfer(TX) direction
					D)	Enable Uart module
					E)	Enable clock access to UART2
					F)	Configure Baudrate
					G)	Configure transfer(TX) direction
					H)	Enable Uart module
	}	
*/
/*-----------------------------------------UART-----------------------------------------*/
#include<stdint.h>
#include"stm32f4xx.h"
/*---------------MACRO---------------*/
#define GPIOAEN     (1U<<0)
#define UART2EN     (1U<<17) 
#define CR1_TE 			(1U<<3)					//	Transmitter enable
#define CR1_UE 			(1U<<13)				//	USART enable
#define SR_TXE 			(1U<<7)					//	Interrupt enable

#define SYS_FRQ						16000000
#define APB1_CLK					SYS_FRQ
#define UART_BAUDRATE			115200
/*------------------------------FUNCTION------------------------------*/

//	compute_uart_bd Function
static uint16_t compute_uart_bd(uint32_t PeriphClk,uint32_t BaudRate)
{
		return (PeriphClk + (BaudRate /2U))/BaudRate;
}

//	uart_set_baudrate Function
static void uart_set_baudrate(USART_TypeDef *USARTx , uint32_t PeriphClk , uint32_t BaudRate)
{
	//
		USARTx->BRR = compute_uart_bd(PeriphClk , BaudRate);//(138<<4 | 7); //0x8A7 --> 10001010 0111
}

//	uart2_write Function
void uart2_write(char ch) //	2nd part (Video)
{
		//		Make sure the transmit data register is empty
		while(!(USART2->SR & SR_TXE)){}
				//		write to transmit the data Register
		USART2->DR = (ch &0xFF);
}

//	usart2_tx_init Function
void uart2_tx_init(void)
{
	/*******************************Configure UART GPIO PIN*******************************/
	//	Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	//	Set PA2 as a alternate function mode.
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);
	//	Set  PA2 as  	a Alternate Function type to UART_TX(AF07)
	GPIOA->AFR[0] |= 	(1U<<8);
	GPIOA->AFR[0] |= 	(1U<<9);
	GPIOA->AFR[0] |= 	(1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);
	
	/*******************************Configure UART module*******************************/
	/*------------------Enable clock access to UART2------------------*/
	RCC->APB1ENR |= UART2EN;
	/*------------------Configure Baudrate------------------*/
	uart_set_baudrate(USART2 , APB1_CLK , UART_BAUDRATE);
	/*------------------Configure transfer(TX) direction------------------*/
	USART2->CR1 = CR1_TE;
	/*------------------Enable Uart module------------------*/
	USART2->CR1 |= CR1_UE;
	
}

int main()
{
		uart2_tx_init();
	while(1)
	{
			uart2_write('H');
			uart2_write('e');
			uart2_write('l');
			uart2_write('l');
			for (volatile int i = 0; i < 100000; i++); // Small delay
		
	}
}
