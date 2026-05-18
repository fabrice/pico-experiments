//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include <cstdint>

//----------------------------------------------------------------

struct gfx_color_rgb_data {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

//----------------------------------------------------------------

gfx_color_rgb_data make_color_rgb_data( uint8_t red, uint8_t green, uint8_t blue ) {
	return { red, green, blue };
}

//----------------------------------------------------------------

uint16_t color_rgb_data_to_rgb565( const gfx_color_rgb_data& color ) {
	return
		((color.red & 0b11111000) << 8) |
		((color.green & 0b11111100) << 3) |
		((color.blue & 0b11111000) >> 3);
}

//----------------------------------------------------------------

gfx_color_rgb_data rgb565_to_color_rgb_data( uint16_t color ) {
	return {
		((color >> 11) & 0b00011111) << 3,
		((color >> 5) & 0b00111111) << 2,
		((color >> 0) & 0b00011111) << 3 };
}

//----------------------------------------------------------------
