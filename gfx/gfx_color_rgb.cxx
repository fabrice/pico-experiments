//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_color_rgb
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------
// includes

#include "gfx_color_rgb.h"
#include "gfx_color_hsb.h"

#include "pico/printf.h"

#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>

//----------------------------------------------------------------

template< typename color_t >
const gfx_color_rgb< color_t > gfx_color_rgb< color_t >::BLACK { gfx::component_cast< bool, color_t >( false ), gfx::component_cast< bool, color_t >( false ), gfx::component_cast< bool, color_t >( false ) };

template< typename color_t >
const gfx_color_rgb< color_t > gfx_color_rgb< color_t >::WHITE { gfx::component_cast< bool, color_t >( true ), gfx::component_cast< bool, color_t >( true ), gfx::component_cast< bool, color_t >( true ) };

template< typename color_t >
const gfx_color_rgb< color_t > gfx_color_rgb< color_t >::RED { gfx::component_cast< bool, color_t >( true ), gfx::component_cast< bool, color_t >( false ), gfx::component_cast< bool, color_t >( false ) };

template< typename color_t >
const gfx_color_rgb< color_t > gfx_color_rgb< color_t >::YELLOW { gfx::component_cast< bool, color_t >( true ), gfx::component_cast< bool, color_t >( true ), gfx::component_cast< bool, color_t >( false ) };

template< typename color_t >
const gfx_color_rgb< color_t > gfx_color_rgb< color_t >::GREEN { gfx::component_cast< bool, color_t >( false ), gfx::component_cast< bool, color_t >( true ), gfx::component_cast< bool, color_t >( false ) };

template< typename color_t >
const gfx_color_rgb< color_t > gfx_color_rgb< color_t >::CYAN { gfx::component_cast< bool, color_t >( false ), gfx::component_cast< bool, color_t >( true ), gfx::component_cast< bool, color_t >( true ) };

template< typename color_t >
const gfx_color_rgb< color_t > gfx_color_rgb< color_t >::BLUE { gfx::component_cast< bool, color_t >( false ), gfx::component_cast< bool, color_t >( false ), gfx::component_cast< bool, color_t >( true ) };

template< typename color_t >
const gfx_color_rgb< color_t > gfx_color_rgb< color_t >::MAGENTA { gfx::component_cast< bool, color_t >( true ), gfx::component_cast< bool, color_t >( false ), gfx::component_cast< bool, color_t >( true ) };

//----------------------------------------------------------------

template< typename color_t >
gfx_color_rgb< color_t >::gfx_color_rgb( float red, float green, float blue )
		requires (!std::is_floating_point_v< color_t >):
		_red { gfx::component_cast< float, color_t >( red ) },
		_green { gfx::component_cast< float, color_t >( green ) },
		_blue { gfx::component_cast< float, color_t >( blue ) } {
}

//----------------------------------------------------------------

template< typename color_t >
color_t gfx_color_rgb< color_t >::get_bri() const {
	return std::max( std::max( _red, _green ), _blue );
}

//----------------------------------------------------------------

template< typename color_t >
gfx_color_rgb< color_t >& gfx_color_rgb< color_t >::operator=( const gfx_color_rgb< color_t >& that ) {
	_red = that._red;
	_green = that._green;
	_blue = that._blue;

	return (*this);
}

//----------------------------------------------------------------

template< typename color_t >
gfx_color_bit gfx_color_rgb< color_t >::to_black_and_white() const {
	return gfx::component_cast< color_t, bool >( this->get_bri() );
}

//----------------------------------------------------------------

template< typename color_t >
uint8_t gfx_color_rgb< color_t >::to_111() const {
	return
		(static_cast< uint8_t >(gfx::component_cast< color_t, bool >( _red )) << 2) |
		(static_cast< uint8_t >(gfx::component_cast< color_t, bool >( _green )) << 1) |
		(static_cast< uint8_t >(gfx::component_cast< color_t, bool >( _blue )) << 0);
}

//----------------------------------------------------------------

template< typename color_t >
uint8_t gfx_color_rgb< color_t >::to_222() const {
	return
		(((gfx::component_cast< color_t, uint8_t >( _red ) >> 6) & 0b0011) << 4) |
		(((gfx::component_cast< color_t, uint8_t >( _green ) >> 6) & 0b0011) << 2) |
		(((gfx::component_cast< color_t, uint8_t >( _blue ) >> 6) & 0b0011) << 0);
}

//----------------------------------------------------------------

template< typename color_t >
uint8_t gfx_color_rgb< color_t >::to_332() const {
	return
		(((gfx::component_cast< color_t, uint8_t >( _red ) >> 5) & 0b0111) << 5) |
		(((gfx::component_cast< color_t, uint8_t >( _green ) >> 5) & 0b0111) << 2) |
		(((gfx::component_cast< color_t, uint8_t >( _blue ) >> 6) & 0b0011) << 0);
}

//----------------------------------------------------------------

template< typename color_t >
uint16_t gfx_color_rgb< color_t >::to_555() const {
	return
		(static_cast<uint16_t>((gfx::component_cast< color_t, uint8_t >( _red ) >> 3) & 0b11111) << 10) |
		(static_cast<uint16_t>((gfx::component_cast< color_t, uint8_t >( _green ) >> 3) & 0b11111) << 5) |
		(static_cast<uint16_t>((gfx::component_cast< color_t, uint8_t >( _blue ) >> 3) & 0b11111) << 0);
}

//----------------------------------------------------------------

template< typename color_t >
uint16_t gfx_color_rgb< color_t >::to_565() const {
	return
		(static_cast<uint16_t>((gfx::component_cast< color_t, uint8_t >( _red ) >> 3) & 0b11111) << 11) |
		(static_cast<uint16_t>((gfx::component_cast< color_t, uint8_t >( _green ) >> 2) & 0b111111) << 5) |
		(static_cast<uint16_t>((gfx::component_cast< color_t, uint8_t >( _blue ) >> 3) & 0b11111) << 0);
}

//----------------------------------------------------------------

template< typename color_t >
std::string_view gfx_color_rgb< color_t >::to_web() const {
	char webcolor[10] {};
	snprintf( webcolor, sizeof(webcolor), "#%2x%2x%2x", (int)gfx::component_cast< color_t, uint8_t >( _red ), (int)gfx::component_cast< color_t, uint8_t >( _green ), (int)gfx::component_cast< color_t, uint8_t >( _blue ) );
	webcolor[ 9 ] = 0;

	return std::string_view( webcolor );
}

//----------------------------------------------------------------

template< typename color_t >
gfx_color_hsb gfx_color_rgb< color_t >::to_hsb() const {
	float cmax = std::max( std::max( gfx::component_cast< color_t, float >( _red ), gfx::component_cast< color_t, float >( _green ) ), gfx::component_cast< color_t, float >( _blue ) );
	float cmin = std::min( std::min( gfx::component_cast< color_t, float >( _red ), gfx::component_cast< color_t, float >( _green ) ), gfx::component_cast< color_t, float >( _blue ) );
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
