cmake_minimum_required(VERSION 3.30)

project(lib_pwm_plus CXX C ASM)

add_library(${PROJECT_NAME} STATIC
	pwm.cxx
	pwm_slice.cxx
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
	lib_std_plus
	pico_stdlib
	hardware_pwm
)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
