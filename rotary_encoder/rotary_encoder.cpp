//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// rotaty encoder
//
//----------------------------------------------------------------

#include "rotary_encoder.h"
#include "rotary_encoder_fn.h"

#include "pico/stdio.h"
#include "pico/printf.h"

#include "gpio_irq_vtable.h"

#include <functional>

//----------------------------------------------------------------

constexpr uint ENCODER_A_GPIO = 7;
constexpr uint ENCODER_B_GPIO = 8;
constexpr uint ENCODER_S_GPIO = 9;

//----------------------------------------------------------------

rotary_encoder::rotary_encoder():
	_a_gpio( ENCODER_A_GPIO ),
	_b_gpio( ENCODER_B_GPIO ),
	_s_gpio( ENCODER_S_GPIO ),
	_rotations( 0 ),
	_clicks( 0 ) {
	this->io_init();
}

//----------------------------------------------------------------

rotary_encoder::rotary_encoder( uint a_gpio, uint b_gpio, uint s_gpio ):
	_a_gpio( a_gpio ),
	_b_gpio( b_gpio ),
	_s_gpio( s_gpio ),
	_rotations( 0 ),
	_clicks( 0 ) {
	this->io_init();
}

//----------------------------------------------------------------

rotary_encoder::~rotary_encoder() {
	this->io_deinit();
}

//----------------------------------------------------------------

void rotary_encoder::io_init() {
	gpio_init( _a_gpio );
    gpio_set_dir( _a_gpio, GPIO_IN );
	gpio_disable_pulls( _a_gpio );
	gpio_set_input_hysteresis_enabled( _a_gpio, true );

	gpio_init( _b_gpio );
    gpio_set_dir( _b_gpio, GPIO_IN );
	gpio_disable_pulls( _b_gpio );
	gpio_set_input_hysteresis_enabled( _b_gpio, true );

	gpio_init( _s_gpio );
    gpio_set_dir( _s_gpio, GPIO_IN );
	gpio_disable_pulls( _s_gpio );
	gpio_set_input_hysteresis_enabled( _s_gpio, true );

	this->interrupts_init();
}

//----------------------------------------------------------------

void rotary_encoder::interrupts_init() {
	gpio_irq_vtable_init();
	gpio_irq_vtable_set_fn_callback( _a_gpio, [this]( uint gpio, uint32_t events ) -> void { this->gpio_interrupt_a( gpio, events ); } );
	gpio_irq_vtable_set_fn_callback( _s_gpio, [this]( uint gpio, uint32_t events ) -> void { this->gpio_interrupt_s( gpio, events ); } );

	gpio_set_irq_enabled( _a_gpio, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true );
	gpio_set_irq_enabled( _s_gpio, GPIO_IRQ_EDGE_FALL, true );
    irq_set_enabled( IO_IRQ_BANK0, true );
}

//----------------------------------------------------------------

void rotary_encoder::io_deinit() {
	gpio_set_irq_enabled( _a_gpio, 0, false );
	gpio_set_irq_enabled( _s_gpio, 0, false );

	gpio_irq_vtable_set_callback( _a_gpio, nullptr );
	gpio_irq_vtable_set_callback( _s_gpio, nullptr );

	gpio_deinit( _a_gpio );
	gpio_deinit( _b_gpio );
	gpio_deinit( _s_gpio );
}

//----------------------------------------------------------------

int8_t rotary_encoder::use_rotation() {
	if ( _rotations > 0 ) {
		_rotations -= 1;
		return 1;
	}
	else if ( _rotations < 0 ) {
		_rotations += 1;
		return -1;
	}

	return 0;
}

//----------------------------------------------------------------

int8_t rotary_encoder::get_direction() const {
	return (_rotations > 0) ? +1 : ((_rotations < 0) ? -1 : 0);
}

//----------------------------------------------------------------

bool rotary_encoder::use_click() {
	if ( _clicks > 0 ) {
		_clicks -= 1;
		return true;
	}

	return false;
}

//----------------------------------------------------------------

void rotary_encoder::gpio_interrupt_a( uint gpio, uint32_t events ) {
	if ( this->is_a_equal_b() ) {
		_rotations += 1;
	}
	else {
		_rotations -= 1;
	}
}

//----------------------------------------------------------------

void rotary_encoder::gpio_interrupt_s( uint gpio, uint32_t events ) {
	if ( this->get_s() == 0 ) {
		_clicks += 1;
	}
}

//----------------------------------------------------------------
