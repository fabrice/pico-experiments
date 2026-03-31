cmake_minimum_required(VERSION 3.30)

project(display_7735_lib CXX C ASM)

add_library(${PROJECT_NAME} STATIC
	display_7735.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/../
  ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
	pico_stdlib
	hardware_pwm
	pico_wire_lib
)
