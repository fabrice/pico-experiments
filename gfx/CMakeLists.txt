cmake_minimum_required(VERSION 3.30)

project(gfx_lib CXX C ASM)

add_library(${PROJECT_NAME} PRIVATE
	gfx_point.cpp
	gfx_rectangle.cpp
	gfx_color_rgb.cpp
	gfx_color_hsb.cpp
	gfx_color_gray.cpp
	gfx_color_argb.cpp
	gfx_canvas.cpp
	gfx_image.cpp
	gfx_bitmap.cpp
	gfx_pixmap.cpp
	gfx_font.cpp
	gfx_glyph.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
	std_plus_lib
	pico_stdlib
)
