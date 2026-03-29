cmake_minimum_required(VERSION 3.30)

project(ee24lc02b_lib CXX C ASM)

add_library(${PROJECT_NAME} STATIC
	ee24lc02b.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/../
  ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
	pico_stdlib
	hardware_i2c
	pico_plus_lib
)
