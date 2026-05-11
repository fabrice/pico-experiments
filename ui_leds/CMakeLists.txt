#-----------------------------------------------------------------

cmake_minimum_required(VERSION 4.0)

#-----------------------------------------------------------------

project(lib_ui_leds CXX C ASM)

add_library(${PROJECT_NAME} STATIC
	ui_leds.cxx
	ui_leds_fn.cxx
)

target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/
)

#-----------------------------------------------------------------

target_link_libraries(${PROJECT_NAME}
	pico_stdlib
	lib_display_7735
)

#-----------------------------------------------------------------

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

target_compile_options(${PROJECT_NAME} PRIVATE -fexec-charset=ISO-8859-1)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)

#-----------------------------------------------------------------
