#ifndef SRC_COM_COM_NRF24L01_REG_HPP_
#define SRC_COM_COM_NRF24L01_REG_HPP_

#include <array>
#include <cstdint>

namespace com {

namespace instruction_word {
static constexpr std::uint8_t R_REGISTER = 0x00;
static constexpr std::uint8_t W_REGISTER = 0x20;
static constexpr std::uint8_t R_RX_PAYLOAD = 0x61;
static constexpr std::uint8_t W_TX_PAYLOAD = 0xa0;
static constexpr std::uint8_t FLUSH_TX = 0xe1;
static constexpr std::uint8_t FLUSH_RX = 0xe2;
static constexpr std::uint8_t REUSE_TX_PL = 0xe3;
static constexpr std::uint8_t NOP = 0xff;
}  // namespace instruction_word

namespace rf_config {
static constexpr std::uint8_t RF_CHANNEL = 20;
}

/// Default value for address width
namespace addr_config {
static constexpr std::uint8_t ADDR_WIDTH = 5U;
}  // namespace addr_config

namespace reg {
/// configuration register
namespace config {
static constexpr std::uint8_t REG_ADDR = 0x0;
static constexpr std::uint8_t MASK_RX_DR = 6;
static constexpr std::uint8_t MASK_TX_DS = 5;
static constexpr std::uint8_t MASK_MAX_RT = 4;
static constexpr std::uint8_t EN_CRC = 3;
static constexpr std::uint8_t CRCO = 2;
static constexpr std::uint8_t PWR_UP = 1;
static constexpr std::uint8_t PRIM_RX = 0;
}  // namespace config

/// enable enhanced shock burst auto acknowledgement
namespace en_aa {
static constexpr std::uint8_t REG_ADDR = 0x1;
static constexpr std::uint8_t ENAA_P5 = 5;
static constexpr std::uint8_t ENAA_P4 = 4;
static constexpr std::uint8_t ENAA_P3 = 3;
static constexpr std::uint8_t ENAA_P2 = 2;
static constexpr std::uint8_t ENAA_P1 = 1;
static constexpr std::uint8_t ENAA_P0 = 0;
}  // namespace en_aa

/// enable RX data pipes
namespace en_rxaddr {
static constexpr std::uint8_t REG_ADDR = 0x2;
static constexpr std::uint8_t ERX_P5 = 5;
static constexpr std::uint8_t ERX_P4 = 4;
static constexpr std::uint8_t ERX_P3 = 3;
static constexpr std::uint8_t ERX_P2 = 2;
static constexpr std::uint8_t ERX_P1 = 1;
static constexpr std::uint8_t ERX_P0 = 1;
}  // namespace en_rxaddr

/// setup of address widths
namespace setup_aw {
static constexpr std::uint8_t REG_ADDR = 0x3;
}  // namespace setup_aw

/// setup of automatic retransmission
namespace setup_retr {
static constexpr std::uint8_t REG_ADDR = 0x4;
}  // namespace setup_retr

/// RF channel setting
namespace rf_ch {
static constexpr std::uint8_t REG_ADDR = 0x5;
}  // namespace rf_ch

/// RF setup register
namespace rf_setup {
static constexpr std::uint8_t REG_ADDR = 0x6;
static constexpr std::uint8_t PLL_LOCK = 4;
static constexpr std::uint8_t RF_DR = 3;
static constexpr std::uint8_t RF_PWR = 1;
static constexpr std::uint8_t LNA_HCURR = 0;
}  // namespace rf_setup

/// Status Register
namespace status {
static constexpr std::uint8_t REG_ADDR = 0x7;
static constexpr std::uint8_t RX_DR = 6;
static constexpr std::uint8_t TX_DS = 5;
static constexpr std::uint8_t MAX_RT = 4;
static constexpr std::uint8_t RX_P_NO = 1;
static constexpr std::uint8_t RX_P_NO_0 = 0b0;
static constexpr std::uint8_t RX_P_NO_1 = 0b1;
static constexpr std::uint8_t RX_P_NO_2 = 0b10;
static constexpr std::uint8_t RX_P_NO_3 = 0b11;
static constexpr std::uint8_t RX_P_NO_4 = 0b100;
static constexpr std::uint8_t RX_P_NO_5 = 0b101;
static constexpr std::uint8_t RX_FIFO_EMPTY = 0b111;
static constexpr std::uint8_t TX_FULL = 0;
}  // namespace status

/// Transmit observe register
namespace observe_tx {
static constexpr std::uint8_t REG_ADDR = 0x8;
static constexpr std::uint8_t PLOS_CNT = 4;
static constexpr std::uint8_t ARC_CNT = 0;
}  // namespace observe_tx

/// Received power detector register
namespace rpd {
static constexpr std::uint8_t REG_ADDR = 0x9;
static constexpr std::uint8_t RPD = 0;
}  // namespace rpd

/// Receive address data pipe 0. 5 Bytes maximum length.
namespace rx_addr_p0 {
static constexpr std::uint8_t REG_ADDR = 0x0a;
}  // namespace rx_addr_p0

/// Receive address data pipe 1. 5 Bytes maximum length.
namespace rx_addr_p1 {
static constexpr std::uint8_t REG_ADDR = 0x0b;
}  // namespace rx_addr_p1

/// Receive address data pipe 2. Only LSB.
namespace rx_addr_p2 {
static constexpr std::uint8_t REG_ADDR = 0x0c;
}  // namespace rx_addr_p2

/// Receive address data pipe 3. Only LSB.
namespace rx_addr_p3 {
static constexpr std::uint8_t REG_ADDR = 0x0d;
}  // namespace rx_addr_p3

/// Receive address data pipe 4. Only LSB.
namespace rx_addr_p4 {
static constexpr std::uint8_t REG_ADDR = 0x0e;
}  // namespace rx_addr_p4

/// Receive address data pipe 5. Only LSB.
namespace rx_addr_p5 {
static constexpr std::uint8_t REG_ADDR = 0x0f;
}  // namespace rx_addr_p5

/// Transmit address. Used for a PTX device only.
namespace tx_addr {
static constexpr std::uint8_t REG_ADDR = 0x10;
}  // namespace tx_addr

/// Number of bytes in RX payload in data pipe 0.
namespace rx_pw_p0 {
static constexpr std::uint8_t REG_ADDR = 0x11;
}  // namespace rx_pw_p0

/// Number of bytes in RX payload in data pipe 1.
namespace rx_pw_p1 {
static constexpr std::uint8_t REG_ADDR = 0x12;
}  // namespace rx_pw_p1

/// Number of bytes in RX payload in data pipe 2.
namespace rx_pw_p2 {
static constexpr std::uint8_t REG_ADDR = 0x13;
}  // namespace rx_pw_p2

/// Number of bytes in RX payload in data pipe 3.
namespace rx_pw_p3 {
static constexpr std::uint8_t REG_ADDR = 0x14;
}  // namespace rx_pw_p3

/// Number of bytes in RX payload in data pipe 4.
namespace rx_pw_p4 {
static constexpr std::uint8_t REG_ADDR = 0x15;
}  // namespace rx_pw_p4

/// Number of bytes in RX payload in data pipe 5.
namespace rx_pw_p5 {
static constexpr std::uint8_t REG_ADDR = 0x16;
}  // namespace rx_pw_p5

/// FIFO status register
namespace fifo_status {
static constexpr std::uint8_t REG_ADDR = 0x17;
static constexpr std::uint8_t TX_REUSE = 6;
static constexpr std::uint8_t TX_FULL = 5;
static constexpr std::uint8_t TX_EMPTY = 4;
static constexpr std::uint8_t RX_FULL = 1;
static constexpr std::uint8_t RX_EMPTY = 0;
}  // namespace fifo_status

}  // namespace reg
}  // namespace com

#endif
