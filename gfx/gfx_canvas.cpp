//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_canvas
//
//----------------------------------------------------------------

#include "pico/stdlib.h"

#include "gfx_types.h"
#include "gfx_canvas.h"
#include "gfx_image.h"
#include "gfx_bitmap.h"
#include "gfx_pixmap.h"


#include "math_plus.h"

#include <algorithm>

//----------------------------------------------------------------

gfx_canvas::gfx_canvas():
	_dimension( 0, 0 ),
	_spot(),
	_lico(),
	_foreground_color( gfx_color_rgb::WHITE ),
	_background_color( gfx_color_rgb::BLACK ),
	_image( nullptr ) {
	_image = new gfx_bitmap( _dimension );
}

//----------------------------------------------------------------

gfx_canvas::gfx_canvas( gfx_wh_t width, gfx_wh_t height ):
	_dimension( width, height ),
	_spot(),
	_lico(),
	_foreground_color( gfx_color_rgb::WHITE ),
	_background_color( gfx_color_rgb::BLACK ),
	_font( nullptr ),
	_image( nullptr ) {
	_image = new gfx_bitmap( _dimension );
}

//----------------------------------------------------------------

gfx_canvas::gfx_canvas( gfx_wh_t width, gfx_wh_t height, uint8_t bits ):
	_dimension( width, height ),
	_spot(),
	_lico(),
	_foreground_color( gfx_color_rgb::WHITE ),
	_background_color( gfx_color_rgb::BLACK ),
	_font( nullptr ),
	_image( nullptr ) {
	if ( bits <= 1 ) {
		_image = new gfx_bitmap( _dimension );
	}
	else if ( (bits >= 3) && (bits <= 24 ) ) {
		_image = new gfx_pixmap( _dimension );
	}
}

//----------------------------------------------------------------

gfx_canvas::gfx_canvas( gfx_dimension& dimension ):
	_dimension( dimension ),
	_spot(),
	_lico(),
	_foreground_color( gfx_color_rgb::WHITE ),
	_background_color( gfx_color_rgb::BLACK ),
	_font( nullptr ),
	_image( nullptr ) {
}

//----------------------------------------------------------------

gfx_canvas::~gfx_canvas() {
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

void gfx_canvas::set_spot( gfx_xy_t x, gfx_xy_t y ) {
	_spot.set_xy( x, y );
}

//----------------------------------------------------------------

void gfx_canvas::move_spot_by( gfx_dxy_t dx, gfx_dxy_t dy ) {
	_spot.set_xy( _spot.get_x() + dx, _spot.get_y() + dy );
}

//----------------------------------------------------------------

void gfx_canvas::set_lico( gfx_xy_t line, gfx_xy_t column ) {
	_lico.set_xy( line, column );
	if ( _font != nullptr ) {
		gfx_dxy_t x_advance = _font->get_x_advance();
		gfx_dxy_t y_advance = _font->get_y_advance();
		this->set_spot( line * y_advance, column * x_advance );
	}
}

//----------------------------------------------------------------

void gfx_canvas::move_lico_by( gfx_dxy_t dline, gfx_dxy_t dcolumn ) {
	_lico.set_xy( _lico.get_x() + dline, _lico.get_y() + dcolumn );
}

//----------------------------------------------------------------

void gfx_canvas::set_font( gfx_font_ref font ) {
	if ( font != nullptr ) font->retain();
	if ( _font != nullptr ) _font->release();
	_font = font;
}

//----------------------------------------------------------------

void gfx_canvas::print( std::string text ) {
	if ( _font == nullptr ) return;

	for ( auto character : text ) {
		if ( _font->has_glyph( character ) ) {
			gfx_glyph glyph = _font->get_glyph( character );
			this->print_glyph( glyph );
		}
	}
}

//----------------------------------------------------------------

void gfx_canvas::print_center( std::string text ) {
	if ( _font == nullptr ) return;

	gfx_wh_t width = _font->get_text_width( text );
	if ( width <= this->get_width() ) {
		gfx_wh_t x = (this->get_width() - width) / 2;
		_spot.set_x( x );
	}

	this->print( text );
}

//----------------------------------------------------------------

void gfx_canvas::print_glyph( const gfx_glyph& glyph ) {
	for ( gfx_xy_t y = 0 ; y < glyph.get_height() ; ++ y ) {
		for ( gfx_xy_t x = 0 ; x < glyph.get_width() ; ++ x ) {
			gfx_color_bit lit = glyph.get_pixel_lit( x, y );
			if ( lit ) {
				this->draw_point( _spot.get_x() + glyph.get_left() + x, _spot.get_y() + glyph.get_top() + y );
			}
		}
	}

	this->move_spot_by( glyph.get_x_advance(), 0 );
}

//----------------------------------------------------------------

void gfx_canvas::draw_point() {
	_image->set_pixel( _spot, _foreground_color );
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

void gfx_canvas::draw_line_to( gfx_xy_t x, gfx_xy_t y ) {
	this->draw_line( _spot.get_x(), _spot.get_y(), x, y );
	_spot.set_xy( x, y );
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

void gfx_canvas::draw_circle( gfx_xy_t r ) {
	this->draw_circle( _spot.get_x(), _spot.get_y(), r );
}

//----------------------------------------------------------------

// https://en.wikipedia.org/wiki/Category:Computer_graphics_algorithms
// https://en.wikipedia.org/wiki/Midpoint_circle_algorithm

void gfx_canvas::draw_circle( gfx_xy_t x, gfx_xy_t y, gfx_xy_t r ) {
	gfx_xy_t ix = 0;
	gfx_xy_t iy = r;
	gfx_dxy_t err = 1 - r;

	while ( ix < iy ) {
		// quadran 1
		_image->set_pixel( x + ix, y - iy, _foreground_color );
		_image->set_pixel( x + iy, y - ix, _foreground_color );

		// quadran 2
		_image->set_pixel( x + ix, y + iy, _foreground_color );
		_image->set_pixel( x + iy, y + ix, _foreground_color );

		// quadrant 3
		_image->set_pixel( x - ix, y + iy, _foreground_color );
		_image->set_pixel( x - iy, y + ix, _foreground_color );

		// quadran 4
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

void gfx_canvas::draw_circle( gfx_point center, gfx_xy_t r ) {
	this->draw_circle( center.get_x(), center.get_y(), r );
}

//----------------------------------------------------------------

void gfx_canvas::draw_circle( gfx_xy_t x, gfx_xy_t y, gfx_xy_t r, uint8_t quadrans ) {
	gfx_xy_t ix = 0;
	gfx_xy_t iy = r;
	gfx_dxy_t err = 1 - r;

	while ( ix < iy ) {
		// quadran 1
		if ( !!(quadrans & 0b0001) ) {
			_image->set_pixel( x + ix, y - iy, _foreground_color );
			_image->set_pixel( x + iy, y - ix, _foreground_color );
		}

		// quadran 2
		if ( !!(quadrans & 0b0010) ) {
			_image->set_pixel( x + ix, y + iy, _foreground_color );
			_image->set_pixel( x + iy, y + ix, _foreground_color );
		}

		// quadrant 3
		if ( !!(quadrans & 0b0100) ) {
			_image->set_pixel( x - ix, y + iy, _foreground_color );
			_image->set_pixel( x - iy, y + ix, _foreground_color );
		}

		// quadran 4
		if ( !!(quadrans & 0b1000) ) {
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

void gfx_canvas::fill_circle( gfx_xy_t x, gfx_xy_t y, gfx_xy_t r, uint8_t quadrans ) {
	gfx_xy_t ix = 0;
	gfx_xy_t iy = r;
	gfx_dxy_t err = 1 - r;

	while ( ix < iy ) {
		// quadran 1
		if ( !!(quadrans & 0b0001) ) {
			this->draw_hline( x, x + ix, y - iy );
			this->draw_hline( x, x + iy, y - ix );
		}

		// quadran 2
		if ( !!(quadrans & 0b0010) ) {
			this->draw_hline( x, x + ix, y + iy );
			this->draw_hline( x, x + iy, y + ix );
		}

		// quadrant 3
		if ( !!(quadrans & 0b0100) ) {
			this->draw_hline( x - ix, x, y + iy );
			this->draw_hline( x - iy, x, y + ix );
		}

		// quadran 4
		if ( !!(quadrans & 0b1000) ) {
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
