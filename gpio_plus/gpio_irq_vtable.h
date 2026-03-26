//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// gpio_irq_vtable
//
//----------------------------------------------------------------

#pragma once
#ifndef _GPIO_IRQ_VTABLE_H
#define _GPIO_IRQ_VTABLE_H

//----------------------------------------------------------------

#include "pico.h"
#include "hardware/gpio.h"

#include <functional>

//----------------------------------------------------------------

using gpio_irq_fn_callback_t = std::function< void(uint, uint32_t) >;

//----------------------------------------------------------------

void gpio_irq_vtable_init();
void gpio_irq_vtable_deinit();

void gpio_irq_vtable_set_callback( uint gpio, gpio_irq_callback_t callback );
void gpio_irq_vtable_set_fn_callback( uint gpio, gpio_irq_fn_callback_t fn_callback );

void gpio_irq_vtable_call_callback( uint gpio, uint32_t events );

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
