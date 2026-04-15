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

class gfx_dimension {

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

	constexpr ~gfx_dimension() = default;

	inline gfx_wh_t get_width() const { return _width; }
	inline gfx_wh_t get_height() const { return _height; }

	inline gfx_wh_t get_diagonal() const { return std::hypot( _width, _height ); }
	inline uint32_t get_area() const { return (uint32_t)_width * (uint32_t)_height; }

	inline bool is_empty() const { return (_width == 0) && (_height == 0); }

	std::strong_ordering operator<=>( const gfx_dimension& that ) const;

};

//----------------------------------------------------------------
