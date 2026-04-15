//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_image
//
//----------------------------------------------------------------

#include "gfx_image.h"

#include "gfx_dimension.h"

#include <vector>

//----------------------------------------------------------------

gfx_bytemap_data gfx_image::make_yx_bytemap() const {
	gfx_wh_t dybytes = (this->get_dimension().get_height() + 7) / 8;
	gfx_bytemap_data bytemap( this->get_dimension().get_width() * dybytes, 0 );

	for ( gfx_xy_t x = 0 ; x < this->get_dimension().get_width() ; ++ x ) {
		for ( gfx_xy_t y = 0 ; y < this->get_dimension().get_height() ; ++ y ) {
			gfx_xy_t yindex = (y + 7) / 8;
			if ( this->get_pixel_lit( x, y ) ) bytemap[ yindex + x * dybytes ] |= (0x01 << y);
			else bytemap[ yindex + x * dybytes ] &= ~(0x01 << y);
		}
	}

	return bytemap;
}

//----------------------------------------------------------------

std::vector< uint16_t > gfx_image::make_pixmap_565() const {
	gfx_dimension dimension = get_dimension();
	std::vector< uint16_t > pixmap( dimension.get_area() );
	for ( gfx_xy_t y = 0 ; y < dimension.get_height() ; ++ y ) {
		for ( gfx_xy_t x = 0 ; x < dimension.get_width() ; ++ x ) {
			uint16_t color = this->get_pixel( x, y ).to_565();
			pixmap[ x + y * dimension.get_width() ] = (uint16_t)((color & 0x00ff) << 8) | (uint16_t)((color & 0xff00) >> 8);
		}
	}

	return pixmap;
}

//----------------------------------------------------------------
