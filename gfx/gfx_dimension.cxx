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

const gfx_dimension gfx_dimension::ZERO { 0, 0 };

//----------------------------------------------------------------

std::strong_ordering gfx_dimension::operator<=>( const gfx_dimension& that ) const {
	if ( (this->get_width() == that.get_width()) && ((*this).get_height() == that.get_height()) ) return std::strong_ordering::equal;
	if ( (this->get_width() < that.get_width()) && ((*this).get_height() < that.get_height()) ) return std::strong_ordering::less;
	if ( (this->get_width() > that.get_width()) && ((*this).get_height() > that.get_height()) ) return std::strong_ordering::greater;

	if ( this->get_area() == that.get_area() ) return std::strong_ordering::equivalent;
	if ( this->get_area() < that.get_area() ) return std::strong_ordering::less;
	if ( this->get_area() > that.get_area() ) return std::strong_ordering::greater;

	return std::strong_ordering::equivalent;
}

//----------------------------------------------------------------
