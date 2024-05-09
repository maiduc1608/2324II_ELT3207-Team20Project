#include<stm32f10x.h>
#include <stm32_SysClkConf.h>

void PWM_Conf(void);
void setDutyCircle(uint32_t d);
int main(void){
	SysClkConf();
	PWM_Conf();
	setDutyCircle(1);
	while(1){
		
	}
}

void PWM_Conf(void){
	RCC->APB2ENR |= 0x04; //supply clock for GPIOA
	RCC->APB1ENR |= 0x02; //supply clock for TIM3

	//configure output A6, input A0, A4.
	GPIOA->CRL &= 0x4B464446;
	GPIOA->CRL |= 0x4B464446;
	
	//configure PWM.
	TIM3->PSC = 21-1;	//set prescaler.
	TIM3->ARR = 2-1;	//set the period of auto reload register.
	TIM3->CCMR1 &= 0x0068;
	TIM3->CCMR1 |= 0x068;	//choose PWM mode.

	TIM3->CR1 &= 0x01;
	TIM3->CR1 |= 0x01; //enable counter.

	TIM3->EGR |=0x01;
	TIM3->CCER |= 0x01; //enable OC1 of TIM3.
}

void setDutyCircle(uint32_t d){
		//set duty by percent of ARR value.
		TIM3->CCR1 = d;
	}
