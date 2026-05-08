cmake_minimum_required(VERSION 4.0)

project(lib_pico_wire CXX C ASM)

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
	lib_pico_plus
	hardware_i2c
	hardware_spi
)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
