//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// display driver
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico/stdlib.h"

#include "wire.h"

#include <cstdint>
#include <cstring>

//----------------------------------------------------------------

class display_driver {

private:

	uint16_t _width { 0 };
	uint16_t _height { 0 };

public:

	display_driver();
	virtual ~display_driver();

	void reset();

	// properties

	uint16_t get_width() const { return _width; }
	uint16_t get_height() const { return _height; }

	// text

	virtual void print( const char* text );
	virtual void print( const char* text, int16_t x, int16_t y );

	virtual void print_left( const char* text, uint8_t line );
	virtual void print_center( const char* text, uint8_t line );
	virtual void print_right( const char* text, uint8_t line );
	virtual void print_aligned( const char* text, uint8_t line, char alignment );

	virtual void printf( const char* format, ... );
	virtual void vprintf( const char* format, va_list arg );

	virtual void print( char character );
	virtual void print( char character, int16_t x, int16_t y );

	virtual void print_glyph( const uint8_t glyph[6] );

	// graphics

	virtual void draw_pixel( int16_t x, int16_t y, uint16_t color );
	virtual void draw_block( int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t color );

	virtual void draw_graymap( const uint8_t* xy_graymap, size_t length, int16_t x, int16_t y, uint16_t width, uint16_t height );
	virtual void draw_pixmap( const uint8_t* xy_pixmap, size_t length, int16_t x, int16_t y, uint16_t width, uint16_t height );
	virtual void draw_bitmap( const uint8_t* yx_bytemap, size_t length, int16_t x, int16_t y, uint16_t width, uint16_t height );

	virtual void fill_screen( uint16_t color );
	virtual void fill_screen( uint8_t red, uint8_t green, uint8_t blue );

	// finishes

	virtual void erase();
	virtual void erase( uint8_t line );
	virtual void erase( uint8_t line, uint8_t column );

};

//----------------------------------------------------------------
