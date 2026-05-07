//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
//! \file gfx_rectangle
//
//----------------------------------------------------------------

#include "gfx_rectangle.h"

#include "pico.h"

#include "gfx_types.h"
#include "gfx_dimension.h"

#include <cmath>
#include <algorithm>

//----------------------------------------------------------------

const gfx_rectangle gfx_rectangle::ZERO { 0, 0, 0, 0 };

//----------------------------------------------------------------

void gfx_rectangle::normalize() {
	const gfx_xy_t left = std::min( this->get_left(), this->get_right() );
	const gfx_xy_t top = std::min( this->get_top(), this->get_bottom() );
	const gfx_xy_t right = std::max( this->get_left(), this->get_right() );
	const gfx_xy_t bottom = std::max( this->get_top(), this->get_bottom() );

	_top_left.set_xy( left, top );
	_bottom_right.set_xy( right, bottom );
}

//----------------------------------------------------------------

void gfx_rectangle::set_left( gfx_xy_t left ) {
	if ( left > this->get_right() ) return;

	_top_left.set_x( left );
}

//----------------------------------------------------------------

void gfx_rectangle::set_top( gfx_xy_t top ) {
	if ( top > this->get_bottom() ) return;

	_top_left.set_y( top );
}

//----------------------------------------------------------------

void gfx_rectangle::set_right( gfx_xy_t right ) {
	if ( right < this->get_left() ) return;

	_bottom_right.set_x( right );
}

//----------------------------------------------------------------

void gfx_rectangle::set_bottom( gfx_xy_t bottom ) {
	if ( bottom < this->get_top() ) return;

	_bottom_right.set_y( bottom );
}

//----------------------------------------------------------------

gfx_wh_t gfx_rectangle::get_diagonal() const {
	return std::hypot( this->get_width(), this->get_height() );
}

//----------------------------------------------------------------

bool gfx_rectangle::is_zero() const {
	return _top_left.is_zero() && _bottom_right.is_zero();
}

//----------------------------------------------------------------

bool gfx_rectangle::is_empty() const {
	return (this->get_width() == 0) && (this->get_height() == 0);
}

//----------------------------------------------------------------

gfx_rectangle& gfx_rectangle::operator+=( const gfx_rectangle& rhs ) {
	const gfx_xy_t left = std::min( this->get_left(), rhs.get_left() );
	const gfx_xy_t top = std::min( this->get_top(), rhs.get_top() );
	const gfx_xy_t right = std::max( this->get_right(), rhs.get_right() );
	const gfx_xy_t bottom = std::max( this->get_bottom(), rhs.get_bottom() );

	_top_left.set_xy( left, top );
	_bottom_right.set_xy( right, bottom );

	return (*this);
}

//----------------------------------------------------------------

gfx_rectangle& gfx_rectangle::operator+=( const gfx_point& rhs ) {
	const gfx_xy_t left = std::min( this->get_left(), rhs.get_x() );
	const gfx_xy_t top = std::min( this->get_top(), rhs.get_y() );
	const gfx_xy_t right = std::max( this->get_right(), rhs.get_x() );
	const gfx_xy_t bottom = std::max( this->get_bottom(), rhs.get_y() );

	_top_left.set_xy( left, top );
	_bottom_right.set_xy( right, bottom );

	return (*this);
}

//----------------------------------------------------------------

gfx_rectangle gfx_rectangle::operator+( const gfx_rectangle& rhs ) const {
	const gfx_xy_t left = std::min( this->get_left(), rhs.get_left() );
	const gfx_xy_t top = std::min( this->get_top(), rhs.get_top() );
	const gfx_xy_t right = std::max( this->get_right(), rhs.get_right() );
	const gfx_xy_t bottom = std::max( this->get_bottom(), rhs.get_bottom() );

	return gfx_rectangle( left, top, right, bottom );
}

//----------------------------------------------------------------

gfx_rectangle gfx_rectangle::operator+( const gfx_point& rhs ) const {
	const gfx_xy_t left = std::min( this->get_left(), rhs.get_x() );
	const gfx_xy_t top = std::min( this->get_top(), rhs.get_y() );
	const gfx_xy_t right = std::max( this->get_right(), rhs.get_x() );
	const gfx_xy_t bottom = std::max( this->get_bottom(), rhs.get_y() );

	return gfx_rectangle( left, top, right, bottom );
}

//----------------------------------------------------------------

/**
 *	\brief < : inside, == : equal, > : outside, <> : neither
 *	\param rhs a rectangle
 *	\return inside, equal, ouside, neither
 */
std::partial_ordering gfx_rectangle::operator<=>( const gfx_rectangle& rhs ) const {
	const auto left = this->get_left() <=> rhs.get_left();
	const auto top = this->get_top() <=> rhs.get_top();
	const auto right = this->get_right() <=> rhs.get_right();
	const auto bottom = this->get_bottom() <=> rhs.get_bottom();

	// ==
	if ( is_eq( left ) && is_eq( top ) && is_eq( right ) && is_eq( bottom ) ) return std::partial_ordering::equivalent;
	// <
	if ( is_gteq( left ) && is_gteq( top ) && is_lteq( right ) && is_lteq( bottom ) ) return std::partial_ordering::less;
	// >
	if ( is_lteq( left ) && is_lteq( top ) && is_gteq( right ) && is_gteq( bottom ) ) return std::partial_ordering::greater;
	// <>
	return std::partial_ordering::unordered;
}

//----------------------------------------------------------------

/**
 *	\brief < : inside, == : equal, > : outside
 *	\param rhs a point
 *	\return inside, equal, ouside
 */
std::weak_ordering gfx_rectangle::operator<=>( const gfx_point& rhs ) const {
	const auto left = this->get_left() <=> rhs.get_x();
	const auto top = this->get_top() <=> rhs.get_y();
	const auto right = this->get_right() <=> rhs.get_x();
	const auto bottom = this->get_bottom() <=> rhs.get_y();

	// ==
	if ( is_eq( left ) && is_lteq( top ) && is_gteq( right ) && is_gteq( bottom ) ) return std::weak_ordering::equivalent;
	if ( is_lteq( left ) && is_eq( top ) && is_gteq( right ) && is_gteq( bottom ) ) return std::weak_ordering::equivalent;
	if ( is_lteq( left ) && is_lteq( top ) && is_eq( right ) && is_gteq( bottom ) ) return std::weak_ordering::equivalent;
	if ( is_lteq( left ) && is_lteq( top ) && is_gteq( right ) && is_eq( bottom ) ) return std::weak_ordering::equivalent;
	// >
	if ( is_lteq( left ) && is_lteq( top ) && is_gteq( right ) && is_gteq( bottom ) ) return std::weak_ordering::greater;
	// <
	return std::weak_ordering::less;
}

//----------------------------------------------------------------

/**
 *	\brief intersection of two rectangles
 *	\param rhs a rectangle
 *	\return intersection rectangle
 */
gfx_rectangle gfx_rectangle::operator&&( const gfx_rectangle& rhs ) const {
	const gfx_xy_t left = std::max( this->get_left(), rhs.get_left() );
	const gfx_xy_t top = std::max( this->get_top(), rhs.get_top() );
	const gfx_xy_t right = std::min( this->get_right(), rhs.get_right() );
	const gfx_xy_t bottom = std::min( this->get_bottom(), rhs.get_bottom() );

	if ( (left <= right) && (top <= bottom) ) {
		return gfx_rectangle( left, top, right, bottom );
	}
	else {
		return gfx_rectangle( 0, 0, 0, 0 );
	}
}

//----------------------------------------------------------------

/**
 *	\brief union of two rectangles
 *	\param rhs a rectangle
 *	\return union rectangle
 */
gfx_rectangle gfx_rectangle::operator||( const gfx_rectangle& rhs ) const {
	const gfx_xy_t left = std::min( this->get_left(), rhs.get_left() );
	const gfx_xy_t top = std::min( this->get_top(), rhs.get_top() );
	const gfx_xy_t right = std::max( this->get_right(), rhs.get_right() );
	const gfx_xy_t bottom = std::max( this->get_bottom(), rhs.get_bottom() );

	if ( (left <= right) && (top <= bottom) ) {
		return gfx_rectangle( left, top, right, bottom );
	}
	else {
		return gfx_rectangle( 0, 0, 0, 0 );
	}
}

//----------------------------------------------------------------

gfx_rectangle& gfx_rectangle::constrain( const gfx_rectangle& that ) {
	const gfx_xy_t left = std::max( (*this).get_left(), that.get_left() );
	const gfx_xy_t top = std::max( (*this).get_top(), that.get_top() );
	const gfx_xy_t right = std::min( (*this).get_right(), that.get_right() );
	const gfx_xy_t bottom = std::min( (*this).get_bottom(), that.get_bottom() );

	if ( (left < right) && (top < bottom) ) {
		_top_left = gfx_point( left, top );
		_bottom_right = gfx_point( right, bottom );
	}
	else {
		_top_left = gfx_point( 0, 0 );
		_bottom_right = gfx_point( 0, 0 );
	}

	return (*this);
}

//----------------------------------------------------------------
