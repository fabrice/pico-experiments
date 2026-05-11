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
/*
 -----------------------------
|  .  |  .  |  .  |  .  |  .  |
|  A  |  S  |  4  |  6  | VCC |
|  .  |  .  |  .  |  .  |  .  |
| GND |  B  |  3  |  5  |  7  |
 -----------       -----------
*/

//----------------------------------------------------------------

class rotary_encoder {

private:

	uint _a_gpio { 255 };
	uint _b_gpio { 255 };
	uint _s_gpio { 255 };

	int32_t _rotations { 0 };
	uint32_t _clicks { 0 };

public:

	static rotary_encoder* make( uint a_gpio, uint b_gpio, uint s_gpio );

	rotary_encoder() = delete;
	rotary_encoder( uint a_gpio, uint b_gpio, uint s_gpio );
	~rotary_encoder();

private:

	void io_init();
	void interrupts_init();
	void io_deinit();

public:

	uint get_a_gpio() const { return _a_gpio; };
	uint get_b_gpio() const { return _b_gpio; };
	uint get_s_gpio() const { return _s_gpio; };

	bool get_a() const { return gpio_get( _a_gpio ); };
	bool get_b() const { return gpio_get( _b_gpio ); };
	bool get_s() const { return gpio_get( _s_gpio ); };

	bool is_a_equal_b() const { return this->get_a() == this->get_b(); };
	bool is_a_notequal_b() const { return this->get_a() != this->get_b(); };

	int32_t get_rotations() const { return _rotations; };
	int8_t use_rotation();

	int8_t get_direction() const;

	uint32_t get_clicks() const { return _clicks; };
	bool use_click();

private:

	void gpio_interrupt_a( uint gpio, uint32_t events );
	void gpio_interrupt_s( uint gpio, uint32_t events );

};

//----------------------------------------------------------------
