#include "gtest/gtest.h"
#include "utilities/byte.hpp"

namespace {

class UtilityByteTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }

  std::unique_ptr<utilities::Byte> unit_under_test;
};

TEST_F(UtilityByteTests, byte_initialize_with_number_5) {
  unit_under_test = std::make_unique<utilities::Byte>(5);

  EXPECT_EQ(5, unit_under_test->Get());
}

TEST_F(UtilityByteTests, byte_initialize_with_number_0) {
  unit_under_test = std::make_unique<utilities::Byte>(0);

  EXPECT_EQ(0, unit_under_test->Get());
}

TEST_F(UtilityByteTests, byte_initialize_with_number_255) {
  unit_under_test = std::make_unique<utilities::Byte>(255);

  EXPECT_EQ(255, unit_under_test->Get());
}

TEST_F(UtilityByteTests, byte_init_0_set_one_bit) {
  unit_under_test = std::make_unique<utilities::Byte>(0);

  unit_under_test->SetBit(3);

  EXPECT_EQ(0b00001000, unit_under_test->Get());
}

TEST_F(UtilityByteTests, byte_init_0_set_two_bits) {
  unit_under_test = std::make_unique<utilities::Byte>(0);

  unit_under_test->SetBit(3);
  unit_under_test->SetBit(5);

  EXPECT_EQ(0b00101000, unit_under_test->Get());
}

TEST_F(UtilityByteTests, byte_init_0_set_three_bits) {
  unit_under_test = std::make_unique<utilities::Byte>(0);

  unit_under_test->SetBit(0);
  unit_under_test->SetBit(3);
  unit_under_test->SetBit(5);

  EXPECT_EQ(0b00101001, unit_under_test->Get());
}

TEST_F(UtilityByteTests, byte_init_0_set_three_bits_clear_one) {
  unit_under_test = std::make_unique<utilities::Byte>(0);

  unit_under_test->SetBit(0);
  unit_under_test->SetBit(3);
  unit_under_test->SetBit(5);

  EXPECT_EQ(0b00101001, unit_under_test->Get());

  unit_under_test->ClearBit(3);

  EXPECT_EQ(0b00100001, unit_under_test->Get());
}

TEST_F(UtilityByteTests, byte_init_0_set_bit_9) {
  unit_under_test = std::make_unique<utilities::Byte>(0);

  unit_under_test->SetBit(3);
  unit_under_test->SetBit(9);

  EXPECT_EQ(0b00001000, unit_under_test->Get());
}

TEST_F(UtilityByteTests, byte_init_0_set_same_bit_twice) {
  unit_under_test = std::make_unique<utilities::Byte>(0);

  unit_under_test->SetBit(3);
  unit_under_test->SetBit(3);

  EXPECT_EQ(0b00001000, unit_under_test->Get());
}

TEST_F(UtilityByteTests, byte_init_0_clear_same_bit_twice) {
  unit_under_test = std::make_unique<utilities::Byte>(0);

  unit_under_test->SetBit(3);
  unit_under_test->ClearBit(3);
  unit_under_test->ClearBit(3);

  EXPECT_EQ(0b00000000, unit_under_test->Get());
}

TEST_F(UtilityByteTests, byte_is_bit_3_high_true) {
  unit_under_test = std::make_unique<utilities::Byte>(0b1000);

  EXPECT_EQ(true, unit_under_test->IsBitHigh(3));
}

TEST_F(UtilityByteTests, byte_is_bit_3_high_false) {
  unit_under_test = std::make_unique<utilities::Byte>(0);

  EXPECT_EQ(false, unit_under_test->IsBitHigh(3));
}

TEST_F(UtilityByteTests, byte_is_bit_3_low_true) {
  unit_under_test = std::make_unique<utilities::Byte>(0b1000);

  EXPECT_EQ(false, unit_under_test->IsBitLow(3));
}

TEST_F(UtilityByteTests, byte_is_bit_3_low_false) {
  unit_under_test = std::make_unique<utilities::Byte>(0);

  EXPECT_EQ(true, unit_under_test->IsBitLow(3));
}

TEST_F(UtilityByteTests, byte_zero_set_low_nibble) {
  unit_under_test = std::make_unique<utilities::Byte>(0);

  unit_under_test->SetLowNibble(0b1010);

  EXPECT_EQ(0b00001010, unit_under_test->Get());
}

TEST_F(UtilityByteTests, byte_zero_set_high_nibble) {
  unit_under_test = std::make_unique<utilities::Byte>(0);

  unit_under_test->SetHighNibble(0b1010);

  EXPECT_EQ(0b10100000, unit_under_test->Get());
}

TEST_F(UtilityByteTests, byte_not_zero_set_low_nibble) {
  unit_under_test = std::make_unique<utilities::Byte>(0b11111111);

  unit_under_test->SetLowNibble(0b1010);

  EXPECT_EQ(0b11111010, unit_under_test->Get());
}

TEST_F(UtilityByteTests, byte_not_zero_set_high_nibble) {
  unit_under_test = std::make_unique<utilities::Byte>(0b11111111);

  unit_under_test->SetHighNibble(0b1010);

  EXPECT_EQ(0b10101111, unit_under_test->Get());
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}