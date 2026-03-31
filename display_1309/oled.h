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

#pragma once
#ifndef _OLED_H
#define _OLED_H

//----------------------------------------------------------------

#include "pico/stdlib.h"

#include "wire.h"

//----------------------------------------------------------------
/*
 -----------------------------       -----------------------
|  .  |  .  |  .  |  .  |  .  |     |  .  |  .  |  .  |  .  |
|  0  |  2  |  4  | SDA | VCC |     | VCC | SDA | SCL | GND |
|  .  |  .  |  .  |  .  |  .  |      -----------------------
| GND |  1  |  3  | RST | SCL |
 -----------       -----------
*/
//----------------------------------------------------------------

constexpr uint8_t SSD1309_ADDRESS = 0x3c;

constexpr uint16_t SSD1309_WIDTH = 128;
constexpr uint16_t SSD1309_HEIGHT = 64;

//----------------------------------------------------------------
//

class OLED;
using oled_ref = OLED*;

//----------------------------------------------------------------
// classe

class OLED {

private:

	OLED();

public:

	OLED( wire_ref wire, uint reset_gpio );
	~OLED();

private:

	void init();
	void display_init();

public:

	wire_ref get_wire() const { return this->_wire; }

	uint16_t get_width() const { return this->_width; }
	uint16_t get_height() const { return this->_height; }

	uint16_t get_column_count() const { return this->_width / 6; }
	uint16_t get_columns_offset() const { return (this->_width % 6) / 2; }
	uint16_t get_line_count() const { return this->_height / 8; }
	uint16_t get_lines_offset() const { return (this->_height % 8) / 2; }

	void set_on( bool on );
	void set_orientation( uint8_t orientation );
	void set_dark_mode( bool mode );
	void set_brightness( uint8_t brightness );
	void set_brightness_db( float brightness_db );

	void draw_logo();

	void set_lico( uint8_t line, uint8_t column );

	void print( const char* text );
	void print( const char* text, uint8_t line, uint8_t column );
	void print_center( const char* text, uint8_t line );

	void printf( const char* format, ... );
	void vprintf( const char* format, va_list arg );

	void print( char character );
	void print( char character, uint8_t line, uint8_t column );
	void print_glyph( uint8_t glyph[6] );

	void draw_bitmap( int16_t x, int16_t y, int16_t width, int16_t height, const uint8_t* bitmap, size_t length );

	void erase();
	void erase( uint8_t line );
	void erase( uint8_t line, uint8_t column );

	void reset();

private:

	wire_ref _wire;
	uint _reset_gpio;

	uint16_t _width;
	uint16_t _height;

	uint8_t _line;
	uint8_t _column;
	const uint8_t* _font; // 5x7

};

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
