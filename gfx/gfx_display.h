//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
//----------------------------------------------------------------

#pragma once
#ifndef _GFX_DISPLAY_H
//#define _GFX_DISPLAY_H

//----------------------------------------------------------------

#include "pico.h"
#include "pico/stdlib.h"

#include "gfx_types.h"
#include "gfx_point.h"

#include <cstring>
#include <cstdint>

//----------------------------------------------------------------
//

class gfx_display;
typedef gfx_display* gfx_display_ref;


//----------------------------------------------------------------
// color modes

constexpr uint8_t GFX_COLOR_MODE_222 = 6;
constexpr uint8_t GFX_COLOR_MODE_232 = 7;
constexpr uint8_t GFX_COLOR_MODE_555 = 15;
constexpr uint8_t GFX_COLOR_MODE_565 = 16;
constexpr uint8_t GFX_COLOR_MODE_888 = 24;


//----------------------------------------------------------------
// classe

class gfx_display {

private:
	uint16_t width;
	uint16_t height;

	gfx_point cursor;

private:
	gfx_display(): width( 0 ), height( 0 ), cursor() {}

public:
	gfx_display( uint16_t width, uint16_t height, uint8_t pixel_size ): width( width ), height( height ), cursor() {}
	virtual ~gfx_display() {}

	uint16_t get_width() const { return this->width; }
	uint16_t get_height() const { return this->height; }

	gfx_point get_cursor() const { return this->cursor; }
	void set_cursor( gfx_point& cursor ) { this->cursor = cursor; }
	void set_cursor( gfx_xy_t x, gfx_xy_t y ) { this->cursor = gfx_point( x, y ); }

	virtual void set_on( bool on ) = 0;
	virtual void set_brightness( uint8_t brightness ) = 0;

	virtual void print_glyph( const uint8_t* const glyph ) = 0;
	virtual void print_bitmap( gfx_xy_t x, gfx_xy_t y, uint16_t width, uint16_t height, const uint8_t* const bitmap, size_t size ) = 0;

	virtual void erase() = 0;
	virtual void erase( gfx_xy_t x, gfx_xy_t y, uint16_t width, uint16_t height ) = 0;

};

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
