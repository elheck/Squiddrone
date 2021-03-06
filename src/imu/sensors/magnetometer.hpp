#ifndef SRC_MAGNETOMETER_HPP_
#define SRC_MAGNETOMETER_HPP_

#include "byte.hpp"
#include "magnetometer_interface.hpp"
#include "sleep.hpp"

namespace imu {

class Magnetometer final : public MagnetometerInterface {
 public:
  Magnetometer() = delete;
  ~Magnetometer() = default;

  explicit Magnetometer(std::shared_ptr<i2c::I2CInterface> i2c_handler) : MagnetometerInterface(i2c_handler){};
  auto Init(const std::uint8_t i2c_address) noexcept -> types::DriverStatus override;
  auto Update(void) noexcept -> types::DriverStatus override;

 private:
  types::EuclideanVector<float> calibration_values_{-1, -1, -1};
  static constexpr float MAX_MAGNETIC_FLUX_IN_MICRO_TESLA = 4912.0f;
  static constexpr float MAX_MAGNETIC_MEASUREMENT_IN_DIGIT_16BIT = 32760.0f;
  static constexpr std::uint32_t REBOOT_TIME_IN_MS = 10;
  static constexpr std::int8_t ST2_REGISTER_BYTE = 6;

  auto SetInitData(void) noexcept -> void;
  auto PowerDownMagnetometer(void) noexcept -> void;
  auto EnterFuseROMAccessMode(void) noexcept -> void;
  auto ConfigureForContinuousRead(void) noexcept -> void;
  auto IsMagnetometerMeasurementReady(void) noexcept -> bool;
  auto HasMagnetometerOverflow(const std::uint8_t st2_register_value) noexcept -> bool;
  auto GetFactorADC2Magnetometer(void) noexcept -> float;
  auto GetCalibrationValues(void) noexcept -> void;
  auto AdjustSensitivity(const std::uint8_t sensitivity_adjustment_value) noexcept -> float;
};

}  // namespace imu

#endif