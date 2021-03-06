#ifndef SRC_IMU_MEASUREMENT_SENSOR_HPP_
#define SRC_IMU_MEASUREMENT_SENSOR_HPP_

#include <memory>
#include "basic_types.hpp"
#include "error_types.hpp"
#include "i2c.hpp"
#include "imu_general_interface.hpp"
#include "mpu9255_data.hpp"

namespace imu {

class GeneralSensor : public GeneralSensorInterface {
 public:
  virtual ~GeneralSensor() = default;

  explicit GeneralSensor(std::shared_ptr<i2c::I2CInterface> i2c_handler) : GeneralSensorInterface(), i2c_handler_(i2c_handler){};
  auto Init(const std::uint8_t i2c_address) noexcept -> types::DriverStatus override;
  auto GetRawValues(void) noexcept -> types::DriverStatus override;

 protected:
  auto IsHardwareConnected(void) -> bool;
  auto Mpu9255Detected(void) noexcept -> bool;
  auto AK8963Detected(void) noexcept -> bool;
  auto CheckI2CDevice(const std::uint8_t register_, const std::uint8_t value) noexcept -> bool;
  auto ReadContentFromRegister(const std::uint8_t read_from_register, const std::uint16_t byte_size) noexcept -> std::vector<std::uint8_t>;
  auto WriteContentIntoRegister(const std::uint8_t write_into_register, const std::uint8_t register_content) noexcept -> void;
  auto ImuConnectionSuccessful(void) noexcept -> bool;
  auto ImuConnectionFailed(void) noexcept -> bool;
  auto SetI2CAdress(const std::uint8_t i2c_address) noexcept -> void;
  auto ConvertUint8BytesIntoInt16SensorValue(const std::vector<std::uint8_t> &raw_vector) noexcept -> std::vector<std::int16_t>;
  auto ConvertUint8BytesIntoInt16(std::uint8_t first_byte, std::uint8_t second_byte) noexcept -> std::int16_t;
  auto IsInitialized(void) noexcept -> bool;

  std::shared_ptr<i2c::I2CInterface> i2c_handler_;
  bool initialized_ = false;
  std::uint8_t i2c_address_ = 0;
  types::DriverStatus imu_status_ = types::DriverStatus::HAL_ERROR;
  std::vector<std::uint8_t> raw_values_;
  std::uint8_t sensor_data_register = 0;
  std::uint8_t register_data_length_in_bytes = 0;
  std::uint8_t config_register = 0;
  bool little_endian = false;
};

}  // namespace imu

#endif