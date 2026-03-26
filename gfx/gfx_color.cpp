//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_color
//
//----------------------------------------------------------------
// includes

#include "gfx_color.h"

#include "gfx_color_hsb.h"

#include <cmath>
#include <bit>


//----------------------------------------------------------------

gfx_color::gfx_color( uint8_t red, uint8_t green, uint8_t blue, uint8_t max ):
	red( red ),
	green( green ),
	blue( blue ) {
	if ( max < 1 ) max = 1;
	if ( max < 255 ) {
		float ratio = 255.0 / (float)max;
		this->red = (uint8_t)((float)red * ratio);
		this->green = (uint8_t)((float)green * ratio);
		this->blue = (uint8_t)((float)blue * ratio);
	}
}

//----------------------------------------------------------------

gfx_color::gfx_color( float red, float green, float blue ):
	red( floor( red * 255.0 ) ),
	green( floor( green * 255.0 ) ),
	blue( floor( blue * 255.0 ) ) {
}

//----------------------------------------------------------------

uint8_t gfx_color::to_111() const {
	return (((red >> 7) & 0x01) << 2) | (((green >> 7) & 0x01) << 1) | (((blue >> 7) & 0x01) << 0);
}

//----------------------------------------------------------------

uint8_t gfx_color::to_222() const {
	return (((red >> 6) & 0x03) << 4) | (((green >> 6) & 0x03) << 2) | (((blue >> 6) & 0x03) << 0);
}

//----------------------------------------------------------------

uint8_t gfx_color::to_332() const {
	return (((red >> 5) & 0x07) << 5) | (((green >> 5) & 0x07) << 2) | (((blue >> 6) & 0x03) << 0);
}

//----------------------------------------------------------------

uint16_t gfx_color::to_444() const {
	return ((uint16_t)((red >> 4) & 0x0f) << 8) | ((uint16_t)((green >> 4) & 0x0f) << 4) | ((uint16_t)((blue >> 4) & 0x0f) << 0);
}

//----------------------------------------------------------------

uint16_t gfx_color::to_555() const {
	return ((uint16_t)((red >> 3) & 0x1f) << 10) | ((uint16_t)((green >> 3) & 0x1f) << 5) | ((uint16_t)((blue >> 3) & 0x1f) << 0);
}

//----------------------------------------------------------------

uint16_t gfx_color::to_565() const {
	return ((uint16_t)((red >> 3) & 0x1f) << 11) | ((uint16_t)((green >> 2) & 0x3f) << 5) | ((uint16_t)((blue >> 3) & 0x1f) << 0);
}

//----------------------------------------------------------------

gfx_color_hsb gfx_color::to_hsb() const {
	gfx_color_hsb hsb;

	float cmax = std::max( std::max( red, green ), blue );
	float cmin = std::min( std::min( red, green ), blue );
	float delta = cmax - cmin;

	float hue = 0.0;
	if ( delta != 0 ) {
		if ( cmax == red ) {
			hue = (green - blue) / delta;
		}
		else if ( cmax == green ) {
			hue = (blue - red) / delta + 2.0;
		}
		else if ( cmax == blue ) {
			hue = (red - green) / delta + 4.0;
		}
		hue = fmodf( (hue * 60.0 + 360.0), 360.0 );
	}

	float sat = 0.0;
	if ( cmax != 0 ) {
		sat = delta / cmax;
	}

	float bri = cmax;

	return gfx_color_hsb( hue, sat, bri );
}

//----------------------------------------------------------------
