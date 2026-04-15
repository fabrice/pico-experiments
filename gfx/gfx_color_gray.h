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
#include "gfx_color_rgb.h"

#include "literals_plus.h"
#include "math_plus.h"

//----------------------------------------------------------------

class gfx_color_gray {

public:

	static const gfx_color_gray BLACK;
	static const gfx_color_gray WHITE;

private:

	uint8_t _gray { 0 };

public:

	gfx_color_gray() = default;
	gfx_color_gray( const gfx_color_gray& that ): _gray { that._gray } {}
	gfx_color_gray( bool lit ): _gray( lit ? 255 : 0 ) {}
	gfx_color_gray( uint8_t gray ): _gray { gray } {}

	gfx_color_gray( uint8_t gray, uint8_t max );
	gfx_color_gray( float gray );

	~gfx_color_gray() = default;

	inline uint8_t get_gray() const { return _gray; }

	uint8_t get_bri() const;

	inline bool is_black() const { return _gray == 0; }
	inline bool is_white() const { return _gray > 0; }
	inline bool is_gray() const { return _gray > 0; }
	inline bool is_lit() const { return _gray > 0; }

	gfx_color_gray& operator=( const gfx_color_gray& that );

	gfx_color_bit to_black_and_white() const;

	[[nodiscard]]
	gfx_color_rgb to_rgb() const;

};

//----------------------------------------------------------------
