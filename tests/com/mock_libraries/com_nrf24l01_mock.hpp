#ifndef TESTS_COM_MOCK_LIBRARIES_COM_NRF24L01_MOCK_HPP_
#define TESTS_COM_MOCK_LIBRARIES_COM_NRF24L01_MOCK_HPP_

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "com_nrf24l01_reg.hpp"
#include "com_nrf24l01_types.hpp"
#include "com_types.hpp"

namespace com {

/**
 * @brief Driver for the NRF24L01 transceiver. 
 * 
 */
class NRF24L01 {
 public:
  MOCK_METHOD((types::com_msg_frame), GetDataPacket, (), (const noexcept));
  MOCK_METHOD((types::ComError), PutDataPacket, (std::uint8_t, types::com_msg_frame &), (noexcept));
  MOCK_METHOD(void, HandleRxIRQ, (), (noexcept));

  NRF24L01() = default;
  ~NRF24L01() = default;
};
}  // namespace com

#endif
