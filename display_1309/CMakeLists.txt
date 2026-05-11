#-----------------------------------------------------------------

cmake_minimum_required(VERSION 4.0)

#-----------------------------------------------------------------

project(lib_display_1309 CXX C ASM)

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

#-----------------------------------------------------------------

target_link_libraries(${PROJECT_NAME}
	lib_std_plus
	pico_stdlib
	lib_pico_plus
	lib_pico_wire
)

#-----------------------------------------------------------------

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

target_compile_options(${PROJECT_NAME} PRIVATE -fexec-charset=ISO-8859-1)
#target_compile_options(${PROJECT_NAME} PRIVATE -Wall)

#-----------------------------------------------------------------
