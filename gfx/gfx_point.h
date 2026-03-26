//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// gfx_point
//
//----------------------------------------------------------------

#pragma once
#ifndef _GFX_POINT_H
#define _GFX_POINT_H

//----------------------------------------------------------------

#include "pico.h"

#include "gfx_types.h"


//----------------------------------------------------------------

class gfx_point {

private:

	gfx_xy_t x;
	gfx_xy_t y;

public:

	gfx_point():
		x( 0 ),
		y( 0 ) {
	}

	gfx_point( const gfx_point& that ):
		x( that.x ),
		y( that.y ) {
	}

	gfx_point( gfx_xy_t x, gfx_xy_t y ):
		x( x ),
		y( y ) {
	}

	inline gfx_xy_t get_x() const { return this->x; }
	inline gfx_xy_t get_y() const { return this->y; }

	inline bool is_null() const { return (this-> x == 0) && (this->y == 0); }

	inline gfx_xy_t get_line( gfx_xy_t line_height ) const {
		return this->y / line_height;
	}

	inline gfx_xy_t get_column( gfx_xy_t column_width ) const {
		return this->x / column_width;
	}

	gfx_point get_lico( gfx_xy_t line_height, gfx_xy_t column_width ) const {
		return gfx_point( this->get_line( line_height ), this->get_column( column_width ) );
	}

};

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
