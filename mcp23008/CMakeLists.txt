cmake_minimum_required(VERSION 3.30)

project(mcp23008_lib CXX C ASM)

add_library(${PROJECT_NAME} STATIC
	mcp23008.cpp
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
