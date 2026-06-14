//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_color_argb
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------
// includes

#include "gfx_color_argb.h"
#include "gfx_color_rgb.h"

#include <cmath>
#include <bit>
#include <algorithm>

//----------------------------------------------------------------

template< typename color_t >
const gfx_color_argb< color_t > gfx_color_argb< color_t >::BLACK { gfx::component_cast< bool, color_t >( false ), gfx::component_cast< bool, color_t >( false ), gfx::component_cast< bool, color_t >( false ), gfx::component_cast< bool, color_t >( false ) };

template< typename color_t >
const gfx_color_argb< color_t > gfx_color_argb< color_t >::WHITE { gfx::component_cast< bool, color_t >( false ), gfx::component_cast< bool, color_t >( true ), gfx::component_cast< bool, color_t >( true ), gfx::component_cast< bool, color_t >( true ) };

template< typename color_t >
const gfx_color_argb< color_t > gfx_color_argb< color_t >::CLEAR { gfx::component_cast< bool, color_t >( true ), gfx::component_cast< bool, color_t >( true ), gfx::component_cast< bool, color_t >( true ), gfx::component_cast< bool, color_t >( true ) };

//----------------------------------------------------------------

template< typename color_t >
gfx_color_argb< color_t >::gfx_color_argb( float alpha, float red, float green, float blue )
		requires (!std::is_floating_point_v< color_t >):
		_alpha( gfx::component_cast< float, color_t >( alpha ) ),
		_red( gfx::component_cast< float, color_t >( red ) ),
		_green( gfx::component_cast< float, color_t >( green ) ),
		_blue( gfx::component_cast< float, color_t >( blue ) ) {
}

//----------------------------------------------------------------

template< typename color_t >
color_t gfx_color_argb< color_t >::get_bri() const {
	return std::max( std::max( _red, _green ), _blue );
}

//----------------------------------------------------------------

template< typename color_t >
gfx_color_argb< color_t >& gfx_color_argb< color_t >::operator=( const gfx_color_argb< color_t >& that ) {
	_alpha = that._alpha;
	_red = that._red;
	_green = that._green;
	_blue = that._blue;

	return (*this);
}

//----------------------------------------------------------------

template< typename color_t >
gfx_color_bit gfx_color_argb< color_t >::to_black_and_white() const {
	return gfx::component_cast< color_t, bool >( this->get_bri() );
}

//----------------------------------------------------------------

template< typename color_t >
uint8_t gfx_color_argb< color_t >::to_2222() const {
	return
		(((gfx::component_cast< color_t, uint8_t >( _alpha ) >> 6) & 0b0011) << 6) |
		(((gfx::component_cast< color_t, uint8_t >( _red ) >> 6) & 0b0011) << 4) |
		(((gfx::component_cast< color_t, uint8_t >( _green ) >> 6) & 0b0011) << 2) |
		(((gfx::component_cast< color_t, uint8_t >( _blue ) >> 6) & 0b0011) << 0);
}

//----------------------------------------------------------------

template< typename color_t >
uint16_t gfx_color_argb< color_t >::to_4444() const {
	return
		(static_cast<uint16_t>((gfx::component_cast< color_t, uint8_t >( _alpha ) >> 4) & 0b1111) << 12) |
		(static_cast<uint16_t>((gfx::component_cast< color_t, uint8_t >( _red ) >> 4) & 0b1111) << 8) |
		(static_cast<uint16_t>((gfx::component_cast< color_t, uint8_t >( _green ) >> 4) & 0b1111) << 4) |
		(static_cast<uint16_t>((gfx::component_cast< color_t, uint8_t >( _blue ) >> 4) & 0b1111) << 0);
}

//----------------------------------------------------------------
