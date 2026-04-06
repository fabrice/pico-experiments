//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// gfx_rectangle
//
//----------------------------------------------------------------

#pragma once
#ifndef _GFX_RECTANGLE_H
#define _GFX_RECTANGLE_H

//----------------------------------------------------------------

#include "pico.h"

#include "gfx_types.h"
#include "gfx_point.h"
#include "gfx_dimension.h"

#include <cmath>

//----------------------------------------------------------------

class gfx_rectangle {

private:

	gfx_point _top_left;
	gfx_point _bottom_right;

public:

	gfx_rectangle():
		_top_left(),
		_bottom_right() {
	}

	gfx_rectangle( const gfx_rectangle& that ):
		_top_left( that._top_left ),
		_bottom_right( that._bottom_right ) {
	}

	gfx_rectangle( gfx_xy_t x1, gfx_xy_t y1, gfx_xy_t x2, gfx_xy_t y2 ):
		_top_left( x1, y1 ),
		_bottom_right( x2, y2 ) {
		this->normalize();
	}

	gfx_rectangle( const gfx_point& p1, const gfx_point& p2 ):
		_top_left( p1 ),
		_bottom_right( p2 ) {
		this->normalize();
	}

	gfx_rectangle( const gfx_point& origin, const gfx_dimension& dimension ):
		_top_left( origin ),
		_bottom_right( origin.get_x() + dimension.get_width(), origin.get_y() + dimension.get_height() ) {
		this->normalize();
	}

private:

	void normalize();

private:

	inline gfx_xy_t get_x1() const { return _top_left.get_x(); }
	inline gfx_xy_t get_y1() const { return _top_left.get_y(); }
	inline gfx_xy_t get_x2() const { return _bottom_right.get_x(); }
	inline gfx_xy_t get_y2() const { return _bottom_right.get_y(); }

public:

	inline gfx_xy_t get_left() const { return _top_left.get_x(); }
	inline gfx_xy_t get_top() const { return _top_left.get_y(); }
	inline gfx_xy_t get_right() const { return _bottom_right.get_x(); }
	inline gfx_xy_t get_bottom() const { return _bottom_right.get_y(); }

	void set_left( gfx_xy_t x );
	void set_top( gfx_xy_t y );
	void set_right( gfx_xy_t x );
	void set_bottom( gfx_xy_t y );

	inline gfx_point get_top_left() const { return _top_left; }
	inline gfx_point get_top_right() const { return gfx_point( this->get_left(), this->get_top() ); }
	inline gfx_point get_bottom_left() const { return gfx_point( this->get_left(), this->get_bottom() ); }
	inline gfx_point get_bottom_right() const { return _bottom_right; }

	inline gfx_wh_t get_width() const { return this->get_right() - this->get_left(); }
	inline gfx_wh_t get_height() const { return this->get_bottom() - this->get_top(); }

	inline uint32_t get_area() const { return this->get_dimension().get_area(); }

	inline gfx_dimension get_dimension() const { return gfx_dimension( this->get_width(), this->get_height() ); }
	inline gfx_rectangle get_box() const { return *this; }

	gfx_wh_t get_diagonal() const;

	bool is_null() const;
	bool is_empty() const;

	void constrain( gfx_rectangle& that ) {
		gfx_xy_t x1 = std::max( this->get_x1(), that.get_x1() );
		gfx_xy_t y1 = std::max( this->get_y1(), that.get_y1() );
		gfx_xy_t x2 = std::min( this->get_x2(), that.get_x2() );
		gfx_xy_t y2 = std::min( this->get_y2(), that.get_y2() );

		if ( (x1 < x2) && (y1 < y2) ) {
			_top_left = gfx_point( x1, y1 );
			_bottom_right = gfx_point( x2, y2 );
		}
		else {
			_top_left = gfx_point( 0, 0 );
			_bottom_right = gfx_point( 0, 0 );
		}
	}

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
