#ifndef SRC_TYPES_ERROR_TYPES_HPP_
#define SRC_TYPES_ERROR_TYPES_HPP_

#include <cstdint>

namespace types {

/**
 * @brief A error type enum
 * 
 */
enum class HalError : int {
  /// Hal function is working
  WORKING,
  /// Configuration returned an error
  CONFIG_ERROR,
  /// parameter failed
  PARAMETER_ERROR
};

/**
 * @brief An input error enum for setter methods
 * 
 */
enum class InputError : int {
  /// Target input is accepted
  INPUT_CORRECT,
  /// Target input is out of defined range
  INPUT_OUT_OF_RANGE,
  /// Target input is not accepted
  INPUT_FAULTY
};

/**
 * @brief A hardware setup enum to identify hardware setup
 *  errors on abstraction levels above the HAL and 
 *  HAL interfacing classes
 * 
 */
enum class HardwareSetupError : int {
  // Setup worked flawlessly
  HARDWARE_SETUP_CORRECT,
  /// Hardware and/or HAL reports errors
  HARDWARE_REPORTS_ERRORS
};

}  // namespace types

#endif