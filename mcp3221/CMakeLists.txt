cmake_minimum_required(VERSION 3.30)

project(lib_mcp3221 CXX C ASM)

add_library(${PROJECT_NAME} STATIC
	mcp3221.cxx
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
	pico_stdlib
	hardware_i2c
	lib_pico_plus
	lib_pico_wire
)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
