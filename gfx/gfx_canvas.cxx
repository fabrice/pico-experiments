//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
//! @file gfx_canvas.cxx
//
//----------------------------------------------------------------

#include "pico/stdlib.h"

#include "gfx_types.h"
#include "gfx_geometry.h"
#include "gfx_canvas.h"
#include "gfx_image.h"
#include "gfx_bitmap.h"
#include "gfx_pixmap.h"

#include <algorithm>

//----------------------------------------------------------------

gfx_canvas::gfx_canvas( gfx_wh_t width, gfx_wh_t height ):
		_dimension { width, height } {
	_image = new gfx_bitmap( _dimension );
}

//----------------------------------------------------------------

gfx_canvas::gfx_canvas( gfx_wh_t width, gfx_wh_t height, uint8_t bits ):
		_dimension { width, height } {
	if ( bits <= 1 ) {
		_image = new gfx_bitmap( _dimension );
	}
	else if ( (bits >= 3) && (bits <= 24 ) ) {
		_image = new gfx_pixmap( _dimension );
	}
}

//----------------------------------------------------------------

gfx_canvas::gfx_canvas( const gfx_dimension& dimension ):
		_dimension { dimension } {
	_image = new gfx_bitmap( _dimension );
}

//----------------------------------------------------------------

gfx_canvas::~gfx_canvas() noexcept {
	if ( _font != nullptr ) {
		_font->release();
		_font = nullptr;
	}
	if ( _image != nullptr ) {
		delete _image;
		_image = nullptr;
	}
}

//----------------------------------------------------------------

void gfx_canvas::set_pencil( const gfx_point& xy ) {
	if ( xy > this->get_box() ) return;

	if ( xy <= this->get_box() ) {
		_pencil = xy;
	}
	else {
		_pencil.set_xy( 0, 0 );
	}
}

//----------------------------------------------------------------

void gfx_canvas::set_pencil( gfx_xy_t x, gfx_xy_t y ) {
	if ( gfx_point( x, y ) <= this->get_box() ) {
		_pencil.set_xy( x, y );
	}
	else {
		_pencil.set_xy( 0, 0 );
	}
}

//----------------------------------------------------------------

void gfx_canvas::move_pencil_by( gfx_dxy_t dx, gfx_dxy_t dy ) {
	const gfx_point xy { static_cast< gfx_xy_t >( _pencil.get_x() + dx ), static_cast< gfx_xy_t >( _pencil.get_y() + dy ) };
	if ( xy > this->get_box() ) return;

	_pencil = xy;
}

//----------------------------------------------------------------

gfx_wh_t gfx_canvas::get_column_count() const {
	if ( _font == nullptr ) return 0;

	if ( _font->is_monospace() ) {
		const auto column_width = _font->get_x_advance();
		const auto column_count = this->get_width() / column_width;

		return column_count;
	}
	else {
		const auto column_width = _font->get_x_advance_max();
		const auto column_count = this->get_width() / column_width;

		return column_count;
	}
}

//----------------------------------------------------------------

gfx_wh_t gfx_canvas::get_line_count() const {
	if ( _font == nullptr ) return 0;

	const auto line_height = _font->get_y_advance();
	const auto line_count = this->get_height() / line_height;

	return line_count;
}

//----------------------------------------------------------------

void gfx_canvas::set_cursor( const gfx_point& xy ) {
	this->set_cursor( xy.get_x(), xy.get_y() );
}

//----------------------------------------------------------------

void gfx_canvas::set_cursor( gfx_xy_t line, gfx_xy_t column ) {
	if ( _font != nullptr ) {
		if ( line > this->get_line_count() ) line = 0;
		if ( column > this->get_column_count() ) column = 0;

		_cursor.set_xy( line, column );

		const auto x = column * this->get_width();
		const auto x_offset = (this->get_width() - x) / 2;
		const auto y = line * this->get_height();
		const auto y_offset = (this->get_height() - y) / 2;
		this->set_pencil( x + x_offset, y + y_offset );
	}
	else {
		_cursor.set_xy( 0, 0 );
	}
}

//----------------------------------------------------------------

void gfx_canvas::move_cursor_by( gfx_dxy_t dline, gfx_dxy_t dcolumn ) {
	if ( _font == nullptr ) return;

	gfx_dxy_t line = _cursor.get_y() + dline;
	if ( line < 0 ) line = 0;
	gfx_dxy_t column = _cursor.get_x() + dcolumn;
	if ( column < 0 ) column = 0;

	this->set_cursor( line, column );
}

//----------------------------------------------------------------

void gfx_canvas::set_font( gfx_font* font ) {
	if ( font != nullptr ) font->retain();
	if ( _font != nullptr ) _font->release();
	_font = font;
	this->set_cursor( _cursor );
}

//----------------------------------------------------------------

void gfx_canvas::print( std::string_view text ) {
	if ( _font == nullptr ) return;

	for ( auto character : text ) {
		if ( _font->has_glyph( character ) ) {
			gfx_glyph glyph = _font->get_glyph( character );
			this->print_glyph( glyph );
		}
	}
}

//----------------------------------------------------------------

void gfx_canvas::print_center( std::string_view text ) {
	if ( _font == nullptr ) return;

	gfx_wh_t width = _font->get_text_width( text );
	if ( width <= this->get_width() ) {
		gfx_wh_t x = (this->get_width() - width) / 2;
		_pencil.set_x( x );
	}

	this->print( text );
}

//----------------------------------------------------------------

void gfx_canvas::print_glyph( const gfx_glyph& glyph ) {
	for ( gfx_xy_t y = 0 ; y < glyph.get_height() ; ++ y ) {
		for ( gfx_xy_t x = 0 ; x < glyph.get_width() ; ++ x ) {
			gfx_color_bit lit = glyph.get_pixel_lit( x, y );
			if ( lit ) {
				this->draw_point( _pencil.get_x() + glyph.get_left() + x, _pencil.get_y() + glyph.get_top() + y );
			}
		}
	}

	this->move_pencil_by( glyph.get_x_advance(), 0 );
}

//----------------------------------------------------------------

void gfx_canvas::draw_point() {
	_image->set_pixel( _pencil, _foreground_color );
}

//----------------------------------------------------------------

void gfx_canvas::draw_point( gfx_xy_t x, gfx_xy_t y ) {
	_image->set_pixel( x, y, _foreground_color );
}

//----------------------------------------------------------------

void gfx_canvas::draw_point( gfx_point point ) {
	_image->set_pixel( point.get_x(), point.get_y(), _foreground_color );
}

//----------------------------------------------------------------

// https://en.wikipedia.org/wiki/Category:Computer_graphics_algorithms
// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

void gfx_canvas::draw_line( gfx_xy_t x1, gfx_xy_t y1, gfx_xy_t x2, gfx_xy_t y2 ) {
	if ( y1 == y2 ) {
		this->draw_hline( x1, x2, y1 );
		return;
	}

	if ( x1 == x2 ) {
		this->draw_vline( x1, y1, y2 );
		return;
	}

	gfx_dxy_t dx = std::abs( x2 - x1 );
	gfx_dxy_t sx = x1 < x2 ? +1 : -1;

	gfx_dxy_t dy = std::abs( y2 - y1 );
	gfx_dxy_t sy = y1 < y2 ? +1 : -1;

	gfx_dxy_t err = dx - dy;

	gfx_xy_t x = x1;
	gfx_xy_t y = y1;

	while ( true ) {
		_image->set_pixel( x, y, _foreground_color );

		gfx_xy_t err2 = err * 2;
		if ( err2 > -dy ) {
			if ( x == x2 ) break;
			err -= dy;
			x += sx;
		}
		if ( err2 < +dx ) {
			if ( y == y2 ) break;
			err += dx;
			y += sy;
		}
	}
}

//----------------------------------------------------------------

void gfx_canvas::draw_hline( gfx_xy_t x1, gfx_xy_t x2, gfx_xy_t y ) {
	gfx_xy_t max_x = std::max( x1, x2 );
	for ( gfx_xy_t x = std::min( x1, x2 ) ; x <= max_x ; ++ x ) {
		this->draw_point( x, y );
	}
}

//----------------------------------------------------------------

void gfx_canvas::draw_vline( gfx_xy_t x, gfx_xy_t y1, gfx_xy_t y2 ) {
	gfx_xy_t max_y = std::max( y1, y2 );
	for ( gfx_xy_t y = std::min( y1, y2 ) ; y <= max_y ; ++ y ) {
		this->draw_point( x, y );
	}
}

//----------------------------------------------------------------

void gfx_canvas::draw_line_to( gfx_xy_t x, gfx_xy_t y ) {
	this->draw_line( _pencil.get_x(), _pencil.get_y(), x, y );
	_pencil.set_xy( x, y );
}

//----------------------------------------------------------------

void gfx_canvas::draw_line_to_polar( float distance, float angle ) {
	float dx = distance * std::cos( angle );
	float dy = distance * std::sin( angle );

	gfx_xy_t x = _pencil.get_x() + static_cast< gfx_dxy_t >( dx );
	gfx_xy_t y = _pencil.get_y() + static_cast< gfx_dxy_t >( dy );

	this->draw_line_to( x, y );
}

//----------------------------------------------------------------

void gfx_canvas::draw_rectangle( gfx_xy_t x1, gfx_xy_t y1, gfx_xy_t x2, gfx_xy_t y2 ) {
	this->draw_hline( x1, x2, y1 ); // top
	this->draw_vline( x1, y1, y2 ); // left
	this->draw_vline( x2, y1, y2 ); // right
	this->draw_hline( x1, x2, y2 ); // bottom
}

//----------------------------------------------------------------

void gfx_canvas::draw_rectangle( gfx_point p1, gfx_point p2 ) {
	this->draw_hline( p1.get_x(), p2.get_x(), p1.get_y() ); // top
	this->draw_vline( p1.get_x(), p1.get_y(), p2.get_y() ); // left
	this->draw_vline( p2.get_x(), p1.get_y(), p2.get_y() ); // right
	this->draw_hline( p1.get_x(), p2.get_x(), p2.get_y() ); // bottom
}

//----------------------------------------------------------------

void gfx_canvas::draw_rectangle( gfx_rectangle rectangle ) {
	this->draw_rectangle( rectangle.get_top_left(), rectangle.get_bottom_right() );
}

//----------------------------------------------------------------

void gfx_canvas::fill_rectangle( gfx_xy_t x1, gfx_xy_t y1, gfx_xy_t x2, gfx_xy_t y2 ) {
	gfx_xy_t max_y = std::max( y1, y2 );
	for ( gfx_xy_t y = std::min( y1, y2 ) ; y < max_y ; ++ y ) {
		this->draw_hline( x1, x2, y );
	}
}

//----------------------------------------------------------------

void gfx_canvas::draw_circle( gfx_xy_t r ) const {
	this->draw_circle( _pencil.get_x(), _pencil.get_y(), r );
}

//----------------------------------------------------------------

// https://en.wikipedia.org/wiki/Category:Computer_graphics_algorithms
// https://en.wikipedia.org/wiki/Midpoint_circle_algorithm

void gfx_canvas::draw_circle( gfx_xy_t x, gfx_xy_t y, gfx_xy_t r ) const {
	gfx_xy_t ix = 0;
	gfx_xy_t iy = r;
	gfx_dxy_t err = 1 - r;

	while ( ix < iy ) {
		// quadrant 1
		_image->set_pixel( x + ix, y - iy, _foreground_color );
		_image->set_pixel( x + iy, y - ix, _foreground_color );

		// quadrant 2
		_image->set_pixel( x + ix, y + iy, _foreground_color );
		_image->set_pixel( x + iy, y + ix, _foreground_color );

		// quadrant 3
		_image->set_pixel( x - ix, y + iy, _foreground_color );
		_image->set_pixel( x - iy, y + ix, _foreground_color );

		// quadrant 4
		_image->set_pixel( x - ix, y - iy, _foreground_color );
		_image->set_pixel( x - iy, y - ix, _foreground_color );

		if ( err < 0 ) {
			err += 2 * ix + 1;
			++ ix;
		}
		else {
			err += 2 * (ix - iy) + 1;
			++ ix;
			-- iy;
		}
	}
}

//----------------------------------------------------------------

void gfx_canvas::draw_circle( const gfx_point& center, gfx_xy_t r ) const {
	this->draw_circle( center.get_x(), center.get_y(), r );
}

//----------------------------------------------------------------

void gfx_canvas::draw_circle( gfx_xy_t x, gfx_xy_t y, gfx_xy_t r, uint8_t quadrants ) const {
	gfx_xy_t ix = 0;
	gfx_xy_t iy = r;
	gfx_dxy_t err = 1 - r;

	while ( ix < iy ) {
		// quadrant 1
		if ( !!(quadrants & 0b0001) ) {
			_image->set_pixel( x + ix, y - iy, _foreground_color );
			_image->set_pixel( x + iy, y - ix, _foreground_color );
		}

		// quadrant 2
		if ( !!(quadrants & 0b0010) ) {
			_image->set_pixel( x + ix, y + iy, _foreground_color );
			_image->set_pixel( x + iy, y + ix, _foreground_color );
		}

		// quadrant 3
		if ( !!(quadrants & 0b0100) ) {
			_image->set_pixel( x - ix, y + iy, _foreground_color );
			_image->set_pixel( x - iy, y + ix, _foreground_color );
		}

		// quadrant 4
		if ( !!(quadrants & 0b1000) ) {
			_image->set_pixel( x - ix, y - iy, _foreground_color );
			_image->set_pixel( x - iy, y - ix, _foreground_color );
		}

		if ( err < 0 ) {
			err += 2 * ix + 1;
			++ ix;
		}
		else {
			err += 2 * (ix - iy) + 1;
			++ ix;
			-- iy;
		}
	}
}

//----------------------------------------------------------------

void gfx_canvas::fill_circle( gfx_xy_t x, gfx_xy_t y, gfx_xy_t r ) {
	gfx_xy_t ix = 0;
	gfx_xy_t iy = r;
	gfx_dxy_t err = 1 - r;

	while ( ix < iy ) {
		// quadrant 1
		this->draw_hline( x, x + ix, y - iy );
		this->draw_hline( x, x + iy, y - ix );

		// quadrant 2
		this->draw_hline( x, x + ix, y + iy );
		this->draw_hline( x, x + iy, y + ix );

		// quadrant 3
		this->draw_hline( x - ix, x, y + iy );
		this->draw_hline( x - iy, x, y + ix );

		// quadrant 4
		this->draw_hline( x - ix, x, y - iy );
		this->draw_hline( x - iy, x, y - ix );

		if ( err < 0 ) {
			err += 2 * ix + 1;
			++ ix;
		}
		else {
			err += 2 * (ix - iy) + 1;
			++ ix;
			-- iy;
		}
	}
}

//----------------------------------------------------------------

void gfx_canvas::fill_circle( gfx_xy_t x, gfx_xy_t y, gfx_xy_t r, uint8_t quadrants ) {
	gfx_xy_t ix = 0;
	gfx_xy_t iy = r;
	gfx_dxy_t err = 1 - r;

	while ( ix < iy ) {
		// quadrant 1
		if ( !!(quadrants & 0b0001) ) {
			this->draw_hline( x, x + ix, y - iy );
			this->draw_hline( x, x + iy, y - ix );
		}

		// quadrant 2
		if ( !!(quadrants & 0b0010) ) {
			this->draw_hline( x, x + ix, y + iy );
			this->draw_hline( x, x + iy, y + ix );
		}

		// quadrant 3
		if ( !!(quadrants & 0b0100) ) {
			this->draw_hline( x - ix, x, y + iy );
			this->draw_hline( x - iy, x, y + ix );
		}

		// quadrant 4
		if ( !!(quadrants & 0b1000) ) {
			this->draw_hline( x - ix, x, y - iy );
			this->draw_hline( x - iy, x, y - ix );
		}

		if ( err < 0 ) {
			err += 2 * ix + 1;
			++ ix;
		}
		else {
			err += 2 * (ix - iy) + 1;
			++ ix;
			-- iy;
		}
	}
}

//----------------------------------------------------------------

void gfx_canvas::draw_round_rectangle( gfx_rectangle rectangle, gfx_xy_t radius ) {
	if ( radius > rectangle.get_width() / 2 ) return;
	if ( radius > rectangle.get_height() / 2 ) return;

	this->draw_hline( rectangle.get_left() + radius, rectangle.get_right() - radius, rectangle.get_top() ); // top
	this->draw_circle( rectangle.get_right() - radius, rectangle.get_top() + radius, radius, 0b0001 );
	this->draw_vline( rectangle.get_left(), rectangle.get_top() + radius, rectangle.get_bottom() - radius ); // left
	this->draw_circle( rectangle.get_right() - radius, rectangle.get_bottom() - radius, radius, 0b0010 );
	this->draw_vline( rectangle.get_right(), rectangle.get_top() + radius, rectangle.get_bottom() - radius ); // right
	this->draw_circle( rectangle.get_left() + radius, rectangle.get_bottom() - radius, radius, 0b0100 );
	this->draw_hline( rectangle.get_left() + radius, rectangle.get_right() - radius, rectangle.get_bottom() ); // bottom
	this->draw_circle( rectangle.get_left() + radius, rectangle.get_top() + radius, radius, 0b1000 );
}

//----------------------------------------------------------------

void gfx_canvas::fill_round_rectangle( gfx_rectangle rectangle, gfx_xy_t radius ) {
	if ( radius > rectangle.get_width() / 2 ) return;
	if ( radius > rectangle.get_height() / 2 ) return;

	this->fill_rectangle( rectangle.get_left() + radius, rectangle.get_top(), rectangle.get_right() - radius, rectangle.get_top() + radius );
	this->fill_circle( rectangle.get_left() + radius, rectangle.get_top() + radius, radius, 0b1000 );
	this->fill_circle( rectangle.get_right() - radius, rectangle.get_top() + radius, radius, 0b0001 );
	this->fill_rectangle( rectangle.get_left(), rectangle.get_top() + radius, rectangle.get_right(), rectangle.get_bottom() - radius );
	this->fill_rectangle( rectangle.get_left() + radius, rectangle.get_bottom() - radius, rectangle.get_right() - radius, rectangle.get_bottom() );
	this->fill_circle( rectangle.get_left() + radius, rectangle.get_bottom() - radius, radius, 0b0100 );
	this->fill_circle( rectangle.get_right() - radius, rectangle.get_bottom() - radius, radius, 0b0010 );
}

//----------------------------------------------------------------

void gfx_canvas::erase() {
	_image->erase();
}

//----------------------------------------------------------------

gfx_bytemap_data gfx_canvas::make_yx_bytemap() const {
	return _image->make_yx_bytemap();
}

//----------------------------------------------------------------

std::vector< uint16_t > gfx_canvas::make_pixmap_565() const {
	return _image->make_pixmap_565();
}

//----------------------------------------------------------------
