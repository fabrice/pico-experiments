//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// gfx_rectangle
//
//----------------------------------------------------------------

#include "pico.h"

#include "gfx_types.h"
#include "gfx_rectangle.h"

#include <cmath>
#include <algorithm>

//----------------------------------------------------------------

void gfx_rectangle::normalize() {
	const gfx_xy_t left = this->get_left();
	const gfx_xy_t top = this->get_top();
	const gfx_xy_t right = this->get_right();
	const gfx_xy_t bottom = this->get_bottom();

	_top_left.set_xy( std::min( left, right ), std::min( top, bottom ) );
	_bottom_right.set_xy( std::max( left, right ), std::max( top, bottom ) );
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

bool gfx_rectangle::is_null() const {
	return _top_left.is_null() && _bottom_right.is_null();
}

//----------------------------------------------------------------

bool gfx_rectangle::is_empty() const {
	return (this->get_width() == 0) && (this->get_height() == 0);
}

//----------------------------------------------------------------

gfx_rectangle& gfx_rectangle::operator+=( const gfx_rectangle& that ) {
	const gfx_xy_t left = std::min( this->get_left(), that.get_left() );
	const gfx_xy_t top = std::min( this->get_top(), that.get_top() );
	const gfx_xy_t right = std::max( this->get_right(), that.get_right() );
	const gfx_xy_t bottom = std::max( this->get_bottom(), that.get_bottom() );

	_top_left.set_xy( left, top );
	_bottom_right.set_xy( right, bottom );

	return *this;
}

//----------------------------------------------------------------

gfx_rectangle& gfx_rectangle::operator+=( const gfx_point& that ) {
	const gfx_xy_t left = std::min( this->get_left(), that.get_x() );
	const gfx_xy_t top = std::min( this->get_top(), that.get_y() );
	const gfx_xy_t right = std::max( this->get_right(), that.get_x() );
	const gfx_xy_t bottom = std::max( this->get_bottom(), that.get_y() );

	_top_left.set_xy( left, top );
	_bottom_right.set_xy( right, bottom );

	return *this;
}

//----------------------------------------------------------------

gfx_rectangle gfx_rectangle::operator+( const gfx_rectangle& that ) const {
	const gfx_xy_t left = std::min( this->get_left(), that.get_left() );
	const gfx_xy_t top = std::min( this->get_top(), that.get_top() );
	const gfx_xy_t right = std::max( this->get_right(), that.get_right() );
	const gfx_xy_t bottom = std::max( this->get_bottom(), that.get_bottom() );

	return gfx_rectangle( left, top, right, bottom );
}

//----------------------------------------------------------------

gfx_rectangle gfx_rectangle::operator+( const gfx_point& that ) const {
	const gfx_xy_t left = std::min( this->get_left(), that.get_x() );
	const gfx_xy_t top = std::min( this->get_top(), that.get_y() );
	const gfx_xy_t right = std::max( this->get_right(), that.get_x() );
	const gfx_xy_t bottom = std::max( this->get_bottom(), that.get_y() );

	return gfx_rectangle( left, top, right, bottom );
}

//----------------------------------------------------------------

std::partial_ordering gfx_rectangle::operator<=>( const gfx_rectangle& that ) const {
	const auto left = this->get_left() <=> that.get_left();
	const auto top = this->get_top() <=> that.get_top();
	const auto right = this->get_right() <=> that.get_right();
	const auto bottom = this->get_bottom() <=> that.get_bottom();

	// ==
	if ( (left == 0) && (top == 0) && (right == 0) && (bottom == 0) ) return std::partial_ordering::equivalent;
	// <
	if ( (left >= 0) && (top >= 0) && (right <= 0) && (bottom <= 0) ) return std::partial_ordering::less;
	// >
	if ( (left <= 0) && (top <= 0) && (right >= 0) && (bottom >= 0) ) return std::partial_ordering::greater;

	return std::partial_ordering::unordered;
}

//----------------------------------------------------------------

std::weak_ordering gfx_rectangle::operator<=>( const gfx_point& that ) const {
	const auto left = this->get_left() <=> that.get_x();
	const auto top = this->get_top() <=> that.get_y();
	const auto right = this->get_right() <=> that.get_x();
	const auto bottom = this->get_bottom() <=> that.get_y();

	// ==
	if ( (left == 0) && (top <= 0) && (right >= 0) && (bottom >= 0) ) return std::weak_ordering::equivalent;
	if ( (left <= 0) && (top == 0) && (right >= 0) && (bottom >= 0) ) return std::weak_ordering::equivalent;
	if ( (left <= 0) && (top <= 0) && (right == 0) && (bottom >= 0) ) return std::weak_ordering::equivalent;
	if ( (left <= 0) && (top <= 0) && (right >= 0) && (bottom == 0) ) return std::weak_ordering::equivalent;
	// <
	if ( (left <= 0) && (top <= 0) && (right >= 0) && (bottom >= 0) ) return std::weak_ordering::less;
	// >
	if ( (left > 0) && (top > 0) && (right < 0) && (bottom < 0) ) return std::weak_ordering::greater;

	return std::weak_ordering::greater;
}

//----------------------------------------------------------------

gfx_rectangle& gfx_rectangle::constrain( const gfx_rectangle& that ) {
	const gfx_xy_t left = std::max( this->get_left(), that.get_left() );
	const gfx_xy_t top = std::max( this->get_top(), that.get_top() );
	const gfx_xy_t right = std::min( this->get_right(), that.get_right() );
	const gfx_xy_t bottom = std::min( this->get_bottom(), that.get_bottom() );

	if ( (left < right) && (top < bottom) ) {
		_top_left = gfx_point( left, top );
		_bottom_right = gfx_point( right, bottom );
	}
	else {
		_top_left = gfx_point( 0, 0 );
		_bottom_right = gfx_point( 0, 0 );
	}

	return *this;
}

//----------------------------------------------------------------

gfx_rectangle gfx_rectangle::intersect( const gfx_rectangle& that ) const {
	const gfx_xy_t left = std::max( this->get_left(), that.get_left() );
	const gfx_xy_t top = std::max( this->get_top(), that.get_top() );
	const gfx_xy_t right = std::min( this->get_right(), that.get_right() );
	const gfx_xy_t bottom = std::min( this->get_bottom(), that.get_bottom() );

	if ( (left < right) && (top < bottom) ) {
		return gfx_rectangle( left, top, right, bottom );
	}
	else {
		return gfx_rectangle();
	}
}

//----------------------------------------------------------------

gfx_rectangle gfx_rectangle::join( const gfx_rectangle& that ) const {
	const gfx_xy_t left = std::min( this->get_left(), that.get_left() );
	const gfx_xy_t top = std::min( this->get_top(), that.get_top() );
	const gfx_xy_t right = std::max( this->get_right(), that.get_right() );
	const gfx_xy_t bottom = std::max( this->get_bottom(), that.get_bottom() );

	return gfx_rectangle( left, top, right, bottom );
}

//----------------------------------------------------------------
