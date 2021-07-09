#ifndef SRC_COM_COM_BUFFER_TYPES_HPP_
#define SRC_COM_COM_BUFFER_TYPES_HPP_

#include <cstdint>

namespace com {

/**
 * @brief Enum class to contain error codes for COM buffer module.
 * 
 */
enum class ComBufferError : std::int8_t {
  /// No error
  COM_BUFFER_OK,
  /// Buffer overflow error
  COM_BUFFER_OVERFLOW,
  /// Buffer IO error i.e. faulty data in buffer
  COM_BUFFER_IO_ERROR
};

/// Max depth for the com buffer.
static constexpr std::uint8_t COM_BUFFER_MAX_QUEUE_LENGTH = 5;
}  // namespace com

#endif