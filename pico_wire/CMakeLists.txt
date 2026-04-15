cmake_minimum_required(VERSION 3.30)

project(pico_wire_lib CXX C ASM)

add_library(${PROJECT_NAME} STATIC
	wire.cxx
	wire_i2c.cxx
	wire_spi.cxx
	wire_uart.cxx
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
	pico_stdlib
	pico_plus_lib
	hardware_i2c
	hardware_spi
)
