//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// display ST7735
// st7735
//
//----------------------------------------------------------------

#pragma once
#ifndef _DISPLAY_7735_H
#define _DISPLAY_7735_H

//----------------------------------------------------------------

#include "pico/stdlib.h"

#include "wire.h"

#include <cstring>

//----------------------------------------------------------------

class display_7735;
using display_7735_ref = display_7735*;

//----------------------------------------------------------------

constexpr uint8_t ST7735_TFTWIDTH = 128;
constexpr uint8_t ST7735_TFTHEIGHT = 160;

//----------------------------------------------------------------

class display_7735 {

public:

	display_7735( wire_ref wire, uint reset_gpio, uint dc_gpio, uint backlight_gpio, uint8_t offset = 0, bool bgr = false );
	~display_7735();

private:

	void display_init();
	void command( uint8_t c );
	void data( uint8_t c );

public:

	void reset();

	inline uint16_t get_width() const { return _width; }
	inline uint16_t get_height() const { return _height; }

	inline uint16_t get_column_count() const { return _width / 6; }
	inline uint16_t get_columns_offset() const { return (_width % 6) / 2; }
	inline uint16_t get_line_count() const { return _height / 8; }
	inline uint16_t get_lines_offset() const { return (_height % 8) / 2; }

	void set_on( bool on );
	void set_brightness( uint8_t brightness );
	void set_brightness_db( float brightness_db );

	void set_addr_window( uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1 );

	void draw_pixel( int16_t x, int16_t y, uint16_t color );
	void draw_block( int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t color );

	void draw_pixmap( int16_t x, int16_t y, uint16_t w, uint16_t h, const uint8_t* pixmap, size_t length );
	void draw_bitmap( int16_t x, int16_t y, uint16_t w, uint16_t h, const uint8_t* bitmap, size_t length );

	void fill_screen( uint16_t color );
	void fill_screen( uint8_t red, uint8_t green, uint8_t blue );

	void set_lico( uint8_t line, uint8_t column );

	void print( int16_t x, int16_t y, char character );
	void print( int16_t x, int16_t y, const char* text );
	void print_left( const char* text, uint8_t line );
	void print_center( uint8_t line, const char* text );
	void print_center( const char* text, uint8_t line );
	void print_right( const char* text, uint8_t line );
	void print_aligned( const char* text, uint8_t line, char alignement );
	void print( const char* text );

	void printf( const char* format, ... );
	void vprintf( const char* format, va_list arg );

	void erase();
	void erase( uint8_t line );
	void erase( uint8_t line, uint8_t column );

	void set_foreground_color( uint16_t color ) { _foreground_color = color; }
	void set_foreground_color( uint8_t red, uint8_t green, uint8_t blue ) { _foreground_color = rgb_to_565( red, green, blue ); }
	void set_background_color( uint16_t color ) { _background_color = color; }
	void set_background_color( uint8_t red, uint8_t green, uint8_t blue ) { _background_color = rgb_to_565( red, green, blue ); }

	void set_font( const uint8_t* font ) { _font = font; }

	static uint16_t rgb_to_565( uint8_t r, uint8_t g, uint8_t b );
	void set_rotation( uint8_t m );

private:

	wire_ref _wire;
	uint _reset_gpio;
	uint _dc_gpio;
	uint _backlight_gpio;
	uint8_t _offset;
	uint16_t _width;
	uint16_t _height;
	uint8_t _brightness;
	uint16_t _foreground_color;
	uint16_t _background_color;
	uint8_t _line;
	uint8_t _column;
	uint8_t _color_mode;
	const uint8_t* _font; // pointer to 5x7 font data in memory

};

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
