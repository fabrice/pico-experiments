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

	gfx_point _top_left { 0, 0 };
	gfx_point _bottom_right { 0, 0 };

public:

	constexpr gfx_rectangle() = default;

	constexpr gfx_rectangle( const gfx_rectangle& that ):
		_top_left( that._top_left ),
		_bottom_right( that._bottom_right ) {
	}

	gfx_rectangle( gfx_xy_t left, gfx_xy_t top, gfx_xy_t right, gfx_xy_t bottom ):
		_top_left( left, top ),
		_bottom_right( right, bottom ) {
		this->normalize();
	}

	gfx_rectangle( const gfx_point& top_left, const gfx_point& bottom_right ):
		_top_left( top_left ),
		_bottom_right( bottom_right ) {
		this->normalize();
	}

	gfx_rectangle( const gfx_point& top_left, const gfx_dimension& dimension ):
		_top_left( top_left ),
		_bottom_right( top_left.get_x() + dimension.get_width(), top_left.get_y() + dimension.get_height() ) {
		this->normalize();
	}

	constexpr ~gfx_rectangle() = default;

private:

	void normalize();

public:

	inline gfx_xy_t get_left() const { return _top_left.get_x(); }
	inline gfx_xy_t get_top() const { return _top_left.get_y(); }
	inline gfx_xy_t get_right() const { return _bottom_right.get_x(); }
	inline gfx_xy_t get_bottom() const { return _bottom_right.get_y(); }

	void set_left( gfx_xy_t left );
	void set_top( gfx_xy_t top );
	void set_right( gfx_xy_t right );
	void set_bottom( gfx_xy_t bottom );

	inline gfx_point get_top_left() const { return _top_left; }
	inline gfx_point get_top_right() const { return gfx_point( this->get_left(), this->get_top() ); }
	inline gfx_point get_bottom_left() const { return gfx_point( this->get_left(), this->get_bottom() ); }
	inline gfx_point get_bottom_right() const { return _bottom_right; }

	inline gfx_wh_t get_width() const { return this->get_right() - this->get_left(); }
	inline gfx_wh_t get_height() const { return this->get_bottom() - this->get_top(); }

	inline gfx_dimension get_dimension() const { return gfx_dimension( this->get_width(), this->get_height() ); }
	inline gfx_rectangle get_box() const { return *this; }

	inline uint32_t get_area() const { return this->get_dimension().get_area(); }

	gfx_wh_t get_diagonal() const;

	bool is_null() const;
	bool is_empty() const;

	gfx_rectangle& operator+=( const gfx_rectangle& that );
	gfx_rectangle& operator+=( const gfx_point& that );

	gfx_rectangle operator+( const gfx_rectangle& that ) const;
	gfx_rectangle operator+( const gfx_point& that ) const;

	std::partial_ordering operator<=>( const gfx_rectangle& that ) const;
	inline bool operator<( const gfx_rectangle& that ) const { return is_lt( (*this) <=> that ); }
	inline bool operator<=( const gfx_rectangle& that ) const { return is_lteq( (*this) <=> that ); }
	inline bool operator>=( const gfx_rectangle& that ) const { return is_gteq( (*this) <=> that ); }
	inline bool operator>( const gfx_rectangle& that ) const { return is_gt( (*this) <=> that ); }

	std::weak_ordering operator<=>( const gfx_point& that ) const;
	inline bool operator<( const gfx_point& that ) const { return is_lt( (*this) <=> that ); }
	inline bool operator<=( const gfx_point& that ) const { return is_lteq( (*this) <=> that ); }
	inline bool operator>=( const gfx_point& that ) const { return is_gteq( (*this) <=> that ); }
	inline bool operator>( const gfx_point& that ) const { return is_gt( (*this) <=> that ); }

	gfx_rectangle& constrain( const gfx_rectangle& that );

	[[nodiscard]]
	gfx_rectangle intersect( const gfx_rectangle& that ) const;

	[[nodiscard]]
	gfx_rectangle join( const gfx_rectangle& that ) const;

};

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
