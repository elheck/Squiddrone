#include "com_interrupt_handler.hpp"

namespace com {
std::shared_ptr<com::NRF24L01> ComInterruptHandler::com_;
}

extern "C" {
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  com::ComInterruptHandler::HandleComInterrupt();
};
}