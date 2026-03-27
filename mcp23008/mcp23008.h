//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// mcp23008
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware_i2c_plus.h"

//----------------------------------------------------------------

constexpr uint8_t MCP23008_ADDRESS = 0x20;

//----------------------------------------------------------------

class mcp23008 {

private:

	i2c_ref wire;
	uint8_t address;

	uint8_t gpio_dir;
	uint8_t gpio_pull_up;

public:

	mcp23008(): wire( nullptr ), address( MCP23008_ADDRESS ), gpio_dir( 0 ), gpio_pull_up( 0 ) {}
	mcp23008( i2c_ref wire, uint8_t address, uint8_t gpio_dir, uint8_t gpio_pull_up ): wire( wire ), address( address ), gpio_dir( gpio_dir ), gpio_pull_up( gpio_pull_up ) {}

	void gpio_init();

	void gpio_set_dir( uint8_t gpio, bool out );
	void gpio_set_pull_up( uint8_t gpio, bool up );

	uint8_t gpio_get_all();
	void gpio_put_all( uint8_t value );

};

//----------------------------------------------------------------
