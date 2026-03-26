//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// Board : Pico Explorer Board
//
// hardware_pwm_plus
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico/stdlib.h" // all the pico base stuff
#include "hardware/pwm.h"
#include "hardware/clocks.h"

//----------------------------------------------------------------

constexpr float pwm_divider_max = 255.0 + 15.0 / 16.0;

//----------------------------------------------------------------

static inline uint16_t pwm_get_clkdiv_int_frac4( uint slice_num ) {
    check_slice_num_param(slice_num);

	return pwm_hw->slice[slice_num].div;
}

//----------------------------------------------------------------

static inline uint16_t pwm_get_wrap( uint slice_num ) {
    check_slice_num_param(slice_num);

	return pwm_hw->slice[slice_num].top;
}

//----------------------------------------------------------------

static inline void pwm_set_chan_duty( uint slice_num, uint chan, float duty ) {
    check_slice_num_param(slice_num);
	valid_params_if( HARDWARE_PWM, (duty >= 0.0f) && (duty <= 1.0f) );

	uint16_t wrap = pwm_get_wrap( slice_num );
	pwm_set_chan_level( slice_num, chan, (uint16_t)(duty * (float)wrap) );
}

//----------------------------------------------------------------

inline float pwm_get_frequency_min() {
	float clock = (float)clock_get_hz( clk_sys );
	return clock / (pwm_divider_max * 65536.0);
}

//----------------------------------------------------------------
