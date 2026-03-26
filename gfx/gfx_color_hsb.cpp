//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_color_hsb
//
//----------------------------------------------------------------
// includes

#include "gfx_color_hsb.h"

#include "gfx_color.h"

#include <cmath>
#include "math_plus.h"


//----------------------------------------------------------------

gfx_color_hsb::gfx_color_hsb( uint16_t hue, uint8_t sat, uint8_t bri ):
	hue( hue ),
	sat( (float)sat / 255.0 ),
	bri( (float)bri / 255.0 ) {
}

//----------------------------------------------------------------

gfx_color_hsb::gfx_color_hsb( const gfx_color_hsb& that ):
    hue( that.hue ),
    sat( that.sat ),
    bri( that.bri ) {
    this->hue = std::fmod( std::abs( this->hue ), 360.0 );
    this->sat = std::abs( this->sat );
    this->sat = constrain( this->sat, 0.0, 1.0 );
    this->bri = std::abs( this->bri );
    this->bri = constrain( this->bri, 0.0, 1.0 );
}

//----------------------------------------------------------------

uint8_t gfx_color_hsb::get_lit() const {
	return floor( (1.0 - this->sat / 2.0) * this->bri * 100.0 );
}

//----------------------------------------------------------------

uint8_t gfx_color_hsb::get_chroma() const {
	return floor( this->sat * this->bri * 100.0 );
}

//----------------------------------------------------------------

gfx_color gfx_color_hsb::to_rgb() const {
	float chroma = this->sat * this->bri;
	float H = this->hue / 60.0;
	float X = chroma * (1.0 - fabsf( fmodf( H , 2.0 ) - 1.0 ));

	float red = 0;
	float green = 0;
	float blue = 0;

	if ( (H >= 0.0) && (H <= 1.0) ) {
		red = chroma;
		green = X;
		blue = 0.0;
	}
	else if ( (H > 1.0) && (H <= 2.0) ) {
		red = X;
		green = chroma;
		blue = 0.0;
	}
	else if ( (H > 2.0) && (H <= 3.0) ) {
		red = 0.0;
		green = chroma;
		blue = X;
	}
	else if ( (H > 3.0) && (H <= 4.0) ) {
		red = 0.0;
		green = X;
		blue = chroma;
	}
	else if ( (H > 4.0) && (H <= 5.0) ) {
		red = X;
		green = 0.0;
		blue = chroma;
	}
	else if ( (H > 5.0) && (H <= 6.0) ) {
		red = chroma;
		green = 0.0;
		blue = X;
	}
	else {
		red = 0.0;
		green = 0.0;
		blue = 0.0;
	}

	float m = this->bri - chroma;
	red += m;
	green += m;
	blue += m;

	return gfx_color( red, green, blue );
}

//----------------------------------------------------------------
