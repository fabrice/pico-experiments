//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// digital potentiometer
// mcp41xxx
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico/stdlib.h"

#include "wire_spi.h"

//----------------------------------------------------------------

class mcp41xxx {

private:

	wire* _wire { nullptr };

	uint8_t _step_p01 { 0x80 };
	uint8_t _step_p10 { 0x80 };


public:

	mcp41xxx() = delete;
	mcp41xxx( wire* wire );
	~mcp41xxx();

	void set_step( uint pot, uint8_t step );
	void set_step_all( uint8_t step );

};

//----------------------------------------------------------------
