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
#include "gfx_color_bit.h"
#include "gfx_color_rgb.h"

#include "literals_plus.h"
#include "math_plus.h"

//----------------------------------------------------------------

class gfx_color_rgb;
class gfx_color_hsb;

//----------------------------------------------------------------

class gfx_color_argb {

public:

	static const gfx_color_argb BLACK;
	static const gfx_color_argb WHITE;
	static const gfx_color_argb CLEAR;

private:

	uint8_t _alpha { 0 };
	uint8_t _red { 0 };
	uint8_t _green { 0 };
	uint8_t _blue { 0 };

public:

	gfx_color_argb() = default;
	gfx_color_argb( const gfx_color_argb& that ): _alpha { that._alpha }, _red { that._red }, _green { that._green }, _blue { that._blue } {}
	gfx_color_argb( const gfx_color_rgb& that ): _alpha { 0 }, _red { that.get_red() }, _green { that.get_green() }, _blue { that.get_blue() } {}
	gfx_color_argb( bool lit ): _alpha { 0 }, _red( lit ? 255 : 0 ), _green( lit ? 255 : 0 ), _blue( lit ? 255 : 0 ) {}
	gfx_color_argb( uint8_t alpha, uint8_t red, uint8_t green, uint8_t blue ): _alpha { alpha }, _red { red }, _green { green }, _blue { blue } {}

	gfx_color_argb( float alpha, float red, float green, float blue );

	~gfx_color_argb() = default;

	inline uint8_t get_alpha() const { return _alpha; }
	inline uint8_t get_red() const { return _red; }
	inline uint8_t get_green() const { return _green; }
	inline uint8_t get_blue() const { return _blue; }

	uint8_t get_bri() const;

	inline bool is_black() const { return (_red == 0) && (_green == 0) && (_blue == 0); };
	inline bool is_white() const { return (_red > 0) && (_red == _green) && (_green == _blue); };
	inline bool is_lit() const { return (_red > 0) || (_green > 0) || (_blue > 0); };

	gfx_color_argb& operator=( const gfx_color_argb& that );

	gfx_color_bit to_black_and_white() const;
	uint8_t to_2222() const;
	uint16_t to_4444() const;
	inline uint32_t to_8888() const { return pack( _alpha, _red, _green, _blue ); };

	[[nodiscard]]
	gfx_color_rgb to_rgb() const { return gfx_color_rgb( _red, _green, _blue ); }

};

//----------------------------------------------------------------
