#include "Serial.h"

void UART_init(void){


	RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;   //ENABLE UART AND OUTPUT OF UART 
	
	//AFIO->MAPR |= AFIO_MAPR_USART1_REMAP;   //IF YOU WANT TO REMAP THE USART TO PB7 PB6

	
	// MAKING THE TX PIN AS OUTPUT, RX IS INPUT BY DEFEULT " FLOATING STATE "
	GPIOA->CRH |= GPIO_CRH_MODE9_0 | GPIO_CRH_CNF9_1;
	GPIOA->CRH &= ~(GPIO_CRH_CNF9_0);
	
	
	//USART1->BRR = 0X1D4C;  // SETTING THE BAUD RATE BY THE EQUATION ON THE DATA SHEET
	USART1->BRR = 0X271;
	
	// 						 RX ENABLE      TX ENABLE      UART ENABLE
	USART1->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;

/*	
	USART1->CR1 |= USART_CR1_RXNEIE | USART_CR1_TXEIE;  //TO ENABLE THE INTURREPT
	NVIC_EnableIRQ(USART1_IRQn);
*/
}

void printMsg(char *msg, ...)
{
 char buff[80];
 //#ifdef DEBUG_UART
 
 va_list args;
 va_start(args,msg);
 vsprintf(buff,msg,args);
 
 for(int i=0;i<strlen(buff);i++)
 {
   USART1->DR = buff[i];
   while(!(USART1->SR & USART_SR_TXE));
  }
 //#endif
} 

