#include "mpu9255.hpp"

namespace imu {

auto Mpu9255::Init(void) noexcept -> types::DriverStatus {
  CreateSensorPointer();

  SetInitConfigMPU9255();

  if (InitAllSensors()) {
    SetToInitialized();
    return types::DriverStatus::OK;
  }
  return types::DriverStatus::HAL_ERROR;
}

auto Mpu9255::CreateSensorPointer(void) noexcept -> void {
  if (gyroscope_ == nullptr) {
    gyroscope_ = std::make_unique<imu::Gyroscope>(i2c_handler_);
  }
  if (accelerometer_ == nullptr) {
    accelerometer_ = std::make_unique<imu::Accelerometer>(i2c_handler_);
  }
  if (magnetometer_ == nullptr) {
    magnetometer_ = std::make_unique<imu::Magnetometer>(i2c_handler_);
  }
  if (temperature_ == nullptr) {
    temperature_ = std::make_unique<imu::Temperature>(i2c_handler_);
  }
}

auto Mpu9255::SetInitConfigMPU9255(void) noexcept -> void {
  auto int_pin_cfg_value = std::make_unique<utilities::Byte>(0);
  int_pin_cfg_value->SetBit(1);  // Set I2C Master of MPU9255 to Bypass mode
  int_pin_cfg_value->SetBit(5);  // Held Pin Level until interrupt status was cleared.
  SetMPU9255Register(INT_PIN_CFG, int_pin_cfg_value->Get());

  auto int_enable_value = std::make_unique<utilities::Byte>(0);
  int_enable_value->SetBit(0);  // Enable Raw Sensor Data Ready interrupt to propagate to interrupt pin.
  SetMPU9255Register(INT_ENABLE, int_enable_value->Get());
}

auto Mpu9255::SetMPU9255Register(const std::uint8_t register_, const std::uint8_t register_value) noexcept -> void {
  i2c_handler_->Write(MPU9255_ADDRESS, {register_, register_value});
}

auto Mpu9255::InitAllSensors(void) noexcept -> bool {
  return (gyroscope_->Init(MPU9255_ADDRESS) == types::DriverStatus::OK &&
          accelerometer_->Init(MPU9255_ADDRESS) == types::DriverStatus::OK &&
          magnetometer_->Init(AK8963_ADDRESS) == types::DriverStatus::OK &&
          temperature_->Init(MPU9255_ADDRESS) == types::DriverStatus::OK);
}

auto Mpu9255::Update(void) noexcept -> types::DriverStatus {
  if (!IsInitialized())
    return types::DriverStatus::HAL_ERROR;

  if (UpdateAllSensors()) {
    SetToInitialized();
    return types::DriverStatus::OK;
  }
  return types::DriverStatus::HAL_ERROR;
}

auto Mpu9255::IsInitialized(void) noexcept -> bool {
  return initialized_;
}

auto Mpu9255::SetToInitialized(void) noexcept -> void {
  initialized_ = true;
}

auto Mpu9255::UpdateAllSensors(void) noexcept -> bool {
  return (gyroscope_->Update() == types::DriverStatus::OK &&
          accelerometer_->Update() == types::DriverStatus::OK &&
          magnetometer_->Update() == types::DriverStatus::OK &&
          temperature_->Update() == types::DriverStatus::OK);
}

auto Mpu9255::SetGyroscopeSensitivity(const types::ImuSensitivity gyroscope_sensitivity) noexcept -> types::DriverStatus {
  if (!IsInitialized())
    return types::DriverStatus::HAL_ERROR;

  return gyroscope_->SetSensitivity(gyroscope_sensitivity);
}

auto Mpu9255::GetGyroscopeSensitivity(void) noexcept -> types::ImuSensitivity {
  if (!IsInitialized())
    return types::ImuSensitivity::FINEST;

  return gyroscope_->GetSensitivity();
}

auto Mpu9255::SetAccelerometerSensitivity(const types::ImuSensitivity accelerometer_sensitivity) noexcept -> types::DriverStatus {
  if (!IsInitialized())
    return types::DriverStatus::HAL_ERROR;

  return accelerometer_->SetSensitivity(accelerometer_sensitivity);
}

auto Mpu9255::GetAccelerometerSensitivity(void) noexcept -> types::ImuSensitivity {
  if (!IsInitialized())
    return types::ImuSensitivity::FINEST;

  return accelerometer_->GetSensitivity();
}

auto Mpu9255::GetGyroscope(void) noexcept -> types::EuclideanVector<std::int16_t> {
  if (!IsInitialized())
    return ReturnVectorDefault();

  return gyroscope_->Get();
}

auto Mpu9255::GetAccelerometer(void) noexcept -> types::EuclideanVector<std::int16_t> {
  if (!IsInitialized())
    return ReturnVectorDefault();

  return accelerometer_->Get();
}

auto Mpu9255::GetMagnetometer(void) noexcept -> types::EuclideanVector<std::int16_t> {
  if (!IsInitialized())
    return ReturnVectorDefault();

  return magnetometer_->Get();
}

auto Mpu9255::ReturnVectorDefault(void) noexcept -> types::EuclideanVector<std::int16_t> {
  return types::EuclideanVector<std::int16_t>{-1, -1, -1};
}

auto Mpu9255::GetTemperature(void) noexcept -> int {
  if (!IsInitialized())
    return -1;

  return temperature_->Get();
}

auto Mpu9255::UnitTestSetGyroscope(std::unique_ptr<imu::GyroscopeInterface> gyroscope) noexcept -> void {
  gyroscope_ = std::move(gyroscope);
}

auto Mpu9255::UnitTestSetAccelerometer(std::unique_ptr<imu::AccelerometerInterface> accelerometer) noexcept -> void {
  accelerometer_ = std::move(accelerometer);
}

auto Mpu9255::UnitTestSetMagnetometer(std::unique_ptr<imu::MagnetometerInterface> magnetometer) noexcept -> void {
  magnetometer_ = std::move(magnetometer);
}

auto Mpu9255::UnitTestSetTemperature(std::unique_ptr<imu::TemperatureInterface> temperature) noexcept -> void {
  temperature_ = std::move(temperature);
}

}  // namespace imu