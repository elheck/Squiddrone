#include "com_nrf24l01.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::NiceMock;
using ::testing::Return;
namespace {
class ComNRF24L01Tests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    com_msg_buffer_ = std::make_unique<NiceMock<com::ComMessageBuffer>>();
    com_spi_protocol_ = std::make_unique<NiceMock<com::NRF24L01SpiProtocol>>();

    ON_CALL(*com_msg_buffer_, GetData).WillByDefault(Return(default_msg_frame_));
  }

  std::unique_ptr<com::ComMessageBuffer> com_msg_buffer_;
  std::unique_ptr<com::NRF24L01SpiProtocol> com_spi_protocol_;

  types::com_msg_frame default_msg_frame_ = {0xAA};
};

TEST_F(ComNRF24L01Tests, com_get_data_packet_successful) {
  auto unit_under_test_ = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer_), std::move(com_spi_protocol_));
  types::com_msg_frame msg_frame_ = {0xAA};

  auto return_value = unit_under_test_->GetDataPacket();
  ASSERT_EQ(return_value, msg_frame_);
}

TEST_F(ComNRF24L01Tests, com_frame_length_exceeding_limit) {
  auto unit_under_test_ = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer_), std::move(com_spi_protocol_));
  types::com_msg_frame long_msg_frame(33);

  auto return_value = unit_under_test_->PutDataPacket(0, long_msg_frame);
  ASSERT_EQ(return_value, types::DriverStatus::INPUT_ERROR);
}

TEST_F(ComNRF24L01Tests, com_put_data_packet_successful) {
  auto unit_under_test_ = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer_), std::move(com_spi_protocol_));

  auto return_value = unit_under_test_->PutDataPacket(0, default_msg_frame_);
  ASSERT_EQ(return_value, types::DriverStatus::OK);
}

TEST_F(ComNRF24L01Tests, com_put_data_packet_hal_reg_access_not_successful) {
  ON_CALL(*com_spi_protocol_, WriteRegister).WillByDefault(Return(types::DriverStatus::HAL_ERROR));

  auto unit_under_test_ = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer_), std::move(com_spi_protocol_));

  auto return_value = unit_under_test_->PutDataPacket(0, default_msg_frame_);
  ASSERT_EQ(return_value, types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01Tests, com_put_data_packet_hal_fifo_access_not_successful) {
  ON_CALL(*com_spi_protocol_, WritePayloadData).WillByDefault(Return(types::DriverStatus::HAL_ERROR));

  auto unit_under_test_ = std::make_unique<com::NRF24L01>(std::move(com_msg_buffer_), std::move(com_spi_protocol_));

  auto return_value = unit_under_test_->PutDataPacket(0, default_msg_frame_);
  ASSERT_EQ(return_value, types::DriverStatus::HAL_ERROR);
}

}  // namespace