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

#include "pico/stdlib.h"

#include "oled.h"

#include "font_5x7.h"
#include "cfpt_logo.h"

#include "hardware/i2c.h"

#include <cmath>
#include "math_plus.h"
#include "pico/printf.h"
#include <cstdio>
#include <cstring>
#include <algorithm>


//----------------------------------------------------------------
// writes

constexpr uint8_t WRITE_COMMAND = 0x00;
constexpr uint8_t WRITE_DATA = 0x40;

//----------------------------------------------------------------
// commands

constexpr uint8_t SET_CONTRAST = 0x81;
// 1 arg :
// contrast 0..255

constexpr uint8_t DISPLAY_ON = 0xa4; // on following memory
constexpr uint8_t DISPLAY_ON_NO_RAM = 0xa5; // on ignoring memory

constexpr uint8_t DISPLAY_ACTIVE_HIGH = 0xa6;
constexpr uint8_t DISPLAY_ACTIVE_LOW = 0xa7;

constexpr uint8_t SET_DISPLAY_OFF = 0xae; // sleep
constexpr uint8_t SET_DISPLAY_ON = 0xaf;

constexpr uint8_t DISPLAY_NOP = 0xe3;

constexpr uint8_t SET_LINE_ADDRESS = 0xb0;
constexpr uint8_t SET_HIGH_COLUMN_ADDRESS = 0x10;
constexpr uint8_t SET_LOW_COLUMN_ADDRESS = 0x00;

constexpr uint8_t SET_MEMORY_ADDRESSING_MODE = 0x20;
// 1 arg :
constexpr uint8_t SET_MEMORY_ADDRESSING_MODE_HORIZONTAL = 0x00;
constexpr uint8_t SET_MEMORY_ADDRESSING_MODE_VERTICAL = 0x01;
constexpr uint8_t SET_MEMORY_ADDRESSING_MODE_PAGE = 0x02;

constexpr uint8_t SET_COLUMN_ADDRESS = 0x21;
constexpr uint8_t SET_PAGE_ADDRESS = 0x22;

constexpr uint8_t SET_START_LINE = 0x40;

constexpr uint8_t SET_MULTIPLEX_RATIO = 0xa8;
// 1 arg :
// mux - 1 : 0x0f..0x3f

// orientation
constexpr uint8_t SET_LEFT_RIGHT = 0xa0;
constexpr uint8_t SET_RIGHT_LEFT = 0xa1;
constexpr uint8_t SET_TOP_BOTTOM = 0xc0;
constexpr uint8_t SET_BOTTOM_TOP = 0xc8;

constexpr uint8_t SET_VERTICAL_OFFSET = 0xd3;
// 1 arg :
// 0x00..0x3f

constexpr uint8_t SET_DISPLAY_CLOCK = 0xd5;
constexpr uint8_t SET_PRECHARGE_PERIOD = 0xd9;
constexpr uint8_t SET_COM_PINS = 0xda;
constexpr uint8_t SET_VCOMH_DESELECT_LEVEL = 0xdb;

constexpr uint8_t SET_COMMAND_LOCK = 0xfd;

//----------------------------------------------------------------

OLED::OLED():
	_wire( nullptr ),
	_address( SSD1309_ADDRESS ),
	_reset_gpio( 0 ),
	_width( SSD1309_WIDTH ),
	_height( SSD1309_HEIGHT ),
	_line( 0 ),
	_column( 0 ),
	_font( font5x7 ) {
}

//----------------------------------------------------------------

OLED::OLED( i2c_ref wire, uint8_t address, uint reset_pin ):
	_wire( wire ),
	_address( address ),
	_reset_gpio( reset_pin ),
	_width( SSD1309_WIDTH ),
	_height( SSD1309_HEIGHT ),
	_line( 0 ),
	_column( 0 ),
	_font( font5x7 ) {
	this->init();
}

//----------------------------------------------------------------

OLED::~OLED() {
	this->erase();
	this->set_on( false );
	this->reset();
}

//----------------------------------------------------------------

void OLED::init() {
	if ( _wire == nullptr ) return;

	this->reset();
	this->display_init();
	sleep_ms( 100 );

	this->set_orientation( 1 );
	this->set_dark_mode( false );
	this->set_brightness( 0x7f );
	this->set_lico( 0, 0 );
	sleep_ms( 100 );

	this->erase();
	this->set_on( true );
}

//----------------------------------------------------------------

void OLED::display_init() {
	if ( _wire == nullptr ) return;

	i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_DISPLAY_OFF );

	i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_LINE_ADDRESS + 0 );
	i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_LOW_COLUMN_ADDRESS + 0 );
	i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_HIGH_COLUMN_ADDRESS + 0 );

	i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_MEMORY_ADDRESSING_MODE, SET_MEMORY_ADDRESSING_MODE_HORIZONTAL );
	i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, DISPLAY_NOP );
	i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, DISPLAY_ACTIVE_HIGH );
	i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_MULTIPLEX_RATIO, 0x3f );
	i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_VERTICAL_OFFSET, 0x00 );

	i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_DISPLAY_CLOCK, 0x70 ); // reset
	i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_PRECHARGE_PERIOD, 0x22 ); // reset
	//i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_COM_PINS, 0x12 );
	//i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_VCOMH_DESELECT_LEVEL, 0x40 );
}

//----------------------------------------------------------------

void OLED::set_on( bool on ) {
	i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, on ? SET_DISPLAY_ON : SET_DISPLAY_OFF );
}

//----------------------------------------------------------------

void OLED::set_orientation( uint8_t orientation ) {
	switch ( orientation ) {
	case 0:
		i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_LEFT_RIGHT );
		i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_TOP_BOTTOM );
		break;
	case 1:
		i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_RIGHT_LEFT );
		i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_BOTTOM_TOP );
		break;
	default:
		i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_LEFT_RIGHT );
		i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_TOP_BOTTOM );
		break;
	}
}

//----------------------------------------------------------------

void OLED::set_dark_mode( bool mode ) {
	i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, mode ? DISPLAY_ACTIVE_LOW : DISPLAY_ACTIVE_HIGH );
}

//----------------------------------------------------------------

void OLED::set_brightness( uint8_t brightness ) {
	i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_CONTRAST, brightness );
}

//----------------------------------------------------------------

void OLED::draw_logo() {
	this->draw_bitmap( 0, 0, 128, 64, cfpt_logo_128_64, cfpt_logo_128_64_length );
}

//----------------------------------------------------------------

void OLED::set_lico( uint8_t line, uint8_t column ) {
	_line = line < this->get_line_count() ? line : (uint8_t)this->get_line_count() - 1;
	_column = _column < this->get_column_count() ? column : (uint8_t)this->get_column_count() - 1;

	uint16_t y = _column * 6 + get_columns_offset();

	i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_LINE_ADDRESS + _line );
	i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_LOW_COLUMN_ADDRESS + ( (y >> 0) & 0x0f ) );
	i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_HIGH_COLUMN_ADDRESS + ( (y >> 4) & 0x0f ) );
}

//----------------------------------------------------------------

void OLED::print( const char* text ) {
	if ( _font == nullptr ) return;

	size_t text_length = strlen( text );
	if ( text_length == 0 ) return;

	uint16_t width = text_length * 6;
	uint8_t buffer[ width + 1 ];
	memset( buffer, 0, width + 1 );

	uint16_t x = 0;
	buffer[ x ] = WRITE_DATA;
	x += 1;

	for ( uint8_t character_index = 0; character_index < text_length; ++ character_index ) {
		char character = text[ character_index ];
		if ( character < ' ' ) break;
		if ( character > 127 ) break;

		uint16_t index = (character - 0x20) * 5;
		memcpy( &buffer[ x ], &_font[ index ], 5 );
		x += 5;
		buffer[ x ] = 0x00;
		x += 1;

		if ( x > width ) break;
	}

	i2c_write_blocking( _wire, _address, buffer, sizeof( buffer ), false );
}

//----------------------------------------------------------------

void OLED::print( const char* text, uint8_t line, uint8_t column ) {
	if ( _font == nullptr ) return;

	this->set_lico( line, column );
	this->print( text );
}

//----------------------------------------------------------------

void OLED::print_center( const char* text, uint8_t line ) {
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

void OLED::printf( const char* format, ... ) {
	va_list args;
	va_start( args, format );
	this->vprintf( format, args );
	va_end( args );
}

//----------------------------------------------------------------

void OLED::vprintf( const char* format, va_list args ) {
	char text[22];
	vsnprintf( text, 22, format, args );
	this->print( text );
}

//----------------------------------------------------------------

void OLED::print( char character ) {
	if ( _font == nullptr ) return;
	if ( character < ' ' ) return;
	if ( character > 127 ) return;

	uint16_t index = (character - 0x20) * 5;
	uint8_t buffer[7];
	buffer[0] = WRITE_DATA;
	memcpy( buffer + 1, &_font[ index ], 5 );
	buffer[6] = 0x00;

	i2c_write_blocking( _wire, _address, buffer, 7, false );
}

//----------------------------------------------------------------

void OLED::print( char character, uint8_t line, uint8_t column ) {
	if ( _font == nullptr ) return;

	this->set_lico( line, column );
	this->print( character );
}

//----------------------------------------------------------------

void OLED::print_glyph( uint8_t glyph[6] ) {
	uint8_t buffer[7];
	buffer[0] = WRITE_DATA;
	memcpy( buffer + 1, glyph, 6 );

	i2c_write_blocking( _wire, _address, buffer, 7, false );
}

//----------------------------------------------------------------

void OLED::draw_bitmap( int16_t x, int16_t y, int16_t width, int16_t height, const uint8_t* bitmap, size_t length ) {
	uint8_t buffer[129];
	memset( buffer, 0x00, 129 );
	buffer[0] = WRITE_DATA;

	for ( uint8_t line = 0; line < 8; ++ line ) {
		i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_LINE_ADDRESS + line );
		i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_LOW_COLUMN_ADDRESS + 0 );
		i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_HIGH_COLUMN_ADDRESS + 0 );

		memcpy( buffer + 1, bitmap + line * 128, 128 );
		i2c_write_blocking( _wire, _address, buffer, std::min( 1 + this->get_width(), 129 ), false );
	}
}

//----------------------------------------------------------------

void OLED::erase() {
	uint8_t buffer[129];
	memset( buffer, 0x00, 129 );
	buffer[0] = WRITE_DATA;

	for ( uint8_t line = 0; line < this->get_line_count(); ++ line ) {
		i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_LINE_ADDRESS + line );
		i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_LOW_COLUMN_ADDRESS + 0 );
		i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_HIGH_COLUMN_ADDRESS + 0 );
		i2c_write_blocking( _wire, _address, buffer, std::min( 1 + this->get_width(), 129 ), false );
	}
}
//----------------------------------------------------------------

void OLED::erase( uint8_t line ) {
	uint8_t buffer[129];
	memset( buffer, 0x00, 129 );
	buffer[0] = WRITE_DATA;

	i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_LINE_ADDRESS + line );
	i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_LOW_COLUMN_ADDRESS + 0 );
	i2c_write_bytes_blocking( _wire, _address, WRITE_COMMAND, SET_HIGH_COLUMN_ADDRESS + 0 );
	i2c_write_blocking( _wire, _address, buffer, std::min( 1 + this->get_width(), 129 ), false );
}

//----------------------------------------------------------------

void OLED::erase( uint8_t line, uint8_t column ) {
	uint8_t buffer[7];
	buffer[0] = WRITE_DATA;
	memset( buffer + 1, 0x00, 6 );

	this->set_lico( line, column );
	i2c_write_blocking( _wire, _address, buffer, 7, false );
}

//----------------------------------------------------------------

void OLED::reset() {
	gpio_put( _reset_gpio, 1 );
	sleep_ms( 100 );
	gpio_put( _reset_gpio, 0 );
	sleep_ms( 200 );
	gpio_put( _reset_gpio, 1 );
	sleep_ms( 100 );
}

//----------------------------------------------------------------
