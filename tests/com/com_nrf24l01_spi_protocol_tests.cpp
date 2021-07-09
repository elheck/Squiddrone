#include "com_nrf24l01_spi_protocol.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::ElementsAre;
using ::testing::Invoke;
using ::testing::NiceMock;
using ::testing::Return;

namespace {
class ComNRF24L01SpiProtocolTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    spi_ = std::make_unique<NiceMock<spi::SPI>>(cs_pin_);
  }
  spi::CSPin cs_pin_;
  std::unique_ptr<spi::SPI> spi_;
  std::unique_ptr<com::NRF24L01SpiProtocol> unit_under_test_;
};

}  // namespace

types::DriverStatus ConstructTestVector(std::vector<std::uint8_t> &mosi, std::vector<std::uint8_t> &miso) noexcept {
  miso.at(0) = 0xaa;
  return types::DriverStatus::OK;
}

TEST_F(ComNRF24L01SpiProtocolTests, read_register_spi_tx_ok) {
  std::uint8_t test_reg_addr = 0xfa;
  EXPECT_CALL(*spi_, Transfer(ElementsAre(com::instruction_word::R_REGISTER | test_reg_addr), ElementsAre(_, _)));
  unit_under_test_ = std::make_unique<com::NRF24L01SpiProtocol>(std::move(spi_));
  auto rv = unit_under_test_->ReadRegister(test_reg_addr);
  ASSERT_EQ(rv.first, types::DriverStatus::OK);
}

TEST_F(ComNRF24L01SpiProtocolTests, read_register_spi_tx_not_ok) {
  std::uint8_t test_reg_addr = 0xfa;
  EXPECT_CALL(*spi_, Transfer(_, _)).WillOnce(Return(types::DriverStatus::HAL_ERROR));
  unit_under_test_ = std::make_unique<com::NRF24L01SpiProtocol>(std::move(spi_));
  auto rv = unit_under_test_->ReadRegister(test_reg_addr);
  ASSERT_EQ(rv.first, types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01SpiProtocolTests, write_register_spi_tx_ok) {
  std::uint8_t test_reg_addr = 0xfa;
  std::uint8_t test_reg_content = 0xaf;
  EXPECT_CALL(*spi_, Write(ElementsAre(com::instruction_word::W_REGISTER | test_reg_addr, test_reg_content)));
  unit_under_test_ = std::make_unique<com::NRF24L01SpiProtocol>(std::move(spi_));
  auto retval = unit_under_test_->WriteRegister(test_reg_addr, test_reg_content);
  ASSERT_EQ(retval, types::DriverStatus::OK);
}

TEST_F(ComNRF24L01SpiProtocolTests, write_register_spi_tx_not_ok) {
  std::uint8_t test_reg_addr = 0xfa;
  std::uint8_t test_reg_content = 0xaf;
  EXPECT_CALL(*spi_, Write(_)).WillOnce(Return(types::DriverStatus::HAL_ERROR));
  unit_under_test_ = std::make_unique<com::NRF24L01SpiProtocol>(std::move(spi_));
  auto retval = unit_under_test_->WriteRegister(test_reg_addr, test_reg_content);
  ASSERT_EQ(retval, types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01SpiProtocolTests, read_register_multibyte_spi_tx_ok) {
  std::uint8_t test_reg_addr = 0xfa;
  std::uint8_t length = 3;
  EXPECT_CALL(*spi_, Transfer(ElementsAre(com::instruction_word::R_REGISTER | test_reg_addr), ElementsAre(_, _, _, _)));
  unit_under_test_ = std::make_unique<com::NRF24L01SpiProtocol>(std::move(spi_));
  auto rv = unit_under_test_->ReadRegister(test_reg_addr, length);
  ASSERT_EQ(rv.first, types::DriverStatus::OK);
}

TEST_F(ComNRF24L01SpiProtocolTests, read_register_multibyte_spi_tx_not_ok) {
  std::uint8_t test_reg_addr = 0xfa;
  std::uint8_t length = 3;
  EXPECT_CALL(*spi_, Transfer(_, _)).WillOnce(Return(types::DriverStatus::HAL_ERROR));
  unit_under_test_ = std::make_unique<com::NRF24L01SpiProtocol>(std::move(spi_));
  auto rv = unit_under_test_->ReadRegister(test_reg_addr, length);
  ASSERT_EQ(rv.first, types::DriverStatus::HAL_ERROR);
}

TEST_F(ComNRF24L01SpiProtocolTests, write_register_multibyte_spi_tx_ok) {
  std::uint8_t test_reg_addr = 0x0a;
  std::vector<std::uint8_t> test_reg_content{0xaf, 0xaf, 0xaf};
  EXPECT_CALL(*spi_, Write(ElementsAre(com::instruction_word::W_REGISTER | test_reg_addr, 0xaf, 0xaf, 0xaf)));
  unit_under_test_ = std::make_unique<com::NRF24L01SpiProtocol>(std::move(spi_));
  auto retval = unit_under_test_->WriteRegister(test_reg_addr, test_reg_content);
  ASSERT_EQ(retval, types::DriverStatus::OK);
}

TEST_F(ComNRF24L01SpiProtocolTests, write_payload_spi_tx_ok) {
  std::vector<std::uint8_t> test_reg_content{0xaf, 0xaf, 0xaf};
  EXPECT_CALL(*spi_, Write(ElementsAre(com::instruction_word::W_TX_PAYLOAD, 0xaf, 0xaf, 0xaf)));
  unit_under_test_ = std::make_unique<com::NRF24L01SpiProtocol>(std::move(spi_));
  auto retval = unit_under_test_->WritePayloadData(test_reg_content);
  ASSERT_EQ(retval, types::DriverStatus::OK);
}

TEST_F(ComNRF24L01SpiProtocolTests, read_payload_spi_tx_ok) {
  std::vector<std::uint8_t> test_payload;
  test_payload.resize(4);
  EXPECT_CALL(*spi_, Transfer(ElementsAre(com::instruction_word::R_RX_PAYLOAD), _));
  unit_under_test_ = std::make_unique<com::NRF24L01SpiProtocol>(std::move(spi_));
  auto retval = unit_under_test_->ReadPayloadData(test_payload);
  EXPECT_THAT(test_payload, ElementsAre(_, _, _));
  ASSERT_EQ(retval, types::DriverStatus::OK);
}

TEST_F(ComNRF24L01SpiProtocolTests, flush_tx_buffer) {
  EXPECT_CALL(*spi_, Write(ElementsAre(com::instruction_word::FLUSH_TX)));
  unit_under_test_ = std::make_unique<com::NRF24L01SpiProtocol>(std::move(spi_));
  unit_under_test_->FlushTxBuffer();
}

TEST_F(ComNRF24L01SpiProtocolTests, flush_rx_buffer) {
  EXPECT_CALL(*spi_, Write(ElementsAre(com::instruction_word::FLUSH_RX)));
  unit_under_test_ = std::make_unique<com::NRF24L01SpiProtocol>(std::move(spi_));
  unit_under_test_->FlushRxBuffer();
}

TEST_F(ComNRF24L01SpiProtocolTests, read_and_clear_irq_flags_ok) {
  std::uint8_t test_reg_addr = com::reg::status::REG_ADDR;
  EXPECT_CALL(*spi_, Transfer(ElementsAre(com::instruction_word::W_REGISTER | test_reg_addr, _), _))
      .WillOnce(Invoke(&ConstructTestVector));
  unit_under_test_ = std::make_unique<com::NRF24L01SpiProtocol>(std::move(spi_));
  auto rv = unit_under_test_->ReadAndClearIRQFlags();
  ASSERT_EQ(rv.second, 0xaa);
  ASSERT_EQ(rv.first, types::DriverStatus::OK);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
