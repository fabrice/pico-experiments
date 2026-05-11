//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// ui leds
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico/stdlib.h"

#include "display_7735.h"

#include <cstdint>
#include <string_view>

//----------------------------------------------------------------

class ui_leds {

private:

	display_7735* _display { nullptr };

	std::string_view _title {};
	std::string_view _message {};

	uint16_t _leds { 0 };
	uint8_t _color { 0b0111 };

public:

	static ui_leds* make( display_7735* display );

	ui_leds() = default;
	explicit ui_leds( display_7735* display ): _display { display } {}
	ui_leds( display_7735* display, const std::string_view& title ): _title { title } {}
	ui_leds( const ui_leds& that ) = delete;

	~ui_leds() noexcept = default;

	void set_title( const std::string_view& text );
	void set_message( const std::string_view& text );

	uint get_led_count() const;

	uint32_t get_leds() const;
	void put_leds( uint32_t leds );
	void clr_leds();

	bool get_led( uint num ) const;
	void put_led( uint num, bool on );
	void set_led( uint num );
	void clr_led( uint num );
	void xor_led( uint num );

	void set_color( bool red, bool green, bool blue );

	void refresh();

private:

	uint16_t get_color() const;
	void refresh_led( uint num );

};

//----------------------------------------------------------------
