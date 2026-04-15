//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_color_hsb
//
//----------------------------------------------------------------

#pragma once
#ifndef _GFX_COLOR_HSB_H
#define _GFX_COLOR_HSB_H

//----------------------------------------------------------------

#include "pico/stdlib.h"

#include "gfx_types.h"
#include "gfx_color_rgb.h"

#include "literals_plus.h"
#include "math_plus.h"

#include <cmath>

//----------------------------------------------------------------

class gfx_color_rgb;
class gfx_color_hsb;

//----------------------------------------------------------------

class gfx_color_hsb {

private:

	float _hue { 0.0f };
	float _sat { 0.0f };
	float _bri { 0.0f };

public:

	gfx_color_hsb() = default;
	gfx_color_hsb( const gfx_color_hsb& that );
	gfx_color_hsb( uint16_t hue, uint8_t sat, uint8_t bri );
	gfx_color_hsb( float hue, float sat, float bri ): _hue { hue }, _sat { sat }, _bri { bri } {}
	~gfx_color_hsb() = default;

	inline uint16_t get_hue() const { return (uint16_t)std::fmod( std::floor( _hue ), 360.0f ); }
	inline uint8_t get_sat() const { return (uint8_t)std::floor( _sat * 255.0f ); }
	inline uint8_t get_bri() const { return (uint8_t)std::floor( _bri * 255.0f ); }

	uint8_t get_lit() const;
	uint8_t get_chroma() const;

	inline bool is_black() const { return _bri == 0.0f; };
	inline bool is_white() const { return (_bri > 0.0f) && (_sat == 0.0f); };
	inline bool is_gray() const { return (_bri > 0.0f) && (_sat == 0.0f); }
	inline bool is_lit() const { return _bri > 0.0f; };

	inline uint32_t to_988() const { return pack( get_hue(), pack( get_sat(), get_bri() ) ); }

	[[nodiscard]]
	gfx_color_rgb to_rgb() const;

};

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
