//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_pixmap
//
//----------------------------------------------------------------

#include "gfx_types.h"
#include "gfx_point.h"
#include "gfx_dimension.h"
#include "gfx_rectangle.h"

#include "gfx_canvas.h"
#include "gfx_pixmap.h"

#include <algorithm>

//----------------------------------------------------------------

gfx_pixmap::gfx_pixmap():
	_dimension() {
	_pixmap.resize( _dimension.get_area(), false );
}

//----------------------------------------------------------------

gfx_pixmap::gfx_pixmap( const gfx_dimension& dimension ):
	_dimension( dimension ) {
	_pixmap.resize( dimension.get_area(), false );
}

//----------------------------------------------------------------

gfx_pixmap::gfx_pixmap( gfx_wh_t width, gfx_wh_t height ):
	_dimension( height, width ) {
	_pixmap.resize( _dimension.get_area(), false );
}

//----------------------------------------------------------------

gfx_pixmap::~gfx_pixmap() {
	_pixmap.clear();
}

//----------------------------------------------------------------

gfx_color_bit gfx_pixmap::get_pixel_lit( gfx_xy_t x, gfx_xy_t y ) const {
	return this->get_pixel( x, y ).is_lit();
}

//----------------------------------------------------------------

gfx_color_rgb gfx_pixmap::get_pixel( gfx_xy_t x, gfx_xy_t y ) const {
	x = constrain<gfx_xy_t>( x, 0, this->get_right() );
	y = constrain<gfx_xy_t>( y, 0, this->get_bottom() );

	size_t index = x + y * this->get_width();
	return _pixmap[ index ];
}

//----------------------------------------------------------------

void gfx_pixmap::set_pixel( gfx_xy_t x, gfx_xy_t y, gfx_color_bit lit ) {
	x = constrain<gfx_xy_t>( x, 0, this->get_right() );
	y = constrain<gfx_xy_t>( y, 0, this->get_bottom() );

	size_t index = x + y * this->get_width();
	_pixmap[ index ] = gfx_color_rgb( lit );
}

//----------------------------------------------------------------

void gfx_pixmap::set_pixel( gfx_point point, gfx_color_bit lit ) {
	this->set_pixel( point.get_x(), point.get_y(), lit );
}

//----------------------------------------------------------------

void gfx_pixmap::set_pixel( gfx_xy_t x, gfx_xy_t y, gfx_color_rgb color ) {
	x = constrain<gfx_xy_t>( x, 0, this->get_right() );
	y = constrain<gfx_xy_t>( y, 0, this->get_bottom() );

	size_t index = x + y * this->get_width();
	_pixmap[ index ] = color;
}

//----------------------------------------------------------------

void gfx_pixmap::set_pixel( gfx_point point, gfx_color_rgb color ) {
	this->set_pixel( point.get_x(), point.get_y(), color );
}

//----------------------------------------------------------------

void gfx_pixmap::erase() {
	for ( size_t index = 0 ; index < _pixmap.size() ; ++ index ) {
		_pixmap[ index ] = gfx_color_rgb::BLACK;
	}
}

//----------------------------------------------------------------

std::vector< uint16_t > gfx_pixmap::make_pixmap_565() const {
	std::vector< uint16_t > pixmap( _dimension.get_area() );
	std::transform( _pixmap.begin(), _pixmap.end(), pixmap.begin(),
		[]( gfx_color_rgb pixel ) -> uint16_t {
			uint16_t color = pixel.to_565();
			return (uint16_t)((color & 0x00ff) << 8) | (uint16_t)((color & 0xff00) >> 8);
		}
	);

   return pixmap;
}

//----------------------------------------------------------------
