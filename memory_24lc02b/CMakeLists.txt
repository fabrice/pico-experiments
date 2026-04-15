cmake_minimum_required(VERSION 3.30)

project(memory_24lc02b_lib CXX C ASM)

add_library(${PROJECT_NAME} STATIC
	memory_24lc02b.cxx
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
	pico_stdlib
	hardware_i2c
	pico_plus_lib
	pico_wire_lib
)
