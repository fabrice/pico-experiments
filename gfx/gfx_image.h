//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_image
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico/stdlib.h"

#include "gfx_types.h"
#include "gfx_geometry.h"
#include "gfx_bytemap_data.h"

#include "gfx_colors.h"

#include "math_plus.h"

#include <vector>

//----------------------------------------------------------------

class gfx_image {

public:

	gfx_image() = default;
	virtual ~gfx_image() = default;

	virtual gfx_dimension get_dimension() const = 0;

	virtual gfx_color_bit get_pixel_lit( gfx_xy_t x, gfx_xy_t y ) const = 0;
	virtual gfx_color_rgb_8 get_pixel( gfx_xy_t x, gfx_xy_t y ) const = 0;

    virtual void set_pixel( gfx_xy_t x, gfx_xy_t y, gfx_color_bit lit ) = 0;
	virtual void set_pixel( gfx_point point, gfx_color_bit lit ) = 0;

    virtual void set_pixel( gfx_xy_t x, gfx_xy_t y, gfx_color_rgb_8 color ) = 0;
	virtual void set_pixel( gfx_point point, gfx_color_rgb_8 color ) = 0;

	virtual void erase() = 0;

	virtual gfx_bytemap_data make_yx_bytemap() const;
	virtual std::vector< uint16_t > make_pixmap_565() const;

};

//----------------------------------------------------------------

inline gfx_dimension gfx_image::get_dimension() const {
	return {};
}

//----------------------------------------------------------------

inline gfx_color_bit gfx_image::get_pixel_lit( gfx_xy_t x, gfx_xy_t y ) const {
	return {};
}

//----------------------------------------------------------------

inline gfx_color_rgb_8 gfx_image::get_pixel( gfx_xy_t x, gfx_xy_t y ) const {
	return {};
}

//----------------------------------------------------------------

inline void gfx_image::set_pixel( gfx_xy_t x, gfx_xy_t y, gfx_color_bit lit ) {
}

//----------------------------------------------------------------

inline void gfx_image::set_pixel( gfx_point point, gfx_color_bit lit ) {
}

//----------------------------------------------------------------

inline void gfx_image::set_pixel( gfx_xy_t x, gfx_xy_t y, gfx_color_rgb_8 color ) {
}

//----------------------------------------------------------------

inline void gfx_image::set_pixel( gfx_point point, gfx_color_rgb_8 color ) {
}

//----------------------------------------------------------------

inline void gfx_image::erase() {
}

//----------------------------------------------------------------
