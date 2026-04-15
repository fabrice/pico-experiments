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
#ifndef _GFX_COLOR_H
#define _GFX_COLOR_H

//----------------------------------------------------------------

#include "pico/stdlib.h"

#include "gfx_types.h"
#include "gfx_color_bit.h"
#include "literals_plus.h"
#include "math_plus.h"

#include <cmath>
#include <string>

//----------------------------------------------------------------

class gfx_color_rgb;
class gfx_color_hsb;

//----------------------------------------------------------------

class gfx_color_rgb {

public:

	static const gfx_color_rgb BLACK;
	static const gfx_color_rgb WHITE;

	static const gfx_color_rgb RED;
	static const gfx_color_rgb YELLOW;
	static const gfx_color_rgb GREEN;
	static const gfx_color_rgb CYAN;
	static const gfx_color_rgb BLUE;
	static const gfx_color_rgb MAGENTA;

private:

	uint8_t _red { 0 };
	uint8_t _green { 0 };
	uint8_t _blue { 0 };

public:

	gfx_color_rgb() = default;
	gfx_color_rgb( const gfx_color_rgb& that ): _red { that._red }, _green { that._green }, _blue { that._blue } {}
	gfx_color_rgb( bool lit ): _red { lit ? 255_u8 : 0_u8 }, _green { lit ? 255_u8 : 0_u8 }, _blue { lit ? 255_u8 : 0_u8 } {}
	gfx_color_rgb( uint8_t red, uint8_t green, uint8_t blue ): _red { red }, _green { green }, _blue { blue } {}

	gfx_color_rgb( uint8_t red, uint8_t green, uint8_t blue, uint8_t max );
	gfx_color_rgb( float red, float green, float blue );

	~gfx_color_rgb() = default;

	inline uint8_t get_red() const { return _red; }
	inline uint8_t get_green() const { return _green; }
	inline uint8_t get_blue() const { return _blue; }

	uint8_t get_bri() const;

	inline bool is_black() const { return (_red == 0) && (_green == 0) && (_blue == 0); };
	inline bool is_white() const { return (_red > 0) && (_red == _green) && (_green == _blue); };
	inline bool is_lit() const { return (_red > 0) || (_green > 0) || (_blue > 0); };

	gfx_color_rgb& operator=( const gfx_color_rgb& that );

	gfx_color_bit to_black_and_white() const;
	uint8_t to_111() const;
	uint8_t to_222() const;
	uint8_t to_332() const;
	uint16_t to_555() const;
	uint16_t to_565() const;
	inline uint32_t to_888() const { return pack( _red, _green, _blue ); };
	std::string to_web() const;

	[[nodiscard]]
	gfx_color_hsb to_hsb() const;

};

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
