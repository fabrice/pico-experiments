//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// ui leds
//
//----------------------------------------------------------------

#include "ui_leds.h"

#include "led_20_32.h"

//----------------------------------------------------------------

constexpr uint UI_LEDS_COUNT = 12;


//----------------------------------------------------------------

ui_leds* ui_leds::make( display_7735* display ) {
	if ( display == nullptr ) return nullptr;

	ui_leds* that = new ui_leds( display );

	return that;
}

//----------------------------------------------------------------

void ui_leds::set_title( const std::string_view& text ) {
	_title = text;

	if ( _display == nullptr ) return;
	_display->print_center( _title.data(), 1 );
}

//----------------------------------------------------------------

void ui_leds::set_message( const std::string_view& text ) {
	_message = text;

	if ( _display == nullptr ) return;
	_display->print_center( _message.data(), 3 );
}

//----------------------------------------------------------------

uint ui_leds::get_led_count() const {
	return UI_LEDS_COUNT;
}

//----------------------------------------------------------------

uint32_t ui_leds::get_leds() const {
	return _leds;
}

//----------------------------------------------------------------

void ui_leds::put_leds( uint32_t leds ) {
	if ( _leds == leds ) return;

	_leds = leds;
	this->refresh();
}

//----------------------------------------------------------------

void ui_leds::clr_leds() {
	_leds = 0;
	this->refresh();
}

//----------------------------------------------------------------

bool ui_leds::get_led( uint num ) const {
	if ( num >= UI_LEDS_COUNT ) return false;

	return !!(_leds & (1 << num));
}

//----------------------------------------------------------------

void ui_leds::put_led( uint num, bool on ) {
	if ( num >= UI_LEDS_COUNT ) return;

	const uint32_t mask = 1 << num;
	_leds = (_leds & ~mask) | (on << num);
	this->refresh_led( num );
}

//----------------------------------------------------------------

void ui_leds::set_led( uint num ) {
	if ( num >= UI_LEDS_COUNT ) return;

	const uint32_t mask = 1 << num;
	_leds |= mask;
	this->refresh_led( num );
}

//----------------------------------------------------------------

void ui_leds::clr_led( uint num ) {
	if ( num >= UI_LEDS_COUNT ) return;

	const uint32_t mask = 1 << num;
	_leds &= ~mask;
	this->refresh_led( num );
}

//----------------------------------------------------------------

void ui_leds::xor_led( uint num ) {
	if ( num >= UI_LEDS_COUNT ) return;

	const uint32_t mask = 1 << num;
	_leds ^= mask;
	this->refresh_led( num );
}

//----------------------------------------------------------------

void ui_leds::set_color( bool red, bool green, bool blue ) {
	_color = (red ? 0b0100 : 0) | (green ? 0b0010 : 0) | (blue ? 0b0001 : 0);
	if ( _color == 0b0000 ) _color = 0b0111;
}

//----------------------------------------------------------------

void ui_leds::refresh() {
	for ( uint num = 0 ; num < UI_LEDS_COUNT ; ++ num ) {
		this->refresh_led( num );
	}
}

//----------------------------------------------------------------

uint16_t ui_leds::get_color() const {
	uint16_t color = 0;

	if ( !!(_color & 0b0100) ) color += static_cast< uint16_t >( 0xf0 & 0b11111000 ) << 8;
	if ( !!(_color & 0b0010) ) color += static_cast< uint16_t >( 0xf0 & 0b11111100 ) << 3;
	if ( !!(_color & 0b0001) ) color += static_cast< uint16_t >( 0xf0 & 0b11111000 ) >> 3;

	return color;
}

//----------------------------------------------------------------

void ui_leds::refresh_led( uint num ) {
	if ( num >= UI_LEDS_COUNT ) return;

	const uint8_t li = num / 4;
	const uint8_t co = 3 - num % 4;
	const uint8_t x = 0 + 15 + co * (20 + 6);
	const uint8_t y = 159 - (li + 1) * ( 32 + 6 );
	const bool on = this->get_led( num );

	if ( _display == nullptr ) return;

	const uint16_t foreground_color = _display->get_foreground_color();
	const uint16_t background_color = _display->get_background_color();

	if ( on ) {
		_display->set_foreground_color( this->get_color() );
	}
	else {
		_display->set_foreground_color( 32, 32, 32 );
	}
	_display->set_background_color( 0, 0, 0 );
	_display->draw_graymap( led_20_32, 640, x, y, 20, 32 );

	_display->set_foreground_color( foreground_color );
	_display->set_background_color( background_color );
}

//----------------------------------------------------------------
