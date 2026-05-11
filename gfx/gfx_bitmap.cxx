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
#include "gfx_bytemap_data.h"

#include "gfx_canvas.h"
#include "gfx_bitmap.h"

//----------------------------------------------------------------

gfx_bitmap::gfx_bitmap( const gfx_dimension& dimension ):
		_dimension( dimension ),
		_bytemap( (dimension.get_area() + 7) / 8, 0x00 ) {
}

//----------------------------------------------------------------

gfx_bitmap::gfx_bitmap( gfx_wh_t width, gfx_wh_t height ):
		_dimension( width, height ),
		_bytemap( (_dimension.get_area() + 7) / 8, 0x00 ) {
}

//----------------------------------------------------------------

gfx_bitmap::~gfx_bitmap() noexcept {
	_bytemap.clear();
}

//----------------------------------------------------------------

gfx_color_bit gfx_bitmap::get_pixel_lit( gfx_xy_t x, gfx_xy_t y ) const {
	if ( gfx_point( x, y ) > this->get_box() ) return false;

	const gfx_xy_t index = x + y * this->get_width();
	return _bytemap.get_bit( index );
}

//----------------------------------------------------------------

gfx_color_rgb_8 gfx_bitmap::get_pixel( gfx_xy_t x, gfx_xy_t y ) const {
	if ( gfx_point( x, y ) > this->get_box() ) return gfx_color_rgb_8::BLACK;

	const gfx_xy_t index = x + y * this->get_width();
	return _bytemap.get_bit( index ) ? gfx_color_rgb_8::WHITE : gfx_color_rgb_8::BLACK;
}

//----------------------------------------------------------------

void gfx_bitmap::set_pixel( gfx_xy_t x, gfx_xy_t y, gfx_color_bit lit ) {
	if ( gfx_point( x, y ) > this->get_box() ) return;

	const gfx_xy_t index = x + y * this->get_width();
	_bytemap.set_bit( index, lit );
}

//----------------------------------------------------------------

void gfx_bitmap::set_pixel( gfx_point point, gfx_color_bit lit ) {
	if ( point > this->get_box() ) return;

	const gfx_xy_t index = point.get_x() + point.get_y() * this->get_width();
	_bytemap.set_bit( index, lit );
}

//----------------------------------------------------------------

void gfx_bitmap::set_pixel( gfx_xy_t x, gfx_xy_t y, gfx_color_rgb_8 color ) {
	if ( gfx_point( x, y ) > this->get_box() ) return;

	const gfx_xy_t index = x + y * this->get_width();
	_bytemap.set_bit( index, color.is_lit() );
}

//----------------------------------------------------------------

void gfx_bitmap::set_pixel( gfx_point point, gfx_color_rgb_8 color ) {
	if ( point > this->get_box() ) return;

	const gfx_xy_t index = point.get_x() + point.get_y() * this->get_width();
	_bytemap.set_bit( index, color.is_lit() );
}

//----------------------------------------------------------------

void gfx_bitmap::erase() {
	_bytemap.fill( 0 );
}

//----------------------------------------------------------------
