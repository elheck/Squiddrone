#ifndef SRC_TYPES_COM_TYPES_HPP_
#define SRC_TYPES_COM_TYPES_HPP_

#include <cstdint>
#include <vector>

namespace types {

/// Max length for com message frames.
static constexpr std::uint8_t COM_MAX_FRAME_LENGTH = 32;

/// Type alias for com message frame datatype
using com_msg_frame = std::vector<std::uint8_t>;
}  // namespace types

#endif