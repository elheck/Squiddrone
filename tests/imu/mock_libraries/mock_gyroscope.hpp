#ifndef MOCK_GYROSCOPE_HPP_
#define MOCK_GYROSCOPE_HPP_

#include <gmock/gmock.h>
#include <memory>
#include "gyroscope_interface.hpp"
#include "mock_i2c.hpp"

namespace imu {

class MockGyroscope : public GyroscopeInterface {
 public:
  MockGyroscope() : GyroscopeInterface(std::move(std::make_unique<i2c::MockI2C>())) {}
  MOCK_METHOD(types::DriverStatus, Init, (std::uint8_t i2c_address), (noexcept));
  MOCK_METHOD(types::DriverStatus, Update, (), (noexcept));
  MOCK_METHOD(types::ImuSensitivity, GetSensitivity, (), (noexcept));
  MOCK_METHOD(types::DriverStatus, SetSensitivity, (types::ImuSensitivity sensitivity), (noexcept));
  MOCK_METHOD(types::EuclideanVector<std::int16_t>, Get, (), (noexcept));
};
}  // namespace imu

#endif