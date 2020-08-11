/**
 * main.cpp
 *
 *  Created on: Oct 4, 2019
 *      Author: aron
 */

#include "stm32g4xx_hal.h"
//
#include "clock_config.h"
#include "cordic_config.h"
#include "crc_config.h"
#include "fmac_config.h"
#include "gpio_config.h"
#include "i2c_config.h"
#include "mcu_settings.h"
#include "serial_config.h"
#include "spi_config.h"
#include "timer_config.h"
#include "mcu_settings.h"
#include "com/com_message_buffer.hpp"
#include "com/nrf24l01.hpp"

int main() {
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_CORDIC_Init();
  MX_CRC_Init();
  MX_FMAC_Init();
  MX_I2C2_Init();
  MX_SPI1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM16_Init();
  MX_TIM17_Init();

  auto com_spi_handle = std::make_unique<spi::SPI>(CSCOM_Pin);
  auto com_msg_buffer = std::make_unique<com::ComMessageBuffer>();
  auto comsys = std::make_unique<com::NRF24L01>(std::move(com_spi_handle), std::move(com_msg_buffer));

  while (1) {
  }
  return 0;
}
