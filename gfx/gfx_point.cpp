//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// gfx_point
//
//----------------------------------------------------------------

#include "gfx_point.h"

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
