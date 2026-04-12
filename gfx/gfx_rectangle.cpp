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
	gfx_xy_t left = this->get_left();
	gfx_xy_t top = this->get_top();
	gfx_xy_t right = this->get_right();
	gfx_xy_t bottom = this->get_bottom();

	_top_left.set_xy( std::min( left, right ), std::min( top, bottom ) );
	_bottom_right.set_xy( std::max( left, right ), std::max( top, bottom ) );
}

//----------------------------------------------------------------

void gfx_rectangle::set_left( gfx_xy_t left ) {
	if ( left > this->get_right() ) return;

	_top_left.set_x( left );
}

//----------------------------------------------------------------

void gfx_rectangle::set_top( gfx_xy_t top ) {
	if ( top > this->get_bottom() ) return;

	_top_left.set_y( top );
}

//----------------------------------------------------------------

void gfx_rectangle::set_right( gfx_xy_t right ) {
	if ( right < this->get_left() ) return;

	_bottom_right.set_x( right );
}

//----------------------------------------------------------------

void gfx_rectangle::set_bottom( gfx_xy_t bottom ) {
	if ( bottom < this->get_top() ) return;

	_bottom_right.set_y( bottom );
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
