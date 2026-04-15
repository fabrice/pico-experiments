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

oled_ptr oled_init( uint8_t i2c_num, uint8_t address, uint reset_gpio ) {
	return OLED::make( i2c_num, address, reset_gpio );
}

//----------------------------------------------------------------

uint16_t oled_get_width( const oled_ptr oled ) {
	if ( oled == nullptr ) return 0;

	return oled->get_width();
}

//----------------------------------------------------------------

uint16_t oled_get_height( const oled_ptr oled ) {
	if ( oled == nullptr ) return 0;

	return oled->get_height();
}

//----------------------------------------------------------------

uint16_t oled_get_column_count( const oled_ptr oled ) {
	if ( oled == nullptr ) return 0;

	return oled->get_column_count();
}

//----------------------------------------------------------------

uint16_t oled_get_line_count( const oled_ptr oled ) {
	if ( oled == nullptr ) return 0;

	return oled->get_line_count();
}

//----------------------------------------------------------------

void oled_set_on( oled_ptr oled, bool on ) {
	if ( oled == nullptr ) return;

	oled->set_on( on );
}

//----------------------------------------------------------------

void oled_set_orientation( oled_ptr oled, uint8_t orientation ) {
	if ( oled == nullptr ) return;

	oled->set_orientation ( orientation );
}

//----------------------------------------------------------------

void oled_set_dark_mode( oled_ptr oled, bool mode ) {
	if ( oled == nullptr ) return;

	oled->set_dark_mode( mode );
}

//----------------------------------------------------------------

void oled_set_brightness( oled_ptr oled, uint8_t brightness ) {
	if ( oled == nullptr ) return;

	oled->set_brightness( brightness );
}

//----------------------------------------------------------------

void oled_set_brightness_db( oled_ptr oled, float brightness_db ) {
	if ( oled == nullptr ) return;

	oled->set_brightness_db( brightness_db );
}

//----------------------------------------------------------------

void oled_set_lico( oled_ptr oled, uint8_t line, uint8_t column ) {
	if ( oled == nullptr ) return;

	oled->set_lico( line, column );
}

//----------------------------------------------------------------

void oled_print( oled_ptr oled, const char* text ) {
	if ( oled == nullptr ) return;

	oled->print( text );
}

//----------------------------------------------------------------

void oled_print( oled_ptr oled, const char* text, uint8_t line, uint8_t column ) {
	if ( oled == nullptr ) return;

	oled->print( text, line, column );
}

//----------------------------------------------------------------

void oled_print_left( oled_ptr oled, const char* text, uint8_t line ) {
	if ( oled == nullptr ) return;

	oled->print_left( text, line );
}

//----------------------------------------------------------------

void oled_print_center( oled_ptr oled, const char* text, uint8_t line ) {
	if ( oled == nullptr ) return;

	oled->print_center( text, line );
}

//----------------------------------------------------------------

void oled_print_right( oled_ptr oled, const char* text, uint8_t line ) {
	if ( oled == nullptr ) return;

	oled->print_right( text, line );
}

//----------------------------------------------------------------

void oled_printf( oled_ptr oled, const char* format, ... ) {
	if ( oled == nullptr ) return;

	va_list args;
	va_start( args, format );
	oled->vprintf( format, args );
	va_end( args );
}

//----------------------------------------------------------------

void oled_print( oled_ptr oled, char character ) {
	if ( oled == nullptr ) return;

	oled->print( character );
}

//----------------------------------------------------------------

void oled_print( oled_ptr oled, char character, uint8_t line, uint8_t column ) {
	if ( oled == nullptr ) return;

	oled->print( character, line, column );
}

//----------------------------------------------------------------

void oled_print_glyph( oled_ptr oled, const uint8_t glyph[6] ) {
	if ( oled == nullptr ) return;

	oled->print_glyph( glyph );
}

//----------------------------------------------------------------

void oled_draw_bitmap( oled_ptr oled, int16_t x, int16_t y, int16_t width, int16_t height, const uint8_t* bitmap, uint16_t length ) {
	if ( oled == nullptr ) return;

	oled->draw_bitmap( x, y, width, height, bitmap, length );
}

//----------------------------------------------------------------

void oled_erase( oled_ptr oled ) {
	if ( oled == nullptr ) return;

	oled->erase();
}

//----------------------------------------------------------------

void oled_erase_line( oled_ptr oled, uint8_t line ) {
	if ( oled == nullptr ) return;

	oled->erase( line );
}

//----------------------------------------------------------------

void oled_erase_character( oled_ptr oled, uint8_t line, uint8_t column ) {
	if ( oled == nullptr ) return;

	oled->erase( line, column );
}

//----------------------------------------------------------------

void oled_deinit( oled_ptr& oled ) {
	if ( oled == nullptr ) return;

	delete oled;
	oled = nullptr;
}

//----------------------------------------------------------------
