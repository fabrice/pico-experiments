//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_bitmap
//
//----------------------------------------------------------------

#pragma once
#ifndef _GFX_BITMAP_H
#define _GFX_BITMAP_H

//----------------------------------------------------------------

#include "pico/stdlib.h"

#include "gfx_types.h"
#include "gfx_geometry.h"
#include "gfx_colors.h"
#include "gfx_image.h"

#include "math_plus.h"

#include <vector>

//----------------------------------------------------------------

class gfx_bitmap : public virtual gfx_image {

private:

	gfx_dimension _dimension { 0, 0 };
	gfx_bytemap_data _bytemap { size_t(0) };

public:

	gfx_bitmap() = delete;
	explicit gfx_bitmap( const gfx_dimension& dimension );
	gfx_bitmap( gfx_wh_t width, gfx_wh_t height );
	virtual ~gfx_bitmap() override;

	inline gfx_wh_t get_width() const { return _dimension.get_width(); }
	inline gfx_wh_t get_height() const { return _dimension.get_height(); }

	inline gfx_xy_t get_right() const { return _dimension.get_width(); }
	inline gfx_xy_t get_bottom() const { return _dimension.get_height(); }

	virtual gfx_dimension get_dimension() const override { return _dimension; }
	inline gfx_rectangle get_box() const { return gfx_rectangle( gfx_point( 0, 0 ), _dimension ); }

	virtual gfx_color_bit get_pixel_lit( gfx_xy_t x, gfx_xy_t y ) const override;
	virtual gfx_color_rgb get_pixel( gfx_xy_t x, gfx_xy_t y ) const override;

	virtual void set_pixel( gfx_xy_t x, gfx_xy_t y, gfx_color_bit lit ) override;
	virtual void set_pixel( gfx_point point, gfx_color_bit lit ) override;

	virtual void set_pixel( gfx_xy_t x, gfx_xy_t y, gfx_color_rgb color ) override;
	virtual void set_pixel( gfx_point point, gfx_color_rgb color ) override;

	virtual void erase() override;

};

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
