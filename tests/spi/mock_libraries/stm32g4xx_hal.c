#include "stm32g4xx_hal.h"

HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size,
                                          uint32_t Timeout) {
  return hspi->mock_return_value;
}

HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint16_t Size,
                                   uint32_t Timeout) {
  return hspi->mock_return_value;
}

void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState) {
  if (GPIOx) {
    GPIOx->mock_test_value = (uint8_t)PinState;
  }
}
