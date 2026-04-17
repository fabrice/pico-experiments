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

constexpr uint8_t MCP23008_ADDRESS { 0x20 };

//----------------------------------------------------------------

class mcp23008 {

private:

	wire* _wire { nullptr };
	uint8_t _address { MCP23008_ADDRESS };

	uint8_t _gpio_dir { 0b00000000 };
	uint8_t _gpio_pull_up { 0b00000000 };

public:

	mcp23008() = delete;
	mcp23008( wire* wire, uint8_t gpio_dir, uint8_t gpio_pull_up );

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
