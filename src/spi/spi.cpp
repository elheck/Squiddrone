#include "spi.hpp"

namespace spi {
auto SPI::Write(std::vector<uint8_t> &mosi_data_buffer) noexcept -> types::DriverStatus {
  HAL_StatusTypeDef transmit_ret_value = HAL_ERROR;
  types::DriverStatus return_value = types::DriverStatus::HAL_ERROR;

  uint8_t transaction_length = static_cast<uint8_t>(mosi_data_buffer.size());

  if (IsTransactionLengthExceedingLimits(transaction_length)) {
    return types::DriverStatus::INPUT_ERROR;
  }

  chip_select_.SetCSActive();

  transmit_ret_value = HAL_SPI_Transmit(&hspi1,
                                        reinterpret_cast<uint8_t *>(mosi_data_buffer.data()),
                                        transaction_length,
                                        types::SPI_HAL_TX_RX_TIMEOUT);

  chip_select_.SetCSInactive();

  if (transmit_ret_value == HAL_OK) {
    return_value = types::DriverStatus::OK;
  }
  if (transmit_ret_value == HAL_TIMEOUT) {
    return_value = types::DriverStatus::TIMEOUT;
  }
  if (transmit_ret_value == HAL_ERROR) {
    return_value = types::DriverStatus::HAL_ERROR;
  }
  return return_value;
}

auto SPI::Transfer(std::vector<uint8_t> &mosi_data_buffer, std::vector<uint8_t> &miso_data_buffer) noexcept -> types::DriverStatus {
  HAL_StatusTypeDef transmit_receive_ret_value = HAL_ERROR;
  types::DriverStatus return_value = types::DriverStatus::HAL_ERROR;

  if (IsMisoBufferTooSmall(mosi_data_buffer, miso_data_buffer)) {
    return types::DriverStatus::INPUT_ERROR;
  }

  uint8_t transaction_length = static_cast<uint8_t>(miso_data_buffer.size());

  if (IsTransactionLengthExceedingLimits(transaction_length)) {
    return types::DriverStatus::INPUT_ERROR;
  }

  chip_select_.SetCSActive();

  transmit_receive_ret_value = HAL_SPI_TransmitReceive(&hspi1,
                                                       reinterpret_cast<uint8_t *>(mosi_data_buffer.data()),
                                                       reinterpret_cast<uint8_t *>(miso_data_buffer.data()),
                                                       transaction_length,
                                                       types::SPI_HAL_TX_RX_TIMEOUT);

  chip_select_.SetCSInactive();

  if (transmit_receive_ret_value == HAL_OK) {
    return_value = types::DriverStatus::OK;
  }
  if (transmit_receive_ret_value == HAL_TIMEOUT) {
    return_value = types::DriverStatus::TIMEOUT;
  }
  if (transmit_receive_ret_value == HAL_ERROR) {
    return_value = types::DriverStatus::HAL_ERROR;
  }
  return return_value;
}

auto SPI::IsTransactionLengthExceedingLimits(std::uint8_t transaction_length) noexcept -> bool {
  return transaction_length > types::SPI_TRANSACTION_LENGTH_LIMIT;
}

auto SPI::IsMisoBufferTooSmall(std::vector<uint8_t> &mosi_buffer, std::vector<uint8_t> &miso_buffer) noexcept -> bool {
  return miso_buffer.size() < mosi_buffer.size();
}

}  // namespace spi
