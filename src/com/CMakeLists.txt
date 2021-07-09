target_include_directories(${ELF_FILE}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR/src/spi}
)

target_sources(${ELF_FILE}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/com_message_buffer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/com_nrf24l01_spi_protocol.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/com_nrf24l01.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/com_interrupt_handler.cpp
)