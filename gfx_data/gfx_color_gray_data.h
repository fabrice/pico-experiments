//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "gfx_color_rgb_data.h"

#include <cstdint>
#include <cmath>

//----------------------------------------------------------------

struct gfx_color_rgb_data;
struct gfx_color_gray_data;

//----------------------------------------------------------------

struct gfx_color_gray_data {
	uint8_t gray;
};

//----------------------------------------------------------------

gfx_color_gray_data make_color_gray_data( uint8_t gray ) {
	return { gray };
}

//----------------------------------------------------------------

gfx_color_rgb_data color_gray_to_rgb_data( const gfx_color_gray_data& color ) {
	return { color.gray, color.gray, color.gray };
}

//----------------------------------------------------------------

gfx_color_gray_data color_rgb_to_gray_data( const gfx_color_rgb_data& color ) {
	const uint8_t gray = std::max( color.red, std::max( color.green, color.blue ) );
	return { gray };
}

//----------------------------------------------------------------

uint16_t color_gray_data_to_rgb565( const gfx_color_gray_data& color ) {
	return
		((color.gray & 0b11111000) << 8) |
		((color.gray & 0b11111100) << 3) |
		((color.gray & 0b11111000) >> 3);
}

//----------------------------------------------------------------
