#include "Timer.h"

void timer4enablePWM(void)
{
		/* set alter-func and GPIOB */
		RCC->APB2ENR |= RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPBEN ;
		
	  RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; 
	

	  /* set B0,1,6,7,8,9 as outputs of the timer */
		GPIOB->CRL |= ((1<<0) | (1<<1) | (1<<3));			//B0
		GPIOB->CRL &= ~(1<<2);		

		GPIOB->CRL |= ((1<<4) | (1<<5) | (1<<7));			//B1	
		GPIOB->CRL &= ~(1<<6);		
	
		GPIOB->CRL |= ((1<<24) | (1<<25) | (1<<27));	//B6
		GPIOB->CRL &= ~(1<<26);
	
		GPIOB->CRL |= ((1<<28) | (1<<29) | (1<<31));  //B7
		GPIOB->CRL &= ~(1<<30);	
	
		GPIOB->CRH |= ((1<<0) | (1<<1) | (1<<3));			//B8
		GPIOB->CRH &= ~(1<<2);		

		GPIOB->CRH |= ((1<<4) | (1<<5) | (1<<7));			//B9
		GPIOB->CRH &= ~(1<<6);		
	
	
		GPIOA->CRL |= ((1<<24) | (1<<25) | (1<<27));	//A6
		GPIOA->CRL &= ~(1<<26);
	
		GPIOA->CRL |= ((1<<28) | (1<<29) | (1<<31));  //A7
		GPIOA->CRL &= ~(1<<30);	
		
		
	
		//enabling the clk for the timer
		TIM4->CR1 |= TIM_CR1_ARPE | TIM_CR1_DIR;      																										//auto reload/preload enableing, counting up
		TIM4->CR1 &= ~( TIM_CR1_CMS_0 | TIM_CR1_CMS_0 );   																							//edge allignd mode 00


		TIM4->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2PE; 														//CCMR2 for the third and fourth channel,preload enable, PWM mode 1, like 2 but inverted
		TIM4->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3PE | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4PE;


		TIM4->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;                 																			 //compare on match, channel 4,3



		//PWM freq = Fclk/PSC/ARR  72MHz/1000
		//PWM Duty = CCR4/ARR

		TIM4->PSC = 0; 																																								//72 MHz divided by--> 7200:
		TIM4->ARR = 7200; 			// ARR is the limit which defines the frequancy, f = 72e6/ARR

		TIM4->CCR1= 0; 				// CCR one for each channel which defines the insta-val of the wave, CCR = ARR * _sin(insta-val)
		TIM4->CCR2= 0; 	
		TIM4->CCR3= 0; 	
		TIM4->CCR4= 0; 
	
		TIM4->CR1 |= TIM_CR1_URS;  
		TIM4->DIER |= (1<<0);   //	We refreash the value of the CCR at the ovelflow of the timer, so the next pyra we get a new sin insta-val
		
}




void timer3enablePWM(void)
{
		/* set alter-func and GPIOB */
		RCC->APB2ENR |= RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPBEN ;
		
	  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; 
	
		// pins are defined in the tim4PWMenable
	
	
		//enabling the clk for the timer
		TIM3->CR1 |= TIM_CR1_ARPE | TIM_CR1_DIR;      																										//auto reload/preload enableing, counting up
		TIM3->CR1 &= ~( TIM_CR1_CMS_0 | TIM_CR1_CMS_0 );   																							//edge allignd mode 00


		TIM3->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2PE; 														//CCMR2 for the third and fourth channel,preload enable, PWM mode 1, like 2 but inverted
		TIM3->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3PE | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4PE;


		TIM3->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;                 																			 //compare on match, channel 4,3



		//PWM freq = Fclk/PSC/ARR  72MHz/1000
		//PWM Duty = CCR4/ARR

		TIM3->PSC = 0; 																																								//72 MHz divided by--> 7200:
		TIM3->ARR = 7200; 			// ARR is the limit which defines the frequancy, f = 72e6/ARR

		TIM3->CCR1= 0; 				// CCR one for each channel which defines the insta-val of the wave, CCR = ARR * _sin(insta-val)
		TIM3->CCR2= 0; 	
		TIM3->CCR3= 0; 	
		TIM3->CCR4= 0; 
	
		TIM3->CR1 |= TIM_CR1_URS;  
		TIM3->DIER |= (1<<0);   //	We refreash the value of the CCR at the ovelflow of the timer, so the next pyra we get a new sin insta-val
		
}


void set_TIM(uint16_t ARR, uint16_t CCR1, uint16_t CCR2, uint16_t CCR3){

		TIM4->ARR = ARR; 			// ARR is the limit which defines the frequancy, f = 72e6/ARR

		TIM4->CCR1= CCR1; 				// CCR one for each channel which defines the insta-val of the wave, CCR = ARR * _sin(insta-val)
		TIM4->CCR2= CCR2; 	
		TIM4->CCR3= CCR3; 	
	
}

void start_timers(void){
		TIM3->EGR |= TIM_EGR_UG; //starting the timer
		TIM3->CR1 |= TIM_CR1_CEN; //starting the timer
	
		TIM4->EGR |= TIM_EGR_UG; //starting the timer
		TIM4->CR1 |= TIM_CR1_CEN; //starting the timer
}





void timer2enablePWM(void)
{

	  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; 
	
		//enabling the clk for the timer
		TIM2->CR1 |= TIM_CR1_ARPE | TIM_CR1_DIR;      																									//auto reload/preload enableing, counting up
		TIM2->CR1 &= ~( TIM_CR1_CMS_0 | TIM_CR1_CMS_0 );   																							//edge allignd mode 00
	
		TIM2->PSC = 2190; 																																								//72 MHz divided by--> 7200:
		TIM2->ARR = 7200; 			// ARR is the limit which defines the frequancy, f = 72e6/ARR

		TIM2->CCR1= 0; 				// CCR one for each channel which defines the insta-val of the wave, CCR = ARR * _sin(insta-val)
		TIM2->CCR2= 0; 	
		TIM2->CCR3= 0; 	
		TIM2->CCR4= 0; 
	
		TIM2->CR1 |= TIM_CR1_URS;  
		TIM2->DIER |= (1<<0);   //	We refreash the value of the CCR at the ovelflow of the timer, so the next pyra we get a new sin insta-val
		
}
