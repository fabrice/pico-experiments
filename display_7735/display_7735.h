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

//----------------------------------------------------------------

#include "pico/stdlib.h"

#include "wire.h"

#include <cstdint>
#include <cstring>

//----------------------------------------------------------------

constexpr uint8_t ST7735_TFTWIDTH { 128 };
constexpr uint8_t ST7735_TFTHEIGHT { 160 };

//----------------------------------------------------------------

class display_7735 {

private:

	wire* _wire { nullptr };
	uint _reset_gpio { 255 };
	uint _dc_gpio { 255 };
	uint _backlight_gpio { 255 };

	uint16_t _width { ST7735_TFTWIDTH };
	uint16_t _height { ST7735_TFTHEIGHT };

	uint8_t _brightness { 0x40 };

	const uint8_t* _font { nullptr };
	uint16_t _foreground_color { 0xffff };
	uint16_t _background_color { 0x0000 };

	uint8_t _line { 0 };
	uint8_t _column { 0 };

	uint8_t _color_mode { 0 };

private:

	display_7735() = delete;

public:

	static display_7735* make( wire* wire, uint reset_gpio, uint dc_gpio, uint backlight_gpio );

	display_7735( wire* wire, uint reset_gpio, uint dc_gpio, uint backlight_gpio, bool bgr = false );
	~display_7735() noexcept;

private:

	void display_init();
	void command( uint8_t c );
	void data( uint8_t c );

public:

	void reset();

	// properties

	uint16_t get_width() const { return _width; }
	uint16_t get_height() const { return _height; }

	void set_font( const uint8_t* font ) { _font = font; }

	uint16_t get_column_count() const { return _width / 6; }
	uint16_t get_columns_offset() const { return (_width % 6) / 2; }
	uint16_t get_line_count() const { return _height / 8; }
	uint16_t get_lines_offset() const { return (_height % 8) / 2; }

	uint16_t get_foreground_color() const { return _foreground_color; }
	uint8_t get_foreground_color_red() const { return (_foreground_color >> 8) & 0b11111000; }
	uint8_t get_foreground_color_green() const { return (_foreground_color >> 5) & 0b11111100; }
	uint8_t get_foreground_color_blue() const { return (_foreground_color << 3) & 0b11111000; }

	void set_foreground_color( uint16_t color ) { _foreground_color = color; }
	void set_foreground_color( uint8_t red, uint8_t green, uint8_t blue ) { _foreground_color = rgb_to_565( red, green, blue ); }

	uint16_t get_background_color() const { return _background_color; }
	uint8_t get_background_color_red() const { return (_background_color >> 8) & 0b11111000; }
	uint8_t get_background_color_green() const { return (_background_color >> 5) & 0b11111100; }
	uint8_t get_background_color_blue() const { return (_background_color << 3) & 0b11111000; }

	void set_background_color( uint16_t color ) { _background_color = color; }
	void set_background_color( uint8_t red, uint8_t green, uint8_t blue ) { _background_color = rgb_to_565( red, green, blue ); }

	// configuration

	void set_on( bool on );
	void set_rotation( uint8_t m );
	void set_brightness( uint8_t brightness );
	void set_brightness_db( float brightness_db );

	void set_addr_window( uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1 );

	void set_lico( uint8_t line, uint8_t column );

	// text

	void print( const char* text );
	void print( const char* text, int16_t x, int16_t y );

	void print_left( const char* text, uint8_t line );
	void print_center( const char* text, uint8_t line );
	void print_right( const char* text, uint8_t line );
	void print_aligned( const char* text, uint8_t line, char alignment );

	void printf( const char* format, ... );
	void vprintf( const char* format, va_list arg );

	void print( char character );
	void print( char character, int16_t x, int16_t y );

	void print_glyph( const uint8_t glyph[6] );

	// graphics

	void draw_pixel( int16_t x, int16_t y, uint16_t color );
	void draw_block( int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t color );

	void draw_graymap( const uint8_t* xy_graymap, size_t length, int16_t x, int16_t y, uint16_t width, uint16_t height );
	void draw_pixmap( const uint8_t* xy_pixmap, size_t length, int16_t x, int16_t y, uint16_t width, uint16_t height );
	void draw_bitmap( const uint8_t* yx_bytemap, size_t length, int16_t x, int16_t y, uint16_t width, uint16_t height );

	void fill_screen( uint16_t color );
	void fill_screen( uint8_t red, uint8_t green, uint8_t blue );

	// finishes

	void erase();
	void erase( uint8_t line );
	void erase( uint8_t line, uint8_t column );

	static uint16_t rgb_to_565( uint8_t r, uint8_t g, uint8_t b );

};

//----------------------------------------------------------------
