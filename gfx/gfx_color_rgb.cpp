//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_color_rgb
//
//----------------------------------------------------------------
// includes

#include "gfx_color_rgb.h"
#include "gfx_color_hsb.h"

#include "pico/printf.h"

#include <cstring>
#include <cmath>
#include <bit>
#include <algorithm>
#include <string>

//----------------------------------------------------------------

const gfx_color_rgb gfx_color_rgb::BLACK = gfx_color_rgb( 0x00_u8, 0x00_u8, 0x00_u8 );
const gfx_color_rgb gfx_color_rgb::WHITE = gfx_color_rgb( 0xff_u8, 0xff_u8, 0xff_u8 );

const gfx_color_rgb gfx_color_rgb::RED = gfx_color_rgb( 0xff_u8, 0x00_u8, 0x00_u8 );
const gfx_color_rgb gfx_color_rgb::YELLOW = gfx_color_rgb( 0xff_u8, 0xff_u8, 0x00_u8 );
const gfx_color_rgb gfx_color_rgb::GREEN = gfx_color_rgb( 0x00_u8, 0xff_u8, 0x00_u8 );
const gfx_color_rgb gfx_color_rgb::CYAN = gfx_color_rgb( 0x00_u8, 0xff_u8, 0xff_u8 );
const gfx_color_rgb gfx_color_rgb::BLUE = gfx_color_rgb( 0x00_u8, 0x00_u8, 0xff_u8 );
const gfx_color_rgb gfx_color_rgb::MAGENTA = gfx_color_rgb( 0xff_u8, 0x00_u8, 0xff_u8 );

//----------------------------------------------------------------

gfx_color_rgb::gfx_color_rgb( uint8_t red, uint8_t green, uint8_t blue, uint8_t max ):
	_red( red ),
	_green( green ),
	_blue( blue ) {
	if ( max < 1 ) max = 1;
	if ( max < 255 ) {
		float ratio = 255.0 / (float)max;
		_red = (uint8_t)((float)red * ratio);
		_green = (uint8_t)((float)green * ratio);
		_blue = (uint8_t)((float)blue * ratio);
	}
}

//----------------------------------------------------------------

gfx_color_rgb::gfx_color_rgb( float red, float green, float blue ):
	_red( std::floor( red * 255.0f ) ),
	_green( std::floor( green * 255.0f ) ),
	_blue( std::floor( blue * 255.0f ) ) {
}

//----------------------------------------------------------------

uint8_t gfx_color_rgb::get_bri() const {
	return std::max( std::max( _red, _green ), _blue );
}

//----------------------------------------------------------------

gfx_color_rgb& gfx_color_rgb::operator=( const gfx_color_rgb& that ) {
	_red = that._red;
	_green = that._green;
	_blue = that._blue;

	return *this;
}

//----------------------------------------------------------------

gfx_color_bit gfx_color_rgb::to_black_and_white() const {
	return std::max( std::max( _red, _green ), _blue ) >= 128;
}

//----------------------------------------------------------------

uint8_t gfx_color_rgb::to_111() const {
	return (((_red >> 7) & 0x01) << 2) | (((_green >> 7) & 0x01) << 1) | (((_blue >> 7) & 0x01) << 0);
}

//----------------------------------------------------------------

uint8_t gfx_color_rgb::to_222() const {
	return (((_red >> 6) & 0b0011) << 4) | (((_green >> 6) & 0b0011) << 2) | (((_blue >> 6) & 0b0011) << 0);
}

//----------------------------------------------------------------

uint8_t gfx_color_rgb::to_332() const {
	return (((_red >> 5) & 0b0111) << 5) | (((_green >> 5) & 0b0111) << 2) | (((_blue >> 6) & 0b0011) << 0);
}

//----------------------------------------------------------------

uint16_t gfx_color_rgb::to_555() const {
	return ((uint16_t)((_red >> 3) & 0x1f) << 10) | ((uint16_t)((_green >> 3) & 0x1f) << 5) | ((uint16_t)((_blue >> 3) & 0x1f) << 0);
}

//----------------------------------------------------------------

uint16_t gfx_color_rgb::to_565() const {
	return ((uint16_t)((_red >> 3) & 0x1f) << 11) | ((uint16_t)((_green >> 2) & 0x3f) << 5) | ((uint16_t)((_blue >> 3) & 0x1f) << 0);
}

//----------------------------------------------------------------

std::string gfx_color_rgb::to_web() const {
	char webcolor[10];
	memset( webcolor, 0, sizeof(webcolor) );
	snprintf( webcolor, sizeof(webcolor), "#%2x%2x%2x", (int)_red, (int)_green, (int)_blue );

	return std::string( webcolor );
}

//----------------------------------------------------------------

gfx_color_hsb gfx_color_rgb::to_hsb() const {
	gfx_color_hsb hsb;

	float cmax = std::max( std::max( _red, _green ), _blue );
	float cmin = std::min( std::min( _red, _green ), _blue );
	float delta = cmax - cmin;

	float hue = 0.0f;
	if ( delta != 0.0f ) {
		if ( cmax == _red ) {
			hue = (_green - _blue) / delta;
		}
		else if ( cmax == _green ) {
			hue = (_blue - _red) / delta + 2.0f;
		}
		else if ( cmax == _blue ) {
			hue = (_red - _green) / delta + 4.0f;
		}
		hue = std::fmod( (hue * 60.0f + 360.0f), 360.0f );
	}

	float sat = 0.0f;
	if ( cmax != 0.0f ) {
		sat = delta / cmax;
	}

	float bri = cmax;

	return gfx_color_hsb( hue, sat, bri );
}

//----------------------------------------------------------------
