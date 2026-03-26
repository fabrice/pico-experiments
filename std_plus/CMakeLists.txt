cmake_minimum_required(VERSION 3.30)

project(std_plus_lib CXX C ASM)

add_library(${PROJECT_NAME} STATIC
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/../
  ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
	pico_stdlib
)
