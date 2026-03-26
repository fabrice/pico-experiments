//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// pwm
//
//----------------------------------------------------------------

#include "pwm_slice.h"

#include "pico/stdlib.h"

#include "hardware/clocks.h"
#include "hardware/pwm.h"

#include "hardware_pwm_plus.h"

//----------------------------------------------------------------

pwm_slice::pwm_slice( uint slice_num ):
	v_reference_count( true ),
	slice_num( slice_num ),
	divider_uint( 1 ),
	divider_frac( 0 ),
	wrap( 65535 ) {
	check_slice_num_param( slice_num );
	this->set_divider( this->divider_uint, this->divider_frac );
	this->set_wrap( this->wrap );
}

//----------------------------------------------------------------

pwm_slice::pwm_slice( uint slice_num, uint8_t divider_uint, uint8_t divider_frac, uint16_t wrap ):
	v_reference_count( true ),
	slice_num( slice_num ),
	divider_uint( divider_uint ),
	divider_frac( divider_frac ),
	wrap( wrap ) {
	check_slice_num_param( slice_num );
	this->set_divider( divider_uint, divider_frac );
	this->set_wrap( wrap );
}

//----------------------------------------------------------------

pwm_slice::pwm_slice( uint slice_num, float divider, uint16_t wrap ):
	v_reference_count( true ),
	slice_num( slice_num ),
	divider_uint( 1 ),
	divider_frac( 0 ),
	wrap( wrap ) {
	check_slice_num_param( slice_num );
	this->set_divider( divider );
	this->set_wrap( wrap );
}

//----------------------------------------------------------------

pwm_slice::pwm_slice( uint slice_num, float frequency ):
	v_reference_count( true ),
	slice_num( slice_num ),
	divider_uint( 1 ),
	divider_frac( 0 ),
	wrap( 65535 ) {
	check_slice_num_param( slice_num );
	this->set_frequency( frequency );
}

//----------------------------------------------------------------

pwm_slice::~pwm_slice() {
	this->set_enabled( false );
}

//----------------------------------------------------------------

float pwm_slice::get_divider() const {
	return (float)divider_uint + (float)divider_frac / 16.0f;
}

//----------------------------------------------------------------

void pwm_slice::set_divider( uint8_t divider_uint, uint8_t divider_frac ) {
	valid_params_if( HARDWARE_PWM, divider_uint >= 1 );
	valid_params_if( HARDWARE_PWM, divider_frac < 16 );

	this->divider_uint = divider_uint;
	this->divider_frac = divider_frac;

	pwm_set_clkdiv_int_frac4( this->slice_num, this->divider_uint, this->divider_frac );
}

//----------------------------------------------------------------

void pwm_slice::set_divider( float divider ) {
	valid_params_if( HARDWARE_PWM, divider >= 1 );
	valid_params_if( HARDWARE_PWM, divider <= (255.0f + 15.0f / 16.0f) );

	divider += 0.5f / 16.0f;
	this->divider_uint = (uint8_t)divider;
	this->divider_frac = (uint8_t)((divider - this->divider_uint) * 16.0f);

	pwm_set_clkdiv_int_frac4( this->slice_num, this->divider_uint, this->divider_frac );
}

//----------------------------------------------------------------

void pwm_slice::set_wrap( uint16_t wrap ) {
	this->wrap = wrap;

	pwm_set_wrap( this->slice_num, this->wrap );
}

//----------------------------------------------------------------

float pwm_slice::get_frequency() const {
	float clock = (float)clock_get_hz( clk_sys );

	return clock / (this->get_divider() * (float)this->wrap);
}

//----------------------------------------------------------------

void pwm_slice::set_frequency( float frequency ) {
	valid_params_if( HARDWARE_PWM, frequency >= 0.0f );

	float clock = (float)clock_get_hz( clk_sys );
	float cycles = clock / frequency;

	float divider = cycles / 65536.0f + 0.5f / 16.0f;
	divider = fmaxf( 1.0f, fminf( divider, 255.0f + 15.0f / 16.0f ) );

	float divider_uint = floorf( divider );
	float divider_frac = floorf( (divider - divider_uint) * 16.0f );
	divider = divider_uint + divider_frac / 16.0f;

	float wrap = floorf( cycles / divider - 1.0f );
	wrap = fmaxf( 0.0f, fminf( wrap, 65535.0f ) );

	this->divider_uint = (uint8_t)divider_uint;
	this->divider_frac = (uint8_t)divider_frac;
	this->wrap = (uint16_t)wrap;

	pwm_set_clkdiv_int_frac4( this->slice_num, this->divider_uint, this->divider_frac );
	pwm_set_wrap( this->slice_num, this->wrap );
}

//----------------------------------------------------------------

void pwm_slice::set_enabled( bool enabled ) {
	pwm_set_enabled( this->slice_num, enabled );
}

//----------------------------------------------------------------
