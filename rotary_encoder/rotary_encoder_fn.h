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
using rotary_encoder_ref = rotary_encoder*;

//----------------------------------------------------------------

rotary_encoder_ref encoder_init( uint a_gpio, uint b_gpio, uint s_gpio );

bool encoder_get_a( rotary_encoder_ref encoder );
bool encoder_get_b( rotary_encoder_ref encoder );
bool encoder_get_s( rotary_encoder_ref encoder );

bool encoder_is_a_equal_b( rotary_encoder_ref encoder );
bool encoder_is_a_notequal_b( rotary_encoder_ref encoder );

int32_t encoder_get_rotations( rotary_encoder_ref encoder );
int8_t encoder_use_rotation( rotary_encoder_ref encoder );

int8_t encoder_get_direction( rotary_encoder_ref encoder );

uint32_t encoder_get_clicks( rotary_encoder_ref encoder );
bool encoder_use_click( rotary_encoder_ref encoder );

void encoder_set_callback_a( rotary_encoder_ref encoder, gpio_irq_callback_t callback );
void encoder_set_callback_s( rotary_encoder_ref encoder, gpio_irq_callback_t callback );

void encoder_deinit( rotary_encoder_ref& encoder );

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
