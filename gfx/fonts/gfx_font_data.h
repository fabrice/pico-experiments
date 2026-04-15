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
	gfx_dxy_t x_advance { 0 };
	gfx_dxy_t y_advance { 0 };
	gfx_glyph_data_map glyphs {};
};

//----------------------------------------------------------------

struct gfx_glyph_data {
	char character { 0 };
	gfx_xy_t x { 0 };
	gfx_xy_t y { 0 };
	gfx_wh_t width { 0 };
	gfx_wh_t height { 0 };
	gfx_dxy_t x_advance { 0 };
	gfx_bytemap_data bytemap { size_t(0) };
};

//----------------------------------------------------------------
