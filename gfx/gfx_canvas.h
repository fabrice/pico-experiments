//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_canvas
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico/stdlib.h"

#include "gfx_types.h"
#include "gfx_geometry.h"
#include "gfx_colors.h"
#include "gfx_image.h"
#include "gfx_font.h"

#include "math_plus.h"

//----------------------------------------------------------------

class gfx_canvas {

private:

	gfx_dimension _dimension { 0, 0 };

	gfx_point _pencil { 0, 0 };
	gfx_point _cursor { 0, 0 };

	gfx_color_rgb_8 _foreground_color { gfx_color_rgb_8::BLACK };
	gfx_color_rgb_8 _background_color { gfx_color_rgb_8::WHITE };

	gfx_font* _font { nullptr };

	gfx_image* _image { nullptr };

public:

	gfx_canvas() = delete;
	gfx_canvas( gfx_wh_t width, gfx_wh_t height );
	gfx_canvas( gfx_wh_t width, gfx_wh_t height, uint8_t bits );
	gfx_canvas( const gfx_dimension& dimension );
	~gfx_canvas() noexcept;

	gfx_wh_t get_width() const { return _dimension.get_width(); }
	gfx_wh_t get_height() const { return _dimension.get_height(); }

	gfx_dimension get_dimension() const { return _dimension; }
	gfx_rectangle get_box() const { return gfx_rectangle( _dimension ); }

	void set_window( gfx_xy_t x, gfx_xy_t y, gfx_wh_t width, gfx_wh_t height );

	gfx_point get_pencil() const { return _pencil; }
	void set_pencil( const gfx_point& xy );
	void set_pencil( gfx_xy_t x, gfx_xy_t y );
	void move_pencil_by( gfx_dxy_t dx, gfx_dxy_t dy );

	gfx_wh_t get_column_count() const;
	gfx_wh_t get_line_count() const;

	gfx_point get_cursor() const { return _cursor; }
	void set_cursor( const gfx_point& xy );
	void set_cursor( gfx_xy_t line, gfx_xy_t column );
	void move_cursor_by( gfx_dxy_t dline, gfx_dxy_t dcolumn );

	gfx_color_rgb_8 get_foreground_color() { return _foreground_color; }
	void set_foreground_color( gfx_color_rgb_8 color ) { _foreground_color = color; }

	gfx_color_rgb_8 get_background_color() { return _background_color; }
	void set_background_color( gfx_color_rgb_8 color ) { _background_color = color; }

	void set_font( gfx_font* font );

	void print( std::string_view text );
	void print_center( std::string_view text );
	void print_glyph( const gfx_glyph& glyph );

	void draw_point();
	void draw_point( gfx_xy_t x, gfx_xy_t y );
	void draw_point( gfx_point point );

	void draw_line( gfx_xy_t x1, gfx_xy_t y1, gfx_xy_t x2, gfx_xy_t y2 );
	void draw_hline( gfx_xy_t x1, gfx_xy_t x2, gfx_xy_t y );
	void draw_vline( gfx_xy_t x, gfx_xy_t y1, gfx_xy_t y2 );

	void draw_line_to( gfx_xy_t x, gfx_xy_t y );
	void draw_line_to_polar( float distance, float angle );

	void draw_rectangle( gfx_xy_t x1, gfx_xy_t y1, gfx_xy_t x2, gfx_xy_t y2 );
	void draw_rectangle( gfx_point p1, gfx_point p2 );
	void draw_rectangle( gfx_rectangle rectangle );

	void fill_rectangle( gfx_xy_t x1, gfx_xy_t y1, gfx_xy_t x2, gfx_xy_t y2 );

	void draw_circle( gfx_xy_t r ) const;
	void draw_circle( gfx_xy_t x, gfx_xy_t y, gfx_xy_t r ) const;
	void draw_circle( const gfx_point& center, gfx_xy_t r ) const;
	void draw_circle( gfx_xy_t x, gfx_xy_t y, gfx_xy_t r, uint8_t quadrants ) const;

	void fill_circle( gfx_xy_t x, gfx_xy_t y, gfx_xy_t r );
	void fill_circle( gfx_xy_t x, gfx_xy_t y, gfx_xy_t r, uint8_t quadrants );

	void draw_round_rectangle( gfx_rectangle rectangle, gfx_xy_t radius );
	void fill_round_rectangle( gfx_rectangle rectangle, gfx_xy_t radius );

	void erase();

	gfx_bytemap_data make_yx_bytemap() const;
	std::vector< uint16_t > make_pixmap_565() const;

};

//----------------------------------------------------------------
