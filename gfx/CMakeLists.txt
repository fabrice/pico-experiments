cmake_minimum_required(VERSION 3.30)

project(gfx_lib CXX C ASM)

add_library(${PROJECT_NAME} STATIC
	gfx_rectangle.cpp
	gfx_bitmap.cpp
	gfx_color.cpp
	gfx_color_hsb.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/../
  ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
	std_plus_lib
	pico_stdlib
)
