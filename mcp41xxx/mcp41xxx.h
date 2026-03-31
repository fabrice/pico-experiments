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

class mcp41xxx;
using mcp41xxx_ref = mcp41xxx*;

//----------------------------------------------------------------

class mcp41xxx {

private:

	wire_ref wire;

	uint8_t step_p01;
	uint8_t step_p10;

private:

	mcp41xxx();

public:

	mcp41xxx( wire_ref wire );
	~mcp41xxx();

	void set_step( uint pot, uint8_t step );
	void set_step_all( uint8_t step );

};

//----------------------------------------------------------------
