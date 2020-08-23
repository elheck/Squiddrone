#ifndef SRC_IMU_MEASUREMENT_SENSOR_HPP_
#define SRC_IMU_MEASUREMENT_SENSOR_HPP_

#include <memory>
#include "basic_types.hpp"
#include "error_types.hpp"
#include "i2c.hpp"
#include "mpu9255_data.hpp"

namespace imu {

class InertialMeasurementSensor {
 public:
  /**
   * @brief The default destructor is sufficent
   */
  virtual ~InertialMeasurementSensor() = default;

  explicit InertialMeasurementSensor(std::unique_ptr<i2c::I2CInterface> i2c_handler) : i2c_handler_(std::move(i2c_handler)){};
  auto Get(void) noexcept -> types::EuclideanVector<int16_t>;
  auto Update(void) noexcept -> types::DriverStatus;

 protected:
  auto Mpu9255Detected(void) noexcept -> bool;
  auto Write(const std::vector<std::uint8_t>& data) noexcept -> void;
  auto ReadContentFromRegister(std::uint8_t read_from_register, std::uint16_t byte_size) noexcept -> std::vector<std::uint8_t>;
  auto ImuConnectionSuccessful(void) noexcept -> bool;
  auto ImuConnectionFailed(void) noexcept -> bool;
  auto SetI2CAdress(std::uint8_t i2c_address) noexcept -> void;
  auto ConvertUint8BytesIntoInt16SensorValue(std::uint8_t first_byte, std::uint8_t second_byte) noexcept -> std::int16_t;
  auto IsInitialized(void) noexcept -> bool;
  auto SetSensorValues(std::int16_t x, std::int16_t y, std::int16_t z) noexcept -> void;
  /// Holds the local reference to euclidean sensor values
  types::EuclideanVector<std::int16_t> sensor_values_{-1, -1, -1};
  /// Holds the local reference to i2c handler
  std::unique_ptr<i2c::I2CInterface> i2c_handler_;
  /// Holds value if Sensor was initialized correctly or not
  bool initialized_ = false;
  /// I2C Address of specific sensor
  std::uint8_t i2c_address_ = 0;
  /// Status of last communication action of IMU sensor
  types::DriverStatus imu_status_ = types::DriverStatus::HAL_ERROR;
  std::uint8_t SENSOR_DATA_REGISTER = 0;
  std::uint8_t CONFIG_REGISTER = 0;
};

enum ImuSensitivityFSSelect : std::uint8_t {
  IMU_FS_FINEST,
  IMU_FS_FINER,
  IMU_FS_ROUGHER,
  IMU_FS_ROUGHEST,
};

}  // namespace imu

#endif