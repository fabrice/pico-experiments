//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// display st7735
//
//----------------------------------------------------------------

#include "pico/stdlib.h"

#include "hardware/pwm.h"

#include "display_7735.h"
#include "cfpt_mono_6x8.h"

#include "math_plus.h"
#include <cmath>
#include <algorithm>
#include <cstdio>

//----------------------------------------------------------------
// commands

constexpr uint8_t ST7735_NOP { 0x00 };
constexpr uint8_t ST7735_SWRESET { 0x01 };
constexpr uint8_t ST7735_RDDID { 0x04 };
constexpr uint8_t ST7735_RDDST { 0x09 };

constexpr uint8_t ST7735_SLPIN { 0x10 };
constexpr uint8_t ST7735_SLPOUT { 0x11 };
constexpr uint8_t ST7735_PTLON { 0x12 };
constexpr uint8_t ST7735_NORON { 0x13 };

constexpr uint8_t ST7735_INVOFF { 0x20 };
constexpr uint8_t ST7735_INVON { 0x21 };
constexpr uint8_t ST7735_DISPOFF { 0x28 };
constexpr uint8_t ST7735_DISPON { 0x29 };
constexpr uint8_t ST7735_CASET { 0x2A };
constexpr uint8_t ST7735_RASET { 0x2B };
constexpr uint8_t ST7735_RAMWR { 0x2C };
constexpr uint8_t ST7735_RAMRD { 0x2E };

constexpr uint8_t ST7735_PTLAR { 0x30 };
constexpr uint8_t ST7735_COLMOD { 0x3A };
constexpr uint8_t ST7735_MADCTL { 0x36 };

constexpr uint8_t ST7735_FRMCTR1 { 0xB1 };
constexpr uint8_t ST7735_FRMCTR2 { 0xB2 };
constexpr uint8_t ST7735_FRMCTR3 { 0xB3 };
constexpr uint8_t ST7735_INVCTR { 0xB4 };
constexpr uint8_t ST7735_DISSET5 { 0xB6 };

constexpr uint8_t ST7735_PWCTR1 { 0xC0 };
constexpr uint8_t ST7735_PWCTR2 { 0xC1 };
constexpr uint8_t ST7735_PWCTR3 { 0xC2 };
constexpr uint8_t ST7735_PWCTR4 { 0xC3 };
constexpr uint8_t ST7735_PWCTR5 { 0xC4 };
constexpr uint8_t ST7735_VMCTR1 { 0xC5 };

constexpr uint8_t ST7735_RDID1 { 0xDA };
constexpr uint8_t ST7735_RDID2 { 0xDB };
constexpr uint8_t ST7735_RDID3 { 0xDC };
constexpr uint8_t ST7735_RDID4 { 0xDD };

constexpr uint8_t ST7735_PWCTR6 { 0xFC };

constexpr uint8_t ST7735_GMCTRP1 { 0xE0 };
constexpr uint8_t ST7735_GMCTRN1 { 0xE1 };

// MADCTL bits
constexpr uint8_t ST7735_MADCTL_MY { 0x80 };
constexpr uint8_t ST7735_MADCTL_MX { 0x40 };
constexpr uint8_t ST7735_MADCTL_MV { 0x20 };
constexpr uint8_t ST7735_MADCTL_ML { 0x10 };
constexpr uint8_t ST7735_MADCTL_RGB { 0x00 };
constexpr uint8_t ST7735_MADCTL_BGR { 0x08 };
constexpr uint8_t ST7735_MADCTL_MH { 0x04 };

constexpr uint8_t DELAY_FLAG { 0x80 };

//----------------------------------------------------------------

display_7735::display_7735( wire* wire, uint reset_gpio, uint dc_gpio, uint backlight_gpio, uint8_t offset, bool bgr ):
	_wire( wire ),
	_reset_gpio( reset_gpio ),
	_dc_gpio( dc_gpio ),
	_backlight_gpio( backlight_gpio ),
	_offset( offset ),
	_brightness( 63 ),
	_font( &cfpt_mono_6x8[0][0] ),
	_color_mode { bgr ? ST7735_MADCTL_BGR : ST7735_MADCTL_RGB } {
	gpio_init( _reset_gpio);
	gpio_set_dir( _reset_gpio, GPIO_OUT );
	gpio_put( _reset_gpio, true );

	gpio_init( _dc_gpio );
	gpio_set_dir( _dc_gpio, GPIO_OUT );
	gpio_put( _dc_gpio, true );

	gpio_init( _backlight_gpio );
	gpio_set_dir( _backlight_gpio, GPIO_OUT );
	gpio_put( _backlight_gpio, false );

	this->display_init();
}

//----------------------------------------------------------------

display_7735::~display_7735() {
	this->erase();
	this->set_on( false );
	this->reset();

	delete _wire;
	_wire = nullptr;
}

//----------------------------------------------------------------

void display_7735::display_init() {
	this->reset();

	const uint8_t commands[] = {
		ST7735_SWRESET, DELAY_FLAG,
			150,
		ST7735_SLPOUT, DELAY_FLAG,
			255,
		ST7735_FRMCTR1, 3,
			0x01, 0x2C, 0x2D,
		ST7735_FRMCTR2, 3,
			0x01, 0x2C, 0x2D,
		ST7735_FRMCTR3, 6,
			0x01, 0x2C, 0x2D,
			0x01, 0x2C, 0x2D,
		ST7735_INVCTR, 1,
			0x07,
		ST7735_PWCTR1, 3,
			0xA2, 0x02, 0x84,
		ST7735_PWCTR2, 1,
			0xC5,
		ST7735_PWCTR3, 2,
			0x0A, 0x00,
		ST7735_PWCTR4, 2,
			0x8A, 0x2A,
		ST7735_PWCTR5, 2,
			0x8A, 0xEE,
		ST7735_VMCTR1, 1,
			0x0E,
		ST7735_INVOFF, 0,
		ST7735_MADCTL, 1,
			0xC8,
		ST7735_COLMOD, 1,
			0x05,
		ST7735_CASET, 4,
			0x00, 0x00, 0x00, 0x7F,
		ST7735_RASET, 4,
			0x00, 0x00, 0x00, 0x9F,
		ST7735_GMCTRP1, 16,
			0x02, 0x1C, 0x07, 0x12,
			0x37, 0x32, 0x29, 0x2D,
			0x29, 0x25, 0x2B, 0x39,
			0x00, 0x01, 0x03, 0x10,
		ST7735_GMCTRN1, 16,
			0x03, 0x1D, 0x07, 0x06,
			0x2E, 0x2C, 0x29, 0x2D,
			0x2E, 0x2E, 0x37, 0x3F,
			0x00, 0x00, 0x02, 0x10,
		ST7735_NORON, DELAY_FLAG,
			10,
//		ST7735_DISPON, DELAY_FLAG,
//			100,
		ST7735_MADCTL, 1,
			static_cast<uint8_t>(0xC0 | _color_mode),
	};

	size_t i = 0;
	size_t length = sizeof(commands);

	while (i < length) {
		uint8_t cmd = commands[i];
		++i;
		uint8_t num_args_and_delay = commands[i];
		++i;
		uint8_t num_args = num_args_and_delay & ~DELAY_FLAG;
		bool has_delay = (num_args_and_delay & DELAY_FLAG) != 0;

		this->command(cmd);

		for ( uint8_t a = 0 ; a < num_args ; ++ a ) {
			this->data(commands[i++]);
		}

		if (has_delay) {
			uint16_t ms = commands[i];
			++ i;
			if (ms == 255) ms = 500;
			sleep_ms(ms);
		}
	}

	this->erase();
	this->set_on( true );
}

//----------------------------------------------------------------

void display_7735::command( uint8_t c ) {
	if ( _wire != nullptr ) {
		gpio_put( _dc_gpio, false );
		_wire->start_communication();
		_wire->write_bytes( c );
		_wire->finish_communication();
		gpio_put( _dc_gpio, true );
	}
}

//----------------------------------------------------------------

void display_7735::data( uint8_t c ) {
	if ( _wire != nullptr ) {
		gpio_put( _dc_gpio, true );
		_wire->start_communication();
		_wire->write_bytes( c );
		_wire->finish_communication();
	}
}

//----------------------------------------------------------------

void display_7735::reset() {
	gpio_put( _reset_gpio, false );
	sleep_ms( 50 );
	gpio_put( _reset_gpio, true );
	sleep_ms( 50 );
}

//----------------------------------------------------------------

void display_7735::set_on( bool on ) {
	if ( !on ) {
		this->set_brightness( 0 );
		sleep_ms( 100 );
	}

	this->command( on ? ST7735_DISPON : ST7735_DISPOFF );

	if ( on ) {
		sleep_ms( 100 );
		this->set_brightness( _brightness );
	}
}

//----------------------------------------------------------------

void display_7735::set_brightness( uint8_t brightness ) {
	_brightness = brightness;

	uint pwm_slice = pwm_gpio_to_slice_num( _backlight_gpio );
	uint pwm_channel = pwm_gpio_to_channel( _backlight_gpio );

	pwm_set_clkdiv( pwm_slice, 150.0 );
    pwm_set_wrap( pwm_slice, 1000 );

	float level = (float)brightness / 255.0 * 1000.0;
	pwm_set_chan_level( pwm_slice, pwm_channel, (uint16_t)std::floor( level ) );

	pwm_set_enabled( pwm_slice, true );

	gpio_set_function( _backlight_gpio, GPIO_FUNC_PWM );
}

//----------------------------------------------------------------

void display_7735::set_brightness_db( float brightness_db ) {
	float brightness = std::pow( 10.0f, brightness_db / 20.0f ) * 255.0f;
	brightness = std::round( constrain( brightness, 0.0f, 255.0f ) );
	this->set_brightness( brightness );
}

//----------------------------------------------------------------

void display_7735::set_addr_window( uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1 ) {
	this->command(ST7735_CASET);
	this->data(0x00);
	this->data(x0 + _offset);
	this->data(0x00);
	this->data(x1 + _offset);

	this->command(ST7735_RASET);
	this->data(0x00);
	this->data(y0 + _offset);
	this->data(0x00);
	this->data(y1 + _offset);

	this->command(ST7735_RAMWR);
}

//----------------------------------------------------------------

void display_7735::draw_pixel( int16_t x, int16_t y, uint16_t color ) {
	if (x < 0 || x >= _width || y < 0 || y >= _height) return;

	this->set_addr_window(x, y, x + 1, y + 1);

	uint8_t buf[2] = {
		static_cast<uint8_t>(color >> 8),
		static_cast<uint8_t>(color & 0xff),
	};
	if ( _wire != nullptr ) {
		gpio_put( _dc_gpio, true );
		_wire->start_communication();
		_wire->write_bytes( static_cast<uint8_t>(color >> 8), static_cast<uint8_t>(color & 0xff) );
		_wire->finish_communication();
	}
}

//----------------------------------------------------------------

void display_7735::draw_block( int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t color ) {
	int max_rows = 500 / w;
	if (max_rows < 1) max_rows = 1;

	uint8_t hi = color >> 8;
	uint8_t lo = color & 0xFF;

	int rows = 0;
	while (rows < h) {
		int block_rows = std::min(max_rows, (int)(h - rows));
		size_t buf_len = (size_t)w * block_rows * 2;
		uint8_t* buf = new uint8_t[buf_len];

		for ( size_t i = 0 ; i < buf_len ; i += 2 ) {
			buf[i] = hi;
			buf[i + 1] = lo;
		}

		this->draw_pixmap( x, y + rows, w, block_rows, buf, buf_len );
		delete[] buf;
		rows += max_rows;
	}
}

//----------------------------------------------------------------

void display_7735::draw_pixmap( int16_t x, int16_t y, uint16_t w, uint16_t h, const uint8_t* pixmap, size_t length ) {
	if (x >= _width || y >= _height) return;

	if ((x + w - 1) >= _width) w = _width - x;
	if ((y + h - 1) >= _height) h = _height - y;

	this->set_addr_window(x, y, x + w - 1, y + h - 1);

	if ( _wire != nullptr ) {
		gpio_put( _dc_gpio, true );
		_wire->start_communication();
		_wire->write_bytes( pixmap, length );
		_wire->finish_communication();
	}
}

//----------------------------------------------------------------

void display_7735::draw_bitmap( int16_t x, int16_t y, uint16_t w, uint16_t h, const uint8_t* bitmap, size_t length ) {
	if (x >= _width || y >= _height) return;

	if ((x + w - 1) >= _width) w = _width - x;
	if ((y + h - 1) >= _height) h = _height - y;

	uint8_t* pixelmap = new uint8_t[ w * h * 2 ] {};
	for ( uint pixx = 0 ; pixx < w ; ++ pixx ) {
		for ( uint pixy = 0 ; pixy < h ; ++ pixy ) {
			uint16_t line = pixy / 8;
			uint8_t bit = pixy % 8;
			uint16_t idx = pixx + w * line;
			uint16_t pixel = !!(bitmap[ idx ] & (1 << bit)) ? _foreground_color : _background_color;
			pixelmap[ (pixx + w * pixy) * 2 + 0 ] = pixel >> 8;
			pixelmap[ (pixx + w * pixy) * 2 + 1 ] = pixel & 0xff;
		}
	}

	this->draw_pixmap( x, y, w, h, (const uint8_t*)pixelmap , w * h * 2 );

	delete[] pixelmap;
}

//----------------------------------------------------------------

void display_7735::fill_screen( uint16_t color ) {
	this->draw_block( 0, 0, _width, _height, color );
}

//----------------------------------------------------------------

void display_7735::fill_screen( uint8_t red, uint8_t green, uint8_t blue ) {
	this->fill_screen( rgb_to_565( red, green, blue ) );
}

//----------------------------------------------------------------

void display_7735::set_lico( uint8_t line, uint8_t column ) {
	if ( line >= get_line_count() ) line = this->get_line_count() - 1;
	if ( column >= get_column_count() ) column = this->get_column_count() - 1;
	_line = line;
	_column = column;
}

//----------------------------------------------------------------

void display_7735::print( int16_t x, int16_t y, char character ) {
	if ( _font == nullptr ) return;

	uint8_t char_buf[6];
	memcpy(char_buf, &_font[ character * 5 ], 5);
	char_buf[5] = 0;

	uint8_t char_image[6 * 8 * 2] {}; // 6 wide, 8 tall, 2 bytes per pixel
	size_t idx = 0;

	uint8_t color_hi = _foreground_color >> 8;
	uint8_t color_lo = _foreground_color & 0xFF;
	uint8_t bg_hi = _background_color >> 8;
	uint8_t bg_lo = _background_color & 0xFF;

	for ( int bit = 0 ; bit < 8 ; ++ bit ) {
		for ( int c = 0 ; c < 6 ; ++ c ) {
			if ((char_buf[c] >> bit) & 0x01) {
				char_image[idx] = color_hi;
				++ idx;
				char_image[idx] = color_lo;
				++ idx;
			} else {
				char_image[idx] = bg_hi;
				++ idx;
				char_image[idx] = bg_lo;
				++ idx;
			}
		}
	}

	this->draw_pixmap( x, y, 6, 8, char_image, sizeof(char_image) );
}

//----------------------------------------------------------------

void display_7735::print( int16_t x, int16_t y, const char* text ) {
	if ( _font == nullptr ) return;

	while ( *text ) {
		print( x, y, *text );
		x += 6;
		text++;
	}
}

//----------------------------------------------------------------

void display_7735::print_center( uint8_t line, const char* text ) {
	if ( _font == nullptr ) return;

	uint8_t column_count = this->get_column_count();
	size_t text_length = strlen( text );
	uint8_t column = 0;
	if ( text_length < column_count ) column = (column_count - text_length) / 2;
	int16_t x = column * 6 + this->get_columns_offset();
	int16_t y = line * 8 + get_lines_offset();
	this->print( x, y, text );
}

//----------------------------------------------------------------

void display_7735::print_left( const char* text, uint8_t line ) {
	if ( _font == nullptr ) return;

	size_t text_length = strlen( text );
	if ( text_length == 0 ) return;

	this->set_lico( line, 0 );
	this->print( text );
}

//----------------------------------------------------------------

void display_7735::print_center( const char* text, uint8_t line ) {
	if ( _font == nullptr ) return;

	size_t text_length = strlen( text );
	if ( text_length == 0 ) return;

	uint8_t column_count = this->get_column_count();
	uint8_t column = 0;
	if ( text_length < column_count ) column = (column_count - text_length) / 2;

	this->set_lico( line, column );
	this->print( text );
}

//----------------------------------------------------------------

void display_7735::print_right( const char* text, uint8_t line ) {
	if ( _font == nullptr ) return;

	size_t text_length = strlen( text );
	if ( text_length == 0 ) return;

	uint8_t column_count = this->get_column_count();
	uint8_t column = 0;
	if ( text_length < column_count ) column = column_count - text_length;

	this->set_lico( line, column );
	this->print( text );
}

//----------------------------------------------------------------

void display_7735::print_aligned( const char* text, uint8_t line, char alignement ) {
	if ( _font == nullptr ) return;

	size_t text_length = strlen( text );
	if ( text_length == 0 ) return;

	uint8_t column_count = this->get_column_count();
	uint8_t column = 0;

	switch ( alignement ) {
	case '<':
		if ( text_length < column_count ) column = 0;
		break;
	case '^':
		if ( text_length < column_count ) column = (column_count - text_length) / 2;
		break;
	case '>':
		if ( text_length < column_count ) column = column_count - text_length;
		break;
	default:
		break;
	}

	this->set_lico( line, column );
	this->print( text );
}

//----------------------------------------------------------------

void display_7735::print( const char* text ) {
	int16_t x = _column * 6 + get_columns_offset();
	int16_t y = _line * 8 + get_lines_offset();

	this->print( x, y, text );
}

//----------------------------------------------------------------

void display_7735::print( char character ) {
	if ( _font == nullptr ) return;

	int16_t x = _column * 6 + get_columns_offset();
	int16_t y = _line * 8 + get_lines_offset();

	this->print( x, y, character );
}

//----------------------------------------------------------------

void display_7735::print_glyph( const uint8_t glyph[6] ) {
	if ( _font == nullptr ) return;

	int16_t x = _column * 6 + get_columns_offset();
	int16_t y = _line * 8 + get_lines_offset();

	uint8_t char_image[6 * 8 * 2] {}; // 6 wide, 8 tall, 2 bytes per pixel
	size_t idx = 0;

	uint8_t color_hi = _foreground_color >> 8;
	uint8_t color_lo = _foreground_color & 0xFF;
	uint8_t bg_hi = _background_color >> 8;
	uint8_t bg_lo = _background_color & 0xFF;

	for ( int bit = 0 ; bit < 8 ; ++ bit ) {
		for ( int c = 0 ; c < 6 ; ++ c ) {
			if ((glyph[c] >> bit) & 0x01) {
				char_image[idx] = color_hi;
				++ idx;
				char_image[idx] = color_lo;
				++ idx;
			} else {
				char_image[idx] = bg_hi;
				++ idx;
				char_image[idx] = bg_lo;
				++ idx;
			}
		}
	}

	this->draw_pixmap( x, y, 6, 8, char_image, sizeof(char_image) );
}

//----------------------------------------------------------------

void display_7735::printf( const char* format, ... ) {
	va_list args;
	va_start( args, format );
	this->vprintf( format, args );
	va_end( args );
}

//----------------------------------------------------------------

void display_7735::vprintf( const char* format, va_list args ) {
	char text[27];
	vsnprintf( text, 27, format, args );
	text[ 26 ] = 0;
	this->print( text );
}

//----------------------------------------------------------------

void display_7735::erase() {
	this->fill_screen( 0 );
}
//----------------------------------------------------------------

void display_7735::erase( uint8_t line ) {
	this->draw_block( 0, 8 * line, this->get_width(), 8, _background_color );
}

//----------------------------------------------------------------

void display_7735::erase( uint8_t line, uint8_t column ) {
	this->draw_block( 6 * column, 8 * line, 6, 8, _background_color );
}

//----------------------------------------------------------------

uint16_t display_7735::rgb_to_565( uint8_t r, uint8_t g, uint8_t b ) {
	return ((r & 0b11111000) << 8) | ((g & 0b11111100) << 3) | ((b & 0b11111000) >> 3);
}

//----------------------------------------------------------------

void display_7735::set_rotation( uint8_t m ) {
	this->command(ST7735_MADCTL);
	uint8_t rotation = m % 4;

	switch (rotation) {
	case 0:
		this->data(ST7735_MADCTL_MX | ST7735_MADCTL_MY | _color_mode);
		_width = ST7735_TFTWIDTH;
		_height = ST7735_TFTHEIGHT;
		break;
	case 1:
		this->data(ST7735_MADCTL_MY | ST7735_MADCTL_MV | _color_mode);
		_width = ST7735_TFTHEIGHT;
		_height = ST7735_TFTWIDTH;
		break;
	case 2:
		this->data(_color_mode);
		_width = ST7735_TFTWIDTH;
		_height = ST7735_TFTHEIGHT;
		break;
	case 3:
		this->data(ST7735_MADCTL_MX | ST7735_MADCTL_MV | _color_mode);
		_width = ST7735_TFTHEIGHT;
		_height = ST7735_TFTWIDTH;
		break;
	}
}

//----------------------------------------------------------------
