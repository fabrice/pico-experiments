//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_color_hsb
//
//----------------------------------------------------------------
// includes

#include "gfx_color_hsb.h"

#include "gfx_color_rgb.h"

#include <cmath>
#include "math_plus.h"


//----------------------------------------------------------------

const gfx_color_hsb gfx_color_hsb::BLACK { 0, 0x00_u8, 0x00_u8 };
const gfx_color_hsb gfx_color_hsb::WHITE { 0, 0x00_u8, 0xff_u8 };

const gfx_color_hsb gfx_color_hsb::RED { 0, 0xff_u8, 0xff_u8 };
const gfx_color_hsb gfx_color_hsb::YELLOW { 60, 0xff_u8, 0xff_u8 };
const gfx_color_hsb gfx_color_hsb::GREEN { 120, 0xff_u8, 0xff_u8 };
const gfx_color_hsb gfx_color_hsb::CYAN { 180, 0xff_u8, 0xff_u8 };
const gfx_color_hsb gfx_color_hsb::BLUE { 240, 0xff_u8, 0xff_u8 };
const gfx_color_hsb gfx_color_hsb::MAGENTA { 300, 0xff_u8, 0xff_u8 };

//----------------------------------------------------------------

gfx_color_hsb::gfx_color_hsb( uint16_t hue, uint8_t sat, uint8_t bri ):
	_hue { static_cast< float >( hue ) },
	_sat { static_cast< float >( sat ) / 255.0f },
	_bri { static_cast< float >( bri ) / 255.0f } {
}

//----------------------------------------------------------------

gfx_color_hsb::gfx_color_hsb( const gfx_color_hsb& that ):
    _hue { that._hue },
    _sat { that._sat },
    _bri { that._bri } {
    _hue = std::fmod( std::abs( _hue ), 360.0f );
    _sat = std::abs( _sat );
    _sat = constrain( _sat, 0.0f, 1.0f );
    _bri = std::abs( _bri );
    _bri = constrain( _bri, 0.0f, 1.0f );
}

//----------------------------------------------------------------

uint8_t gfx_color_hsb::get_lit() const {
	return std::floor( (1.0f - _sat / 2.0f) * _bri * 100.0f );
}

//----------------------------------------------------------------

uint8_t gfx_color_hsb::get_chroma() const {
	return std::floor( _sat * _bri * 100.0f );
}

//----------------------------------------------------------------

gfx_color_rgb gfx_color_hsb::to_rgb() const {
	float chroma = _sat * _bri;
	float h = _hue / 60.0f;
	float x = chroma * (1.0f - std::abs( std::fmod( h , 2.0f ) - 1.0f ));

	float red = 0.0f;
	float green = 0.0f;
	float blue = 0.0f;

	if ( (h >= 0.0f) && (h <= 1.0f) ) {
		red = chroma;
		green = x;
		blue = 0.0f;
	}
	else if ( (h > 1.0f) && (h <= 2.0f) ) {
		red = x;
		green = chroma;
		blue = 0.0f;
	}
	else if ( (h > 2.0f) && (h <= 3.0f) ) {
		red = 0.0f;
		green = chroma;
		blue = x;
	}
	else if ( (h > 3.0f) && (h <= 4.0f) ) {
		red = 0.0f;
		green = x;
		blue = chroma;
	}
	else if ( (h > 4.0f) && (h <= 5.0f) ) {
		red = x;
		green = 0.0f;
		blue = chroma;
	}
	else if ( (h > 5.0f) && (h <= 6.0f) ) {
		red = chroma;
		green = 0.0f;
		blue = x;
	}
	else {
		red = 0.0f;
		green = 0.0f;
		blue = 0.0f;
	}

	float m = _bri - chroma;
	red += m;
	green += m;
	blue += m;

	return gfx_color_rgb( red, green, blue );
}

//----------------------------------------------------------------
