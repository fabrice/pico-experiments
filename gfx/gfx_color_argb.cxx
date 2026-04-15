//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_color_argb
//
//----------------------------------------------------------------
// includes

#include "gfx_color_argb.h"
#include "gfx_color_rgb.h"

#include <cmath>
#include <bit>
#include <algorithm>

//----------------------------------------------------------------

const gfx_color_argb gfx_color_argb::BLACK = gfx_color_argb( 0x00_u8, 0x00_u8, 0x00_u8, 0x00_u8 );
const gfx_color_argb gfx_color_argb::WHITE = gfx_color_argb( 0x00_u8, 0xff_u8, 0xff_u8, 0xff_u8 );
const gfx_color_argb gfx_color_argb::CLEAR = gfx_color_argb( 0xff_u8, 0xff_u8, 0xff_u8, 0xff_u8 );

//----------------------------------------------------------------

gfx_color_argb::gfx_color_argb( float alpha, float red, float green, float blue ):
	_alpha( std::floor( alpha * 255.0f ) ),
	_red( std::floor( red * 255.0f ) ),
	_green( std::floor( green * 255.0f ) ),
	_blue( std::floor( blue * 255.0f ) ) {
}

//----------------------------------------------------------------

uint8_t gfx_color_argb::get_bri() const {
	return std::max( std::max( _red, _green ), _blue );
}

//----------------------------------------------------------------

gfx_color_argb& gfx_color_argb::operator=( const gfx_color_argb& that ) {
	_alpha = that._alpha;
	_red = that._red;
	_green = that._green;
	_blue = that._blue;

	return *this;
}

//----------------------------------------------------------------

gfx_color_bit gfx_color_argb::to_black_and_white() const {
	return std::max( std::max( _red, _green ), _blue ) >= 128;
}

//----------------------------------------------------------------

uint8_t gfx_color_argb::to_2222() const {
	return (((_alpha >> 6) & 0b0011) << 6) | (((_red >> 6) & 0b0011) << 4) | (((_green >> 6) & 0b0011) << 2) | (((_blue >> 6) & 0b0011) << 0);
}

//----------------------------------------------------------------

uint16_t gfx_color_argb::to_4444() const {
	return ((uint16_t)((_alpha >> 4) & 0x0f) << 12) | ((uint16_t)((_red >> 4) & 0x0f) << 8) | ((uint16_t)((_green >> 4) & 0x0f) << 4) | ((uint16_t)((_blue >> 4) & 0x0f) << 0);
}

//----------------------------------------------------------------
