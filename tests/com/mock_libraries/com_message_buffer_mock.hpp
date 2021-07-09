#ifndef TESTS_MOCK_LIBRARIES_COM_COM_MESSAGE_BUFFER_HPP_
#define TESTS_MOCK_LIBRARIES_COM_COM_MESSAGE_BUFFER_HPP_

#include <array>
#include <queue>
#include "com_buffer_types.hpp"
#include "com_types.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace com {

class ComMessageBuffer {
 public:
  ComMessageBuffer() : test_member(0){};
  MOCK_METHOD(ComBufferError, PutData, (types::com_msg_frame & data), (const, noexcept));
  MOCK_METHOD(types::com_msg_frame, GetData, (), (const, noexcept));
  MOCK_METHOD(bool, BufferIsEmpty, (), (noexcept));

  std::uint8_t test_member;
};
}  // namespace com

#endif
