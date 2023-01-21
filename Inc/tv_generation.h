#ifndef TV_GENERATION_H_
#define TV_GENERATION_H_

#include <stm32f1xx.h>
#include "buffer.h"
#include "osd_position.h"
#include "utils.h"

#define START_LINE 30
//const uint16_t END_STR = 735;
#define LINES_PER_PIXEL 3

volatile uint8_t isFrame = 0;
volatile uint16_t strCounter = 0;
volatile uint8_t strRepitCounter = 0;
volatile uint16_t currentBufferStr = 0;




uint8_t serialBuffer[100];
uint8_t str_attitude1[] = "time_boot_ms: %10d";

uint16_t second = 0;
uint8_t frames = 0;
uint8_t buffer[12];

void EXTI3_IRQHandler(void) {
	SET_BIT(EXTI->PR, EXTI_PR_PR3); //Считаем Кадры PR - регистр ожидания. Если не записать 1 то не выйдем из прерывания
	strCounter = 0;
	isFrame = 1;
	currentBufferStr = 0;

	uint8_t *ptr;
	ptr = intToString(osd_data.satellites_visible, buffer);
	printStringWithPlaceholder(25, 4, ptr, 2);

	ptr = intToString(osd_data.alt, buffer);
	printStringWithPlaceholder(44, 108, ptr, 4);

	ptr = msToHourMinSecStr(osd_data.time_boot_ms, buffer);
	printStringWithPlaceholder(4, 227, ptr, 8);

	ptr = FPToString(osd_data.climb, buffer);
	printStringWithPlaceholder(45, 122, ptr, 6);

	ptr = FPToString(osd_data.voltage, buffer);
	printStringWithPlaceholder(25, 227, ptr, 4);

	ptr = intToString(osd_data.groundspeed, buffer);
	printStringWithPlaceholder(4, 108, ptr, 3);

	ptr = FPToString(osd_data.current_battery, buffer);
	printStringWithPlaceholder(33, 227, ptr, 5);

	ptr = intToString(osd_data.current_consumed, buffer);
	printStringWithPlaceholder(44, 227, ptr, 5);


}



void EXTI4_IRQHandler(void) {
	SET_BIT(EXTI->PR, EXTI_PR_PR4); //Считаем строки PR - регистр ожидания. Если не записать 1 то не выйдем из прерывания


	if (isFrame) {
		strCounter++;

		if (strCounter >= START_LINE) {
			DMA1_Channel3->CCR &= ~DMA_CCR_EN;
			SPI1->CR1 |= (SPI_CR1_SSI);
			TIM2->CR1 &= ~TIM_CR1_CEN;
			uint16_t *ptr = &osd_buffer[currentBufferStr];

			DMA1_Channel3->CMAR = (uint32_t) &osd_buffer[currentBufferStr];
			DMA1_Channel3->CNDTR = BUFFER_COLUMNS/2;
			DMA1_Channel3->CCR |= DMA_CCR_EN;

			TIM2->CNT = 0;
			SET_BIT(TIM2->CR1, TIM_CR1_CEN);
			SPI1->CR1 &= ~SPI_CR1_SSI;

			strRepitCounter++;
			if(strRepitCounter >= LINES_PER_PIXEL) {
				strRepitCounter = 0;
				if(currentBufferStr < BUFFER_LINES - 1) {
					currentBufferStr++;
				} else {
					isFrame = 0;

				}
			}
		}
	}
}

void SPI1_DMA_Init() {
	//Настройка SPI1
	//PA5 - SCK (floating input)
	//PA6 - MISO (Alternate function PUSH/PULL)


	RCC->APB2ENR |= (RCC_APB2ENR_SPI1EN | RCC_APB2ENR_IOPAEN);
	GPIOA->CRL &= ~(GPIO_CRL_CNF5_0 | GPIO_CRL_CNF6_0);
	GPIOA->CRL |= (GPIO_CRL_CNF5_0| GPIO_CRL_MODE6_0 | GPIO_CRL_MODE6_1 | GPIO_CRL_CNF6_1);
	SPI1->CR1 |= (SPI_CR1_SSM | SPI_CR1_DFF | SPI_CR1_BIDIOE | SPI_CR1_BIDIMODE | SPI_CR1_LSBFIRST);
	SPI1->CR2 |= SPI_CR2_TXDMAEN;
	SET_BIT(SPI1->CR1, SPI_CR1_SPE);
	SPI1->CR1 |= SPI_CR1_SSI;

	//Настройки DMA
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	DMA1_Channel3->CPAR = (uint32_t) &(SPI1->DR);

	DMA1_Channel3->CCR |= (DMA_CCR_PSIZE_0| DMA_CCR_MSIZE_0 | DMA_CCR_MINC | DMA_CCR_DIR );




}

void SPI_DMA_write(uint16_t *data, uint16_t size) {
	DMA1_Channel3->CCR &= ~DMA_CCR_EN;
	SPI1->CR1|= (SPI_CR1_SSI);
	TIM2->CR1 &= ~TIM_CR1_CEN;

	DMA1_Channel3->CMAR = (uint32_t) data;
	DMA1_Channel3->CNDTR = size;
	DMA1_Channel3->CCR |= DMA_CCR_EN;

	SPI1->DR=0;
	SPI1->CR1&= ~SPI_CR1_SSI;
	TIM2->CNT = 0;
	SET_BIT(TIM2->CR1, TIM_CR1_CEN);
}

void SPI_clock_init() {
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; //включить тактирование порта A
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //включить тактирование таймера 2
	//PA0 - выход ШИМ канал 1 таймер 2
	//выход, частота 50МГц
	//пушпул, альтернативная функция
	MODIFY_REG(GPIOA->CRL, GPIO_CRL_CNF0_0,
			(GPIO_CRL_CNF0_1 | GPIO_CRL_MODE0_0 | GPIO_CRL_MODE0_1));
	TIM2->PSC = 0;		//насколько делится максимальная частота
	TIM2->ARR = 5;		//до скольки таймер считает перед сбросом
	TIM2->CCR1 = 3;		//на каком числе переключение
	SET_BIT(TIM2->CCER, TIM_CCER_CC1E);	//разблокируем выход
	//OC1M = 110: режим 1 PWM - при счёте вверх, канал 1 находится в активном состоянии
	//пока TIMx_CNT<TIMx_CCR1, иначе канал будет в неактивном состоянии; при счёте вниз,
	//канал 1 находится в неактивном состоянии (OC1REF=0) пока TIMx_CNT>TIMx_CCR1,
	// иначе - в активном (OC1REF=1).
	SET_BIT(TIM2->CCMR1, (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2));
	SET_BIT(TIM2->CR1, TIM_CR1_CEN); //Включить таймер
}

void startTimer() {
	TIM2->CNT = 0;
	SET_BIT(TIM2->CR1, TIM_CR1_CEN);
}

void stopTimer() {
	CLEAR_BIT(TIM2->CR1, TIM_CR1_CEN);
}

void TV_EXTI_init() {
	//Захват синхроимпульсов от LM1881

	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPBEN); //Включаем тактирование порта B
	MODIFY_REG(GPIOB-> CRL, GPIO_CRL_CNF3_Msk, 0b10 << GPIO_CRL_CNF3_Pos); //PB3 01: Input with pull-up / pull-down
	MODIFY_REG(GPIOB-> CRL, GPIO_CRL_MODE3_Msk, 0b00 << GPIO_CRL_MODE3_Pos); //PB3 00: Input mode (reset state)

	//GPIOB->BSRR = GPIO_BSRR_BS3; //Intpu with pull-up
	SET_BIT(GPIOB->ODR, GPIO_ODR_ODR3);

	MODIFY_REG(GPIOB-> CRL, GPIO_CRL_CNF4_Msk, 0b10 << GPIO_CRL_CNF4_Pos); //PB4 01: Input with pull-up / pull-down
	MODIFY_REG(GPIOB-> CRL, GPIO_CRL_MODE4_Msk, 0b00 << GPIO_CRL_MODE4_Pos); //PB4 00: Input mode (reset state)
	//GPIOB->BSRR = GPIO_BSRR_BS4; //Intpu with pull-up
	SET_BIT(GPIOB->ODR, GPIO_ODR_ODR4);

	//Настройка EXTI для PB3 PB4
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_AFIOEN);//Запускаем тактирование альтернативных функций

	//Выбирам для PB3 селектор EXTI1 и выставляем EXTI3 для порта B
	MODIFY_REG(AFIO->EXTICR[0], AFIO_EXTICR1_EXTI3_Msk, 0b0001 << AFIO_EXTICR1_EXTI3_Pos);

	//Выбирам для PB4 селектор EXTI2 и выставляем EXTI4 для порта B
	MODIFY_REG(AFIO->EXTICR[1], AFIO_EXTICR2_EXTI4_Msk, 0b0001 << AFIO_EXTICR2_EXTI4_Pos);

	SET_BIT(EXTI->IMR, EXTI_IMR_MR3); //Разрешить прерывания EXTI3
	SET_BIT(EXTI->IMR, EXTI_IMR_MR4); //Разрешить прерывания EXTI4

	SET_BIT(EXTI->RTSR, EXTI_FTSR_TR3); //Порт PB3 выставляем прерывание по нарастающему фронту
	SET_BIT(EXTI->RTSR, EXTI_FTSR_TR4); //Порт PB4 выставляем прерывание по нарастающему фронту

	NVIC_EnableIRQ(EXTI3_IRQn); // Включаем прерывание
	NVIC_EnableIRQ(EXTI4_IRQn); // Включаем прерывание

	NVIC_SetPriority(EXTI4_IRQn, 2);
	NVIC_SetPriority(EXTI3_IRQn, 3);
}

void TV_generation_start() {
	TV_EXTI_init();
	SPI1_DMA_Init();
	SPI_clock_init();
	clearScreen(&osd_buffer[0][0]);

	OSD_STATIC_IMAGE();

}
#endif
