#ifndef SRC_MPU9255_HPP_
#define SRC_MPU9255_HPP_

#include "accelerometer.hpp"
#include "accelerometer_virtual_interface.hpp"
#include "generic_imu.hpp"
#include "gyroscope.hpp"
#include "gyroscope_virtual_interface.hpp"
#include "magnetometer.hpp"
#include "magnetometer_virtual_interface.hpp"
#include "temperature.hpp"
#include "temperature_virtual_interface.hpp"

namespace imu {

class Mpu9255 final : public GenericInertialMeasurementUnit {
 public:
  Mpu9255() = delete;
  virtual ~Mpu9255() = default;
  explicit Mpu9255(std::shared_ptr<i2c::I2CInterface> i2c_handler) : GenericInertialMeasurementUnit(i2c_handler) {}
  auto Init(void) noexcept -> types::DriverStatus override;
  auto Update(void) noexcept -> types::DriverStatus override;
  auto SetGyroscopeSensitivity(const types::ImuSensitivity gyroscope_sensitivity) noexcept -> types::DriverStatus override;
  auto GetGyroscopeSensitivity(void) noexcept -> types::ImuSensitivity override;
  auto SetAccelerometerSensitivity(const types::ImuSensitivity accelerometer_sensitivity) noexcept -> types::DriverStatus override;
  auto GetAccelerometerSensitivity(void) noexcept -> types::ImuSensitivity override;
  auto GetGyroscope(void) noexcept -> types::EuclideanVector<std::int16_t> override;
  auto GetAccelerometer(void) noexcept -> types::EuclideanVector<std::int16_t> override;
  auto GetMagnetometer(void) noexcept -> types::EuclideanVector<std::int16_t> override;
  auto GetTemperature(void) noexcept -> int override;
  auto IsInitialized(void) noexcept -> bool;

  auto UnitTestSetGyroscope(std::unique_ptr<imu::GyroscopeInterface> gyroscope) -> void;
  auto UnitTestSetAccelerometer(std::unique_ptr<imu::AccelerometerInterface> accelerometer) -> void;
  auto UnitTestSetMagnetometer(std::unique_ptr<imu::MagnetometerInterface> magnetometer) -> void;
  auto UnitTestSetTemperature(std::unique_ptr<imu::TemperatureInterface> temperature) -> void;

 protected:
  auto AllSensorsAreOK(const types::DriverStatus gyroscope_status,
                       const types::DriverStatus accelerometer_status,
                       const types::DriverStatus magnetometer_status,
                       const types::DriverStatus temperature_status) noexcept -> bool;
  auto SetInitConfigMPU9255(void) -> void;
  auto SetInitConfigAK8963(void) -> void;
  auto SetMPU9255Register(const std::uint8_t register_, const std::uint8_t register_value) -> void;

  bool initialized_ = false;
  std::unique_ptr<imu::GyroscopeInterface> gyroscope_ = NULL;
  std::unique_ptr<imu::AccelerometerInterface> accelerometer_ = NULL;
  std::unique_ptr<imu::MagnetometerInterface> magnetometer_ = NULL;
  std::unique_ptr<imu::TemperatureInterface> temperature_ = NULL;
};

}  // namespace imu

#endif