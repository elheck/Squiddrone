#include <gmock/gmock.h>
#include "gtest/gtest.h"
#include "imu_interface.hpp"
#include "inertial_measurement.hpp"
#include "mock_i2c.hpp"
#include "mock_mpu9255.hpp"

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

namespace {

class ImuIntegrationTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    ON_CALL(*i2c_handler_, Write)
        .WillByDefault(Return(types::DriverStatus::OK));

    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, _, _, _))
        .WillByDefault(Return(answer_to_who_am_i));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::WHO_AM_I_MPU9255_REGISTER, _, _))
        .WillByDefault(Return(answer_to_who_am_i));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::WHO_AM_I_AK8963_REGISTER, _, _))
        .WillByDefault(Return(answer_to_who_am_i_AK8963));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::GYRO_CONFIG, _, _))
        .WillByDefault(Return(answer_to_gyro_config));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::GYRO_MEASUREMENT_DATA, _, _))
        .WillByDefault(Return(answer_to_gyro_update));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::ACCEL_CONFIG, _, _))
        .WillByDefault(Return(answer_to_accelerometer_config));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::ACCEL_MEASUREMENT_DATA, _, _))
        .WillByDefault(Return(answer_to_accelerometer_update));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::AK8963_ASAX, _, _))
        .WillByDefault(Return(magnetometer_answer_calibration_values));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::AK8963_ST1, _, _))
        .WillByDefault(Return(magnetometer_answer_to_measurement_ready));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::MAGNETOMETER_MEASUREMENT_DATA, _, _))
        .WillByDefault(Return(answer_to_magnetometer_update));
    ON_CALL(*i2c_handler_, ReadContentFromRegister(_, imu::TEMP_MEASUREMENT_DATA, _, _))
        .WillByDefault(Return(answer_to_temperature_update));
  }

  virtual void ConfigureUnitUnderTest() {
    unit_under_test_ = std::make_unique<imu::InertialMeasurement>(i2c_handler_);
  }

  std::shared_ptr<i2c::MockI2C> i2c_handler_ = std::make_shared<NiceMock<i2c::MockI2C>>();
  std::unique_ptr<imu::InertialMeasurement> unit_under_test_;

  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_who_am_i{
      types::DriverStatus::OK, {imu::WHO_AM_I_MPU9255_VALUE}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_who_am_i_AK8963{
      types::DriverStatus::OK, {imu::WHO_AM_I_AK8963_VALUE}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_gyro_config{
      types::DriverStatus::OK, {0b11111111}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_accelerometer_config{
      types::DriverStatus::OK, {0b11111111}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_gyro_update{
      types::DriverStatus::OK, {0x7F, 0xFF, 0x00, 0x00, 0x80, 0x00}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_accelerometer_update{
      types::DriverStatus::OK, {0x7F, 0xFF, 0x00, 0x00, 0x80, 0x00}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_magnetometer_update{
      types::DriverStatus::OK, {0b11111000, 0b01111111, 0, 0, 0b00001000, 0b10000000, 0}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> answer_to_temperature_update{
      types::DriverStatus::OK, {2, 112}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> magnetometer_answer_to_measurement_ready{
      types::DriverStatus::OK, {0b00000001}};
  std::pair<types::DriverStatus, std::vector<std::uint8_t>> magnetometer_answer_calibration_values{
      types::DriverStatus::OK, {128, 128, 128}};
};

TEST_F(ImuIntegrationTests, integration_test_gyroscope_happy_path) {
  ConfigureUnitUnderTest();

  types::EuclideanVector<std::int16_t> expected_value{2000, 0, -2000};

  auto init_return = unit_under_test_->Init();
  unit_under_test_->SetGyroscopeSensitivity(types::ImuSensitivity::FINEST);

  EXPECT_EQ(init_return, types::DriverStatus::OK);

  auto update_return = unit_under_test_->Update();

  EXPECT_EQ(update_return, types::DriverStatus::OK);

  auto gyroscope_return = unit_under_test_->GetGyroscope();

  EXPECT_EQ(gyroscope_return.x, expected_value.x);
  EXPECT_EQ(gyroscope_return.y, expected_value.y);
  EXPECT_EQ(gyroscope_return.z, expected_value.z);
}

TEST_F(ImuIntegrationTests, integration_test_accelerometer_happy_path) {
  ConfigureUnitUnderTest();

  types::EuclideanVector<std::int16_t> expected_value{16, 0, -16};

  auto init_return = unit_under_test_->Init();
  unit_under_test_->SetAccelerometerSensitivity(types::ImuSensitivity::FINEST);

  EXPECT_EQ(init_return, types::DriverStatus::OK);

  auto update_return = unit_under_test_->Update();

  EXPECT_EQ(update_return, types::DriverStatus::OK);

  auto accelerometer_return = unit_under_test_->GetAccelerometer();

  EXPECT_EQ(accelerometer_return.x, expected_value.x);
  EXPECT_EQ(accelerometer_return.y, expected_value.y);
  EXPECT_EQ(accelerometer_return.z, expected_value.z);
}

TEST_F(ImuIntegrationTests, integration_test_magnetometer_happy_path) {
  ConfigureUnitUnderTest();

  auto init_return = unit_under_test_->Init();

  EXPECT_EQ(init_return, types::DriverStatus::OK);

  auto update_return = unit_under_test_->Update();

  EXPECT_EQ(update_return, types::DriverStatus::OK);

  auto magnetometer_return = unit_under_test_->GetMagnetometer();

  EXPECT_EQ(magnetometer_return.x, 4912);
  EXPECT_EQ(magnetometer_return.y, 0);
  EXPECT_EQ(magnetometer_return.z, -4912);
}

TEST_F(ImuIntegrationTests, integration_test_temperature_happy_path) {
  ConfigureUnitUnderTest();

  auto init_return = unit_under_test_->Init();

  EXPECT_EQ(init_return, types::DriverStatus::OK);

  auto update_return = unit_under_test_->Update();

  EXPECT_EQ(update_return, types::DriverStatus::OK);

  auto temperature_return = unit_under_test_->GetTemperature();

  EXPECT_EQ(temperature_return, 22);
}

TEST_F(ImuIntegrationTests, integration_test_Update_without_Init) {
  ConfigureUnitUnderTest();

  auto update_return = unit_under_test_->Update();

  EXPECT_EQ(update_return, types::DriverStatus::HAL_ERROR);
}

TEST_F(ImuIntegrationTests, integration_GetGyroscope_without_Init) {
  ConfigureUnitUnderTest();

  auto gyroscope_return = unit_under_test_->GetGyroscope();

  EXPECT_EQ(gyroscope_return.x, -1);
  EXPECT_EQ(gyroscope_return.y, -1);
  EXPECT_EQ(gyroscope_return.z, -1);
}

TEST_F(ImuIntegrationTests, integration_SetGyroscopeSensitivity) {
  ConfigureUnitUnderTest();

  unit_under_test_->Init();

  unit_under_test_->SetGyroscopeSensitivity(types::ImuSensitivity::FINEST);

  EXPECT_EQ(unit_under_test_->GetGyroscopeSensitivity(), types::ImuSensitivity::FINEST);

  unit_under_test_->SetGyroscopeSensitivity(types::ImuSensitivity::ROUGHEST);

  EXPECT_EQ(unit_under_test_->GetGyroscopeSensitivity(), types::ImuSensitivity::ROUGHEST);
}

TEST_F(ImuIntegrationTests, integration_SetAccelerometerSensitivity) {
  ConfigureUnitUnderTest();

  unit_under_test_->Init();

  unit_under_test_->SetAccelerometerSensitivity(types::ImuSensitivity::FINEST);

  EXPECT_EQ(unit_under_test_->GetAccelerometerSensitivity(), types::ImuSensitivity::FINEST);

  unit_under_test_->SetAccelerometerSensitivity(types::ImuSensitivity::ROUGHEST);

  EXPECT_EQ(unit_under_test_->GetAccelerometerSensitivity(), types::ImuSensitivity::ROUGHEST);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}