//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// pwm
//
//----------------------------------------------------------------

#include "pwm.h"

#include "pico/stdlib.h"

#include "hardware/clocks.h"
#include "hardware/pwm.h"

#include "hardware_pwm_plus.h"

//----------------------------------------------------------------

pwm::pwm( uint gpio ):
	gpio( gpio ),
	slice( nullptr ),
	level( 0 ) {
	uint slice_num = pwm_gpio_to_slice_num( this->gpio );
	this->slice = new pwm_slice( slice_num );
	this->io_init();
	this->set_duty( 0.5f );
}

//----------------------------------------------------------------

pwm::pwm( uint gpio, float divider, uint16_t wrap, uint16_t level ):
	gpio( gpio ),
	slice( nullptr ),
	level( level ) {
	uint slice_num = pwm_gpio_to_slice_num( this->gpio );
	this->slice = new pwm_slice( slice_num, divider, wrap );
	this->io_init();
	this->set_level( level );
}

//----------------------------------------------------------------

pwm::pwm( uint gpio, uint8_t divider_uint, uint8_t divider_frac, uint16_t wrap, uint16_t level ):
	gpio( gpio ),
	slice( nullptr ),
	level( level ) {
	uint slice_num = pwm_gpio_to_slice_num( this->gpio );
	this->slice = new pwm_slice( slice_num, divider_uint, divider_frac, wrap );
	this->io_init();
	this->set_level( level );
}

//----------------------------------------------------------------

pwm::pwm( uint gpio, float frequency, float duty ):
	gpio( gpio ),
	slice( nullptr ),
	level( 0 ) {
	uint slice_num = pwm_gpio_to_slice_num( this->gpio );
	this->slice = new pwm_slice( slice_num, frequency );
	this->io_init();
	this->set_duty( duty );
}

//----------------------------------------------------------------

pwm::pwm( uint gpio, pwm_slice_ref slice ):
	gpio( gpio ),
	slice( slice ),
	level( 0 ) {
	this->slice->retain();
	this->io_init();
	this->set_duty( 0.5f );
}

//----------------------------------------------------------------

void pwm::io_init() {
	gpio_init( this->gpio );
	gpio_set_dir( this->gpio, GPIO_OUT );
	gpio_put( this->gpio, false );
}

//----------------------------------------------------------------

pwm::~pwm() {
	this->set_channel_enabled( false, false );
	gpio_deinit( gpio );

	this->slice->release();
	this->slice = nullptr;
}

//----------------------------------------------------------------

void pwm::set_divider( float divider ) {
	valid_params_if( HARDWARE_PWM, divider >= 1 );
	valid_params_if( HARDWARE_PWM, divider <= (255.0f + 15.0f / 16.0f) );

	slice->set_divider( divider );
}

//----------------------------------------------------------------

void pwm::set_divider( uint8_t divider_uint, uint8_t divider_frac ) {
	valid_params_if( HARDWARE_PWM, divider_uint >= 1 );
	valid_params_if( HARDWARE_PWM, divider_frac < 16 );

	slice->set_divider( divider_uint, divider_frac );
}

//----------------------------------------------------------------

void pwm::set_frequency( float frequency ) {
	valid_params_if( HARDWARE_PWM, frequency >= 0.0f );

	slice->set_frequency( frequency );
}

//----------------------------------------------------------------

void pwm::set_level( uint16_t level ) {
	this->level = level;

	uint slice_num = pwm_gpio_to_slice_num( this->gpio );
	uint channel_num = pwm_gpio_to_channel( this->gpio );
	pwm_set_chan_level( slice_num, channel_num, this->level );
}

//----------------------------------------------------------------

void pwm::set_duty( float duty ) {
	valid_params_if( HARDWARE_PWM, (duty >= 0.0f) && (duty <= 1.0f) );

	duty = constrain( duty, 0.0f, 1.0f );
	this->level = (uint16_t)(duty * (float)this->slice->get_wrap());

	uint slice_num = pwm_gpio_to_slice_num( this->gpio );
	uint channel_num = pwm_gpio_to_channel( this->gpio );
	pwm_set_chan_level( slice_num, channel_num, this->level );
}

//----------------------------------------------------------------

/*! pwm::set_duty_db()
 * \brief règle le rapport cyclique en dB, 0 correspondant à 100%, -40 correspondant à 1%.
 * \param duty_dB rapport cyclique, 0 dB : 100%, -6 dB : 50%, -40 dB : 1%, -60 : 0.1%
 */
void pwm::set_duty_db( float duty_dB ) {
	float duty = std::pow( 10.0f, duty_dB / 20.0f );
	duty = constrain( duty, 0.0f, 1.0f );
	this->set_duty( duty );
}

//----------------------------------------------------------------

void pwm::set_channel_enabled() {
	uint slice_num = pwm_gpio_to_slice_num( this->gpio );
	uint channel_num = pwm_gpio_to_channel( this->gpio );
	pwm_set_chan_level( slice_num, channel_num, this->level );
	pwm_set_enabled( slice_num, true );

	gpio_set_function( this->gpio, GPIO_FUNC_PWM );
}

//----------------------------------------------------------------

void pwm::set_channel_enabled( bool enabled, bool state ) {
	uint slice_num = pwm_gpio_to_slice_num( this->gpio );
	uint channel_num = pwm_gpio_to_channel( this->gpio );

	if ( enabled ) {
		pwm_set_chan_level( slice_num, channel_num, this->level );
		pwm_set_enabled( slice_num, true );

		gpio_set_function( this->gpio, GPIO_FUNC_PWM );
	}
	else {
		pwm_set_chan_level( slice_num, channel_num, state ? 65535 : 0 );

		gpio_set_function( this->gpio, GPIO_FUNC_SIO );
		gpio_set_dir( this->gpio, GPIO_OUT );
		gpio_put( this->gpio, state );
	}
}

//----------------------------------------------------------------

void pwm::set_enabled() {
	uint slice_num = pwm_gpio_to_slice_num( this->gpio );
	uint channel_num = pwm_gpio_to_channel( this->gpio );
	pwm_set_chan_level( slice_num, channel_num, this->level );
	pwm_set_enabled( slice_num, true );

	gpio_set_function( this->gpio, GPIO_FUNC_PWM );
}

//----------------------------------------------------------------

void pwm::set_enabled( bool enabled, bool state ) {
	uint slice_num = pwm_gpio_to_slice_num( this->gpio );
	uint channel_num = pwm_gpio_to_channel( this->gpio );

	if ( enabled ) {
		pwm_set_chan_level( slice_num, channel_num, this->level );
		pwm_set_enabled( slice_num, true );

		gpio_set_function( this->gpio, GPIO_FUNC_PWM );
	}
	else {
		pwm_set_chan_level( slice_num, channel_num, state ? 65535 : 0 );
		pwm_set_enabled( slice_num, false );

		gpio_set_function( this->gpio, GPIO_FUNC_SIO );
		gpio_set_dir( this->gpio, GPIO_OUT );
		gpio_put( this->gpio, state );
	}
}

//----------------------------------------------------------------
