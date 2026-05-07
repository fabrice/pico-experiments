cmake_minimum_required(VERSION 3.30)

project(lib_gpio_plus CXX C ASM)

add_library(${PROJECT_NAME} STATIC
	gpio_irq_vtable.cxx
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
	pico_stdlib
)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
