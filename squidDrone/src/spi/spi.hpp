#ifndef SRC_SPI_SPI_HPP_
#define SRC_SPI_SPI_HPP_

#include "spi_interface.hpp"

namespace spi {

class SPI final : spi::SPIInterface {
 public:
  SPI() = delete;
  explicit SPI(const std::uint8_t chip_select) : spi::SPIInterface(), chip_select_(chip_select){};
  auto Transfer(std::unique_ptr<std::uint8_t> RxData, std::unique_ptr<std::uint8_t> TxData) noexcept -> spi::SPIStatus override;

 private:
  std::uint8_t chip_select_;
};

}  // namespace spi

#endif