//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// écran OLED école
// SSD1309
// proof of concept
//
//----------------------------------------------------------------

#include "oled_fn.h"
#include "oled.h"

#include "pico/stdlib.h"
#include "wire_i2c.h"

#include <cmath>
#include "math_plus.h"
#include <cstring>

//----------------------------------------------------------------

oled_ref oled_init( uint8_t i2c_num, uint8_t address, uint reset_gpio ) {
	wire_ref wire = new wire_i2c( i2c_num, address );
	return new OLED( wire, reset_gpio );
}

//----------------------------------------------------------------

uint16_t oled_get_width( oled_ref oled ) {
	if ( oled == nullptr ) return 0;

	return oled->get_width();
}

//----------------------------------------------------------------

uint16_t oled_get_height( oled_ref oled ) {
	if ( oled == nullptr ) return 0;

	return oled->get_height();
}

//----------------------------------------------------------------

uint16_t oled_get_column_count( oled_ref oled ) {

	if ( oled == nullptr ) return 0;

	return oled->get_column_count();
}

//----------------------------------------------------------------

uint16_t oled_get_line_count( oled_ref oled ) {
	if ( oled == nullptr ) return 0;

	return oled->get_line_count();
}

//----------------------------------------------------------------

void oled_set_on( oled_ref oled, bool on ) {
	if ( oled == nullptr ) return;

	oled->set_on( on );
}

//----------------------------------------------------------------

void oled_set_orientation( oled_ref oled, uint8_t orientation ) {
	if ( oled == nullptr ) return;

	oled->set_orientation ( orientation );
}

//----------------------------------------------------------------

void oled_set_dark_mode( oled_ref oled, bool mode ) {
	if ( oled == nullptr ) return;

	oled->set_dark_mode( mode );
}

//----------------------------------------------------------------

void oled_set_brightness( oled_ref oled, uint8_t brightness ) {
	if ( oled == nullptr ) return;

	oled->set_brightness( brightness );
}

//----------------------------------------------------------------

void oled_set_lico( oled_ref oled, uint8_t line, uint8_t column ) {
	if ( oled == nullptr ) return;

	oled->set_lico( line, column );
}

//----------------------------------------------------------------

void oled_print( oled_ref oled, const char* const text ) {
	if ( oled == nullptr ) return;

	oled->print( text );
}

//----------------------------------------------------------------

void oled_print( oled_ref oled, const char* const text, uint8_t line, uint8_t column ) {
	if ( oled == nullptr ) return;

	oled->print( text, line, column );
}

//----------------------------------------------------------------

void oled_print_center( oled_ref oled, const char* const text, uint8_t line ) {
	if ( oled == nullptr ) return;

	oled->print_center( text, line );
}

//----------------------------------------------------------------

void oled_printf( oled_ref oled, const char* format, ... ) {
	if ( oled == nullptr ) return;

	va_list args;
	va_start( args, format );
	oled->vprintf( format, args );
	va_end( args );
}

//----------------------------------------------------------------

void oled_print( oled_ref oled, char character ) {
	if ( oled == nullptr ) return;

	oled->print( character );
}

//----------------------------------------------------------------

void oled_print( oled_ref oled, char character, uint8_t line, uint8_t column ) {
	if ( oled == nullptr ) return;

	oled->print( character, line, column );
}

//----------------------------------------------------------------

void oled_print_glyph( oled_ref oled, uint8_t glyph[6] ) {
	if ( oled == nullptr ) return;

	oled->print_glyph( glyph );
}

//----------------------------------------------------------------

void oled_draw_bitmap( oled_ref oled, int16_t x, int16_t y, int16_t width, int16_t height, uint8_t* bitmap, uint16_t length ) {
	if ( oled == nullptr ) return;

	oled->draw_bitmap( x, y, width, height, bitmap, length );
}

//----------------------------------------------------------------

void oled_erase( oled_ref oled ) {
	if ( oled == nullptr ) return;

	oled->erase();
}

//----------------------------------------------------------------

void oled_erase_line( oled_ref oled, uint8_t line ) {
	if ( oled == nullptr ) return;

	oled->erase( line );
}

//----------------------------------------------------------------

void oled_erase_character( oled_ref oled, uint8_t line, uint8_t column ) {
	if ( oled == nullptr ) return;

	oled->erase( line, column );
}

//----------------------------------------------------------------

void oled_deinit( oled_ref& oled ) {
	if ( oled == nullptr ) return;

	delete oled;
	oled = nullptr;
}

//----------------------------------------------------------------
