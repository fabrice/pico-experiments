//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// adc
// mcp3221
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico/stdlib.h"

#include "wire_i2c.h"
#include "hardware_i2c_plus.h"

//----------------------------------------------------------------

constexpr uint8_t MCP3221_ADDRESS { 0x4d }; // 0x9a >> 1

//----------------------------------------------------------------

class mcp3221 {

private:

	wire* _wire { nullptr };
	uint8_t _address { MCP3221_ADDRESS };

	uint16_t _adc { 0 };

public:

	static mcp3221* make( uint i2c_num, uint8_t address );

	mcp3221() = delete;
	mcp3221( wire* wire );

	~mcp3221() noexcept;

	uint16_t get_adc() { return _adc; }

	void start_adc();
	uint16_t read_adc();

};

//----------------------------------------------------------------
