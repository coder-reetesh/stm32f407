/*
SR = Status Register
CR = Control Register
SYS_FRQ = System Frequency for APB1_CLK enable
CR1_UE = USART enable
SR_TXE = Interrupt enable [ Transfer (TX) ]
SR_RXNE = Interrupt enable [ Receiver (RX) ]

===================================WORK INSTRUCTION===================================
//	Compute_uart_bd Function
//	uart_set_baudrate Function
//	uart2_write Function
//	uart2_read Function
//	usart2_tx_init Function
	{
			1.	Enable clock access to GPIOA.
			2.	Set PA2 as a alternate function mode.
			3.	Set  PA2 ( TRANSMIT ) and PA3 ( RECEIVED ) as	a Alternate Function type to UART_TX(AF07).
			4.	Configure UART module
					A)	Enable clock access to UART2
					B)	Configure Baudrate
					C)	Set PA2 as a alternate function mode.			( TRANSMIT )
					D)	Set PA3 as a alternate function mode.			( RECEIVED )
					E)	Enable Uart module
					F)	Enable clock access to UART2
					G)	Configure Baudrate
					H)	Configure transfer(TX) and Receiver(RE) direction
					I)	Enable Uart module
					
	}	
*/

/*-----------------------------------------UART-----------------------------------------*/
#include<stdint.h>
#include<stdio.h>
#include"stm32f4xx.h"

/*---------------MACRO---------------*/
#define GPIOAEN     (1U<<0)
#define GPIODEN     (1U<<3)
#define UART2EN     (1U<<17) 

#define CR1_TE 			(1U<<3)					//	Transmitter enable (TX)
#define CR1_RE 			(1U<<2)					//	Receiver enable (RX)

#define CR1_UE 				(1U<<13)				//	USART enable
#define SR_TXE 				(1U<<7)					//	Interrupt enable (TX)
#define SR_RXNE 			(1U<<5)					//	Interrupt enable (RX)

#define SYS_FRQ						16000000
#define APB1_CLK					SYS_FRQ
#define UART_BAUDRATE			115200
//--------------LED PIN--------------
#define LED_GREEN_PIN   (1<<12)
#define LED_ORANGE_PIN  (1<<13)
#define LED_RED_PIN     (1<<14)
#define LED_BLUE_PIN    (1<<15)

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



static int y=0;
//	uart2_write Function
void uart2_write(char ch)
{
		//		Make sure the transmit data register is empty
		while(!(USART2->SR & SR_TXE)){y++;}
				//		write to transmit the data Register
		USART2->DR = (ch &0xFF);
}




//	uart2_read Function
char uart2_read(void)
{
				//		Make sure the receive data register is not empty
	volatile unsigned int UART_SR;
	UART_SR = USART2->SR;
		while(!(UART_SR & SR_RXNE)){
			UART_SR = USART2->SR;		
		}
				//		read transmit the data Register
		return USART2->DR;
}




//	usart2_tx_init Function
void uart2_rxtx_init(void)
{
	/*******************************Configure UART GPIO PIN*******************************/
	//	Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	//	Set PA2 as a alternate function mode.			( TRANSMIT )
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);
	
	//	----------Set PA3 as a alternate function mode.			( RECEIVED )----------
	GPIOA->MODER &= ~(1U<<6);
	GPIOA->MODER |= (1U<<7);
	
	//	Set  PA2 as a Alternate Function type to UART_TX(AF07)			( TRANSMIT )
	GPIOA->AFR[0] |= 	(1U<<8);
	GPIOA->AFR[0] |= 	(1U<<9);
	GPIOA->AFR[0] |= 	(1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);
	
	//	----------Set  PA3 as a Alternate Function type to UART_RX(AF07)			( RECEIVED )----------
	GPIOA->AFR[0] |= 	(1U<<12);
	GPIOA->AFR[0] |= 	(1U<<13);
	GPIOA->AFR[0] |= 	(1U<<14);
	GPIOA->AFR[0] &= ~(1U<<15);
	
/*******************************Configure UART module*******************************/
	
	/*------------------Enable clock access to UART2------------------*/
	RCC->APB1ENR |= UART2EN;
	
	/*------------------Configure Baudrate------------------*/
	uart_set_baudrate(USART2 , APB1_CLK , UART_BAUDRATE);
	
	/*------------------Configure transfer(TX) and Receiver(RE) direction------------------*/
	USART2->CR1 = (CR1_TE | CR1_RE);
	
	/*------------------Enable Uart module------------------*/
	USART2->CR1 |= CR1_UE;
}




/*//	printf function
int __io_putchar(int ch)
{
		uart2_write(ch);
		return ch;
}*/




//	delayMS(int n)
void delayMs(int n) 
{
    int i;
    for (; n > 0; n--)
    for (i = 0; i < 3195; i++) ;
}




// global veriable
char key;
int k=0;


int main()
{
		RCC->AHB1ENR |= GPIOAEN | GPIODEN;
		GPIOD->MODER &= ~((3<<24)|(3<<26)|(3<<28)|(3<<30)); //Clear All bits
		GPIOD->MODER |=  ((1<<24)|(1<<26)|(1<<28)|(1<<30)); // Set All Bits
		
		uart2_rxtx_init();
		
	while(1)
	{
			//printf("Program Ready to execute...\n\r");
			GPIOD->ODR =LED_GREEN_PIN;	//BLUE
			delayMs(2000);
		
					uart2_write('B');
					uart2_write('L');
					uart2_write('I');
					uart2_write('N');
					uart2_write('K');
					uart2_write(' ');
					uart2_write('\t');
					uart2_write('\n');
			//printf("Wait for your response...\n\r press 1 to Blink all LEDS \n\r");
			GPIOD->ODR =LED_ORANGE_PIN;	//BLUE
			delayMs(3000);
				key=uart2_read();
				if(key == '1')
				{
					for(int k=0;k<5;k++)
						{
							delayMs(3000);
							GPIOD->BSRR = LED_BLUE_PIN;
							delayMs(3000);
							GPIOD->BSRR = LED_GREEN_PIN;
							delayMs(3000);
							GPIOD->ODR =LED_RED_PIN;
							delayMs(4000);
							GPIOD->ODR =LED_ORANGE_PIN;
							delayMs(4000);
							uart2_write('R');
							uart2_write('E');
							uart2_write('A');
							uart2_write('D');
							uart2_write(' ');
							uart2_write('\t');
						}
					
				}
				else
				{
							uart2_write('W');
							uart2_write('R');
							uart2_write('O');
							uart2_write('N');
							uart2_write('G');
							uart2_write(' ');
							uart2_write('\t');
							GPIOD->ODR =LED_RED_PIN;
							delayMs(2500);
						//GPIOD->ODR &= ~(LED_GREEN_PIN | LED_BLUE_PIN | LED_RED_PIN | LED_ORANGE_PIN);
						//delayMs(30);
					//GPIOD->BSRR |=(1U<<21);
					key='0';
				}
	}
}
