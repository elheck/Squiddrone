#include "sensor_single_value.hpp"

namespace imu {

auto SensorSingleValue::Update(void) noexcept -> types::DriverStatus {
  GeneralSensor::GetRawValues();

  if (ImuConnectionSuccessful()) {
    SetSensorValue(
        ConvertUint8BytesIntoInt16SensorValue(raw_values_).at(0));
    return types::DriverStatus::OK;
  }

  return types::DriverStatus::HAL_ERROR;
}

auto SensorSingleValue::Get(void) noexcept -> std::int16_t {
  return sensor_value_;
}

auto SensorSingleValue::SetSensorValue(const std::int16_t new_value) noexcept -> void {
  sensor_value_ = new_value;
}

}  // namespace imu