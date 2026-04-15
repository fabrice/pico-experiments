cmake_minimum_required(VERSION 3.30)

project(pwm_plus_lib CXX C ASM)

add_library(${PROJECT_NAME} STATIC
	pwm.cxx
	pwm_slice.cxx
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
	std_plus_lib
	pico_stdlib
	hardware_pwm
)
