//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_color_gray
//
//----------------------------------------------------------------
// includes

#include "gfx_color_gray.h"

#include "gfx_color_rgb.h"

#include <cmath>
#include <bit>
#include <algorithm>

//----------------------------------------------------------------

const gfx_color_gray gfx_color_gray::BLACK = gfx_color_gray( 0x00_u8 );
const gfx_color_gray gfx_color_gray::WHITE = gfx_color_gray( 0xff_u8 );

//----------------------------------------------------------------

gfx_color_gray::gfx_color_gray( uint8_t gray, uint8_t max ):
	_gray( gray ) {
	if ( max < 1 ) max = 1;
	if ( max < 255 ) {
		float ratio = 255.0 / (float)max;
		_gray = (uint8_t)((float)gray * ratio);
	}
}

//----------------------------------------------------------------

gfx_color_gray::gfx_color_gray( float gray ):
	_gray( std::floor( gray * 255.0f ) ) {
}

//----------------------------------------------------------------

uint8_t gfx_color_gray::get_bri() const {
	return _gray;
}

//----------------------------------------------------------------

gfx_color_gray& gfx_color_gray::operator=( const gfx_color_gray& that ) {
	_gray = that._gray;

	return *this;
}

//----------------------------------------------------------------

gfx_color_bit gfx_color_gray::to_black_and_white() const {
	return _gray >= 128;
}

//----------------------------------------------------------------

gfx_color_rgb gfx_color_gray::to_rgb() const {
	return gfx_color_rgb( _gray, _gray, _gray );
}

//----------------------------------------------------------------
