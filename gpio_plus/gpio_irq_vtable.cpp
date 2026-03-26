//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// gpio_irq_vtable
//
//----------------------------------------------------------------

#include "gpio_irq_vtable.h"

#include "pico/printf.h"

#include <vector>
#include <functional>

//----------------------------------------------------------------

__isr
void gpio_irq_vtable_callback( uint gpio, uint32_t events );

//----------------------------------------------------------------

static std::vector< gpio_irq_fn_callback_t > gpio_irq_fn_vtable( 32, nullptr );

//----------------------------------------------------------------

void gpio_irq_vtable_init() {
	gpio_irq_fn_vtable.resize( 32, nullptr );

	gpio_set_irq_callback( &gpio_irq_vtable_callback );
}

//----------------------------------------------------------------

void gpio_irq_vtable_deinit() {
	gpio_irq_fn_vtable.clear();
	gpio_irq_fn_vtable.shrink_to_fit();
}

//----------------------------------------------------------------

void gpio_irq_vtable_set_callback( uint gpio, gpio_irq_callback_t callback ) {
	//gpio_irq_vtable_set_fn_callback( gpio, [callback]( uint gpio, uint32_t events ) -> void { callback( gpio, events ); } );
	gpio_irq_vtable_set_fn_callback( gpio, callback );
}

//----------------------------------------------------------------

void gpio_irq_vtable_set_fn_callback( uint gpio, gpio_irq_fn_callback_t fn_callback ) {
	if ( gpio_irq_fn_vtable.size() <= gpio ) gpio_irq_fn_vtable.resize( gpio + 1, nullptr );
	gpio_irq_fn_vtable.at( gpio ) = fn_callback;
}

//----------------------------------------------------------------

void gpio_irq_vtable_call_callback( uint gpio, uint32_t events ) {
	gpio_irq_vtable_callback( gpio, events );
}

//----------------------------------------------------------------

__isr
void gpio_irq_vtable_callback( uint gpio, uint32_t events ) {
	size_t fn_callback_count = gpio_irq_fn_vtable.size();
	if ( fn_callback_count == 0 ) return;

	if ( gpio < fn_callback_count ) {
		gpio_irq_fn_callback_t fn_callback = gpio_irq_fn_vtable.at( gpio );
		if ( fn_callback != nullptr ) fn_callback( gpio, events );
	}
}

//----------------------------------------------------------------
