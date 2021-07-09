#ifndef SRC_COM_COM_NRF24L01_HPP_
#define SRC_COM_COM_NRF24L01_HPP_
#include <algorithm>

#include "com_interface.hpp"
#include "com_nrf24l01_reg.hpp"
#include "com_nrf24l01_types.hpp"
#ifndef UNIT_TEST
#include "com_nrf24l01_spi_protocol.hpp"
#include "utilities/byte.hpp"
#else
#include "byte_mock.hpp"
#include "com_nrf24l01_spi_protocol_mock.hpp"
#endif

namespace com {

/**
 * @brief Driver for the NRF24L01 transceiver. 
 * 
 */
class NRF24L01 final : public ComInterface {
 public:
  auto GetDataPacket() const noexcept -> types::com_msg_frame override;
  auto PutDataPacket(std::uint8_t target_id, types::com_msg_frame &payload) noexcept
      -> types::DriverStatus override;
  auto HandleRxIRQ() noexcept -> void;

  explicit NRF24L01(std::unique_ptr<com::ComMessageBuffer> msg_buf,
                    std::unique_ptr<NRF24L01SpiProtocol> spi_protocol) : ComInterface(std::move(msg_buf)),
                                                                         spi_protocol_(std::move(spi_protocol)),
                                                                         irq_flags(0),
                                                                         current_operation_mode_(com::OperationMode::UNDEFINED),
                                                                         is_initialized_(false) {
    InitTransceiver(com::rf_config::RF_CHANNEL, DataRateSetting::RF_DR_1MBPS, RFPowerSetting::RF_PWR_0DBM, CRCEncodingScheme::CRC_16BIT);
    InitRx();
  };
  NRF24L01() = delete;
  virtual ~NRF24L01() = default;

 private:
  std::unique_ptr<NRF24L01SpiProtocol> spi_protocol_;
  std::uint8_t irq_flags;
  OperationMode current_operation_mode_;
  bool is_initialized_;

  //Pipe configuration
  auto EnableDataPipe(DataPipe pipe_no) noexcept -> types::DriverStatus;
  auto DisableDataPipe(DataPipe pipe_no) noexcept -> types::DriverStatus;

  auto SetTxAddress(data_pipe_address tx_addr) const noexcept -> types::DriverStatus;
  auto SetRxAddress(DataPipe pipe_no, data_pipe_address rx_addr) const noexcept -> types::DriverStatus;
  auto GetPipeAddress(DataPipe pipe_no) noexcept -> data_pipe_address;

  auto SetRxPayloadSize(DataPipe pipe_no, std::size_t payload_size) const noexcept -> types::DriverStatus;
  auto EnableAutoAck(DataPipe pipe_no) noexcept -> types::DriverStatus;

  // Mode switching
  auto InitTx() noexcept -> types::DriverStatus;
  auto InitRx() noexcept -> types::DriverStatus;

  // Transceiver hardware configuration
  auto InitTransceiver(std::uint8_t channel,
                       DataRateSetting data_rate,
                       RFPowerSetting rf_power,
                       CRCEncodingScheme encoding_scheme) noexcept -> types::DriverStatus;
  auto SetOperationMode(OperationMode mode) noexcept -> types::DriverStatus;
  auto SetPowerState(State power_state) noexcept -> types::DriverStatus;
  auto SetRFChannel(std::uint8_t channel) noexcept -> types::DriverStatus;
  auto SetDataRate(DataRateSetting data_rate) noexcept -> types::DriverStatus;
  auto SetRFOutputPower(RFPowerSetting rf_power) noexcept -> types::DriverStatus;
  auto MaskInterruptOnIntPin(MaskeableInterrupts interrupt) -> types::DriverStatus;
  // Not sure if we ever need this
  auto SetLNAGain(State state) noexcept -> types::DriverStatus;

  // General protocol configuration
  auto SetAddressWidth(DataPipeAddressWidth address_width) noexcept -> types::DriverStatus;
  auto EnableCRC() noexcept -> types::DriverStatus;
  auto SetCRCEncodingScheme(CRCEncodingScheme encoding_scheme) noexcept -> types::DriverStatus;
  auto ConfigAutoRetransmission(AutoRetransmissionDelay delay, AutoRetransmitCount count) noexcept -> types::DriverStatus;

  // Status register access
  auto CarrierDetected() noexcept -> bool;
};
}  // namespace com

#endif
