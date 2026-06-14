//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// working_led
//
//----------------------------------------------------------------

#include "working_led.h"

#include "hardware/gpio.h"
#include "pico/time.h"
#include "pico/status_led.h"

#include <cstdint>
#include <cmath>

//----------------------------------------------------------------

namespace local {

uint gpio = 255;

uint32_t period = 0;
float cycle = 0;

absolute_time_t timestamp;

}

//----------------------------------------------------------------

void working_led_init( uint gpio, uint32_t period, float cycle ) {
	if ( (cycle < 0.0f) || (cycle > 1.0f) ) cycle = 0.5f;

	local::gpio = gpio;
	local::period = period;
	local::cycle = cycle;
	local::timestamp = get_absolute_time();

	if ( local::gpio < 255 ) {
		gpio_init( local::gpio );
		gpio_set_dir( local::gpio, GPIO_OUT );
		gpio_put( local::gpio, false );
	}
	else {
		status_led_init();
		status_led_set_state( true );
	}
}

//----------------------------------------------------------------

void working_led_set_period( uint32_t period ) {
	local::period = period;
	working_led_start();
}

//----------------------------------------------------------------

void working_led_set_cycle( float cycle ) {
	local::cycle = cycle;
	working_led_tick();
}

//----------------------------------------------------------------

void working_led_start() {
	local::timestamp = get_absolute_time();
	working_led_set_led();
}

//----------------------------------------------------------------

void working_led_tick() {
	absolute_time_t now = get_absolute_time();
	absolute_time_t then = delayed_by_ms( local::timestamp, local::period );

	if ( now > then ) {
		local::timestamp = then;
		working_led_set_led();
	}
	else {
		uint32_t toggle_ms = static_cast< uint32_t >( std::round( static_cast< float >( local::period ) * local::cycle ) );
		working_led_put_led( now < delayed_by_ms( local::timestamp, toggle_ms ) );
	}
}

//----------------------------------------------------------------

bool working_led_get_led() {
	if ( local::gpio < 255 ) {
		return gpio_get( local::gpio );
	}
	else {
		return status_led_get_state();
	}
}

//----------------------------------------------------------------

void working_led_put_led( bool on ) {
	if ( local::gpio < 255 ) {
		gpio_put( local::gpio, on );
	}
	else {
		status_led_set_state( on );
	}
}

//----------------------------------------------------------------

void working_led_set_led() {
	working_led_put_led( true );
}

//----------------------------------------------------------------

void working_led_clr_led() {
	working_led_put_led( false );
}

//----------------------------------------------------------------

void working_led_xor_led() {
	working_led_put_led( working_led_get_led() );
}

//----------------------------------------------------------------
