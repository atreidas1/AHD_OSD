#ifndef USART1_H_
#define USART1_H_

#include <stm32f1xx.h>
#include "mavlink/mavlink.h"

#define RX_BUFFER_SIZE0 512

void USART_init();
void USART_write (uint8_t* data, uint16_t sz);
void USART_writeByte(uint8_t byte);
uint8_t USART_readByte(void);
uint16_t USART_available(void);


uint8_t rx_buffer_overflow0;

// USART0 Receiver buffer

uint8_t rx_buffer0[RX_BUFFER_SIZE0];
uint16_t rx_wr_index0=0, rx_rd_index0 = 0;
uint16_t rx_counter0 = 0;

mavlink_status_t status;
mavlink_message_t msg;
int chan = 0;



mavlink_attitude_t attitude;
uint8_t attitudeNeedRead = 0;
mavlink_heartbeat_t heartbeat;
mavlink_sys_status_t sys_status;
mavlink_nav_controller_output_t cntr_out;
mavlink_battery_status_t bat_status;


void USART1_IRQHandler(void) {
//	if (READ_BIT(USART1->SR, USART_SR_RXNE)) { /*следим за состоянием даннго флага 1 — данные пришли, 0- пусто*/
//		rx_buffer0[rx_wr_index0++] = USART1->DR;
//		if (rx_wr_index0 == RX_BUFFER_SIZE0)
//			rx_wr_index0 = 0;
//		if (++rx_counter0 == RX_BUFFER_SIZE0) {
//			rx_counter0 = 0;
//			rx_buffer_overflow0 = 1;
//		}
//	}
	if (READ_BIT(USART1->SR, USART_SR_RXNE)) {
		if (mavlink_parse_char(chan, USART1->DR, &msg, &status)== MAVLINK_FRAMING_OK) {
			switch (msg.msgid) {
			case 30: {
				mavlink_msg_attitude_decode(&msg, &attitude);
				attitudeNeedRead = 1;
			}
				break;
			case MAVLINK_MSG_ID_HEARTBEAT: {
				mavlink_msg_heartbeat_decode(&msg, &heartbeat);
			}
				break;
			case MAVLINK_MSG_ID_SYS_STATUS: {
				mavlink_msg_sys_status_decode(&msg, &sys_status);
			}
				break;
			case MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT: {
				mavlink_msg_nav_controller_output_decode(&msg, &cntr_out);
			}
				break;

			case MAVLINK_MSG_ID_BATTERY_STATUS: {
				mavlink_msg_battery_status_decode(&msg, &bat_status);
			}
				break;
			default:
				break;
			}
		}
	}
}


uint8_t USART_readByte(void) {
	uint8_t data;
	while (rx_counter0 == 0);
	data = rx_buffer0[rx_rd_index0++];
	if (rx_rd_index0 == RX_BUFFER_SIZE0)
		rx_rd_index0 = 0;
	__disable_irq();
	--rx_counter0;
	__enable_irq();
	return data;
}

uint16_t USART_available(void) {
	return rx_counter0;
}

void USART_init() {
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	MODIFY_REG(GPIOA->CRH, GPIO_CRH_MODE10 | GPIO_CRH_CNF10_1 | GPIO_CRH_CNF9_0,
			GPIO_CRH_CNF10_0 | GPIO_CRH_MODE9 | GPIO_CRH_CNF9_1);
	if (READ_BIT(USART1->CR1, USART_CR1_UE) != (USART_CR1_UE)) {
		MODIFY_REG(USART1->CR1, USART_CR1_M | USART_CR1_PCE | USART_CR1_PS,
				USART_CR1_TE |USART_CR1_RE);
	}
	//Async Mode
	CLEAR_BIT(USART1->CR2, (USART_CR2_LINEN | USART_CR2_CLKEN));
	CLEAR_BIT(USART1->CR3, (USART_CR3_SCEN | USART_CR3_IREN | USART_CR3_HDSEL));
	// Пример вычисления значения BRR
	//	Частота тактирования UART1 72 мГц, нам нужна скорость 9600 бод. Вычисляем значение USARTDIV.
	//
	//	USARTDIV = Fck / (16 * BAUD) = 72000000 / (16 * 9600) = 468,75
	//
	//	Значение регистра USART_BRR = 468,75 * 16 = 7500.
	//
	//	USART1->BRR = 7500; // скорость 9600 бод
	USART1->BRR = 7500;
	USART1->CR1|=USART_CR1_RXNEIE; //Разрешаем генерировать прерывание по приему
	NVIC_EnableIRQ (USART1_IRQn); //Включаем прерывание, указываем вектор
	NVIC_SetPriority(USART1_IRQn, 4);
	//Enable
	SET_BIT(USART1->CR1, USART_CR1_UE);
}

void USART_write(uint8_t *data, uint16_t sz) {
	uint16_t ind = 0;
	while (ind < sz) {
		while (READ_BIT(USART1->SR, USART_SR_TXE) != (USART_SR_TXE)) {
		}
		USART1->DR = (uint16_t) data[ind];
		ind++;
	}
}

void USART_writeByte(uint8_t byte) {
	while (READ_BIT(USART1->SR, USART_SR_TXE) != (USART_SR_TXE)){}
	USART1->DR = (uint16_t) byte;
}

void USART_print(uint8_t *str) {
	uint8_t i = 0;
	uint8_t chr = 0;
	while((chr=*(str+i)) != 0){
		while (READ_BIT(USART1->SR, USART_SR_TXE) != (USART_SR_TXE)){}
		USART1->DR = (uint16_t) chr;
		i++;
	};
}


#endif /* USART1_H_ */
