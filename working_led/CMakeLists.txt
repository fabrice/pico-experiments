cmake_minimum_required(VERSION 4.0)

project(lib_working_led CXX C ASM)

add_library(${PROJECT_NAME} STATIC
	working_led.cxx
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
	pico_stdlib
)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

target_compile_options(${PROJECT_NAME} PRIVATE -fexec-charset=ISO-8859-1)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
