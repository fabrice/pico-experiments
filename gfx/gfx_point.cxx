//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// gfx_point
//
//----------------------------------------------------------------

#include "gfx_point.h"

#include "gfx_rectangle.h"

#include <cmath>

//----------------------------------------------------------------

void gfx_point::set_r( float r ) {
	float phi = this->get_phi();
	this->set_polar( r, phi );
}

//----------------------------------------------------------------

void gfx_point::set_phi( float phi ) {
	float r = this->get_r();
	this->set_polar( r, phi );
}

//----------------------------------------------------------------

void gfx_point::set_rphi( float r, float phi ) {
	_x = std::round( std::abs( r ) * std::sin( phi ) );
	_y = std::round( std::abs( r ) * std::cos( phi ) );
}

//----------------------------------------------------------------

void gfx_point::set_polar( float r, float phi ) {
	_x = std::round( std::abs( r ) * std::sin( phi ) );
	_y = std::round( std::abs( r ) * std::cos( phi ) );
}

//----------------------------------------------------------------

gfx_rectangle gfx_point::operator+( const gfx_point& that ) const {
	const gfx_xy_t left = std::min( this->get_x(), that.get_x() );
	const gfx_xy_t top = std::min( this->get_y(), that.get_y() );
	const gfx_xy_t right = std::max( this->get_x(), that.get_x() );
	const gfx_xy_t bottom = std::max( this->get_y(), that.get_y() );

	return gfx_rectangle( left, top, right, bottom );
}

//----------------------------------------------------------------

gfx_rectangle gfx_point::operator+( const gfx_rectangle& that ) const {
	const gfx_xy_t left = std::min( this->get_x(), that.get_left() );
	const gfx_xy_t top = std::min( this->get_y(), that.get_top() );
	const gfx_xy_t right = std::max( this->get_x(), that.get_right() );
	const gfx_xy_t bottom = std::max( this->get_y(), that.get_bottom() );

	return gfx_rectangle( left, top, right, bottom );
}

//----------------------------------------------------------------

std::partial_ordering gfx_point::operator<=>( const gfx_point& that ) const {
	const auto x = this->get_x() <=> that.get_x();
	const auto y = this->get_y() <=> that.get_y();

	// ==
	if ( (x == 0) && (y == 0) ) return std::partial_ordering::equivalent;
	// <
	if ( !((x >= 0) && (y >= 0)) ) return std::partial_ordering::less;
	// >
	if ( !((x <= 0) && (y <= 0)) ) return std::partial_ordering::greater;

	return std::partial_ordering::unordered;
}

//----------------------------------------------------------------
