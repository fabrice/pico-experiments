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

#include "pico.h"
#include "pico/stdlib.h"

#include <cmath>


//----------------------------------------------------------------

class gfx_color;
class gfx_color_hsb;

//----------------------------------------------------------------

class gfx_color_hsb {

private:
	float hue;
	float sat;
	float bri;

public:

	gfx_color_hsb(): hue( 0 ), sat( 0 ), bri( 0 ) {}
	gfx_color_hsb( const gfx_color_hsb& that );
	gfx_color_hsb( uint16_t hue, uint8_t sat, uint8_t bri );

	inline uint16_t get_hue() const { return fmodf( floor( hue ), 360.0 ); }
	inline uint8_t get_sat() const { return floor( sat * 255.0 ); }
	inline uint8_t get_bri() const { return floor( bri * 255.0 ); }

	uint8_t get_lit() const;
	uint8_t get_chroma() const;

	inline bool is_black() const { return this->bri == 0.0; };
	inline bool is_white() const { return (this->sat == 0.0) && (this->bri > 0.0); };

	[[nodiscard]]
	gfx_color to_rgb() const;

};

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
