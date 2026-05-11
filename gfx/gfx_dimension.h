//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// gfx_dimension
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico.h"

#include "gfx_types.h"

#include <cmath>

//----------------------------------------------------------------

class gfx_dimension;
class gfx_rectangle;

//----------------------------------------------------------------

class gfx_dimension {

public:

	static const gfx_dimension ZERO;

private:

	gfx_wh_t _width { 0 };
	gfx_wh_t _height { 0 };

public:

	constexpr gfx_dimension() = default;

	constexpr gfx_dimension( const gfx_dimension& that ):
		_width { that._width },
		_height { that._height } {
	}

	constexpr gfx_dimension( gfx_wh_t width, gfx_wh_t height ):
		_width { width },
		_height { height } {
	}

	constexpr ~gfx_dimension() noexcept = default;

	gfx_wh_t get_width() const { return _width; }
	gfx_wh_t get_height() const { return _height; }

	gfx_wh_t get_diagonal() const { return std::hypot( _width, _height ); }
	gfx_area_t get_area() const { return (gfx_area_t)_width * (gfx_area_t)_height; }

	bool is_zero() const { return (_width == 0) && (_height == 0); }

	std::strong_ordering operator<=>( const gfx_dimension& that ) const;
	bool operator<( const gfx_dimension& that ) const {
		return is_lt( (*this) <=> that ); }
	bool operator<=( const gfx_dimension& that ) const {
		return is_lteq( (*this) <=> that ); }
	bool operator==( const gfx_dimension& that ) const {
		return is_eq( (*this) <=> that ); }
	bool operator>=( const gfx_dimension& that ) const {
		return is_gteq( (*this) <=> that ); }
	bool operator>( const gfx_dimension& that ) const {
		return is_gt( (*this) <=> that ); }

};

//----------------------------------------------------------------

static_assert( std::regular< gfx_dimension > );

//----------------------------------------------------------------
