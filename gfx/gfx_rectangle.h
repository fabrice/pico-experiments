//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// gfx_rectangle
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico.h"

#include "gfx_types.h"
#include "gfx_point.h"
#include "gfx_dimension.h"

#include <cmath>

//----------------------------------------------------------------

class gfx_rectangle {

public:

	static const gfx_rectangle ZERO;

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

	explicit gfx_rectangle( const gfx_dimension dimension ):
			_top_left { 0, 0 },
			_bottom_right( 0 + dimension.get_width(), 0 + dimension.get_height() ) {
	}

	constexpr ~gfx_rectangle() noexcept = default;

private:

	void normalize();

public:

	gfx_xy_t get_left() const { return _top_left.get_x(); }
	gfx_xy_t get_top() const { return _top_left.get_y(); }
	gfx_xy_t get_right() const { return _bottom_right.get_x(); }
	gfx_xy_t get_bottom() const { return _bottom_right.get_y(); }

	void set_left( gfx_xy_t left );
	void set_top( gfx_xy_t top );
	void set_right( gfx_xy_t right );
	void set_bottom( gfx_xy_t bottom );

	gfx_point get_top_left() const { return _top_left; }
	gfx_point get_top_right() const { return gfx_point( this->get_left(), this->get_top() ); }
	gfx_point get_bottom_left() const { return gfx_point( this->get_left(), this->get_bottom() ); }
	gfx_point get_bottom_right() const { return _bottom_right; }

	gfx_wh_t get_width() const { return this->get_right() - this->get_left(); }
	gfx_wh_t get_height() const { return this->get_bottom() - this->get_top(); }

	gfx_dimension get_dimension() const { return gfx_dimension( this->get_width(), this->get_height() ); }
	gfx_rectangle get_box() const { return (*this); }

	gfx_area_t get_area() const { return this->get_dimension().get_area(); }

	gfx_wh_t get_diagonal() const;

	bool is_zero() const;
	bool is_empty() const;

	gfx_rectangle& operator=( const gfx_rectangle& rhs );

	gfx_rectangle& operator+=( const gfx_rectangle& rhs );
	gfx_rectangle& operator+=( const gfx_point& rhs );

	gfx_rectangle operator+( const gfx_rectangle& rhs ) const;
	gfx_rectangle operator+( const gfx_point& rhs ) const;

	std::partial_ordering operator<=>( const gfx_rectangle& rhs ) const;
	bool operator<( const gfx_rectangle& rhs ) const { return is_lt( (*this) <=> rhs ); }
	bool operator<=( const gfx_rectangle& rhs ) const { return is_lteq( (*this) <=> rhs ); }
	bool operator==( const gfx_rectangle& rhs ) const { return is_eq( (*this) <=> rhs ); }
	bool operator>=( const gfx_rectangle& rhs ) const { return is_gteq( (*this) <=> rhs ); }
	bool operator>( const gfx_rectangle& rhs ) const { return is_gt( (*this) <=> rhs ); }

	std::weak_ordering operator<=>( const gfx_point& rhs ) const;
	bool operator<( const gfx_point& rhs ) const { return is_lt( (*this) <=> rhs ); }
	bool operator<=( const gfx_point& rhs ) const { return is_lteq( (*this) <=> rhs ); }
	bool operator==( const gfx_point& rhs ) const { return is_eq( (*this) <=> rhs ); }
	bool operator>=( const gfx_point& rhs ) const { return is_gteq( (*this) <=> rhs ); }
	bool operator>( const gfx_point& rhs ) const { return is_gt( (*this) <=> rhs ); }

	// intersection
	[[nodiscard]] gfx_rectangle operator&&( const gfx_rectangle& rhs ) const;
	// union
	[[nodiscard]] gfx_rectangle operator||( const gfx_rectangle& rhs ) const;

	gfx_rectangle& constrain( const gfx_rectangle& that );

};

//----------------------------------------------------------------

static_assert( std::regular< gfx_rectangle > );

//----------------------------------------------------------------
