#ifndef SRC_COM_COM_INTERRUPT_HANDLER_HPP_
#define SRC_COM_COM_INTERRUPT_HANDLER_HPP_

#ifndef UNIT_TEST
#include "com_nrf24l01.hpp"
#else
#include "com_nrf24l01_mock.hpp"
#endif

namespace com {
/**
 * @brief This class directs calls from the HAL GPIO interrupt handler to the com
 * driver class. Current implementation is stateful! So be aware that the 
 * com driver has to be made known to the class.
 * 
 */
class ComInterruptHandler {
 public:
  /**
   * @brief This function is called by the HAL EXTI callback.
   * 
   */
  static auto HandleComInterrupt() noexcept -> void {
    if (com_ != nullptr) {
      com_->HandleRxIRQ();
    }
  };
  /**
   * @brief Set the Com Driver object
   * 
   * @param com_object 
   */
  static auto SetComDriver(std::shared_ptr<com::NRF24L01> com_object) noexcept -> void {
    com_ = com_object;
  };
  /**
   * @brief This class does not have a constructor.
   * 
   */
  ComInterruptHandler() = delete;
  /**
   * @brief Destroy the Com Interrupt Handler object
   * 
   */
  virtual ~ComInterruptHandler() = default;

 private:
  /**
   * @brief Static shared pointer to the com driver object.
   * 
   */
  static std::shared_ptr<com::NRF24L01> com_;
};

}  // namespace com

#endif
