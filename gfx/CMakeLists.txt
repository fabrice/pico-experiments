cmake_minimum_required(VERSION 3.30)

project(gfx_lib CXX C ASM)

add_library(${PROJECT_NAME} STATIC
	gfx_point.cxx
	gfx_rectangle.cxx
	gfx_color_rgb.cxx
	gfx_color_hsb.cxx
	gfx_color_gray.cxx
	gfx_color_argb.cxx
	gfx_canvas.cxx
	gfx_image.cxx
	gfx_bitmap.cxx
	gfx_pixmap.cxx
	gfx_font.cxx
	gfx_glyph.cxx
	fonts/cfpt_mono_6x8.cxx
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(${PROJECT_NAME}
	std_plus_lib
	pico_stdlib
)
