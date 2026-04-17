//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// rotaty encoder
//
//----------------------------------------------------------------

#pragma once
#ifndef _ROTARY_ENCODER_FN_H
#define _ROTARY_ENCODER_FN_H

//----------------------------------------------------------------

#include "pico/stdio.h"

#include "hardware/gpio.h"

//----------------------------------------------------------------

class rotary_encoder;

//----------------------------------------------------------------

rotary_encoder* encoder_init( uint a_gpio, uint b_gpio, uint s_gpio );

bool encoder_get_a( const rotary_encoder* encoder );
bool encoder_get_b( const rotary_encoder* encoder );
bool encoder_get_s( const rotary_encoder* encoder );

bool encoder_is_a_equal_b( const rotary_encoder* encoder );
bool encoder_is_a_notequal_b( const rotary_encoder* encoder );

int32_t encoder_get_rotations( const rotary_encoder* encoder );
int8_t encoder_use_rotation( rotary_encoder* encoder );

int8_t encoder_get_direction( const rotary_encoder* encoder );

uint32_t encoder_get_clicks( const rotary_encoder* encoder );
bool encoder_use_click( rotary_encoder* encoder );

void encoder_set_callback_a( rotary_encoder* encoder, gpio_irq_callback_t callback );
void encoder_set_callback_s( rotary_encoder* encoder, gpio_irq_callback_t callback );

void encoder_deinit( rotary_encoder*& encoder );

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
