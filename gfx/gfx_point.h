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

#include <cmath>

//----------------------------------------------------------------

class gfx_point {

private:

	gfx_xy_t _x;
	gfx_xy_t _y;

public:

	gfx_point():
		_x( 0 ),
		_y( 0 ) {
	}

	gfx_point( const gfx_point& that ):
		_x( that._x ),
		_y( that._y ) {
	}

	gfx_point( gfx_xy_t x, gfx_xy_t y ):
		_x( x ),
		_y( y ) {
	}

	inline gfx_xy_t get_x() const { return _x; }
	inline void set_x( gfx_xy_t x ) { _x = x; }

	inline gfx_xy_t get_y() const { return _y; }
	inline void set_y( gfx_xy_t y ) { _y = y; }

	inline void set_xy( gfx_xy_t x, gfx_xy_t y ) { _x = x; _y = y; }

	inline float get_r() const { return std::hypot( _x, _y ); }
	void set_r( float r );

	inline float get_phi() const { return std::atan2( _y, _x ); }
	void set_phi( float phi );

	void set_rphi( float r, float phi );
	void set_polar( float r, float phi );

	inline gfx_point& operator=( const gfx_point& that ) { _x = that._x; _y = that._y; return *this; }

	inline bool is_null() const { return (_x == 0) && (_y == 0); }

	inline gfx_xy_t get_line( gfx_xy_t line_height ) const {
		return _y / line_height;
	}

	inline gfx_xy_t get_column( gfx_xy_t column_width ) const {
		return _x / column_width;
	}

	gfx_point get_lico( gfx_xy_t line_height, gfx_xy_t column_width ) const {
		return gfx_point( this->get_line( line_height ), this->get_column( column_width ) );
	}

};

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
