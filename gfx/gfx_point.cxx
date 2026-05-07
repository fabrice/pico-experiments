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

const gfx_point gfx_point::ZERO { 0, 0 };

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

gfx_rectangle gfx_point::operator+( const gfx_point& rhs ) const {
	const gfx_xy_t left = std::min( (*this).get_x(), rhs.get_x() );
	const gfx_xy_t top = std::min( (*this).get_y(), rhs.get_y() );
	const gfx_xy_t right = std::max( (*this).get_x(), rhs.get_x() );
	const gfx_xy_t bottom = std::max( (*this).get_y(), rhs.get_y() );

	return gfx_rectangle( left, top, right, bottom );
}

//----------------------------------------------------------------

gfx_rectangle gfx_point::operator+( const gfx_rectangle& rhs ) const {
	const gfx_xy_t left = std::min( (*this).get_x(), rhs.get_left() );
	const gfx_xy_t top = std::min( (*this).get_y(), rhs.get_top() );
	const gfx_xy_t right = std::max( (*this).get_x(), rhs.get_right() );
	const gfx_xy_t bottom = std::max( (*this).get_y(), rhs.get_bottom() );

	return gfx_rectangle( left, top, right, bottom );
}

//----------------------------------------------------------------

/**
 *	\brief < : quadrant 4, == : equal, > : quadrant 2, <> : quadrants 1 & 3
 *	\param rhs a point
 *	\return quadrant
 */
std::partial_ordering gfx_point::operator<=>( const gfx_point& rhs ) const {
	const auto x = (*this).get_x() <=> rhs.get_x();
	const auto y = (*this).get_y() <=> rhs.get_y();

	// ==
	if ( is_eq( x ) && is_eq( y ) ) return std::partial_ordering::equivalent;
	// <
	if ( is_lteq( x ) && is_lteq( y ) ) return std::partial_ordering::less;
	// >
	if ( is_gteq( x ) && is_gteq( y ) ) return std::partial_ordering::greater;
	// <>
	return std::partial_ordering::unordered;
}

//----------------------------------------------------------------

/**
 *	\brief < : inside, == : equal, > : outside
 *	\param rhs a rectangle
 *	\return inside, equal, ouside
 */
std::weak_ordering gfx_point::operator<=>( const gfx_rectangle& rhs ) const {
	const auto left = (*this).get_x() <=> rhs.get_left();
	const auto top = (*this).get_y() <=> rhs.get_top();
	const auto right = (*this).get_x() <=> rhs.get_right();
	const auto bottom = (*this).get_y() <=> rhs.get_bottom();

	// ==
	if ( is_eq( left ) && is_gteq( top ) && is_lteq( right ) && is_lteq( bottom ) ) return std::weak_ordering::equivalent;
	if ( is_gteq( left ) && is_eq( top ) && is_lteq( right ) && is_lteq( bottom ) ) return std::weak_ordering::equivalent;
	if ( is_gteq( left ) && is_gteq( top ) && is_eq( right ) && is_lteq( bottom ) ) return std::weak_ordering::equivalent;
	if ( is_gteq( left ) && is_gteq( top ) && is_lteq( right ) && is_eq( bottom ) ) return std::weak_ordering::equivalent;
	// <
	if ( is_gteq( left ) && is_gteq( top ) && is_lteq( right ) && is_lteq( bottom ) ) return std::weak_ordering::less;
	// >
	if ( is_lt( left ) || is_lt( top ) || is_gt( right ) || is_gt( bottom ) ) return std::weak_ordering::greater;

	return std::weak_ordering::greater;
}

//----------------------------------------------------------------
