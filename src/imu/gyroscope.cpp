#include "gyroscope.hpp"

namespace imu {

auto Gyroscope::Init(std::uint8_t i2c_address) noexcept -> types::HalError {
  SetI2CAdress(i2c_address);
  initialized_ = false;

  if (!Mpu9255Detected()) {
    return types::HalError::CONFIG_ERROR;
  }

  initialized_ = true;
  sensor_values_.x = 0;
  sensor_values_.y = 0;
  sensor_values_.z = 0;

  if (!ImuConnectionSuccessful(SetSensitivity(sensitivity_))) {
    initialized_ = false;
    return types::HalError::CONFIG_ERROR;
  }

  return types::HalError::WORKING;
}

auto Gyroscope::Update(void) noexcept -> types::HalError {
  if (!initialized_)
    return types::HalError::CONFIG_ERROR;

  types::HalError imu_status;
  std::vector<uint8_t> data;
  std::tie(imu_status, data) = ReadDataBytes(GYRO_XOUT_H, 6);

  if (ImuConnectionSuccessful(imu_status)) {
    sensor_values_.x = ConvertUint8BytesIntoInt16SensorValue(data.at(0), data.at(1));
    sensor_values_.y = ConvertUint8BytesIntoInt16SensorValue(data.at(2), data.at(3));
    sensor_values_.z = ConvertUint8BytesIntoInt16SensorValue(data.at(4), data.at(5));
  }

  return types::HalError::WORKING;
}

auto Gyroscope::SetSensitivity(types::GyroscopeSensitivity gyroscope_sensitivity) noexcept -> types::HalError {
  if (!initialized_) {
    return types::HalError::CONFIG_ERROR;
  }

  uint8_t gyro_fs_sel = 0;

  if (gyroscope_sensitivity == types::GyroscopeSensitivity::FINEST) {
    gyro_fs_sel = 0b00;  /// +- 250 dps full scale; 131 °/s sensitivity
  } else if (gyroscope_sensitivity == types::GyroscopeSensitivity::FINER) {
    gyro_fs_sel = 0b01;
  } else if (gyroscope_sensitivity == types::GyroscopeSensitivity::ROUGHER) {
    gyro_fs_sel = 0b10;
  } else if (gyroscope_sensitivity == types::GyroscopeSensitivity::ROUGHEST) {
    gyro_fs_sel = 0b11;  /// +- 2000 dps full scale; 16.4 °/s sensitivity
  }

  types::HalError imu_status;
  std::vector<uint8_t> gyro_config;
  std::tie(imu_status, gyro_config) = ReadDataBytes(GYRO_CONFIG, 1);

  if (!ImuConnectionSuccessful(imu_status)) {
    return types::HalError::CONFIG_ERROR;
  }

  uint8_t new_gyro_config = gyro_config.at(0) | gyro_fs_sel << 3;
  std::vector<uint8_t> data = {GYRO_CONFIG, new_gyro_config};
  imu_status = Write(data);

  if (!ImuConnectionSuccessful(imu_status)) {
    return types::HalError::CONFIG_ERROR;
  }

  sensitivity_ = gyroscope_sensitivity;
  return types::HalError::WORKING;
}

auto Gyroscope::GetSensitivity(void) noexcept -> types::GyroscopeSensitivity {
  return sensitivity_;
}

}  // namespace imu