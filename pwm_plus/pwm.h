//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// pwm
//
//----------------------------------------------------------------

#pragma once
#ifndef _PWM_H
#define _PWM_H

//----------------------------------------------------------------

#include "pico/stdlib.h"

#include "pwm_slice.h"

#include "hardware/pwm.h"

#include "hardware_pwm_plus.h"
#include "math_plus.h"

//----------------------------------------------------------------

class pwm;
using pwm_ref = pwm*;

//----------------------------------------------------------------

class pwm {

private:

	uint gpio;
	pwm_slice_ref slice;
	uint16_t level;

public:

	pwm( uint gpio );
	pwm( uint gpio, float divider, uint16_t wrap, uint16_t level );
	pwm( uint gpio, uint8_t divider_uint, uint8_t divider_frac, uint16_t wrap, uint16_t level );
	pwm( uint gpio, float frequency, float duty );
	pwm( uint gpio, pwm_slice_ref slice );

private:

	void io_init();

public:

	~pwm();

	inline uint get_gpio() const { return this->gpio; };

	// slice

	inline pwm_slice_ref get_slice() { return this->slice; };

	inline uint8_t get_divider_uint() const { return this->slice->get_divider_uint(); };
	inline uint8_t get_divider_frac() const { return this->slice->get_divider_frac(); };
	inline float get_divider() const { return this->slice->get_divider(); };
	inline uint16_t get_divider_pack() const { return this->slice->get_divider_pack(); };

	void set_divider( float divider );
	void set_divider( uint8_t divider_uint, uint8_t divider_frac );

	inline void set_wrap( uint16_t wrap ) { this->slice->set_wrap( wrap ); };
	
	inline float get_frequency() const { return slice->get_frequency(); };
	void set_frequency( float frequency );

	// channel

	void set_level( uint16_t level );
	void set_duty( float duty );

	void set_channel_enabled();
	void set_channel_enabled( bool enabled, bool state );

	void set_enabled();
	void set_enabled( bool enabled, bool state );

};

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
