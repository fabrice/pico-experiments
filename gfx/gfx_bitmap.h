//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_bitmap
//
//----------------------------------------------------------------

#pragma once
#ifndef _GFX_BITMAP_H
#define _GFX_BITMAP_H

//----------------------------------------------------------------

#include "pico.h"
#include "pico/stdlib.h"

#include "math_plus.h"


//----------------------------------------------------------------

class gfx_bitmap {

private:
	uint16_t width;
	uint16_t height;
	uint8_t pixel_size;

	uint16_t cursor_x;
	uint16_t cursor_y;

public:

	gfx_bitmap(): width( 0 ), height( 0 ), pixel_size( 1 ) {}

	inline uint16_t get_width() const { return width; }
	inline uint16_t get_height() const { return height; }

	void move_cusor_to( uint16_t x, uint16_t y );
	void move_cusor_by( int16_t dx, int16_t dy );

	void draw_line( uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2 );

};

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
