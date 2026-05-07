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
#include "gfx_geometry.h"

#include "gfx_canvas.h"
#include "gfx_pixmap.h"

#include <algorithm>

//----------------------------------------------------------------

gfx_pixmap::gfx_pixmap( const gfx_dimension& dimension ):
		_dimension( dimension ),
		_pixmap( dimension.get_area(), gfx_color_rgb_8::BLACK ) {
}

//----------------------------------------------------------------

gfx_pixmap::gfx_pixmap( gfx_wh_t width, gfx_wh_t height ):
		_dimension { width, height },
		_pixmap( _dimension.get_area(), gfx_color_rgb_8::BLACK ) {
}

//----------------------------------------------------------------

gfx_pixmap::~gfx_pixmap() {
	_pixmap.clear();
}

//----------------------------------------------------------------

gfx_color_bit gfx_pixmap::get_pixel_lit( gfx_xy_t x, gfx_xy_t y ) const {
	if ( gfx_point( x, y ) > this->get_box() ) return false;

	const gfx_wh_t index = x + y * this->get_width();
	return _pixmap[ index ].is_lit();
}

//----------------------------------------------------------------

gfx_color_rgb_8 gfx_pixmap::get_pixel( gfx_xy_t x, gfx_xy_t y ) const {
	if ( gfx_point( x, y ) > this->get_box() ) return gfx_color_rgb_8::BLACK;

	const gfx_wh_t index = x + y * this->get_width();
	return _pixmap[ index ];
}

//----------------------------------------------------------------

void gfx_pixmap::set_pixel( gfx_xy_t x, gfx_xy_t y, gfx_color_bit lit ) {
	if ( gfx_point( x, y ) > this->get_box() ) return;

	const gfx_wh_t index = x + y * this->get_width();
	_pixmap[ index ] = gfx_color_rgb( lit );
}

//----------------------------------------------------------------

void gfx_pixmap::set_pixel( gfx_point point, gfx_color_bit lit ) {
	if ( point > this->get_box() ) return;

	const gfx_wh_t index = point.get_x() + point.get_y() * this->get_width();
	_pixmap[ index ] = gfx_color_rgb( lit );
}

//----------------------------------------------------------------

void gfx_pixmap::set_pixel( gfx_xy_t x, gfx_xy_t y, gfx_color_rgb_8 color ) {
	if ( gfx_point( x, y ) > this->get_box() ) return;

	const gfx_wh_t index = x + y * this->get_width();
	_pixmap[ index ] = color;
}

//----------------------------------------------------------------

void gfx_pixmap::set_pixel( gfx_point point, gfx_color_rgb_8 color ) {
	if ( point > this->get_box() ) return;

	const gfx_wh_t index = point.get_x() + point.get_y() * this->get_width();
	_pixmap[ index ] = color;
}

//----------------------------------------------------------------

void gfx_pixmap::erase() {
	std::ranges::fill( _pixmap, gfx_color_rgb_8::BLACK );
}

//----------------------------------------------------------------

std::vector< uint16_t > gfx_pixmap::make_pixmap_565() const {
	std::vector< uint16_t > pixmap( _dimension.get_area() );
	std::transform( _pixmap.begin(), _pixmap.end(), pixmap.begin(),
		[]( gfx_color_rgb_8 pixel ) -> uint16_t {
			uint16_t color = pixel.to_565();
			return static_cast< uint16_t >(( color & 0x00ff ) << 8) | static_cast< uint16_t >(( color & 0xff00 ) >> 8);
		}
	);

   return pixmap;
}

//----------------------------------------------------------------
