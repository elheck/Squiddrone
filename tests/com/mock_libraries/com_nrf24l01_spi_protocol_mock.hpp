#ifndef TESTS_COM_MOCK_LIBRARIES_COM_NRF24L01_SPI_PROTOCOL_MOCK_HPP_
#define TESTS_COM_MOCK_LIBRARIES_COM_NRF24L01_SPI_PROTOCOL_MOCK_HPP_

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace com {

using ReadRegSinglebyteReturn = std::pair<types::DriverStatus, std::uint8_t>;
using ReadRegMultibyteReturn = std::pair<types::DriverStatus, std::vector<std::uint8_t>>;

class NRF24L01SpiProtocol {
 public:
  NRF24L01SpiProtocol() = default;
  MOCK_METHOD(ReadRegSinglebyteReturn, ReadRegister, (std::uint8_t), (noexcept));
  MOCK_METHOD(ReadRegMultibyteReturn, ReadRegister, (std::uint8_t, std::uint8_t), (noexcept));
  MOCK_METHOD((types::DriverStatus), WriteRegister, (std::uint8_t, std::uint8_t), (noexcept));
  MOCK_METHOD((types::DriverStatus), FlushTxBuffer, (), (noexcept));
  MOCK_METHOD((types::DriverStatus), FlushRxBuffer, (), (noexcept));
  MOCK_METHOD((std::pair<types::DriverStatus, std::uint8_t>), ReadAndClearIRQFlags, (), (noexcept));
  MOCK_METHOD((types::DriverStatus), WritePayloadData, (std::vector<std::uint8_t>), (noexcept));
  MOCK_METHOD((types::DriverStatus), ReadPayloadData, (std::vector<std::uint8_t>), (noexcept));
};
}  // namespace com

#endif