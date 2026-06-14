//----------------------------------------------------------------

#include "neopixels_fn.h"

//----------------------------------------------------------------

neopixels* neopixels_init( uint gpio ) {
	return neopixels::make( gpio );
}

//----------------------------------------------------------------

void neopixels_deinit( neopixels*& that ) {
	if ( that != nullptr ) {
		delete that;
		that = nullptr;
	}
}

//----------------------------------------------------------------

void neopixels_start( const neopixels* that ) {
	if ( that == nullptr ) return;

	that->start();
}

//----------------------------------------------------------------

void neopixels_send_reset( const neopixels* that ) {
	if ( that == nullptr ) return;

	that->send_reset();
}

//----------------------------------------------------------------

void neopixels_send_rgb( const neopixels* that, uint8_t red, uint8_t green, uint8_t blue ) {
	if ( that == nullptr ) return;

	that->send_rgb( red, green, blue );
}

//----------------------------------------------------------------

void neopixels_send_rgbw( const neopixels* that, uint8_t red, uint8_t green, uint8_t blue, uint8_t white ) {
	if ( that == nullptr ) return;

	that->send_rgbw( red, green, blue, white );
}

//----------------------------------------------------------------

void neopixels_send_white( const neopixels* that, uint8_t white ) {
	if ( that == nullptr ) return;

	that->send_white( white );
}

//----------------------------------------------------------------

void neopixels_send_black( const neopixels* that ) {
	if ( that == nullptr ) return;

	that->send_black();
}

//----------------------------------------------------------------

void neopixels_send_many_black( const neopixels* that, size_t count ) {
	if ( that == nullptr ) return;

	that->send_many_black( count );
}

//----------------------------------------------------------------

void neopixels_send_all_rgb( const neopixels* that, uint8_t red, uint8_t green, uint8_t blue ) {
	if ( that == nullptr ) return;

	that->send_all_rgb( red, green, blue );
}

//----------------------------------------------------------------

void neopixels_send_all_rgbw( const neopixels* that, uint8_t red, uint8_t green, uint8_t blue, uint8_t white ) {
	if ( that == nullptr ) return;

	that->send_all_rgbw( red, green, blue, white );
}

//----------------------------------------------------------------

void neopixels_send_all_white( const neopixels* that, uint8_t white ) {
	if ( that == nullptr ) return;

	that->send_all_white( white );
}

//----------------------------------------------------------------

void neopixels_send_all_black( const neopixels* that ) {
	if ( that == nullptr ) return;

	that->send_all_black();
}

//----------------------------------------------------------------

void neopixels_finish( const neopixels* that ) {
	if ( that == nullptr ) return;

	that->finish();
}

//----------------------------------------------------------------
