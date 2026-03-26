//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_color
//
//----------------------------------------------------------------

#pragma once
#ifndef _GFX_COLOR_H
#define _GFX_COLOR_H

//----------------------------------------------------------------

#include "pico.h"
#include "pico/stdlib.h"

#include <cmath>
#include "math_plus.h"


//----------------------------------------------------------------

class gfx_color;
class gfx_color_hsb;

//----------------------------------------------------------------

class gfx_color {

private:
	uint8_t red;
	uint8_t green;
	uint8_t blue;

public:

	gfx_color(): red( 0 ), green( 0 ), blue( 0 ) {}
	gfx_color( const gfx_color& that ): red( that.red ), green( that.green ), blue( that.blue ) {}
	gfx_color( uint8_t red, uint8_t green, uint8_t blue ): red( red ), green( green ), blue( blue ) {}
	gfx_color( uint8_t red, uint8_t green, uint8_t blue, uint8_t max );

	gfx_color( float red, float green, float blue );

	inline uint8_t get_red() const { return red; }
	inline uint8_t get_green() const { return green; }
	inline uint8_t get_blue() const { return blue; }

	inline bool is_black() const { return (this->red == 0) && (this->green == 0) && (this->blue == 0); };
	inline bool is_white() const { return (this->red == this->green) && (this->green == this->blue) && !this->is_black(); };

	uint8_t to_111() const;
	uint8_t to_222() const;
	uint8_t to_332() const;
	uint16_t to_444() const;
	uint16_t to_555() const;
	uint16_t to_565() const;
	inline uint32_t to_888() const { return pack( red, green, blue ); };

	[[nodiscard]]
	gfx_color_hsb to_hsb() const;

};

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
