cmake_minimum_required(VERSION 4.0)

project(lib_mcp41xxx CXX C ASM)

add_library(${PROJECT_NAME} STATIC
	mcp41xxx.cxx
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
	pico_stdlib
	lib_pico_plus
	lib_pico_wire
)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
