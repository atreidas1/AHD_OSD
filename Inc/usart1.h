#ifndef USART1_H_
#define USART1_H_

#include <stm32f1xx.h>
#include "mavlink/mavlink.h"
#include "osd_data.h"
#include "utils.h"

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

Osd_data osd_data;

uint8_t messages[40];
uint8_t index1 = 0;

void USART1_IRQHandler(void) {
	if (READ_BIT(USART1->SR, USART_SR_RXNE)) {
		if (mavlink_parse_char(chan, USART1->DR, &msg, &status)) {
			contain(msg.msgid);
			switch (msg.msgid) {
			case MAVLINK_MSG_ID_ATTITUDE: {
				osd_data.pitch = round(ToDeg(mavlink_msg_attitude_get_pitch(&msg)));
				osd_data.roll = round(ToDeg(mavlink_msg_attitude_get_roll(&msg)));
			}
				break;
			case MAVLINK_MSG_ID_HEARTBEAT: {
				osd_data.custom_mode = mavlink_msg_heartbeat_get_custom_mode(&msg);
				osd_data.system_status = mavlink_msg_heartbeat_get_system_status(&msg);
				uint8_t curr_base_mode =  mavlink_msg_heartbeat_get_base_mode(&msg);
				//if was armed just now
				if((curr_base_mode & MAV_MODE_FLAG_SAFETY_ARMED) && !(osd_data.base_mode & MAV_MODE_FLAG_SAFETY_ARMED)) {
					osd_data.arming_time_ms = osd_data.time_boot_ms;
					osd_data.home_lat = osd_data.lat;
					osd_data.home_lon = osd_data.lon;
					osd_data.total_distance = 0;
				}
				osd_data.base_mode = curr_base_mode;
			}
				break;
			case MAVLINK_MSG_ID_GPS_RAW_INT: {
				osd_data.fix_type = mavlink_msg_gps_raw_int_get_fix_type(&msg);
				osd_data.satellites_visible = mavlink_msg_gps_raw_int_get_satellites_visible(&msg);
			}
				break;
			case MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT: {
				osd_data.nav_bearing = mavlink_msg_nav_controller_output_get_nav_bearing(&msg);
				osd_data.target_bearing = mavlink_msg_nav_controller_output_get_target_bearing(&msg);
				osd_data.wp_dist = mavlink_msg_nav_controller_output_get_wp_dist(&msg);
			}
				break;

			case MAVLINK_MSG_ID_BATTERY_STATUS: {
				osd_data.current_consumed = mavlink_msg_battery_status_get_current_consumed(&msg);
				osd_data.current_battery = mavlink_msg_battery_status_get_current_battery(&msg)/10;
				osd_data.voltage = mavlink_msg_battery_status_get_voltages_i(&msg, 0)/100;
			}
				break;
			case MAVLINK_MSG_ID_VFR_HUD: {
				osd_data.airspeed = mavlink_msg_vfr_hud_get_airspeed(&msg)*36;
				osd_data.groundspeed = mavlink_msg_vfr_hud_get_groundspeed(&msg)*3.6;
				//osd_data.alt = mavlink_msg_vfr_hud_get_alt(&msg);
				osd_data.climb = toFixedPoint1(mavlink_msg_vfr_hud_get_climb(&msg));
				osd_data.heading = mavlink_msg_vfr_hud_get_heading(&msg);
				osd_data.throttle = mavlink_msg_vfr_hud_get_throttle(&msg);
			}
				break;

			case MAVLINK_MSG_ID_RC_CHANNELS_RAW: {
				osd_data.rssi = mavlink_msg_rc_channels_get_rssi(&msg);
				osd_data.time_boot_ms = mavlink_msg_rc_channels_get_time_boot_ms(&msg);
			}

		     	break;

			case MAVLINK_MSG_ID_GLOBAL_POSITION_INT: {
				osd_data.alt = mavlink_msg_global_position_int_get_relative_alt(&msg)/1000;
				osd_data.lat = mavlink_msg_global_position_int_get_lat(&msg);///10000000.0;
				osd_data.lon = mavlink_msg_global_position_int_get_lon(&msg);///10000000.0;

				//osd_data.alt2 = mavlink_msg_global_position_int_cov_get_alt(&msg);
			}

				break;
			default:
				break;
			}
		}

	}
}

void contain(uint8_t id){
	uint8_t contains = 0;
	for (int var = 0; var < index1; var++) {
		if(messages[var] == id) {
			contains = 1;
			break;
		}
	}

	if(contains == 0 || index1==0) {
		messages[index1] = id;
		index1++;
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
	USART1->BRR = 1250;
	USART1->CR1|=USART_CR1_RXNEIE; //Разрешаем генерировать прерывание по приему
	NVIC_EnableIRQ (USART1_IRQn); //Включаем прерывание, указываем вектор
	NVIC_SetPriority(USART1_IRQn, 3);
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
