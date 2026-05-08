cmake_minimum_required(VERSION 4.0)

project(lib_gfx CXX C ASM)

add_library(${PROJECT_NAME} STATIC
	gfx_point.cxx
	gfx_rectangle.cxx
	gfx_color_hsb.cxx
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
	lib_std_plus
	pico_stdlib
)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

target_compile_options(${PROJECT_NAME} PRIVATE -fexec-charset=ISO-8859-1)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
