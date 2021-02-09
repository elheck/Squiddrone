#include "mpu9255.hpp"

namespace imu {

auto Mpu9255::Init(void) noexcept -> types::DriverStatus {
  if (gyroscope_ == NULL) {
    gyroscope_ = std::make_unique<imu::Gyroscope>(i2c_handler_);
  }
  if (accelerometer_ == NULL) {
    accelerometer_ = std::make_unique<imu::Accelerometer>(i2c_handler_);
  }
  if (magnetometer_ == NULL) {
    magnetometer_ = std::make_unique<imu::Magnetometer>(i2c_handler_);
  }
  if (temperature_ == NULL) {
    temperature_ = std::make_unique<imu::Temperature>(i2c_handler_);
  }

  auto gyro_init = gyroscope_->Init(MPU9255_ADDRESS);
  auto accel_init = accelerometer_->Init(MPU9255_ADDRESS);
  auto temperature_init = temperature_->Init(MPU9255_ADDRESS);

  SetInitConfigMPU9255();

  auto magneto_init = magnetometer_->Init(AK8963_ADDRESS);

  SetInitConfigAK8963();
  if (AllSensorsAreOK(gyro_init, accel_init, magneto_init, temperature_init)) {
    initialized_ = true;
    return types::DriverStatus::OK;
  }
  return types::DriverStatus::HAL_ERROR;
}

auto Mpu9255::SetInitConfigMPU9255(void) -> void {
  SetMPU9255Register(INT_PIN_CFG, 0x22);
  SetMPU9255Register(INT_ENABLE, 0x01);
}

auto Mpu9255::SetInitConfigAK8963(void) -> void {
  SetAK8963Register(AK8963_CNTL, 0x00);  // Power down magnetometer
  utilities::Sleep(10);
  SetAK8963Register(AK8963_CNTL, 0x0F);  // Enter Fuse ROM access mode
  SetAK8963Register(AK8963_CNTL, 0x00);  // Power down magnetometer
  utilities::Sleep(10);
  // Configure the magnetometer for continuous read and highest resolution
  // set Mscale bit 4 to 1 (0) to enable 16 (14) bit resolution in CNTL register,
  // and enable continuous mode data acquisition Mmode (bits [3:0]), 0010 for 8 Hz and 0110 for 100 Hz sample rates
  SetAK8963Register(AK8963_CNTL, 1 << 4 | 0x02);  // Set magnetometer data resolution and sample ODR
}

auto Mpu9255::SetMPU9255Register(std::uint8_t register_, std::uint8_t register_value) -> void {
  i2c_handler_->Write(MPU9255_ADDRESS, {register_, register_value});
}

auto Mpu9255::SetAK8963Register(std::uint8_t register_, std::uint8_t register_value) -> void {
  i2c_handler_->Write(AK8963_ADDRESS, {register_, register_value});
}

auto Mpu9255::Update(void) noexcept -> types::DriverStatus {
  if (!IsInitialized())
    return types::DriverStatus::HAL_ERROR;

  if (AllSensorsAreOK(gyroscope_->Update(), accelerometer_->Update(), magnetometer_->Update(), temperature_->Update())) {
    initialized_ = true;
    return types::DriverStatus::OK;
  }
  return types::DriverStatus::HAL_ERROR;
}

auto Mpu9255::SetGyroscopeSensitivity(types::ImuSensitivity gyroscope_sensitivity) noexcept -> types::DriverStatus {
  if (!IsInitialized())
    return types::DriverStatus::HAL_ERROR;

  return gyroscope_->SetSensitivity(gyroscope_sensitivity);
}

auto Mpu9255::GetGyroscopeSensitivity(void) noexcept -> types::ImuSensitivity {
  return gyroscope_->GetSensitivity();
}

auto Mpu9255::SetAccelerometerSensitivity(types::ImuSensitivity accelerometer_sensitivity) noexcept -> types::DriverStatus {
  if (!IsInitialized())
    return types::DriverStatus::HAL_ERROR;

  return accelerometer_->SetSensitivity(accelerometer_sensitivity);
}

auto Mpu9255::GetAccelerometerSensitivity(void) noexcept -> types::ImuSensitivity {
  return accelerometer_->GetSensitivity();
}

auto Mpu9255::GetGyroscope(void) noexcept -> types::EuclideanVector<std::int16_t> {
  if (!IsInitialized()) {
    return types::EuclideanVector<std::int16_t>{-1, -1, -1};
  }

  return gyroscope_->Get();
}

auto Mpu9255::GetAccelerometer(void) noexcept -> types::EuclideanVector<std::int16_t> {
  if (!IsInitialized()) {
    return types::EuclideanVector<std::int16_t>{-1, -1, -1};
  }

  return accelerometer_->Get();
}

auto Mpu9255::GetMagnetometer(void) noexcept -> types::EuclideanVector<std::int16_t> {
  if (!IsInitialized()) {
    return types::EuclideanVector<std::int16_t>{-1, -1, -1};
  }

  return magnetometer_->Get();
}

auto Mpu9255::GetTemperature(void) noexcept -> int {
  if (!IsInitialized()) {
    return -1;
  }

  return temperature_->Get_();
}

auto Mpu9255::IsInitialized(void) noexcept -> bool {
  return initialized_;
}

auto Mpu9255::AllSensorsAreOK(types::DriverStatus gyroscope_status,
                              types::DriverStatus accelerometer_status,
                              types::DriverStatus magnetometer_status,
                              types::DriverStatus temperature_status) noexcept -> bool {
  if (gyroscope_status == types::DriverStatus::OK &&
      accelerometer_status == types::DriverStatus::OK &&
      magnetometer_status == types::DriverStatus::OK &&
      temperature_status == types::DriverStatus::OK) {
    return true;
  } else {
    return false;
  }
}

auto Mpu9255::UnitTestSetGyroscope(std::unique_ptr<imu::GyroscopeInterface> gyroscope) -> void {
  gyroscope_ = std::move(gyroscope);
}

auto Mpu9255::UnitTestSetAccelerometer(std::unique_ptr<imu::AccelerometerInterface> accelerometer) -> void {
  accelerometer_ = std::move(accelerometer);
}

auto Mpu9255::UnitTestSetMagnetometer(std::unique_ptr<imu::MagnetometerInterface> magnetometer) -> void {
  magnetometer_ = std::move(magnetometer);
}

auto Mpu9255::UnitTestSetTemperature(std::unique_ptr<imu::TemperatureInterface> temperature) -> void {
  temperature_ = std::move(temperature);
}

}  // namespace imu