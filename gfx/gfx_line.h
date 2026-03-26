//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// gfx_line
//
//----------------------------------------------------------------

#pragma once
#ifndef _GFX_LINE_H
#define _GFX_LINE_H

//----------------------------------------------------------------

#include "pico.h"

#include "gfx_point.h"

#include <cmath>


//----------------------------------------------------------------

class gfx_line {

private:

	gfx_point left;
	gfx_point right;

public:

	gfx_line():
		left(),
		right() {
	}

	gfx_line( const gfx_line& that ):
		left( that.left ),
		right( that.right ) {
	}

	gfx_line( gfx_xy_t x1, gfx_xy_t y1, gfx_xy_t x2, gfx_xy_t y2 ):
		left( x1, y1 ),
		right( x2, y2 ) {
		this->normalize();
	}

	gfx_line( gfx_point& p1, gfx_point& p2 ):
		left( p1 ),
		right( p2 ) {
		this->normalize();
	}

private:
	void normalize() {
		if ( this->left.get_x() > this->right.get_x() ) {
			gfx_point point = this->left;
			this->left = this->right;
			this->right = point;
		}
	}

public:

	inline gfx_xy_t get_x1() const { return this->left.get_x(); }
	inline gfx_xy_t get_y1() const { return this->left.get_y(); }
	inline gfx_xy_t get_x2() const { return this->right.get_x(); }
	inline gfx_xy_t get_y2() const { return this->right.get_y(); }

	inline gfx_point get_left() const { return this->left; }
	inline gfx_point get_right() const { return this->right; }

	inline gfx_xy_t get_width() const { return std::abs( this->get_x2() - this->get_x1() ); }
	inline gfx_xy_t get_height() const { return std::abs( this->get_y2() - this->get_y1() ); }
	inline gfx_xy_t get_length() const { return std::hypot( this->get_width(), this->get_height() ); }

	inline bool is_null() const { return this->left.is_null() && this->right.is_null(); }
	inline bool is_empty() const { return (this->get_width() == 0) && (this->get_height() == 0); }

};

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
