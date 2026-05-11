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

#include "pico/stdlib.h"

#include "gfx_types.h"
#include "gfx_colors.h"

#include "literals_plus.h"
#include "math_plus.h"

//----------------------------------------------------------------

class gfx_color_hsb;

template< typename color_t > class gfx_color_argb;

using gfx_color_argb_8 = gfx_color_argb< uint8_t >;
using gfx_color_argb_16 = gfx_color_argb< uint16_t >;
using gfx_color_argb_f = gfx_color_argb< float >;

//----------------------------------------------------------------

template< typename color_t = uint8_t >
class gfx_color_argb {

public:

	using alpha_t = color_t;
	using red_t = color_t;
	using green_t = color_t;
	using blue_t = color_t;

	static const gfx_color_argb BLACK;
	static const gfx_color_argb WHITE;
	static const gfx_color_argb CLEAR;

private:

	color_t _alpha { 0 };
	color_t _red { 0 };
	color_t _green { 0 };
	color_t _blue { 0 };

public:

	gfx_color_argb() = default;
	gfx_color_argb( const gfx_color_argb& that ) = default;
	explicit gfx_color_argb( const gfx_color_rgb< color_t >& that ): _red { gfx::component_cast< uint8_t, color_t >( that.get_red() ) }, _green { gfx::component_cast< uint8_t, color_t >( that.get_green() ) }, _blue { gfx::component_cast< uint8_t, color_t >( that.get_blue() ) } {}
	explicit gfx_color_argb( const gfx_color_gray< color_t >& that ): _red { that.get_gray() }, _green { that.get_gray() }, _blue { that.get_gray() } {}
	explicit gfx_color_argb( bool lit ): _red( gfx::component_cast< bool, color_t >( lit ) ), _green( gfx::component_cast< bool, color_t >( lit ) ), _blue( gfx::component_cast< bool, color_t >( lit ) ) {}
	gfx_color_argb( color_t alpha, color_t red, color_t green, color_t blue ): _alpha { alpha }, _red { red }, _green { green }, _blue { blue } {}

	gfx_color_argb( float alpha, float red, float green, float blue ) requires (!std::is_floating_point_v< color_t >);

	~gfx_color_argb() noexcept = default;

	color_t get_alpha() const { return _alpha; }
	color_t get_red() const { return _red; }
	color_t get_green() const { return _green; }
	color_t get_blue() const { return _blue; }

	color_t get_bri() const;

	bool is_black() const { return (_red == 0) && (_green == _red) && (_blue == _red); };
	bool is_white() const { return (gfx::component_cast< color_t, uint8_t >( _red ) == std::numeric_limits< uint8_t >::max()) && (_green == _red) && (_blue == _red); };
	bool is_gray() const { return (_red > 0) && (gfx::component_cast< color_t, uint8_t >( _red ) < std::numeric_limits< uint8_t >::max()) && (_green == _red) && (_blue == _red); };
	bool is_lit() const { return (_red > 0) || (_green > 0) || (_blue > 0); };

	gfx_color_argb& operator=( const gfx_color_argb& that );

	gfx_color_bit to_black_and_white() const;
	uint8_t to_2222() const;
	uint16_t to_4444() const;
	uint32_t to_8888() const { return pack( gfx::component_cast< color_t, uint8_t >( _alpha ), gfx::component_cast< color_t, uint8_t >( _red ), gfx::component_cast< color_t, uint8_t >( _green ), gfx::component_cast< color_t, uint8_t >( _blue ) ); };

	[[nodiscard]]
	gfx_color_rgb< uint8_t > to_rgb() const { return gfx_color_rgb( gfx::component_cast< color_t, uint8_t >( _red ), gfx::component_cast< color_t, uint8_t >( _green ), gfx::component_cast< color_t, uint8_t >( _blue ) ); }

};

//----------------------------------------------------------------

static_assert( std::semiregular< gfx_color_argb< uint8_t > > );
static_assert( std::semiregular< gfx_color_argb< float > > );

//----------------------------------------------------------------
