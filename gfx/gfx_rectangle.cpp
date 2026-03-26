//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// gfx_rectangle.cpp
//
//----------------------------------------------------------------

#include "pico.h"

#include "gfx_types.h"
#include "gfx_rectangle.h"

#include <cmath>


//----------------------------------------------------------------

void gfx_rectangle::normalize() {
	gfx_xy_t x1 = this->get_x1();
	gfx_xy_t y1 = this->get_y1();
	gfx_xy_t x2 = this->get_x2();
	gfx_xy_t y2 = this->get_y2();

	top_left = gfx_point( std::min( x1, x2 ), std::min( y1, y2 ) );
	bottom_right = gfx_point( std::max( x1, x2 ), std::max( y1, y2 ) );
}

//----------------------------------------------------------------

gfx_xy_t gfx_rectangle::get_diagonal() const {
	return std::hypot( this->get_width(), this->get_height() );
}

//----------------------------------------------------------------

bool gfx_rectangle::is_null() const {
	return this->top_left.is_null() && this->bottom_right.is_null();
}

//----------------------------------------------------------------

bool gfx_rectangle::is_empty() const {
	return (this->get_width() == 0) && (this->get_height() == 0);
}

//----------------------------------------------------------------
