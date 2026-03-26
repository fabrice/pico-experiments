//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// rotaty encoder
//
//----------------------------------------------------------------

#pragma once
#ifndef _ROTARY_ENCODER_H
#define _ROTARY_ENCODER_H

//----------------------------------------------------------------

#include "pico/stdio.h"

#include "hardware/gpio.h"


//----------------------------------------------------------------
/*
 -----------------------------
|  .  |  .  |  .  |  .  |  .  |
|  A  |  S  |  4  |  6  | VCC |
|  .  |  .  |  .  |  .  |  .  |
| GND |  B  |  3  |  5  |  7  |
 -----------       -----------
*/
//----------------------------------------------------------------

class rotary_encoder;
using rotary_encoder_ref = rotary_encoder*;

//----------------------------------------------------------------

class rotary_encoder {
private:
	uint a_gpio;
	uint b_gpio;
	uint s_gpio;

	int32_t rotations;
	uint32_t clicks;

private:
	rotary_encoder();

public:
	rotary_encoder( uint a_gpio, uint b_gpio, uint s_gpio );
	~rotary_encoder();

private:
	void io_init();
	void interrupts_init();
	void io_deinit();

public:
	inline uint get_a_gpio() const { return this->a_gpio; };
	inline uint get_b_gpio() const { return this->b_gpio; };
	inline uint get_s_gpio() const { return this->s_gpio; };

	inline bool get_a() const { return gpio_get( this->a_gpio ); };
	inline bool get_b() const { return gpio_get( this->b_gpio ); };
	inline bool get_s() const { return gpio_get( this->s_gpio ); };

	inline bool is_a_equal_b() const { return this->get_a() == this->get_b(); };
	inline bool is_a_notequal_b() const { return this->get_a() != this->get_b(); };

	inline int32_t get_rotations() const { return this->rotations; };
	int8_t use_rotation();

	int8_t get_direction() const;

	inline uint32_t get_clicks() const { return this->clicks; };
	bool use_click();

private:
	void gpio_interrupt_a( uint gpio, uint32_t events );
	void gpio_interrupt_s( uint gpio, uint32_t events );
};

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
