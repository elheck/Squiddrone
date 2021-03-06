#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "spi.hpp"

using ::testing::NiceMock;
using ::testing::Return;

namespace {

class SPITests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    unit_under_test_ = std::make_unique<spi::SPI>(cs_pin);
  }

  NiceMock<spi::CSPin> cs_pin;
  std::unique_ptr<spi::SPI> unit_under_test_;
  std::vector<std::uint8_t> miso_buffer;
  std::vector<std::uint8_t> mosi_buffer;
};
}  // namespace

TEST_F(SPITests, transfer_exceeding_buffer_size_limit) {
  std::vector<std::uint8_t> too_large_buffer(65);
  types::DriverStatus rv = unit_under_test_->Transfer(mosi_buffer, too_large_buffer);
  EXPECT_EQ(rv, types::DriverStatus::INPUT_ERROR);
}

TEST_F(SPITests, transfer_buffer_size_limit_at_maximum) {
  hspi1.mock_return_value = HAL_StatusTypeDef::HAL_OK;
  std::vector<std::uint8_t> miso_buffer(64);
  types::DriverStatus rv = unit_under_test_->Transfer(mosi_buffer, miso_buffer);
  EXPECT_EQ(rv, types::DriverStatus::OK);
}

TEST_F(SPITests, transfer_buffer_size_limit_zero) {
  hspi1.mock_return_value = HAL_StatusTypeDef::HAL_OK;
  std::vector<std::uint8_t> zero_size_buffer(0);
  types::DriverStatus rv = unit_under_test_->Transfer(zero_size_buffer, miso_buffer);
  EXPECT_EQ(rv, types::DriverStatus::OK);
}

TEST_F(SPITests, transfer_miso_buffer_too_small) {
  hspi1.mock_return_value = HAL_StatusTypeDef::HAL_OK;
  std::vector<std::uint8_t> mosi_buffer(5);
  std::vector<std::uint8_t> small_miso_buffer(0);
  types::DriverStatus rv = unit_under_test_->Transfer(mosi_buffer, small_miso_buffer);
  EXPECT_EQ(rv, types::DriverStatus::INPUT_ERROR);
}

TEST_F(SPITests, transfer_successful_spi_transfer) {
  hspi1.mock_return_value = HAL_StatusTypeDef::HAL_OK;
  types::DriverStatus rv = unit_under_test_->Transfer(miso_buffer, mosi_buffer);
  EXPECT_EQ(rv, types::DriverStatus::OK);
}

TEST_F(SPITests, transfer_timeout_during_spi_transfer) {
  hspi1.mock_return_value = HAL_StatusTypeDef::HAL_TIMEOUT;
  types::DriverStatus rv = unit_under_test_->Transfer(miso_buffer, mosi_buffer);
  EXPECT_EQ(rv, types::DriverStatus::TIMEOUT);
}

TEST_F(SPITests, transfer_spi_hal_error) {
  hspi1.mock_return_value = HAL_StatusTypeDef::HAL_ERROR;
  types::DriverStatus rv = unit_under_test_->Transfer(miso_buffer, mosi_buffer);
  EXPECT_EQ(rv, types::DriverStatus::HAL_ERROR);
}

TEST_F(SPITests, transfer_spi_hal_busy) {
  hspi1.mock_return_value = HAL_StatusTypeDef::HAL_BUSY;
  types::DriverStatus rv = unit_under_test_->Transfer(miso_buffer, mosi_buffer);
  EXPECT_EQ(rv, types::DriverStatus::HAL_ERROR);
}

TEST_F(SPITests, write_exceeding_buffer_size_limit) {
  std::vector<std::uint8_t> too_large_buffer(65);
  types::DriverStatus rv = unit_under_test_->Write(too_large_buffer);
  EXPECT_EQ(rv, types::DriverStatus::INPUT_ERROR);
}

TEST_F(SPITests, write_buffer_size_limit_at_maximum) {
  hspi1.mock_return_value = HAL_StatusTypeDef::HAL_OK;
  std::vector<std::uint8_t> mosi_buffer(64);
  types::DriverStatus rv = unit_under_test_->Write(mosi_buffer);
  EXPECT_EQ(rv, types::DriverStatus::OK);
}

TEST_F(SPITests, write_buffer_size_limit_zero) {
  hspi1.mock_return_value = HAL_StatusTypeDef::HAL_OK;
  std::vector<std::uint8_t> zero_size_buffer(0);
  types::DriverStatus rv = unit_under_test_->Write(zero_size_buffer);
  EXPECT_EQ(rv, types::DriverStatus::OK);
}

TEST_F(SPITests, write_successful_spi_transfer) {
  hspi1.mock_return_value = HAL_StatusTypeDef::HAL_OK;
  types::DriverStatus rv = unit_under_test_->Write(mosi_buffer);
  EXPECT_EQ(rv, types::DriverStatus::OK);
}

TEST_F(SPITests, write_timeout_during_spi_transfer) {
  hspi1.mock_return_value = HAL_StatusTypeDef::HAL_TIMEOUT;
  types::DriverStatus rv = unit_under_test_->Write(mosi_buffer);
  EXPECT_EQ(rv, types::DriverStatus::TIMEOUT);
}

TEST_F(SPITests, write_spi_hal_error) {
  hspi1.mock_return_value = HAL_StatusTypeDef::HAL_ERROR;
  types::DriverStatus rv = unit_under_test_->Write(mosi_buffer);
  EXPECT_EQ(rv, types::DriverStatus::HAL_ERROR);
}

TEST_F(SPITests, write_spi_hal_busy) {
  hspi1.mock_return_value = HAL_StatusTypeDef::HAL_BUSY;
  types::DriverStatus rv = unit_under_test_->Write(mosi_buffer);
  EXPECT_EQ(rv, types::DriverStatus::HAL_ERROR);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}