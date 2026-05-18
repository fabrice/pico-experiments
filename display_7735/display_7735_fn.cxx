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

#include <cstring>

//----------------------------------------------------------------

constexpr uint SPI0_SCLK_GPIO { 18 };
constexpr uint SPI0_MISO_GPIO { 16 };
constexpr uint SPI0_MOSI_GPIO { 19 };

constexpr uint ST7735_CS_GPIO { 17 };
constexpr uint ST7735_DC_GPIO { 3 };
constexpr uint ST7735_BACKLIGHT_GPIO { 2 };

//----------------------------------------------------------------

display_7735* display_7735_init( uint8_t spi_num, uint reset_gpio ) {
	auto display_wire_spi = wire_spi::make( spi_num, ST7735_CS_GPIO );
	display_wire_spi->io_init( SPI0_SCLK_GPIO, SPI0_MISO_GPIO, SPI0_MOSI_GPIO, 8e6 );

	auto driver = new display_7735( display_wire_spi, reset_gpio, ST7735_DC_GPIO, ST7735_BACKLIGHT_GPIO );

	return driver;
}

//----------------------------------------------------------------

uint16_t display_7735_get_width( const display_7735* that ) {
	if ( that == nullptr ) return 0;

	return that->get_width();
}

//----------------------------------------------------------------

uint16_t display_7735_get_height( const display_7735* that ) {
	if ( that == nullptr ) return 0;

	return that->get_height();
}

//----------------------------------------------------------------

uint16_t display_7735_get_column_count( const display_7735* that ) {
	if ( that == nullptr ) return 0;

	return that->get_column_count();
}

//----------------------------------------------------------------

uint16_t display_7735_get_line_count( const display_7735* that ) {
	if ( that == nullptr ) return 0;

	return that->get_line_count();
}

//----------------------------------------------------------------

void display_7735_set_on( display_7735* that, bool on ) {
	if ( that == nullptr ) return;

	that->set_on( on );
}

//----------------------------------------------------------------

void display_7735_set_brightness( display_7735* that, uint8_t brightness ) {
	if ( that == nullptr ) return;

	that->set_brightness( brightness );
}

//----------------------------------------------------------------

void display_7735_set_brightness_db( display_7735* that, float brightness_db ) {
	if ( that == nullptr ) return;

	that->set_brightness_db( brightness_db );
}

//----------------------------------------------------------------

void display_7735_set_cursor( display_7735* that, uint8_t line, uint8_t column ) {
	if ( that == nullptr ) return;

	that->set_cursor( line, column );
}

//----------------------------------------------------------------

void display_7735_print( display_7735* that, const char* text ) {
	if ( that == nullptr ) return;

	that->print( text );
}

//----------------------------------------------------------------

void display_7735_print( display_7735* that, const char* text, uint8_t line, uint8_t column ) {
	if ( that == nullptr ) return;

	that->set_cursor( line, column );
	that->print( text );
}

//----------------------------------------------------------------

void display_7735_print_left( display_7735* that, const char* text, uint8_t line ) {
	if ( that == nullptr ) return;

	that->print_left( text, line );
}

//----------------------------------------------------------------

void display_7735_print_center( display_7735* that, const char* text, uint8_t line ) {
	if ( that == nullptr ) return;

	that->print_center( text, line );
}

//----------------------------------------------------------------

void display_7735_print_right( display_7735* that, const char* text, uint8_t line ) {
	if ( that == nullptr ) return;

	that->print_right( text, line );
}

//----------------------------------------------------------------

void display_7735_printf( display_7735* that, const char* format, ... ) {
	if ( that == nullptr ) return;

	va_list args;
	va_start( args, format );
	that->vprintf( format, args );
	va_end( args );
}

//----------------------------------------------------------------

void display_7735_print( display_7735* that, char character ) {
	if ( that == nullptr ) return;

	that->print( character );
}

//----------------------------------------------------------------

void display_7735_print( display_7735* that, char character, uint8_t line, uint8_t column ) {
	if ( that == nullptr ) return;

	that->set_cursor( line, column );
	that->print( character );
}

//----------------------------------------------------------------

void display_7735_print_glyph( display_7735* that, const uint8_t glyph[6] ) {
	if ( that == nullptr ) return;

	that->print_glyph( glyph );
}

//----------------------------------------------------------------

void display_7735_draw_pixel( display_7735* that, int16_t x, int16_t y, uint16_t color ) {
	if ( that == nullptr ) return;

	that->draw_pixel( x, y, color );
}

//----------------------------------------------------------------

void display_7735_draw_line( display_7735* that, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color ) {
	if ( that == nullptr ) return;

	that->draw_line( x1, y1, x2, y2, color );
}

//----------------------------------------------------------------

void display_7735_draw_line_to( display_7735* that, int16_t x, int16_t y, uint16_t color ) {
	if ( that == nullptr ) return;

	that->draw_line_to( x, y, color );
}

//----------------------------------------------------------------

void display_7735_draw_pixmap( display_7735* that, const uint8_t* pixmap, uint16_t length, int16_t x, int16_t y, int16_t width, int16_t height ) {
	if ( that == nullptr ) return;

	that->draw_pixmap( pixmap, length, x, y, width, height );
}

//----------------------------------------------------------------

void display_7735_draw_bitmap( display_7735* that, const uint8_t* bitmap, uint16_t length, int16_t x, int16_t y, int16_t width, int16_t height ) {
	if ( that == nullptr ) return;

	that->draw_bitmap( bitmap, length, x, y, width, height );
}

//----------------------------------------------------------------

void display_7735_erase( display_7735* that ) {
	if ( that == nullptr ) return;

	that->erase();
}

//----------------------------------------------------------------

void display_7735_erase_line( display_7735* that, uint8_t line ) {
	if ( that == nullptr ) return;

	that->erase( line );
}

//----------------------------------------------------------------

void display_7735_erase_character( display_7735* that, uint8_t line, uint8_t column ) {
	if ( that == nullptr ) return;

	that->erase( line, column );
}

//----------------------------------------------------------------

void display_7735_deinit( display_7735*& that ) {
	if ( that == nullptr ) return;

	delete that;
	that = nullptr;
}

//----------------------------------------------------------------
