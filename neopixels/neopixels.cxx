//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// neopixels
//
//----------------------------------------------------------------

#include "neopixels.h"

#include "pico/status_led.h"
#include "ws2812.pio.h"

//----------------------------------------------------------------

neopixels* neopixels::make( uint gpio ) {
	auto that = new neopixels( gpio, FORMAT_RGB, 1 );
	return that;
}

//----------------------------------------------------------------

neopixels* neopixels::make( uint gpio, uint8_t format, size_t count ) {
	auto that = new neopixels( gpio, format, count );
	return that;
}

//----------------------------------------------------------------

neopixels::neopixels( uint gpio, uint8_t format, size_t count ):
		_gpio { gpio },
		_format { format },
		_count { count } {
	gpio_init( _gpio );
	gpio_set_dir( _gpio, GPIO_OUT );
	gpio_put( _gpio, false );

	if ( (_format != FORMAT_RGB) && (_format != FORMAT_GRB) && (_format != FORMAT_RGBW) && (_format != FORMAT_GRBW) ) _format = FORMAT_RGB;
	uint8_t bits = 24;
	if ( (_format == FORMAT_RGBW) || (_format == FORMAT_GRBW) ) bits = 32;

	// pio
	bool success = pio_claim_free_sm_and_add_program_for_gpio_range( &ws2812_program, &_pio, &_pio_state_machine, &_pio_offset, _gpio, 1, true );
	if ( success ) ws2812_program_init( _pio, _pio_state_machine, _pio_offset, _gpio, 800000, bits == 32 );

	this->start();
}

//----------------------------------------------------------------

neopixels::~neopixels() {
	this->start();
	this->send_all_black();
	this->finish();

	if ( _pio != nullptr ) {
		pio_remove_program_and_unclaim_sm( &ws2812_program, _pio, _pio_state_machine, _pio_offset );
		_pio = nullptr; 
		_pio_state_machine = 0;
		_pio_offset = 0;
	}
}

//----------------------------------------------------------------

void neopixels::send_reset() const {
	if ( _gpio == 255 ) return;

	gpio_put( _gpio, false );
	sleep_us( RESET_TIME );
}

//----------------------------------------------------------------

void neopixels::send_rgb( uint8_t red, uint8_t green, uint8_t blue ) const {
	if ( _pio == nullptr ) return;

	uint32_t pixel = 0;
	switch ( _format ) {
	case FORMAT_RGB:
		pixel = (uint32_t)red << 24 | (uint32_t)green << 16 | (uint32_t)blue << 8;
		break;
	case FORMAT_GRB:
		pixel = (uint32_t)green << 24 | (uint32_t)red << 16 | (uint32_t)blue << 8;
		break;
	default:
		pixel = (uint32_t)red << 24 | (uint32_t)green << 16 | (uint32_t)blue << 8;
		break;
	}
	pio_sm_put_blocking( _pio, _pio_state_machine, pixel );
}

//----------------------------------------------------------------

void neopixels::send_rgbw( uint8_t red, uint8_t green, uint8_t blue, uint8_t white ) const {
	if ( _pio == nullptr ) return;

	uint32_t pixel = 0;
	switch ( _format ) {
	case FORMAT_RGB:
		pixel = (uint32_t)red << 24 | (uint32_t)green << 16 | (uint32_t)blue << 8;
		break;
	case FORMAT_GRB:
		pixel = (uint32_t)green << 24 | (uint32_t)red << 16 | (uint32_t)blue << 8;
		break;
	case FORMAT_RGBW:
		pixel = (uint32_t)red << 24 | (uint32_t)green << 16 | (uint32_t)blue << 8 | (uint32_t)white;
		break;
	case FORMAT_GRBW:
		pixel = (uint32_t)green << 24 | (uint32_t)red << 16 | (uint32_t)blue << 8 | (uint32_t)white;
		break;
	default:
		pixel = (uint32_t)red << 24 | (uint32_t)green << 16 | (uint32_t)blue << 8 | (uint32_t)white;
		break;
	}
	pio_sm_put_blocking( _pio, _pio_state_machine, pixel );
}

//----------------------------------------------------------------

void neopixels::send_white( uint8_t white ) const {
	switch ( _format ) {
	case FORMAT_RGB:
	case FORMAT_GRB:
		this->send_rgb( white, white, white );
		break;
	case FORMAT_RGBW:
	case FORMAT_GRBW:
		this->send_rgbw( 0, 0, 0, white );
		break;
	default:
		this->send_rgbw( white, white, white, white );
		break;
	}
}

//----------------------------------------------------------------

void neopixels::send_black() const {
	this->send_rgbw( 0, 0, 0, 0 );
}

//----------------------------------------------------------------

void neopixels::send_many_rgb( size_t count, uint8_t red, uint8_t green, uint8_t blue ) const {
	for ( size_t index = 0 ; index < count ; ++ index ) {
		this->send_rgb( red, green, blue );
	}
}

//----------------------------------------------------------------

void neopixels::send_many_rgbw( size_t count, uint8_t red, uint8_t green, uint8_t blue, uint8_t white ) const {
	for ( size_t index = 0 ; index < count ; ++ index ) {
		this->send_rgbw( red, green, blue, white );
	}
}

//----------------------------------------------------------------

void neopixels::send_many_white( size_t count, uint8_t white ) const {
	for ( size_t index = 0 ; index < count ; ++ index ) {
		this->send_white( white );
	}
}

//----------------------------------------------------------------

void neopixels::send_many_black( size_t count ) const {
	for ( size_t index = 0 ; index < count ; ++ index ) {
		this->send_black();
	}
}

//----------------------------------------------------------------

void neopixels::send_all_rgb( uint8_t red, uint8_t green, uint8_t blue ) const {
	this->send_many_rgb( _count, red, green, blue );
}

//----------------------------------------------------------------

void neopixels::send_all_rgbw( uint8_t red, uint8_t green, uint8_t blue, uint8_t white ) const {
	this->send_many_rgbw( _count, red, green, blue, white );
}

//----------------------------------------------------------------

void neopixels::send_all_white( uint8_t white ) const {
	this->send_many_white( _count, white );
}

//----------------------------------------------------------------

void neopixels::send_all_black() const {
	this->send_many_black( _count );
}

//----------------------------------------------------------------
