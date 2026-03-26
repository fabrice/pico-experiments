//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// gfx_rectangle.h
//
//----------------------------------------------------------------

#pragma once
#ifndef _GFX_RECTANGLE_H
#define _GFX_RECTANGLE_H

//----------------------------------------------------------------

#include "pico.h"

#include "gfx_point.h"
#include "gfx_line.h"

#include <cmath>


//----------------------------------------------------------------

class gfx_rectangle {

private:

	gfx_point top_left;
	gfx_point bottom_right;

public:

	gfx_rectangle():
		top_left(),
		bottom_right() {
	}

	gfx_rectangle( const gfx_rectangle& that ):
		top_left( that.top_left ),
		bottom_right( that.bottom_right ) {
	}

	gfx_rectangle( gfx_xy_t x1, gfx_xy_t y1, gfx_xy_t x2, gfx_xy_t y2 ):
		top_left( x1, y1 ),
		bottom_right( x2, y2 ) {
		this->normalize();
	}

	gfx_rectangle( gfx_point& p1, gfx_point& p2 ):
		top_left( p1 ),
		bottom_right( p2 ) {
		this->normalize();
	}

	gfx_rectangle( gfx_line& line ):
		top_left( line.get_left() ),
		bottom_right( line.get_right() ) {
		this->normalize();
	}

private:
	void normalize();

public:

	inline gfx_xy_t get_x1() const { return this->top_left.get_x(); }
	inline gfx_xy_t get_y1() const { return this->top_left.get_y(); }
	inline gfx_xy_t get_x2() const { return this->bottom_right.get_x(); }
	inline gfx_xy_t get_y2() const { return this->bottom_right.get_y(); }

	inline gfx_point get_top_left() const { return this->top_left; }
	inline gfx_point get_top_right() const { return gfx_point( this->get_x2(), this->get_y1() ); }
	inline gfx_point get_bottom_left() const { return gfx_point( this->get_x1(), this->get_y2() ); }
	inline gfx_point get_bottom_right() const { return this->bottom_right; }

	inline gfx_xy_t get_width() const { return this->get_x2() - this->get_x1(); }
	inline gfx_xy_t get_height() const { return this->get_y2() - this->get_y1(); }
	gfx_xy_t get_diagonal() const;

	bool is_null() const;
	bool is_empty() const;

	[[nodiscard]]
	gfx_rectangle intersect( gfx_rectangle& that ) const {
		gfx_xy_t x1 = std::max( this->get_x1(), that.get_x1() );
		gfx_xy_t y1 = std::max( this->get_y1(), that.get_y1() );
		gfx_xy_t x2 = std::min( this->get_x2(), that.get_x2() );
		gfx_xy_t y2 = std::min( this->get_y2(), that.get_y2() );

		if ( (x1 < x2) && (y1 < y2) ) {
			return gfx_rectangle( x1, y1, x2, y2 );
		}
		else {
			return gfx_rectangle();
		}
	}

	[[nodiscard]]
	gfx_rectangle join( gfx_rectangle& that ) const {
		gfx_xy_t x1 = std::min( this->get_x1(), that.get_x1() );
		gfx_xy_t y1 = std::min( this->get_y1(), that.get_y1() );
		gfx_xy_t x2 = std::max( this->get_x2(), that.get_x2() );
		gfx_xy_t y2 = std::max( this->get_y2(), that.get_y2() );

		return gfx_rectangle( x1, y1, x2, y2 );
	}

};

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
