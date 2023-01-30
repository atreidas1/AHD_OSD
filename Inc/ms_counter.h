#ifndef MS_COUNTER_H_
#define MS_COUNTER_H_

#include <stm32f1xx.h>
#define BOOT_MS ((TIM3->CNT)>>1)
void MsCounterInit() {
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; //включить тактирование таймера 2
	TIM3->PSC = 35999;		//насколько делится максимальная частота
//	TIM3->CR1 |= TIM_CR1_CKD_0;
	TIM3->CR1 |= TIM_CR1_CEN;
}


#endif /* MS_COUNTER_H_ */
