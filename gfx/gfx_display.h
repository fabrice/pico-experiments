//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico.h"
#include "pico/stdlib.h"

#include "gfx_types.h"
#include "gfx_point.h"

#include <cstring>
#include <cstdint>

//----------------------------------------------------------------
// color modes

constexpr uint8_t GFX_COLOR_MODE_222 { 6 };
constexpr uint8_t GFX_COLOR_MODE_232 { 7 };
constexpr uint8_t GFX_COLOR_MODE_555 { 15 };
constexpr uint8_t GFX_COLOR_MODE_565 { 16 };
constexpr uint8_t GFX_COLOR_MODE_888 { 24 };

//----------------------------------------------------------------

class gfx_display {

private:

	uint16_t _width { 0 };
	uint16_t _height { 0 };

	gfx_point _pencil { 0, 0 };
	gfx_point _cursor { 0, 0 };

private:

	gfx_display() = delete;

public:

	gfx_display( uint16_t width, uint16_t height, uint8_t pixel_size ): _width { width }, _height { height } {}
	virtual ~gfx_display() noexcept = default;

	uint16_t get_width() const { return _width; }
	uint16_t get_height() const { return _height; }

	gfx_point get_pencil() const { return _pencil; }
	void set_pencil( gfx_point& spot ) { _pencil = spot; }
	void set_pencil( gfx_xy_t x, gfx_xy_t y ) { _pencil = gfx_point( x, y ); }

	virtual void set_on( bool on ) = 0;
	virtual void set_brightness( uint8_t brightness ) = 0;

	virtual void print_glyph( const uint8_t* const glyph ) = 0;
	virtual void print_bitmap( gfx_xy_t x, gfx_xy_t y, uint16_t width, uint16_t height, const uint8_t* const bitmap, size_t size ) = 0;

	virtual void erase() = 0;
	virtual void erase( gfx_xy_t x, gfx_xy_t y, uint16_t width, uint16_t height ) = 0;

};

//----------------------------------------------------------------
