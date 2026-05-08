cmake_minimum_required(VERSION 4.0)

project(lib_buzzer CXX C ASM)

add_library(${PROJECT_NAME} STATIC
	buzzer.cxx
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
	pico_stdlib
	lib_pwm_plus
)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
