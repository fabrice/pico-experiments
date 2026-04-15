//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// gfx_dimension
//
//----------------------------------------------------------------

#include "gfx_dimension.h"

//----------------------------------------------------------------

std::strong_ordering gfx_dimension::operator<=>( const gfx_dimension& that ) const {
	if ( (_width == that._width) && (_height == that._height) ) return std::strong_ordering::equal;
	if ( (_width < that._width) && (_height < that._height) ) return std::strong_ordering::less;
	if ( (_width > that._width) && (_height > that._height) ) return std::strong_ordering::greater;

	if ( this->get_area() == that.get_area() ) return std::strong_ordering::equivalent;
	if ( this->get_area() < that.get_area() ) return std::strong_ordering::less;
	if ( this->get_area() > that.get_area() ) return std::strong_ordering::greater;

	return std::strong_ordering::equivalent;
}

//----------------------------------------------------------------
