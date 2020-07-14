/*
	Six Step Comm code for the stm32, first 60deg and the last are PWM
	
	hall sensors --> done
	timersPWM --> done
	
	ALGOimplementation 
	
	speedcontroller
	
		// TIM4ch1 -> S1H
		// TIM4ch2 -> S2H
		// TIM4ch3 -> S3H

		// TIM3ch1 -> S1L
		// TIM3ch2 -> S2L
		// TIM3ch3 -> S3L

*/

#include "Serial.h"
#include "sine.h"
#include "ADC.h"
#include "Timer.h"
#include <math.h>


uint16_t samples[2];
_Bool hallA=0;
_Bool hallB=0;
_Bool hallC=0;

uint8_t STEP=0; 

void sensor_pin_init(void){
	/* A0,1,2, inputs with pull up with inturrepts */

	GPIOA->CRL |= (1<<3);
	GPIOA->CRL &= ~(1<<2);		

	GPIOA->CRL |= (1<<7);
	GPIOA->CRL &= ~(1<<6);		
	
	GPIOA->CRL |= (1<<11);
	GPIOA->CRL &= ~(1<<10);		
	
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN;
	AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PA | AFIO_EXTICR1_EXTI1_PA | AFIO_EXTICR1_EXTI2_PA;
	
	EXTI->RTSR |= ((1<<0)|(1<<1)|(1<<2));
	EXTI->IMR |= ((1<<0)|(1<<1)|(1<<2));
	
}










uint8_t steps(){
  
		if( hallA == 1 && hallB == 0 && hallC == 0 ){         // step 6  //100
			STEP = 6;
			
    }    
    else if( hallA == 0 && hallB == 1 && hallC == 0 ){  // step 4  //010  
			STEP = 4;
			
    }
    else if( hallA == 1 && hallB == 1 && hallC == 0){  // step 5  //110
			STEP = 5;
			
    }
    else if( hallA == 0 && hallB == 0 && hallC ==1 ){   // step 2  //001
			STEP = 2;
			
    }
    else if( hallA == 1 && hallB ==0 && hallC ==1 ){    // step 1  //101
			STEP = 1;
			
    }
    else if( hallA == 0 && hallB == 1 && hallC == 1 ){  // step 3  //011
			STEP = 3;
			
    }
		else{
			STEP = 0;
			
    }
   		
}


void action(uint8_t step){
    uint16_t high_speed = map(samples[0],0,4096,0,7200);
	
    switch (step) {
			
      case 1:
				TIM4->CCR1=high_speed;			//S1H
				TIM3->CCR1=0;								//S1L
			
				TIM4->CCR2=0;								//S2H
				TIM3->CCR2=high_speed;			//S2L
			
				TIM4->CCR3=0;								//S3H
				TIM3->CCR3=0;								//S3L
        break;
        
      case 2:
				TIM4->CCR1=high_speed;			//S1H
				TIM3->CCR1=0;								//S1L
			
				TIM4->CCR2=0;								//S2H
				TIM3->CCR2=0;								//S2L
			
				TIM4->CCR3=0;								//S3H
				TIM3->CCR3=high_speed;			//S3L
        break;

      case 3:
				TIM4->CCR1=0;								//S1H
				TIM3->CCR1=0;								//S1L
			
				TIM4->CCR2=high_speed;			//S2H
				TIM3->CCR2=0;								//S2L
			
				TIM4->CCR3=0;								//S3H
				TIM3->CCR3=high_speed;			//S3L
        break;
        
      case 4:
				TIM4->CCR1=0;								//S1H
				TIM3->CCR1=high_speed;			//S1L
			
				TIM4->CCR2=high_speed;			//S2H
				TIM3->CCR2=0;								//S2L
			
				TIM4->CCR3=0;								//S3H
				TIM3->CCR3=0;								//S3L
        break;
        
      case 5:
				TIM4->CCR1=0;								//S1H
				TIM3->CCR1=high_speed;			//S1L
			
				TIM4->CCR2=0;								//S2H
				TIM3->CCR2=0;								//S2L
			
				TIM4->CCR3=high_speed;			//S3H
				TIM3->CCR3=0;								//S3L
        break;
        
      case 6:
				TIM4->CCR1=0;								//S1H
				TIM3->CCR1=0;								//S1L
			
				TIM4->CCR2=0;								//S2H
				TIM3->CCR2=high_speed;			//S2L
			
				TIM4->CCR3=high_speed;			//S3H
				TIM3->CCR3=0;								//S3L
        break;
        
      default:

        break;
			
  }  
}



int main(){
	
	// utilites
	UART_init();
	ADC_init(samples);
	
	// sensro inturrept
	sensor_pin_init();
	
	// Timers PWM
	timer3enablePWM();
	timer4enablePWM();
	start_timers();
	
	printMsg("starting");
	
	TIM4->CCR1=4800;
	TIM3->CCR1=7200/2;	
	
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);

	



	while(1){	
		
		
		TIM4->CCR1=TIM4->CCR2=TIM4->CCR3=map(samples[0],0,4096,0,7200);
		
		TIM3->CCR1=TIM3->CCR2=TIM3->CCR3=(7200-map(samples[0],0,4096,0,7200));
		
	}
	
}

void  EXTI0_IRQHandler(){
	hallA=!hallA;
	steps();
	action(STEP);
	EXTI->PR |= (1<<0); 
	printMsg("zero ext");
}
 
void  EXTI1_IRQHandler(){
	hallB=!hallB;
	steps();
	action(STEP);
	EXTI->PR |= (1<<0); 
	printMsg("one ext");
}

void  EXTI2_IRQHandler(){
	hallB=!hallB;
	steps();
	action(STEP);
	EXTI->PR |= (1<<0); 
	printMsg("two ext");
}

