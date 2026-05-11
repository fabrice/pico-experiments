//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// rotaty encoder
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico/stdio.h"

#include "hardware/gpio.h"

//----------------------------------------------------------------

class rotary_encoder;

//----------------------------------------------------------------

rotary_encoder* encoder_init( uint a_gpio, uint b_gpio, uint s_gpio );

bool encoder_get_a( const rotary_encoder* that );
bool encoder_get_b( const rotary_encoder* that );
bool encoder_get_s( const rotary_encoder* that );

bool encoder_is_a_equal_b( const rotary_encoder* that );
bool encoder_is_a_notequal_b( const rotary_encoder* that );

int32_t encoder_get_rotations( const rotary_encoder* that );
int8_t encoder_use_rotation( rotary_encoder* that );

int8_t encoder_get_direction( const rotary_encoder* that );

uint32_t encoder_get_clicks( const rotary_encoder* that );
bool encoder_use_click( rotary_encoder* that );

void encoder_set_callback_a( rotary_encoder* that, gpio_irq_callback_t callback );
void encoder_set_callback_s( rotary_encoder* that, gpio_irq_callback_t callback );

void encoder_deinit( rotary_encoder*& that );

//----------------------------------------------------------------
