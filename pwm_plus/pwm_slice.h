//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// pwm_slice
//
//----------------------------------------------------------------

#pragma once
#ifndef _PWM_SLICE_H
#define _PWM_SLICE_H

//----------------------------------------------------------------

#include "pico/stdlib.h"

#include "hardware/pwm.h"

#include "hardware_pwm_plus.h"
#include "math_plus.h"
#include "v_reference_count.h"

//----------------------------------------------------------------

class pwm_slice;
using pwm_slice_ref = pwm_slice*;

//----------------------------------------------------------------

class pwm_slice : public virtual v_reference_count {

private:

	uint _slice_num;
	uint8_t _divider_uint;
	uint8_t _divider_frac;
	uint16_t _wrap;

public:

	pwm_slice( uint slice_num );
	pwm_slice( uint slice_num, uint8_t divider_uint, uint8_t divider_frac, uint16_t wrap );
	pwm_slice( uint slice_num, float divider, uint16_t wrap );
	pwm_slice( uint slice_num, float frequency );

private:

	virtual ~pwm_slice() override;

public:

	inline uint get_slice_num() const { return _slice_num; };
	inline uint8_t get_divider_uint() const { return _divider_uint; };
	inline uint8_t get_divider_frac() const { return _divider_frac; };
	float get_divider() const;
	inline uint16_t get_divider_pack() const { return pack( _divider_uint, _divider_frac ); };

	void set_divider( uint8_t divider_uint, uint8_t divider_frac );
	void set_divider( float divider );

	inline uint16_t get_wrap() const { return _wrap; };
	void set_wrap( uint16_t wrap );

	float get_frequency() const;
	void set_frequency( float frequency );

	void set_enabled( bool enabled );

};

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
