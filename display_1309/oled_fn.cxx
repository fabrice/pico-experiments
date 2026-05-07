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

#include <cstring>

//----------------------------------------------------------------

OLED* oled_init( uint8_t i2c_num, uint8_t address, uint reset_gpio ) {
	return OLED::make( i2c_num, address, reset_gpio );
}

//----------------------------------------------------------------

uint16_t oled_get_width( const OLED* that ) {
	if ( that == nullptr ) return 0;

	return that->get_width();
}

//----------------------------------------------------------------

uint16_t oled_get_height( const OLED* that ) {
	if ( that == nullptr ) return 0;

	return that->get_height();
}

//----------------------------------------------------------------

uint16_t oled_get_column_count( const OLED* that ) {
	if ( that == nullptr ) return 0;

	return that->get_column_count();
}

//----------------------------------------------------------------

uint16_t oled_get_line_count( const OLED* that ) {
	if ( that == nullptr ) return 0;

	return that->get_line_count();
}

//----------------------------------------------------------------

void oled_set_on( OLED* that, bool on ) {
	if ( that == nullptr ) return;

	that->set_on( on );
}

//----------------------------------------------------------------

void oled_set_orientation( OLED* that, uint8_t orientation ) {
	if ( that == nullptr ) return;

	that->set_orientation ( orientation );
}

//----------------------------------------------------------------

void oled_set_dark_mode( OLED* that, bool mode ) {
	if ( that == nullptr ) return;

	that->set_dark_mode( mode );
}

//----------------------------------------------------------------

void oled_set_brightness( OLED* that, uint8_t brightness ) {
	if ( that == nullptr ) return;

	that->set_brightness( brightness );
}

//----------------------------------------------------------------

void oled_set_brightness_db( OLED* that, float brightness_db ) {
	if ( that == nullptr ) return;

	that->set_brightness_db( brightness_db );
}

//----------------------------------------------------------------

void oled_set_lico( OLED* that, uint8_t line, uint8_t column ) {
	if ( that == nullptr ) return;

	that->set_lico( line, column );
}

//----------------------------------------------------------------

void oled_print( OLED* that, const char* text ) {
	if ( that == nullptr ) return;

	that->print( text );
}

//----------------------------------------------------------------

void oled_print( OLED* that, const char* text, uint8_t line, uint8_t column ) {
	if ( that == nullptr ) return;

	that->print( text, line, column );
}

//----------------------------------------------------------------

void oled_print_left( OLED* that, const char* text, uint8_t line ) {
	if ( that == nullptr ) return;

	that->print_left( text, line );
}

//----------------------------------------------------------------

void oled_print_center( OLED* that, const char* text, uint8_t line ) {
	if ( that == nullptr ) return;

	that->print_center( text, line );
}

//----------------------------------------------------------------

void oled_print_right( OLED* that, const char* text, uint8_t line ) {
	if ( that == nullptr ) return;

	that->print_right( text, line );
}

//----------------------------------------------------------------

void oled_printf( OLED* that, const char* format, ... ) {
	if ( that == nullptr ) return;

	va_list args;
	va_start( args, format );
	that->vprintf( format, args );
	va_end( args );
}

//----------------------------------------------------------------

void oled_print( OLED* that, char character ) {
	if ( that == nullptr ) return;

	that->print( character );
}

//----------------------------------------------------------------

void oled_print( OLED* that, char character, uint8_t line, uint8_t column ) {
	if ( that == nullptr ) return;

	that->print( character, line, column );
}

//----------------------------------------------------------------

void oled_print_glyph( OLED* that, const uint8_t glyph[6] ) {
	if ( that == nullptr ) return;

	that->print_glyph( glyph );
}

//----------------------------------------------------------------

void oled_draw_yx_bytemap( OLED* that, const uint8_t* yx_bytemap, uint16_t length ) {
	if ( that == nullptr ) return;

	that->draw_yx_bytemap( yx_bytemap, length );
}

//----------------------------------------------------------------

void oled_erase( OLED* that ) {
	if ( that == nullptr ) return;

	that->erase();
}

//----------------------------------------------------------------

void oled_erase_line( OLED* that, uint8_t line ) {
	if ( that == nullptr ) return;

	that->erase( line );
}

//----------------------------------------------------------------

void oled_erase_character( OLED* that, uint8_t line, uint8_t column ) {
	if ( that == nullptr ) return;

	that->erase( line, column );
}

//----------------------------------------------------------------

void oled_deinit( OLED*& that ) {
	if ( that == nullptr ) return;

	delete that;
	that = nullptr;
}

//----------------------------------------------------------------
