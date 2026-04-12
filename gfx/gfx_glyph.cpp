//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_glyph
//
//----------------------------------------------------------------

#include "gfx_glyph.h"

#include <cstring>
#include <cstdio>
#include <algorithm>

//----------------------------------------------------------------

gfx_glyph::gfx_glyph():
	_character( 0 ),
	_box(),
	_x_advance( 0 ),
	_bytemap( (_box.get_area() + 7) / 8, 0x00 ) {
}

//----------------------------------------------------------------

gfx_glyph::gfx_glyph( char character, gfx_xy_t left, gfx_xy_t top, gfx_wh_t width, gfx_wh_t height, gfx_dxy_t x_advance ):
	_character( character ),
	_box( gfx_point( left, top ), gfx_dimension( width, height ) ),
	_x_advance( x_advance ),
	_bytemap( (_box.get_area() + 7) / 8, 0x00 ) {
}

//----------------------------------------------------------------

gfx_glyph::gfx_glyph( const gfx_glyph_data& glyph_data ):
	_character( glyph_data.character ),
	_box( gfx_point( glyph_data.x, glyph_data.y ), gfx_dimension( glyph_data.width, glyph_data.height ) ),
	_x_advance( glyph_data.x_advance ),
	_bytemap( glyph_data.bytemap ) {
	this->set_bytemap( glyph_data.bytemap );
}

//----------------------------------------------------------------

gfx_glyph::gfx_glyph( const gfx_glyph& that ):
	_character( that._character ),
	_box( that._box ),
	_x_advance( that._x_advance ),
	_bytemap( that._bytemap ) {
}

//----------------------------------------------------------------

void gfx_glyph::minimize() {
	if ( this->is_empty() ) {
		this->set_box( gfx_rectangle() );
		return;
	}

	while ( true ) {
		if ( this->get_height() == 0 ) break;

		gfx_xy_t y = this->get_height() - 1;
		if ( this->is_line_empty( y ) ) {
			this->remove_line( y );
			_box.set_bottom( _box.get_bottom() - 1 );
		}
		else {
			break;
		}
	}

	while ( true ) {
		if ( this->get_height() == 0 ) break;

		gfx_xy_t y = 0;
		if ( this->is_line_empty( y ) ) {
			this->remove_line( y );
			_box.set_top( _box.get_top() + 1 );
		}
		else {
			break;
		}
	}

	while ( true ) {
		if ( this->get_width() == 0 ) break;

		gfx_xy_t x = this->get_width() - 1;
		if ( this->is_column_empty( x ) ) {
			this->remove_column( x );
			_box.set_right( _box.get_right() - 1 );
		}
		else {
			break;
		}
	}

	while ( true ) {
		if ( this->get_width() == 0 ) break;

		gfx_xy_t x = 0;
		if ( this->is_column_empty( x ) ) {
			this->remove_column( x );
			_box.set_left( _box.get_left() + 1 );
		}
		else {
			break;
		}
	}
}

//----------------------------------------------------------------

void gfx_glyph::maximize() {
	gfx_bytemap_data bytemap( (this->get_right() * this->get_bottom() + 7) / 8, 0 );
	for ( gfx_xy_t y = 0 ; y < this->get_height() ; ++ y ) {
		for ( gfx_xy_t x = 0 ; x < this->get_width() ; ++ x ) {
			if ( this->get_pixel_lit( x, y ) ) {
				size_t index = (this->get_left() + x) + (this->get_top() + y) * this->get_right();
				bytemap[ index / 8 ] |= (0x80 >> (index % 8));
			}
		}
	}
	_bytemap = bytemap;
}

//----------------------------------------------------------------

bool gfx_glyph::is_empty() const {
	if ( this->get_width() == 0 ) return true;
	if ( this->get_height() == 0 ) return true;

	return !std::any_of( _bytemap.begin(), _bytemap.end(), []( const auto byte ) -> bool { return byte > 0; } );
}

//----------------------------------------------------------------

bool gfx_glyph::is_line_empty( gfx_xy_t y ) const {
	if ( y >= this->get_height() ) return true;
	if ( this->get_width() == 0 ) return true;
	if ( this->get_height() == 0 ) return true;

	for ( gfx_xy_t x = 0 ; x < this->get_width() ; ++ x ) {
		if ( this->get_pixel_lit( x, y ) ) {
			return false;
		}
	}

	return true;
}

//----------------------------------------------------------------

void gfx_glyph::remove_line( gfx_xy_t y ) {
	if ( y >= this->get_height() ) return;
	if ( this->get_width() == 0 ) return;
	if ( this->get_height() == 0 ) return;

	gfx_wh_t dheight = this->get_height() - 1;
	gfx_bytemap_data bytemap( (this->get_width() * dheight + 7) / 8, false );
	gfx_xy_t dy = 0;
	for ( gfx_xy_t sy = 0 ; sy < this->get_height() ; ++ sy ) {
		if ( sy != y ) {
			for ( gfx_xy_t x = 0 ; x < this->get_width() ; ++ x ) {
				if ( this->get_pixel_lit( x, sy ) ) {
					size_t index = x + dy * this->get_width();
					bytemap[ index / 8 ] |= (0x80 >> (index % 8));
				}
			}
			++ dy;
		}
	}
	_bytemap = bytemap;
}

//----------------------------------------------------------------

bool gfx_glyph::is_column_empty( gfx_xy_t x ) const {
	if ( x >= this->get_width() ) return true;
	if ( this->get_width() == 0 ) return true;
	if ( this->get_height() == 0 ) return true;

	for ( gfx_xy_t y = 0 ; y < this->get_height() ; ++ y ) {
		if ( this->get_pixel_lit( x, y ) ) {
			return false;
		}
	}

	return true;
}

//----------------------------------------------------------------

void gfx_glyph::remove_column( gfx_xy_t x ) {
	if ( x >= this->get_width() ) return;
	if ( this->get_height() == 0 ) return;
	if ( this->get_width() == 0 ) return;

	gfx_wh_t dwidth = this->get_width() - 1;
	gfx_bytemap_data bytemap( (dwidth * this->get_height() + 7) / 8, false );
	for ( gfx_xy_t y = 0 ; y < this->get_height() ; ++ y ) {
		gfx_xy_t dx = 0;
		for ( gfx_xy_t sx = 0 ; sx < this->get_width() ; ++ sx ) {
			if ( sx != x ) {
				if ( this->get_pixel_lit( sx, y ) ) {
					size_t index = dx + y * dwidth;
					bytemap[ index / 8 ] |= (0x80 >> (index % 8));
				}
				++ dx;
			}
		}
	}
	_bytemap = bytemap;
}

//----------------------------------------------------------------

gfx_glyph::~gfx_glyph() {
	_bytemap.clear();
}

//----------------------------------------------------------------

gfx_glyph& gfx_glyph::operator=( const gfx_glyph& that ) {
	_character = that._character;
	_box = that._box;
	_x_advance = that._x_advance;
	_bytemap = that._bytemap;

	return *this;
}

//----------------------------------------------------------------

void gfx_glyph::set_bytemap( const gfx_bytemap_data& bytemap ) {
	size_t bit_count = _box.get_area();
	size_t byte_count = (bit_count + 7) / 8;
	_bytemap.resize( byte_count, false );

	for ( gfx_xy_t y = 0 ; y < this->get_height() ; ++ y ) {
		for ( gfx_xy_t x = 0 ; x < this->get_width() ; ++ x ) {
			uint index = x + y * this->get_width();
			bool bit = !!(bytemap[ index / 8 ] & (0x80 >> (index % 8)));
			this->set_pixel_lit( x, y, bit );
		}
	}
}

//----------------------------------------------------------------

void gfx_glyph::set_bitmap_xy( const uint8_t* bitmap, size_t length ) {
	size_t bit_count = _box.get_area();
	size_t byte_count = (bit_count + 7) / 8;
	_bytemap.resize( byte_count, false );

	for ( gfx_xy_t y = 0 ; y < this->get_height() ; ++ y ) {
		for ( gfx_xy_t x = 0 ; x < this->get_width() ; ++ x ) {
			uint index = x + y * this->get_width();
			bool bit = !!(bitmap[ index / 8 ] & (0x80 >> (index % 8)));
			this->set_pixel_lit( x, y, bit );
		}
	}
}

//----------------------------------------------------------------

void gfx_glyph::set_bitmap_yx( const uint8_t* bitmap, size_t length, bool lsb_first, bool invert ) {
	size_t bit_count = _box.get_area();
	size_t byte_count = (bit_count + 7) / 8;
	_bytemap.resize( byte_count, false );

	for ( gfx_xy_t y = 0 ; y < this->get_height() ; ++ y ) {
		for ( gfx_xy_t x = 0 ; x < this->get_width() ; ++ x ) {
			uint index = x * this->get_height() + y;
			bool bit = !!(bitmap[ index / 8 ] & ( lsb_first ? (0x01 << (index % 8)) : (0x80 >> (index % 8)) ) );
			this->set_pixel_lit( x, y, invert ? !bit : bit );
		}
	}
}

//----------------------------------------------------------------

gfx_color_bit gfx_glyph::get_pixel_lit( gfx_xy_t x, gfx_xy_t y ) const {
	size_t index = x + y * this->get_width();
	return !!(_bytemap[ index / 8 ] & (0x80 >> (index % 8)));
}

//----------------------------------------------------------------

void gfx_glyph::set_pixel_lit( gfx_xy_t x, gfx_xy_t y, gfx_color_bit lit ) {
	size_t index = x + y * this->get_width();
	if ( lit ) _bytemap[ index / 8 ] |= (0x80 >> (index % 8));
	else _bytemap[ index / 8 ] &= ~(0x80 >> (index % 8));
}

//----------------------------------------------------------------
