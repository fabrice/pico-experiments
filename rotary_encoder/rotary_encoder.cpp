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
	a_gpio( ENCODER_A_GPIO ),
	b_gpio( ENCODER_B_GPIO ),
	s_gpio( ENCODER_S_GPIO ),
	rotations( 0 ),
	clicks( 0 ) {
	this->io_init();
}

//----------------------------------------------------------------

rotary_encoder::rotary_encoder( uint a_gpio, uint b_gpio, uint s_gpio ):
	a_gpio( a_gpio ),
	b_gpio( b_gpio ),
	s_gpio( s_gpio ),
	rotations( 0 ),
	clicks( 0 ) {
	this->io_init();
}

//----------------------------------------------------------------

rotary_encoder::~rotary_encoder() {
	this->io_deinit();
}

//----------------------------------------------------------------

void rotary_encoder::io_init() {
	gpio_init( this->a_gpio );
    gpio_set_dir( this->a_gpio, GPIO_IN );
	gpio_disable_pulls( this->a_gpio );
	gpio_set_input_hysteresis_enabled( this->a_gpio, true );

	gpio_init( this->b_gpio );
    gpio_set_dir( this->b_gpio, GPIO_IN );
	gpio_disable_pulls( this->b_gpio );
	gpio_set_input_hysteresis_enabled( this->b_gpio, true );

	gpio_init( this->s_gpio );
    gpio_set_dir( this->s_gpio, GPIO_IN );
	gpio_disable_pulls( this->s_gpio );
	gpio_set_input_hysteresis_enabled( this->s_gpio, true );

	this->interrupts_init();
}

//----------------------------------------------------------------

void rotary_encoder::interrupts_init() {
	gpio_irq_vtable_init();
	gpio_irq_vtable_set_fn_callback( this->a_gpio, [this]( uint gpio, uint32_t events ) -> void { this->gpio_interrupt_a( gpio, events ); } );
	gpio_irq_vtable_set_fn_callback( this->s_gpio, [this]( uint gpio, uint32_t events ) -> void { this->gpio_interrupt_s( gpio, events ); } );

	gpio_set_irq_enabled( this->a_gpio, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true );
	gpio_set_irq_enabled( this->s_gpio, GPIO_IRQ_EDGE_FALL, true );
    irq_set_enabled( IO_IRQ_BANK0, true );
}

//----------------------------------------------------------------

void rotary_encoder::io_deinit() {
	gpio_set_irq_enabled( this->a_gpio, 0, false );
	gpio_set_irq_enabled( this->s_gpio, 0, false );

	gpio_irq_vtable_set_callback( this->a_gpio, nullptr );
	gpio_irq_vtable_set_callback( this->s_gpio, nullptr );

	gpio_deinit( this->a_gpio );
	gpio_deinit( this->b_gpio );
	gpio_deinit( this->s_gpio );
}

//----------------------------------------------------------------

int8_t rotary_encoder::use_rotation() {
	if ( this->rotations > 0 ) {
		this->rotations -= 1;
		return 1;
	}
	else if ( this->rotations < 0 ) {
		this->rotations += 1;
		return -1;
	}

	return 0;
}

//----------------------------------------------------------------

int8_t rotary_encoder::get_direction() const {
	return (this->rotations > 0) ? +1 : ((this->rotations < 0) ? -1 : 0);
}

//----------------------------------------------------------------

bool rotary_encoder::use_click() {
	if ( this->clicks > 0 ) {
		this->clicks -= 1;
		return true;
	}

	return false;
}

//----------------------------------------------------------------

void rotary_encoder::gpio_interrupt_a( uint gpio, uint32_t events ) {
	if ( this->is_a_equal_b() ) {
		this->rotations += 1;
	}
	else {
		this->rotations -= 1;
	}
}

//----------------------------------------------------------------

void rotary_encoder::gpio_interrupt_s( uint gpio, uint32_t events ) {
	if ( this->get_s() == 0 ) {
		this->clicks += 1;
	}
}

//----------------------------------------------------------------
