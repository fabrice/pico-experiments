//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_bitmap
//
//----------------------------------------------------------------

#include "gfx_types.h"
#include "gfx_geometry.h"
#include "gfx_color_rgb.h"
#include "gfx_bytemap.h"

#include "gfx_canvas.h"
#include "gfx_bitmap.h"

//----------------------------------------------------------------

gfx_bitmap::gfx_bitmap( const gfx_dimension& dimension ):
	_dimension( dimension ),
	_bytemap( (_dimension.get_area() + 7) / 8, 0x00 ) {
}

//----------------------------------------------------------------

gfx_bitmap::gfx_bitmap( gfx_wh_t width, gfx_wh_t height ):
	_dimension( width, height ),
	_bytemap( (_dimension.get_area() + 7) / 8, 0x00 ) {
}

//----------------------------------------------------------------

gfx_bitmap::~gfx_bitmap() {
	_bytemap.clear();
}

//----------------------------------------------------------------

gfx_color_bit gfx_bitmap::get_pixel_lit( gfx_xy_t x, gfx_xy_t y ) const {
	x = constrain<gfx_xy_t>( x, 0, this->get_right() );
	y = constrain<gfx_xy_t>( y, 0, this->get_bottom() );

	gfx_xy_t index = x + y * this->get_width();
	return bytemap_get_bit( _bytemap, index );
}

//----------------------------------------------------------------

gfx_color_rgb gfx_bitmap::get_pixel( gfx_xy_t x, gfx_xy_t y ) const {
	return this->get_pixel_lit( x, y ) ? gfx_color_rgb::WHITE : gfx_color_rgb::BLACK;
}

//----------------------------------------------------------------

void gfx_bitmap::set_pixel( gfx_xy_t x, gfx_xy_t y, gfx_color_bit lit ) {
	x = constrain<gfx_xy_t>( x, 0, this->get_right() );
	y = constrain<gfx_xy_t>( y, 0, this->get_bottom() );

	gfx_xy_t index = x + y * this->get_width();
	bytemap_set_bit( _bytemap, index, lit );
}

//----------------------------------------------------------------

void gfx_bitmap::set_pixel( gfx_point point, gfx_color_bit lit ) {
	this->set_pixel( point.get_x(), point.get_y(), lit );
}

//----------------------------------------------------------------

void gfx_bitmap::set_pixel( gfx_xy_t x, gfx_xy_t y, gfx_color_rgb color ) {
	this->set_pixel( x, y, color.is_lit() );
}

//----------------------------------------------------------------

void gfx_bitmap::set_pixel( gfx_point point, gfx_color_rgb color ) {
	this->set_pixel( point, color.is_lit() );
}

//----------------------------------------------------------------

void gfx_bitmap::erase() {
	std::ranges::fill( _bytemap, 0 );
}

//----------------------------------------------------------------
