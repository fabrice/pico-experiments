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

#include "mcp41xxx.h"

#include "pico/stdlib.h"

//----------------------------------------------------------------

constexpr uint8_t MCP41_WRITE = 0x10;
constexpr uint8_t MCP41_SHUTDOWN = 0x20;
constexpr uint8_t MCP41_POT01 = 0x01;
constexpr uint8_t MCP41_POT10 = 0x02;
constexpr uint8_t MCP41_POT11 = 0x03;

constexpr uint8_t MCP41_WRITE_POT01 = MCP41_WRITE | MCP41_POT01;
constexpr uint8_t MCP41_WRITE_POT10 = MCP41_WRITE | MCP41_POT10;
constexpr uint8_t MCP41_WRITE_POT11 = MCP41_WRITE | MCP41_POT11;

constexpr uint8_t MCP41_SHUTDOWN_POT11 = MCP41_SHUTDOWN | MCP41_POT11;

//----------------------------------------------------------------

mcp41xxx::mcp41xxx():
	wire( nullptr ),
	step_p01( 127 ),
	step_p10( 127 ) {
}

//----------------------------------------------------------------

mcp41xxx::mcp41xxx( wire_ref wire ):
	wire( wire ),
	step_p01( 127 ),
	step_p10( 127 ) {
	this->set_step_all( 127 );
}

//----------------------------------------------------------------

mcp41xxx::~mcp41xxx() {
	if ( wire != nullptr ) {
		wire->start_communication();
		wire->write_bytes( MCP41_SHUTDOWN_POT11, 0x00 );
		wire->finish_communication();

		delete wire;
		wire = nullptr;
	}
}

//----------------------------------------------------------------

void mcp41xxx::set_step( uint pot, uint8_t step ) {
	switch ( pot ) {
		case 0:
			step_p01 = step;
			if ( wire != nullptr ) {
				wire->start_communication();
				wire->write_bytes( MCP41_WRITE_POT01, step_p01 );
				wire->finish_communication();
			}
			break;
		case 1:
			step_p10 = step;
			if ( wire != nullptr ) {
				wire->start_communication();
				wire->write_bytes( MCP41_WRITE_POT10, step_p10 );
				wire->finish_communication();
			}
			break;
	}
}

//----------------------------------------------------------------

void mcp41xxx::set_step_all( uint8_t step ) {
	step_p01 = step;
	step_p10 = step;
	if ( wire != nullptr ) {
		wire->start_communication();
		wire->write_bytes( MCP41_WRITE_POT11, step );
		wire->finish_communication();
	}
}

//----------------------------------------------------------------
