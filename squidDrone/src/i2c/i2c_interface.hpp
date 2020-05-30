#ifndef SRC_I2C_INTERFACE_HPP_
#define SRC_I2C_INTERFACE_HPP_

#include "i2c_status.hpp"
#include <stdint.h>
#include <vector>
#include <tuple>

namespace i2c {

  class I2CInterface {
    public:
      virtual ~I2CInterface() = default;
      explicit I2CInterface(void){};

      virtual auto Read(uint8_t address, uint16_t byte_size, uint32_t timeout=I2C_STANDARD_TIMEOUT_IN_MS) noexcept -> std::tuple<I2CStatus, std::vector<uint8_t>> = 0;
      virtual auto Write(uint8_t address, const std::vector<uint8_t>& data, uint32_t timeout=I2C_STANDARD_TIMEOUT_IN_MS) noexcept -> I2CStatus = 0;
    protected:
      static constexpr int I2C_STANDARD_TIMEOUT_IN_MS = 200;
  };

} // namespace i2c

#endif