#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "com_interface.hpp"

using ::testing::NiceMock;
using ::testing::Return;

namespace {
class ConcreteComInterface final : public com::ComInterface {
 private:
  types::com_msg_frame ret_array_ = {0};

 public:
  using com::ComInterface::msg_buffer_;
  explicit ConcreteComInterface(std::unique_ptr<com::ComMessageBuffer> com_buf) : com::ComInterface(std::move(com_buf)) {}

  auto GetDataPacket() const noexcept -> types::com_msg_frame override {
    return msg_buffer_->GetData();
  }

  auto PutDataPacket(std::uint8_t target_id, types::com_msg_frame &payload) noexcept -> types::DriverStatus override {
    return types::DriverStatus::OK;
  }
};

class ComInterfaceTests : public ::testing::Test {
 protected:
  std::unique_ptr<com::ComMessageBuffer> com_buffer_ = std::make_unique<NiceMock<com::ComMessageBuffer>>();
  types::com_msg_frame default_return_ = {0xAA};

  virtual void SetUp() {
    ON_CALL(*com_buffer_, GetData).WillByDefault(Return(default_return_));
    com_buffer_->test_member = 0xfa;
  }
};
}  // namespace

TEST_F(ComInterfaceTests, is_constructible_with_com_buffer) {
  auto unit_under_test = std::make_unique<ConcreteComInterface>(std::move(com_buffer_));
  ASSERT_EQ(0xfa, unit_under_test->msg_buffer_->test_member);
}

TEST_F(ComInterfaceTests, get_data_packet) {
  types::com_msg_frame data_compare = {0xAA};
  auto unit_under_test = std::make_unique<ConcreteComInterface>(std::move(com_buffer_));
  ASSERT_EQ(data_compare, unit_under_test->GetDataPacket());
  ASSERT_THAT(unit_under_test->GetDataPacket(), data_compare);
}

TEST_F(ComInterfaceTests, put_data_packet) {
  types::com_msg_frame data;
  auto unit_under_test = std::make_unique<ConcreteComInterface>(std::move(com_buffer_));
  ASSERT_EQ(types::DriverStatus::OK, unit_under_test->PutDataPacket(1, data));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
