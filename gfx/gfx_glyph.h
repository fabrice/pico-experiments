//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_glyph
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "gfx_types.h"
#include "gfx_geometry.h"
#include "gfx_color_bit.h"

#include "fonts/gfx_font_data.h"

#include "third/adafruit_font_data.h"

#include <vector>

//----------------------------------------------------------------

class gfx_glyph;
using gfx_glyph_ref = gfx_glyph*;

//----------------------------------------------------------------

class gfx_glyph {

private:

	char _character { 0 };
	gfx_rectangle _box { 0, 0, 0, 0 };
	gfx_dxy_t _x_advance { 0 };
	gfx_bytemap_data _bytemap { size_t(0) };

public:

	gfx_glyph() = default;
	
	gfx_glyph( char character, gfx_xy_t left, gfx_xy_t top, gfx_wh_t width, gfx_wh_t height, gfx_dxy_t x_advance );
	gfx_glyph( const gfx_glyph_data& glyph_data );

public:

	gfx_glyph( const gfx_glyph& that );

public:

	void minimize();

private:

	bool is_empty() const;
	bool is_line_empty( gfx_xy_t y ) const;
	void remove_line( gfx_xy_t y );
	bool is_column_empty( gfx_xy_t x ) const;
	void remove_column( gfx_xy_t x );

public:

	~gfx_glyph();

	inline char get_character() const { return _character; }
	inline void set_character( char character ) { _character = character; }

	inline gfx_rectangle get_box() const { return _box; }
	inline void set_box( gfx_rectangle box ) { _box = box; _bytemap.resize( (_box.get_area() + 7) / 8, false ); }

	inline gfx_xy_t get_left() const { return _box.get_left(); }
	inline gfx_xy_t get_top() const { return _box.get_top(); }
	inline gfx_xy_t get_right() const { return _box.get_right(); }
	inline gfx_xy_t get_bottom() const { return _box.get_bottom(); }

	inline gfx_wh_t get_width() const { return _box.get_width(); }
	inline gfx_wh_t get_height() const { return _box.get_height(); }

	inline gfx_point get_top_left() const { return _box.get_top_left(); }
	inline gfx_dimension get_dimension() const { return _box.get_dimension(); }

	inline gfx_dxy_t get_x_advance() const { return _x_advance; }

	gfx_glyph& operator=( const gfx_glyph& that );

	std::strong_ordering operator<=>( const gfx_glyph& that ) const;

	void set_bytemap( const gfx_bytemap_data& bytemap );
	void set_bitmap_xy( const uint8_t* bitmap, size_t length );
	void set_bitmap_yx( const uint8_t* bitmap, size_t length, bool lsb_first = true, bool invert = false );

	gfx_color_bit get_pixel_lit( gfx_xy_t x, gfx_xy_t y ) const;
	void set_pixel_lit( gfx_xy_t x, gfx_xy_t y, gfx_color_bit lit );

};

//----------------------------------------------------------------
