cmake_minimum_required(VERSION 3.30)

project(display_1309_lib CXX C ASM)

add_library(${PROJECT_NAME} STATIC
	oled.cxx
	oled_fn.cxx
	oled_oledkit_fn.cxx
	cfpt_mono_6x8.cxx
	cfpt_logo.cxx
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
	std_plus_lib
	pico_stdlib
	pico_plus_lib
	pico_wire_lib
)
