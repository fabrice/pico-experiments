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

class pwm {

private:

	uint _gpio { 255 };
	pwm_slice* _slice { nullptr };
	uint16_t _level { 32767 };

public:

	pwm() = delete;
	pwm( uint gpio );
	pwm( uint gpio, float divider, uint16_t wrap, uint16_t level );
	pwm( uint gpio, uint8_t divider_uint, uint8_t divider_frac, uint16_t wrap, uint16_t level );
	pwm( uint gpio, float frequency, float duty );
	pwm( uint gpio, pwm_slice* slice );

private:

	void io_init();

public:

	~pwm();

	inline uint get_gpio() const { return _gpio; };

	// slice

	inline pwm_slice* get_slice() { return _slice; };

	inline uint8_t get_divider_uint() const { return _slice->get_divider_uint(); };
	inline uint8_t get_divider_frac() const { return _slice->get_divider_frac(); };
	inline float get_divider() const { return _slice->get_divider(); };
	inline uint16_t get_divider_pack() const { return _slice->get_divider_pack(); };

	void set_divider( float divider );
	void set_divider( uint8_t divider_uint, uint8_t divider_frac );

	inline void set_wrap( uint16_t wrap ) { _slice->set_wrap( wrap ); };
	
	inline float get_frequency() const { return _slice->get_frequency(); };
	void set_frequency( float frequency );

	// channel

	void set_level( uint16_t level );
	void set_duty( float duty );
	void set_duty_db( float duty_dB );

	void set_channel_enabled();
	void set_channel_enabled( bool enabled, bool state );

	void set_enabled();
	void set_enabled( bool enabled, bool state );

};

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
