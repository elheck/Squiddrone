#include "com_nrf24l01_mock.hpp"

namespace com {

auto NRF24L01::HandleRxIRQ() noexcept -> void {
  handle_rx_irq_was_called = true;
}

}  // namespace com
