#-----------------------------------------------------------------

cmake_minimum_required(VERSION 4.0)

#-----------------------------------------------------------------

project(lib_display_7735 CXX C ASM)

add_library(${PROJECT_NAME} STATIC
	display_7735.cxx
	display_7735_fn.cxx
	cfpt_mono_6x8.cxx
)

target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/
)

#-----------------------------------------------------------------

target_link_libraries(${PROJECT_NAME}
	pico_stdlib
	hardware_pwm
	lib_std_plus
	lib_pico_wire
)

#-----------------------------------------------------------------

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

target_compile_options(${PROJECT_NAME} PRIVATE -fexec-charset=ISO-8859-1)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)

#-----------------------------------------------------------------
