#ifndef COM_COM_NRF24L01_TYPES_HPP_
#define COM_COM_NRF24L01_TYPES_HPP_

namespace com {

enum class State : std::uint8_t {
  DISABLED = 0,
  ENABLED
};

enum class CRCEncodingScheme : std::uint8_t {
  CRC_8BIT,
  CRC_16BIT
};

enum class DataPipe : std::uint8_t {
  RX_PIPE_0 = 0,
  RX_PIPE_1,
  RX_PIPE_2,
  RX_PIPE_3,
  RX_PIPE_4,
  RX_PIPE_5,
  TX_PIPE
};

enum class DataPipeAddressWidth : std::uint8_t {
  AW_3BYTES = 0x1,
  AW_4BYTES = 0x2,
  AW_5BYTES = 0x3,
};

enum class AutoRetransmissionDelay : std::uint8_t {
  // auto retransmission delay 250-4000 us
  ARD250US = 0x0,
  ARD500US = 0x1,
  ARD750US = 0x2,
  ARD1000US = 0x3,
  ARD1250US = 0x4,
  ARD1500US = 0x5,
  ARD1750US = 0x6,
  ARD2000US = 0x7,
  ARD2250US = 0x8,
  ARD2500US = 0x9,
  ARD2750US = 0xa,
  ARD3000US = 0xb,
  ARD3250US = 0xc,
  ARD3500US = 0xd,
  ARD3750US = 0xe,
  ARD4000US = 0xf
};

enum class AutoRetransmitCount : std::uint8_t {
  // auto retransmit count 0-15 in case of failed auto retransmit
  ARC0 = 0x0,
  ARC1 = 0x1,
  ARC2 = 0x2,
  ARC3 = 0x3,
  ARC4 = 0x4,
  ARC5 = 0x5,
  ARC6 = 0x6,
  ARC7 = 0x7,
  ARC8 = 0x8,
  ARC9 = 0x9,
  ARC10 = 0xa,
  ARC11 = 0xb,
  ARC12 = 0xc,
  ARC13 = 0xd,
  ARC14 = 0xe,
  ARC15 = 0xf
};

enum class OperationMode : std::uint8_t {
  UNDEFINED = 0,
  PRIM_RX,
  PRIM_TX
};

enum class RFPowerSetting : std::uint8_t {
  RF_PWR_18DBM = 0x0,
  RF_PWR_12DBM = 0x1,
  RF_PWR_6DBM = 0x2,
  RF_PWR_0DBM = 0x3
};

enum class DataRateSetting : std::uint8_t {
  RF_DR_1MBPS = 0,
  RF_DR_2MPBS = 1
};

enum class MaskeableInterrupts : std::uint8_t {
  MAX_NR_OF_RETRIES_REACHED = 4,
  TX_DATA_SENT = 5,
  RX_DATA_READY = 6
};

using data_pipe_address = std::array<std::uint8_t, 5>;
using register_t = std::uint8_t;

}  // namespace com

#endif
