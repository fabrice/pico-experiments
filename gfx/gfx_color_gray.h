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

#include "pico/stdlib.h"

#include "gfx_types.h"
#include "gfx_color_casts.h"
#include "gfx_color_bit.h"

#include "literals_plus.h"
#include "math_plus.h"

//----------------------------------------------------------------

template< typename color_t > class gfx_color_rgb;

template< typename color_t > class gfx_color_gray;

using gfx_color_gray_8 = gfx_color_gray< uint8_t >;
using gfx_color_gray_16 = gfx_color_gray< uint8_t >;
using gfx_color_gray_f = gfx_color_gray< float >;

//----------------------------------------------------------------

template< typename color_t = uint8_t >
class gfx_color_gray {

public:

	using component_t = color_t;

	static const gfx_color_gray BLACK;
	static const gfx_color_gray WHITE;

private:

	color_t _gray { 0 };

public:

	gfx_color_gray() = default;
	gfx_color_gray( const gfx_color_gray& that ): _gray { that._gray } {}

	template< typename color_2_t >
	gfx_color_gray( const gfx_color_gray< color_2_t >& that );

	explicit gfx_color_gray( bool lit ) requires (!std::is_same_v< color_t, bool >): _gray { gfx::component_cast< bool, color_t >( lit ) } {}
	explicit gfx_color_gray( color_t gray ): _gray { gray } {}

	explicit gfx_color_gray( float gray ) requires (!std::is_floating_point_v< color_t >);

	~gfx_color_gray() = default;

	inline color_t get_gray() const { return _gray; }

	color_t get_bri() const;

	inline bool is_black() const { return _gray == 0; }
	inline bool is_white() const { return _gray == std::numeric_limits< color_t >::max(); }
	inline bool is_gray() const { return (_gray > 0) && (_gray < std::numeric_limits< color_t >::max()); }
	inline bool is_lit() const { return _gray > 0; }

	gfx_color_gray& operator=( const gfx_color_gray& rhs );

	gfx_color_bit to_black_and_white() const;

};

//----------------------------------------------------------------

#include "gfx_color_gray.cxx"

//----------------------------------------------------------------
