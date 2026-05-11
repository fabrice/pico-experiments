//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// gfx_point
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico.h"

#include "gfx_types.h"

#include <cmath>

//----------------------------------------------------------------

class gfx_point;
class gfx_rectangle;

//----------------------------------------------------------------

class gfx_point {

public:

	static const gfx_point ZERO;

private:

	gfx_xy_t _x { 0 };
	gfx_xy_t _y { 0 };

public:

	constexpr gfx_point() = default;
	constexpr gfx_point( const gfx_point& that ): _x { that._x }, _y { that._y } {}
	constexpr gfx_point( gfx_xy_t x, gfx_xy_t y ): _x { x }, _y { y } {}
	constexpr ~gfx_point() noexcept = default;

	gfx_xy_t get_x() const { return _x; }
	void set_x( gfx_xy_t x ) { _x = x; }

	gfx_xy_t get_y() const { return _y; }
	void set_y( gfx_xy_t y ) { _y = y; }

	void set_xy( gfx_xy_t x, gfx_xy_t y ) { _x = x; _y = y; }

	float get_r() const { return std::hypot( _x, _y ); }
	void set_r( float r );

	float get_phi() const { return std::atan2( _y, _x ); }
	void set_phi( float phi );

	void set_rphi( float r, float phi );
	void set_polar( float r, float phi );

	gfx_point& operator=( const gfx_point& rhs ) { _x = rhs._x; _y = rhs._y; return (*this); }

	gfx_rectangle operator+( const gfx_point& rhs ) const;
	gfx_rectangle operator+( const gfx_rectangle& rhs ) const;

	std::partial_ordering operator<=>( const gfx_point& rhs ) const;
	bool operator<( const gfx_point& rhs ) const { return is_lt( (*this) <=> rhs ); }
	bool operator<=( const gfx_point& rhs ) const { return is_lteq( (*this) <=> rhs ); }
	bool operator==( const gfx_point& rhs ) const { return is_eq( (*this) <=> rhs ); }
	bool operator>=( const gfx_point& rhs ) const { return is_gteq( (*this) <=> rhs ); }
	bool operator>( const gfx_point& rhs ) const { return is_gt( (*this) <=> rhs ); }

	std::weak_ordering operator<=>( const gfx_rectangle& rhs ) const;
	bool operator<( const gfx_rectangle& rhs ) const { return is_lt( (*this) <=> rhs ); }
	bool operator<=( const gfx_rectangle& rhs ) const { return is_lteq( (*this) <=> rhs ); }
	bool operator==( const gfx_rectangle& rhs ) const { return is_eq( (*this) <=> rhs ); }
	bool operator>=( const gfx_rectangle& rhs ) const { return is_gteq( (*this) <=> rhs ); }
	bool operator>( const gfx_rectangle& rhs ) const { return is_gt( (*this) <=> rhs ); }

	bool is_zero() const { return (_x == 0) && (_y == 0); }

	gfx_xy_t get_line( gfx_xy_t line_height ) const { return _y / line_height; }
	gfx_xy_t get_column( gfx_xy_t column_width ) const { return _x / column_width; }
	gfx_point get_lico( gfx_xy_t line_height, gfx_xy_t column_width ) const { return gfx_point( _x / column_width, _y / line_height ); }

};

//----------------------------------------------------------------

static_assert( std::regular< gfx_point > );

//----------------------------------------------------------------
