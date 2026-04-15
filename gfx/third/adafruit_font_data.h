//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include <cstdint>

//----------------------------------------------------------------

struct adafruit_gfx_glyph_data {
	uint16_t bitmapOffset { 0 }; ///< Pointer into GFXfont->bitmap
	uint8_t width { 0 };         ///< Bitmap dimensions in pixels
	uint8_t height { 0 };        ///< Bitmap dimensions in pixels
	uint8_t xAdvance { 0 };      ///< Distance to advance cursor (x axis)
	int8_t xOffset { 0 };        ///< X dist from cursor pos to UL corner
	int8_t yOffset { 0 };        ///< Y dist from cursor pos to UL corner
};

//----------------------------------------------------------------

struct adafruit_gfx_font_data {
	const uint8_t* bitmap { nullptr };  ///< Glyph bitmaps, concatenated
	adafruit_gfx_glyph_data* glyph { nullptr };  ///< Glyph array
	uint16_t first { 0 };   ///< ASCII extents (first char)
	uint16_t last { 0 };    ///< ASCII extents (last char)
	uint8_t yAdvance { 0 }; ///< Newline distance (y axis)
};

//----------------------------------------------------------------
