#ifndef SRC_I2C_HANDLER_HPP_
#define SRC_I2C_HANDLER_HPP_

#include "stm32g4xx_hal.h"
#include "i2c_config.h"
#include "i2c_interface.hpp"

namespace i2c {

  class I2C final : public I2CInterface {
    public:
      ~I2C() = default;
      explicit I2C(void): I2CInterface(){};

      auto read(uint8_t address, uint16_t byte_size, uint32_t timeout=I2C_STANDARD_TIMEOUT_IN_MS) noexcept -> std::tuple<I2CStatus, std::vector<uint8_t>> override;
      auto write(uint8_t address, const std::vector<uint8_t>& data, uint32_t timeout=I2C_STANDARD_TIMEOUT_IN_MS) noexcept -> I2CStatus override;
    private:
      auto check_for_valid_input_read(uint8_t address, uint16_t byte_size, uint32_t timeout) noexcept -> bool;
      auto check_for_valid_input_write(uint8_t address, const std::vector<uint8_t>& data, uint32_t timeout) noexcept -> bool;
      auto modify_address_for_i2c_7bit(uint8_t address) noexcept -> uint8_t;
      auto get_i2c_status(HAL_StatusTypeDef hal_status) noexcept -> I2CStatus;
      auto check_if_i2c_address_is_valid(uint8_t address) noexcept -> bool;
      auto check_if_i2c_amount_of_bytes_is_valid(uint16_t amount_of_bytes) noexcept -> bool;
      auto check_if_i2c_timeout_is_valid(uint32_t timeout) noexcept -> bool;
  };

} // namespace i2c

#endif