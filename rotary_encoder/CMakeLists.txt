cmake_minimum_required(VERSION 3.30)

project(rotary_encoder_lib CXX C ASM)

add_library(${PROJECT_NAME} STATIC
	rotary_encoder.cpp
	rotary_encoder_fn.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
	pico_stdlib
	gpio_plus_lib
)
