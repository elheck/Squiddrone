#ifndef TESTS_COM_MOCK_LIBRARIES_COM_NRF24L01_MOCK_HPP_
#define TESTS_COM_MOCK_LIBRARIES_COM_NRF24L01_MOCK_HPP_

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "com_nrf24l01_reg.hpp"
#include "com_nrf24l01_types.hpp"
#include "com_types.hpp"
#include "error_types.hpp"

namespace com {

/**
 * @brief Driver for the NRF24L01 transceiver. 
 * 
 */

class NRF24L01 {
 public:
  MOCK_METHOD((types::com_msg_frame), GetDataPacket, (), (const noexcept));
  MOCK_METHOD((types::DriverStatus), PutDataPacket, (std::uint8_t, types::com_msg_frame &), (noexcept));
  // Necessary to use a fake, because of a leakage problem.
  auto HandleRxIRQ() noexcept -> void;

  bool handle_rx_irq_was_called = false;

  NRF24L01() = default;
  ~NRF24L01() = default;
};
}  // namespace com

#endif
