#include "ADC.h"



void ADC_init(uint16_t *samples){
	
		// change ADC clock prescaler 
		RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;

	
		// enable DMA1 clock
		RCC->AHBENR |= RCC_AHBENR_DMA1EN;

	
		// RCC clock for adc and ALT function 
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN ;

	
		/* A0 as ADC0, and A1 as ADC1 */
		GPIOA->CRL |= GPIO_CRL_CNF4_1;
		GPIOA->CRL &= ~(GPIO_CRL_CNF4_0);

		GPIOA->CRL |= GPIO_CRL_CNF5_1;
		GPIOA->CRL &= ~(GPIO_CRL_CNF5_0);


		/* setting sampling rate of A0-ADC0, and A-ADC1 */
		ADC1->SMPR2 |= ADC_SMPR2_SMP4_2 | ADC_SMPR2_SMP4_0 | ADC_SMPR2_SMP4_1 ;
		ADC1->SMPR2 |= ADC_SMPR2_SMP5_2 | ADC_SMPR2_SMP5_0 | ADC_SMPR2_SMP5_1 ;


		// set the sequance 
		ADC1->SQR1 |= ADC_SQR1_L_0;   //two conversions 
		ADC1->SQR3 |= (4<<0);   		  // channel 5 first sequance, From 0->4 are the first channel selsctor
		ADC1->SQR3 |= (5<<5);   			// channel 7 second sequance, (the channel << sequance+=5 )


		// adc control reg, scan and DMA
		ADC1->CR1 |= ADC_CR1_SCAN;
		ADC1->CR2 |= ADC_CR2_DMA;
	 	 


		//************************************
		//					DAM settings
		DMA1_Channel1->CPAR = (uint32_t)(&ADC1->DR);
		DMA1_Channel1->CMAR = (uint32_t)(samples);

		// how many transfer 
		DMA1_Channel1->CNDTR =2;

		// control reg, CIRCULAR MODE , MEMORY INCREAMENT, PREPHERAL SIZE, MEMORY SIZE
		DMA1_Channel1->CCR |= DMA_CCR1_CIRC | DMA_CCR1_MINC | DMA_CCR1_PSIZE_0 | DMA_CCR1_MSIZE_0;
		DMA1_Channel1->CCR |= DMA_CCR1_EN;

	 
	 

		// enable the adc and set it to continous mode 
		ADC1->CR2 |= ADC_CR2_ADON | ADC_CR2_CONT;
		for(int i =0;i<10000;i++);

		ADC1->CR2 |= ADC_CR2_ADON; 
		for(int i =0;i<10000;i++);

		ADC1->CR2 |= ADC_CR2_CAL; 
		for(int i =0;i<10000;i++);


}


