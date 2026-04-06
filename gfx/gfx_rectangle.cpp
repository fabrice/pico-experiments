//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// gfx_rectangle
//
//----------------------------------------------------------------

#include "pico.h"

#include "gfx_types.h"
#include "gfx_rectangle.h"

#include <cmath>
#include <algorithm>

//----------------------------------------------------------------

void gfx_rectangle::normalize() {
	gfx_xy_t x1 = this->get_x1();
	gfx_xy_t y1 = this->get_y1();
	gfx_xy_t x2 = this->get_x2();
	gfx_xy_t y2 = this->get_y2();

	_top_left.set_xy( std::min( x1, x2 ), std::min( y1, y2 ) );
	_bottom_right.set_xy( std::max( x1, x2 ), std::max( y1, y2 ) );
}

//----------------------------------------------------------------

void gfx_rectangle::set_left( gfx_xy_t x ) {
	if ( x > this->get_right() ) return;

	_top_left.set_x( x );
}

//----------------------------------------------------------------

void gfx_rectangle::set_top( gfx_xy_t y ) {
	if ( y > this->get_bottom() ) return;

	_top_left.set_y( y );
}

//----------------------------------------------------------------

void gfx_rectangle::set_right( gfx_xy_t x ) {
	if ( x < this->get_left() ) return;

	_bottom_right.set_x( x );
}

//----------------------------------------------------------------

void gfx_rectangle::set_bottom( gfx_xy_t y ) {
	if ( y < this->get_top() ) return;

	_bottom_right.set_y( y );
}

//----------------------------------------------------------------

gfx_wh_t gfx_rectangle::get_diagonal() const {
	return std::hypot( this->get_width(), this->get_height() );
}

//----------------------------------------------------------------

bool gfx_rectangle::is_null() const {
	return _top_left.is_null() && _bottom_right.is_null();
}

//----------------------------------------------------------------

bool gfx_rectangle::is_empty() const {
	return (this->get_width() == 0) && (this->get_height() == 0);
}

//----------------------------------------------------------------
