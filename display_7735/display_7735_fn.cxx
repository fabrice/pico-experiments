//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// display ST7735
// st7735
//
//----------------------------------------------------------------

#include "display_7735_fn.h"
#include "display_7735.h"

#include "pico/stdlib.h"
#include "wire_spi.h"

#include <cmath>
#include "math_plus.h"
#include <cstring>

//----------------------------------------------------------------

constexpr uint SPI0_SCLK_GPIO { 18 };
constexpr uint SPI0_MISO_GPIO { 16 };
constexpr uint SPI0_MOSI_GPIO { 19 };

constexpr uint ST7735_CS_GPIO { 17 };
constexpr uint ST7735_DC_GPIO { 3 };
constexpr uint ST7735_BACKLIGHT_GPIO { 2 };

//----------------------------------------------------------------

display_7735_ptr display_7735_init( uint8_t spi_num, uint reset_gpio ) {
	wire_spi_ptr display_wire_spi = new wire_spi( spi_num, ST7735_CS_GPIO );
	display_wire_spi->io_init( SPI0_SCLK_GPIO, SPI0_MISO_GPIO, SPI0_MOSI_GPIO, 8e6 );
	return new display_7735( display_wire_spi, reset_gpio, ST7735_DC_GPIO, ST7735_BACKLIGHT_GPIO );
}

//----------------------------------------------------------------

uint16_t display_7735_get_width( const display_7735_ptr display ) {
	if ( display == nullptr ) return 0;

	return display->get_width();
}

//----------------------------------------------------------------

uint16_t display_7735_get_height( const display_7735_ptr display ) {
	if ( display == nullptr ) return 0;

	return display->get_height();
}

//----------------------------------------------------------------

uint16_t display_7735_get_column_count( const display_7735_ptr display ) {
	if ( display == nullptr ) return 0;

	return display->get_column_count();
}

//----------------------------------------------------------------

uint16_t display_7735_get_line_count( const display_7735_ptr display ) {
	if ( display == nullptr ) return 0;

	return display->get_line_count();
}

//----------------------------------------------------------------

void display_7735_set_on( display_7735_ptr display, bool on ) {
	if ( display == nullptr ) return;

	display->set_on( on );
}

//----------------------------------------------------------------

void display_7735_set_brightness( display_7735_ptr display, uint8_t brightness ) {
	if ( display == nullptr ) return;

	display->set_brightness( brightness );
}

//----------------------------------------------------------------

void display_7735_set_brightness_db( display_7735_ptr display, float brightness_db ) {
	if ( display == nullptr ) return;

	display->set_brightness_db( brightness_db );
}

//----------------------------------------------------------------

void display_7735_set_lico( display_7735_ptr display, uint8_t line, uint8_t column ) {
	if ( display == nullptr ) return;

	display->set_lico( line, column );
}

//----------------------------------------------------------------

void display_7735_print( display_7735_ptr display, const char* text ) {
	if ( display == nullptr ) return;

	display->print( text );
}

//----------------------------------------------------------------

void display_7735_print( display_7735_ptr display, const char* text, uint8_t line, uint8_t column ) {
	if ( display == nullptr ) return;

	display->print( line, column, text );
}

//----------------------------------------------------------------

void display_7735_print_left( display_7735_ptr display, const char* text, uint8_t line ) {
	if ( display == nullptr ) return;

	display->print_left( text, line );
}

//----------------------------------------------------------------

void display_7735_print_center( display_7735_ptr display, const char* text, uint8_t line ) {
	if ( display == nullptr ) return;

	display->print_center( text, line );
}

//----------------------------------------------------------------

void display_7735_print_right( display_7735_ptr display, const char* text, uint8_t line ) {
	if ( display == nullptr ) return;

	display->print_right( text, line );
}

//----------------------------------------------------------------

void display_7735_printf( display_7735_ptr display, const char* format, ... ) {
	if ( display == nullptr ) return;

	va_list args;
	va_start( args, format );
	display->vprintf( format, args );
	va_end( args );
}

//----------------------------------------------------------------

void display_7735_print( display_7735_ptr display, char character ) {
	if ( display == nullptr ) return;

	display->print( character );
}

//----------------------------------------------------------------

void display_7735_print( display_7735_ptr display, char character, uint8_t line, uint8_t column ) {
	if ( display == nullptr ) return;

	display->print( line, column, character );
}

//----------------------------------------------------------------

void display_7735_print_glyph( display_7735_ptr display, const uint8_t glyph[6] ) {
	if ( display == nullptr ) return;

	display->print_glyph( glyph );
}

//----------------------------------------------------------------

void display_7735_draw_pixmap( display_7735_ptr display, int16_t x, int16_t y, int16_t width, int16_t height, const uint8_t* pixmap, uint16_t length ) {
	if ( display == nullptr ) return;

	display->draw_pixmap( x, y, width, height, pixmap, length );
}

//----------------------------------------------------------------

void display_7735_draw_bitmap( display_7735_ptr display, int16_t x, int16_t y, int16_t width, int16_t height, const uint8_t* bitmap, uint16_t length ) {
	if ( display == nullptr ) return;

	display->draw_bitmap( x, y, width, height, bitmap, length );
}

//----------------------------------------------------------------

void display_7735_erase( display_7735_ptr display ) {
	if ( display == nullptr ) return;

	display->erase();
}

//----------------------------------------------------------------

void display_7735_erase_line( display_7735_ptr display, uint8_t line ) {
	if ( display == nullptr ) return;

	display->erase( line );
}

//----------------------------------------------------------------

void display_7735_erase_character( display_7735_ptr display, uint8_t line, uint8_t column ) {
	if ( display == nullptr ) return;

	display->erase( line, column );
}

//----------------------------------------------------------------

void display_7735_deinit( display_7735_ptr& display ) {
	if ( display == nullptr ) return;

	delete display;
	display = nullptr;
}

//----------------------------------------------------------------
