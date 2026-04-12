//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_font_data
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "gfx_types.h"

#include <cstdint>
#include <vector>
#include <map>

//----------------------------------------------------------------

struct gfx_font_data;
struct gfx_glyph_data;
using gfx_glyph_data_map = std::map< char, gfx_glyph_data >;

//----------------------------------------------------------------

struct gfx_font_data {
	gfx_dxy_t x_advance;
	gfx_dxy_t y_advance;
	gfx_glyph_data_map glyphs;
};

//----------------------------------------------------------------

struct gfx_glyph_data {
	char character;
	gfx_xy_t x;
	gfx_xy_t y;
	gfx_wh_t width;
	gfx_wh_t height;
	gfx_dxy_t x_advance;
	gfx_bytemap_data bytemap;
};

//----------------------------------------------------------------
