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

#include "gfx_color_gray.h"
#include "gfx_color_hsb.h"

#include "literals_plus.h"
#include "math_plus.h"

#include <cmath>
#include <string>

//----------------------------------------------------------------

class gfx_color_hsb;

template< typename color_t > class gfx_color_rgb;

using gfx_color_rgb_8 = gfx_color_rgb< uint8_t >;
using gfx_color_rgb_16 = gfx_color_rgb< uint16_t >;
using gfx_color_rgb_f = gfx_color_rgb< float >;

//----------------------------------------------------------------

template< typename color_t = uint8_t >
class gfx_color_rgb {

public:

	using red_t = color_t;
	using green_t = color_t;
	using blue_t = color_t;

	static const gfx_color_rgb BLACK;
	static const gfx_color_rgb WHITE;

	static const gfx_color_rgb RED;
	static const gfx_color_rgb YELLOW;
	static const gfx_color_rgb GREEN;
	static const gfx_color_rgb CYAN;
	static const gfx_color_rgb BLUE;
	static const gfx_color_rgb MAGENTA;

private:

	color_t _red { 0 };
	color_t _green { 0 };
	color_t _blue { 0 };

public:

	gfx_color_rgb() = default;
	gfx_color_rgb( const gfx_color_rgb& that ): _red { that._red }, _green { that._green }, _blue { that._blue } {}
	gfx_color_rgb( const gfx_color_gray< color_t >& that ): _red { that.get_gray() }, _green { that.get_gray() }, _blue { that.get_gray() } {}
	explicit gfx_color_rgb( bool lit ): _red { gfx::component_cast< bool, color_t >( lit ) }, _green { gfx::component_cast< bool, color_t >( lit ) }, _blue { gfx::component_cast< bool, color_t >( lit ) } {}
	gfx_color_rgb( color_t red, color_t green, color_t blue ): _red { red }, _green { green }, _blue { blue } {}

	gfx_color_rgb( float red, float green, float blue ) requires (!std::is_floating_point_v< color_t >);

	~gfx_color_rgb() = default;

	inline color_t get_red() const { return _red; }
	inline color_t get_green() const { return _green; }
	inline color_t get_blue() const { return _blue; }

	color_t get_bri() const;

	inline bool is_black() const { return (_red == 0) && (_green == _red) && (_blue == _red); };
	inline bool is_white() const { return (gfx::component_cast< color_t, uint8_t >( _red ) == std::numeric_limits< uint8_t >::max()) && (_green == _red) && (_blue == _red); };
	inline bool is_gray() const { return (_red > 0) && (gfx::component_cast< color_t, uint8_t >( _red ) < std::numeric_limits< uint8_t >::max()) && (_green == _red) && (_blue == _red); };
	inline bool is_lit() const { return (_red > 0) || (_green > 0) || (_blue > 0); };

	gfx_color_rgb& operator=( const gfx_color_rgb& that );

	gfx_color_bit to_black_and_white() const;
	uint8_t to_111() const;
	uint8_t to_222() const;
	uint8_t to_332() const;
	uint16_t to_555() const;
	uint16_t to_565() const;
	inline uint32_t to_888() const { return pack( gfx::component_cast< color_t, uint8_t >( _red ), gfx::component_cast< color_t, uint8_t >( _green ), gfx::component_cast< color_t, uint8_t >( _blue ) ); };
	std::string_view to_web() const;

	[[nodiscard]]
	gfx_color_hsb to_hsb() const;

};

//----------------------------------------------------------------
