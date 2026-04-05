//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gpio expander
// mcp23008
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico/stdlib.h"

#include "wire_i2c.h"
#include "hardware_i2c_plus.h"

//----------------------------------------------------------------

class mcp23008;
using mcp23008_ref = mcp23008*;

//----------------------------------------------------------------

constexpr uint8_t MCP23008_ADDRESS = 0x20;

//----------------------------------------------------------------

class mcp23008 {

private:

	wire_ref _wire;
	uint8_t _address;

	uint8_t _gpio_dir;
	uint8_t _gpio_pull_up;

public:

	mcp23008();
	mcp23008( wire_ref wire, uint8_t gpio_dir, uint8_t gpio_pull_up );

private:

	void gpio_init();

public:

	~mcp23008();

	void gpio_set_dir( uint8_t gpio, bool out );
	void gpio_set_pull_up( uint8_t gpio, bool up );

	uint8_t gpio_get_all();
	void gpio_put_all( uint8_t value );

	uint8_t gpio_get( uint8_t gpio );
	void gpio_put( uint8_t gpio, bool value );

};

//----------------------------------------------------------------
