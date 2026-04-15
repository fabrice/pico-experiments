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

#include <vector>

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

constexpr uint8_t SSD1309_ADDRESS { 0x3c };

constexpr uint16_t SSD1309_WIDTH { 128 };
constexpr uint16_t SSD1309_HEIGHT { 64 };

//----------------------------------------------------------------
//

class OLED;
using oled_ptr = OLED*;

//----------------------------------------------------------------
// classe

class OLED {

private:

	wire_ptr _wire { nullptr };
	uint _reset_gpio { 255 };

	uint16_t _width { 0 };
	uint16_t _height { 0 };

	uint8_t _line { 0 };
	uint8_t _column { 0 };
	const uint8_t* _font { nullptr };

public:

	static oled_ptr make( uint8_t i2c_num, uint reset_gpio );
	static oled_ptr make( uint8_t i2c_num, uint8_t address, uint reset_gpio );

	OLED() = delete;
	OLED( wire_ptr wire, uint reset_gpio );
	~OLED();

private:

	void init();
	void display_init();

public:

	wire_ptr get_wire() const { return _wire; }

	uint16_t get_width() const { return _width; }
	uint16_t get_height() const { return _height; }

	uint16_t get_column_count() const { return _width / 6; }
	uint16_t get_columns_offset() const { return (_width % 6) / 2; }
	uint16_t get_line_count() const { return _height / 8; }
	uint16_t get_lines_offset() const { return (_height % 8) / 2; }

	void set_on( bool on );
	void set_orientation( uint8_t orientation );
	void set_dark_mode( bool mode );
	void set_brightness( uint8_t brightness );
	void set_brightness_db( float brightness_db );

	void draw_logo();

	void set_lico( uint8_t line, uint8_t column );

	void print( const char* text );
	void print( const char* text, uint8_t line, uint8_t column );
	void print_left( const char* text, uint8_t line );
	void print_center( const char* text, uint8_t line );
	void print_right( const char* text, uint8_t line );
	void print_aligned( const char* text, uint8_t line, char alignement );

	void printf( const char* format, ... );
	void vprintf( const char* format, va_list arg );

	void print( char character );
	void print( char character, uint8_t line, uint8_t column );
	void print_glyph( const uint8_t glyph[6] );

	void draw_bitmap( int16_t x, int16_t y, uint16_t width, uint16_t height, const uint8_t* bitmap, size_t length );
	void draw_bitmap( int16_t x, int16_t y, uint16_t width, uint16_t height, std::vector< bool > bitmap );

	void erase();
	void erase( uint8_t line );
	void erase( uint8_t line, uint8_t column );

	void reset();

};

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
