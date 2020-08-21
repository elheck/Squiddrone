#ifndef SRC_GYROSCOPE_HPP_
#define SRC_GYROSCOPE_HPP_

#include "imu_sensitivity.hpp"
#include "inertial_measurement_sensor.hpp"
#include "mpu9255_data.hpp"

namespace imu {

class Gyroscope : public InertialMeasurementSensor {
 public:
  Gyroscope() = delete;
  ~Gyroscope() = default;

  explicit Gyroscope(std::unique_ptr<i2c::I2CInterface> i2c_handler) : InertialMeasurementSensor(std::move(i2c_handler)){};
  auto Init(std::uint8_t i2c_address) noexcept -> types::DriverStatus;
  auto Update(void) noexcept -> types::DriverStatus;

  auto GetSensitivity(void) noexcept -> types::ImuSensitivity;
  auto SetSensitivity(types::ImuSensitivity gyroscope_sensitivity) noexcept -> types::DriverStatus;

 private:
  auto GetGyroscopeConfigRegisterDataForSensitivity(types::ImuSensitivity gyroscope_sensitivity) noexcept -> std::uint8_t;
  auto SendSensitivityRegisterData(types::ImuSensitivity gyroscope_sensitivity) noexcept -> void;
  auto SaveNewGyroscopeSensitivity(types::ImuSensitivity gyroscope_sensitivity) noexcept -> void;

  types::ImuSensitivity sensitivity_ = types::ImuSensitivity::FINEST;
};

enum GyroscopeSensitivityFSSelect : std::uint8_t {
  GYROSCOPE_FS_FINEST,  /// +- 250 dps full scale; 131 °/s sensitivity
  GYROSCOPE_FS_FINER,
  GYROSCOPE_FS_ROUGHER,
  GYROSCOPE_FS_ROUGHEST,  /// +- 2000 dps full scale; 16.4 °/s sensitivity
};

}  // namespace imu

#endif