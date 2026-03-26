cmake_minimum_required(VERSION 3.30)

project(oled_lib CXX C ASM)

add_library(${PROJECT_NAME} STATIC
	oled.cpp
	oled_fn.cpp
	oled_oledkit_fn.cpp
	cfpt_logo.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/../
  ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
	std_plus_lib
	pico_stdlib
	hardware_i2c
	pico_plus_lib
)
