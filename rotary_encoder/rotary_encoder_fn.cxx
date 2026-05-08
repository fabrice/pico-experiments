//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// rotaty encoder
//
//----------------------------------------------------------------

#include "rotary_encoder_fn.h"
#include "rotary_encoder.h"

#include "pico/stdio.h"
#include "pico/printf.h"

#include "gpio_irq_vtable.h"

//----------------------------------------------------------------

constexpr uint ENCODER_A_GPIO { 7 };
constexpr uint ENCODER_B_GPIO { 8 };
constexpr uint ENCODER_S_GPIO { 9 };

//----------------------------------------------------------------

rotary_encoder* encoder_init( uint a_gpio, uint b_gpio, uint s_gpio ) {
	return new rotary_encoder( a_gpio, b_gpio, s_gpio );
}

//----------------------------------------------------------------

bool encoder_get_a( const rotary_encoder* that ) {
	if ( that == nullptr ) return false;

	return that->get_a();
}

//----------------------------------------------------------------

bool encoder_get_b( const rotary_encoder* that ) {
	if ( that == nullptr ) return false;

	return that->get_b();
}

//----------------------------------------------------------------

bool encoder_get_s( const rotary_encoder* that ) {
	if ( that == nullptr ) return false;

	return that->get_s();
}

//----------------------------------------------------------------

bool encoder_is_a_equal_b( const rotary_encoder* that ) {
	if ( that == nullptr ) return false;

	return that->is_a_equal_b();
}

//----------------------------------------------------------------

bool encoder_is_a_notequal_b( const rotary_encoder* that ) {
	if ( that == nullptr ) return false;

	return that->is_a_notequal_b();
}

//----------------------------------------------------------------

int32_t encoder_get_rotations( const rotary_encoder* that ) {
	if ( that == nullptr ) return 0;

	return that->get_rotations();
}

//----------------------------------------------------------------

int8_t encoder_use_rotation( rotary_encoder* that ) {
	if ( that == nullptr ) return 0;

	return that->use_rotation();
}

//----------------------------------------------------------------

int8_t encoder_get_direction( const rotary_encoder* that ) {
	if ( that == nullptr ) return 0;

	return that->get_direction();
}

//----------------------------------------------------------------

uint32_t encoder_get_clicks( const rotary_encoder* that ) {
	if ( that == nullptr ) return 0;

	return that->get_clicks();
}

//----------------------------------------------------------------

bool encoder_use_click( rotary_encoder* that ) {
	if ( that == nullptr ) return false;

	return that->use_click();
}

//----------------------------------------------------------------

void encoder_set_callback_a( rotary_encoder* that, gpio_irq_callback_t callback ) {
	if ( that == nullptr ) return;

	gpio_irq_vtable_set_callback( that->get_a_gpio(), callback );
}

//----------------------------------------------------------------

void encoder_set_callback_s( rotary_encoder* that, gpio_irq_callback_t callback ) {
	if ( that == nullptr ) return;

	gpio_irq_vtable_set_callback( that->get_s_gpio(), callback );
}

//----------------------------------------------------------------

void encoder_deinit( rotary_encoder*& that ) {
	if ( that == nullptr ) return;

	delete that;
	that = nullptr;
}

//----------------------------------------------------------------
