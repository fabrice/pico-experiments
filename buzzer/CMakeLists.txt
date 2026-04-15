cmake_minimum_required(VERSION 3.30)

project(buzzer_lib CXX C ASM)

add_library(${PROJECT_NAME} STATIC
	buzzer.cxx
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
	pico_stdlib
	pwm_plus_lib
)
