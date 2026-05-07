//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// ui_leds_fn
//
//----------------------------------------------------------------

#include "ui_leds_fn.h"

#include "ui_leds.h"

#include <cstdint>

//----------------------------------------------------------------

namespace local {

ui_leds* leds = nullptr;

}

//----------------------------------------------------------------

int ui_leds_init() {
	if ( local::leds != nullptr ) return PICO_ERROR_GENERIC;

	auto that = new ui_leds();
	local::leds = that;

	return PICO_OK;
}

//----------------------------------------------------------------

void ui_leds_set_title( const std::string_view& text ) {
	if ( local::leds == nullptr ) return;

	local::leds->set_title( text );
}

//----------------------------------------------------------------

void ui_leds_set_title( ui_leds* that, const std::string_view& text ) {
	if ( that == nullptr ) return;

	that->set_title( text );
}

//----------------------------------------------------------------

void ui_leds_set_message( const std::string_view& text ) {
	if ( local::leds == nullptr ) return;

	local::leds->set_message( text );
}

//----------------------------------------------------------------

void ui_leds_set_message( ui_leds* that, const std::string_view& text ) {
	if ( that == nullptr ) return;

	that->set_message( text );
}

//----------------------------------------------------------------

uint ui_leds_get_led_count() {
	if ( local::leds == nullptr ) return 0;

	return local::leds->get_led_count();
}

//----------------------------------------------------------------

uint ui_leds_get_led_count( const ui_leds* that ) {
	if ( that == nullptr ) return 0;

	return that->get_led_count();
}

//----------------------------------------------------------------

uint32_t ui_leds_get_leds() {
	if ( local::leds == nullptr ) return 0;

	return local::leds->get_leds();
}

//----------------------------------------------------------------

uint32_t ui_leds_get_leds( const ui_leds* that ) {
	if ( that == nullptr ) return 0;

	return that->get_leds();
}

//----------------------------------------------------------------

bool ui_leds_get_led( uint num ) {
	if ( local::leds == nullptr ) return false;

	return local::leds->get_led( num );
}

//----------------------------------------------------------------

bool ui_leds_get_led( const ui_leds* that, uint num ) {
	if ( that == nullptr ) return false;

	return that->get_led( num );
}

//----------------------------------------------------------------

void ui_leds_put_leds( uint32_t leds ) {
	if ( local::leds == nullptr ) return;

	local::leds->put_leds( leds );
}

//----------------------------------------------------------------

void ui_leds_put_leds( ui_leds* that, uint32_t leds ) {
	if ( that == nullptr ) return;

	that->put_leds( leds );
}

//----------------------------------------------------------------

void ui_leds_put_led( uint num, bool on ) {
	if ( local::leds == nullptr ) return;

	local::leds->put_led( num, on );
}

//----------------------------------------------------------------

void ui_leds_put_led( ui_leds* that, uint num, bool on ) {
	if ( that == nullptr ) return;

	that->put_led( num, on );
}

//----------------------------------------------------------------

void ui_leds_set_led( uint num ) {
	if ( local::leds == nullptr ) return;

	local::leds->set_led( num );
}

//----------------------------------------------------------------

void ui_leds_set_led( ui_leds* that, uint num ) {
	if ( that == nullptr ) return;

	that->set_led( num );
}

//----------------------------------------------------------------

void ui_leds_clr_led( uint num ) {
	if ( local::leds == nullptr ) return;

	local::leds->clr_led( num );
}

//----------------------------------------------------------------

void ui_leds_clr_led( ui_leds* that, uint num ) {
	if ( that == nullptr ) return;

	that->clr_led( num );
}

//----------------------------------------------------------------

void ui_leds_xor_led( uint num ) {
	if ( local::leds == nullptr ) return;

	local::leds->xor_led( num );
}

//----------------------------------------------------------------

void ui_leds_xor_led( ui_leds* that, uint num ) {
	if ( that == nullptr ) return;

	that->xor_led( num );
}

//----------------------------------------------------------------

void ui_leds_set_color( bool red, bool green, bool blue ) {
	if ( local::leds == nullptr ) return;

	local::leds->set_color( red, green, blue );
}

//----------------------------------------------------------------

void ui_leds_set_color( ui_leds* that, bool red, bool green, bool blue ) {
	if ( that == nullptr ) return;

	that->set_color( red, green, blue );
}

//----------------------------------------------------------------

void ui_leds_deinit() {
	if ( local::leds == nullptr ) return;

	delete local::leds;
	local::leds = nullptr;
}

//----------------------------------------------------------------

void ui_leds_deinit( ui_leds*& that ) {
	if ( that == nullptr ) return;

	if ( local::leds == that ) local::leds = nullptr;
	delete that;
	that = nullptr;
}

//----------------------------------------------------------------
