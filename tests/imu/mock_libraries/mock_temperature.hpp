#ifndef MOCK_TEMPERATURE_HPP_
#define MOCK_TEMPERATURE_HPP_

#include <gmock/gmock.h>
#include <memory>
#include "mock_i2c.hpp"
#include "temperature_interface.hpp"

namespace imu {

class MockTemperature : public TemperatureInterface {
 public:
  MockTemperature() : TemperatureInterface(std::move(std::make_unique<i2c::MockI2C>())) {}
  MOCK_METHOD(types::DriverStatus, Init, (std::uint8_t i2c_address), (noexcept));
  MOCK_METHOD(types::DriverStatus, Update, (), (noexcept));
  MOCK_METHOD(int16_t, Get, (), (noexcept));
};
}  // namespace imu

#endif