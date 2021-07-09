#ifndef SRC_SPI_SPI_HPP_
#define SRC_SPI_SPI_HPP_

#include <array>
#include "mcu_settings.h"
#include "spi_interface.hpp"
#include "stm32g4xx_hal.h"

//preserve include order
#ifndef UNIT_TEST
#include "cspin.hpp"
#else
#include "cspin_mock.hpp"
#endif
#include "spi_config.h"

namespace spi {

/**
 * @brief Concrete implementation of the SPI interface.
 * 
 */
class SPI final : spi::SPIInterface {
 public:
  SPI() = delete;
  explicit SPI(CSPin &chip_select) : spi::SPIInterface(), chip_select_(chip_select){};
  virtual ~SPI() = default;

  auto Write(std::vector<std::uint8_t> &mosi_data_buffer) noexcept -> types::DriverStatus override;
  auto Transfer(std::vector<std::uint8_t> &mosi_data_buffer, std::vector<std::uint8_t> &miso_data_buffer) noexcept -> types::DriverStatus override;

 private:
  CSPin &chip_select_;

  auto IsTransactionLengthExceedingLimits(std::uint8_t transaction_length) noexcept -> bool;
  auto IsMisoBufferTooSmall(std::vector<std::uint8_t> &mosi_buffer, std::vector<std::uint8_t> &miso_buffer) noexcept -> bool;
  auto CheckHALReturnValue(HAL_StatusTypeDef hal_return_value) -> types::DriverStatus;
};

}  // namespace spi

#endif
