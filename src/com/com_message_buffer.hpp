#ifndef SRC_COM_MESSAGE_BUFFER_HPP_
#define SRC_COM_MESSAGE_BUFFER_HPP_

#include <array>
#include <queue>
#include "com_buffer_types.hpp"
#include "com_types.hpp"

namespace com {
/** 
 * @brief This class represents a queue style buffer for communication
 * frames exchanged between drones.
 * 
 */
class ComMessageBuffer {
 public:
  /** 
   * @brief Construct a new Com Message Buffer object
   * 
   */
  ComMessageBuffer(){};

  /** 
   * @brief Transfer data to queue buffer. 
   * 
   * @param data Reference to data frame. Must conform to data frame specifications.
   * @return types::ComError COM_OK if ok, COM_BUFFER_OVERFLOW if buffer is full,
   * COM_BUFFER_IO_ERROR if com frame too large.
   * 
   */
  auto PutData(types::com_msg_frame &data) noexcept -> ComBufferError;

  /** 
   * @brief Retrieve data frame from queue buffer.
   * 
   * @return types::com_msg_frame 
   * 
   */
  auto GetData() noexcept -> types::com_msg_frame;

  /**
   * @brief Check if the buffer is empty.
   * 
   * @return true If buffer is empty returns true.
   * @return false If buffer is not empty returns false.
   */
  auto BufferIsEmpty() const noexcept -> bool;

 private:
  /** 
   * @brief Queue to hold the 32 byte long data frames. Queue shall be emptied on
   * each execution slice and the data frames shall be processed.
   * 
   */
  std::queue<types::com_msg_frame> data_;
};
}  // namespace com

#endif
