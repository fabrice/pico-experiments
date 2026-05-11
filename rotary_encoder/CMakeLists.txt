#-----------------------------------------------------------------

cmake_minimum_required(VERSION 4.0)

#-----------------------------------------------------------------

project(lib_rotary_encoder CXX C ASM)

add_library(${PROJECT_NAME} STATIC
	rotary_encoder.cxx
	rotary_encoder_fn.cxx
)

target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/
)

#-----------------------------------------------------------------

target_link_libraries(${PROJECT_NAME}
	pico_stdlib
	lib_gpio_plus
)

#-----------------------------------------------------------------

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

#-----------------------------------------------------------------
