//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_color_gray
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------
// includes

#include "gfx_color_gray.h"
#include "gfx_color_casts.h"

#include "gfx_color_rgb.h"

#include <cmath>
#include <algorithm>

//----------------------------------------------------------------

template< typename color_t >
const gfx_color_gray< color_t > gfx_color_gray< color_t >::BLACK { gfx::component_cast< bool, color_t >( false ) };

template< typename color_t >
const gfx_color_gray< color_t > gfx_color_gray< color_t >::WHITE { gfx::component_cast< bool, color_t >( true ) };

//----------------------------------------------------------------

template< typename color_t > template< typename color_2_t >
gfx_color_gray< color_t >::gfx_color_gray( const gfx_color_gray< color_2_t >& that ):
		_gray { gfx::component_cast< color_2_t, color_t >( that._gray ) } {
}

//----------------------------------------------------------------

template< typename color_t >
gfx_color_gray< color_t >::gfx_color_gray( float gray ) requires (!std::is_floating_point_v< color_t >):
		_gray { gfx::component_cast< float, color_t >( gray ) } {
}

//----------------------------------------------------------------

template< typename color_t >
color_t gfx_color_gray< color_t >::get_bri() const {
	return _gray;
}

//----------------------------------------------------------------

template< typename color_t >
gfx_color_gray< color_t >& gfx_color_gray< color_t >::operator=( const gfx_color_gray< color_t >& rhs ) {
	_gray = rhs._gray;

	return (*this);
}

//----------------------------------------------------------------

template< typename color_t >
gfx_color_bit gfx_color_gray< color_t >::to_black_and_white() const {
	return gfx::component_cast< color_t, bool >( _gray );
}

//----------------------------------------------------------------
