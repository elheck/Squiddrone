#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "i2c.hpp"

namespace {

class I2CTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    unit_under_test_ = std::make_unique<i2c::I2C>();
  }

  std::unique_ptr<i2c::I2C> unit_under_test_;

  std::uint8_t address = 0x10;
  std::uint16_t byte_size = 3;
  std::uint32_t timeout = 2;
  std::uint8_t register_ = 0x10;
  std::vector<uint8_t> data = {1, 2};

  types::DriverStatus result_status;
  std::vector<uint8_t> result_data;
};

TEST_F(I2CTests, read_successful) {
  std::tie(result_status, result_data) = unit_under_test_->Read(address, byte_size, timeout);

  EXPECT_EQ(result_status, types::DriverStatus::OK);
  EXPECT_THAT(result_data, testing::ElementsAre(1, 2, 3));
}

TEST_F(I2CTests, read_failed) {
  address = 0x11;
  std::tie(result_status, result_data) = unit_under_test_->Read(address, byte_size, timeout);

  EXPECT_EQ(result_status, types::DriverStatus::HAL_ERROR);
}

TEST_F(I2CTests, read_timeout) {
  address = 0x12;
  std::tie(result_status, result_data) = unit_under_test_->Read(address, byte_size, timeout);

  EXPECT_EQ(result_status, types::DriverStatus::TIMEOUT);
}

TEST_F(I2CTests, read_busy) {
  address = 0x13;
  std::tie(result_status, result_data) = unit_under_test_->Read(address, byte_size, timeout);

  EXPECT_EQ(result_status, types::DriverStatus::HAL_ERROR);
}

TEST_F(I2CTests, read_byte_size_0) {
  byte_size = 0;
  std::tie(result_status, result_data) = unit_under_test_->Read(address, byte_size, timeout);

  EXPECT_EQ(result_status, types::DriverStatus::HAL_ERROR);
}

TEST_F(I2CTests, read_byte_size_upper_boundary_plus_1) {
  byte_size = 33;
  std::tie(result_status, result_data) = unit_under_test_->Read(address, byte_size, timeout);

  EXPECT_EQ(result_status, types::DriverStatus::HAL_ERROR);
}

TEST_F(I2CTests, read_timeout_0) {
  timeout = 0;
  std::tie(result_status, result_data) = unit_under_test_->Read(address, byte_size, timeout);

  EXPECT_EQ(result_status, types::DriverStatus::HAL_ERROR);
}

TEST_F(I2CTests, read_address_out_of_range_0) {
  address = 0x00;
  std::tie(result_status, result_data) = unit_under_test_->Read(address, byte_size, timeout);

  EXPECT_EQ(result_status, types::DriverStatus::HAL_ERROR);
}

TEST_F(I2CTests, read_address_out_of_range_0x78) {
  address = 0x78;
  std::tie(result_status, result_data) = unit_under_test_->Read(address, byte_size, timeout);

  EXPECT_EQ(result_status, types::DriverStatus::HAL_ERROR);
}

TEST_F(I2CTests, write_successful) {
  auto result_status = unit_under_test_->Write(address, data, timeout);

  EXPECT_EQ(result_status, types::DriverStatus::OK);
}

TEST_F(I2CTests, write_failed) {
  address = 0x11;
  auto result_status = unit_under_test_->Write(address, data, timeout);

  EXPECT_EQ(result_status, types::DriverStatus::HAL_ERROR);
}

TEST_F(I2CTests, write_timeout) {
  address = 0x12;
  auto result_status = unit_under_test_->Write(address, data, timeout);

  EXPECT_EQ(result_status, types::DriverStatus::TIMEOUT);
}

TEST_F(I2CTests, write_busy) {
  address = 0x13;
  auto result_status = unit_under_test_->Write(address, data, timeout);

  EXPECT_EQ(result_status, types::DriverStatus::HAL_ERROR);
}

TEST_F(I2CTests, write_data_empty) {
  data.clear();
  auto result_status = unit_under_test_->Write(address, data, timeout);

  EXPECT_EQ(result_status, types::DriverStatus::INPUT_ERROR);
}

TEST_F(I2CTests, write_timeout_0) {
  timeout = 0;
  auto result_status = unit_under_test_->Write(address, data, timeout);

  EXPECT_EQ(result_status, types::DriverStatus::INPUT_ERROR);
}

TEST_F(I2CTests, write_address_out_of_range_0) {
  address = 0x0;
  auto result_status = unit_under_test_->Write(address, data, timeout);

  EXPECT_EQ(result_status, types::DriverStatus::INPUT_ERROR);
}

TEST_F(I2CTests, write_address_out_of_range_0x78) {
  address = 0x78;
  auto result_status = unit_under_test_->Write(address, data, timeout);

  EXPECT_EQ(result_status, types::DriverStatus::INPUT_ERROR);
}

TEST_F(I2CTests, read_register_content_OK) {
  address = 0x14;
  types::DriverStatus result_status;
  std::vector<uint8_t> content_of_register;
  std::tie(result_status, content_of_register) = unit_under_test_->ReadContentFromRegister(address, register_, 4, timeout);

  EXPECT_EQ(result_status, types::DriverStatus::OK);
  EXPECT_THAT(content_of_register, testing::ElementsAre(5, 5, 6, 7));
}

TEST_F(I2CTests, read_register_content_wrong_address) {
  address = 0x78;

  types::DriverStatus result_status;
  std::vector<uint8_t> content_of_register;
  std::tie(result_status, content_of_register) = unit_under_test_->ReadContentFromRegister(address, register_, 1, timeout);

  EXPECT_EQ(result_status, types::DriverStatus::INPUT_ERROR);
}

TEST_F(I2CTests, read_register_content_invalid_register) {
  address = 0x15;
  register_ = 0x15;
  types::DriverStatus result_status;
  std::vector<uint8_t> content_of_register;
  std::tie(result_status, content_of_register) = unit_under_test_->ReadContentFromRegister(address, register_, 1, timeout);

  EXPECT_EQ(result_status, types::DriverStatus::HAL_ERROR);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}