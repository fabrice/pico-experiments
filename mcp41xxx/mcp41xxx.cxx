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

constexpr uint8_t MCP41_WRITE { 0x10 };
constexpr uint8_t MCP41_SHUTDOWN { 0x20 };
constexpr uint8_t MCP41_POT01 { 0b0001 };
constexpr uint8_t MCP41_POT10 { 0b0010 };
constexpr uint8_t MCP41_POT11 { MCP41_POT10 | MCP41_POT01 };

constexpr uint8_t MCP41_WRITE_POT01 { MCP41_WRITE | MCP41_POT01 };
constexpr uint8_t MCP41_WRITE_POT10 { MCP41_WRITE | MCP41_POT10 };
constexpr uint8_t MCP41_WRITE_POT11 { MCP41_WRITE | MCP41_POT11 };

constexpr uint8_t MCP41_SHUTDOWN_POT11 { MCP41_SHUTDOWN | MCP41_POT11 };

//----------------------------------------------------------------

mcp41xxx::mcp41xxx( wire* wire ):
	_wire { wire },
	_step_p01 { 0x80 },
	_step_p10 { 0x80 } {

	this->set_step_all( 0x80 );
}

//----------------------------------------------------------------

mcp41xxx::~mcp41xxx() {
	if ( _wire != nullptr ) {
		_wire->start_communication();
		_wire->write_bytes( MCP41_SHUTDOWN_POT11, 0x00 );
		_wire->finish_communication();

		delete _wire;
		_wire = nullptr;
	}
}

//----------------------------------------------------------------

void mcp41xxx::set_step( uint pot, uint8_t step ) {
	switch ( pot ) {
		case 0:
			_step_p01 = step;
			if ( _wire != nullptr ) {
				_wire->start_communication();
				_wire->write_bytes( MCP41_WRITE_POT01, _step_p01 );
				_wire->finish_communication();
			}
			break;
		case 1:
			_step_p10 = step;
			if ( _wire != nullptr ) {
				_wire->start_communication();
				_wire->write_bytes( MCP41_WRITE_POT10, _step_p10 );
				_wire->finish_communication();
			}
			break;
	}
}

//----------------------------------------------------------------

void mcp41xxx::set_step_all( uint8_t step ) {
	_step_p01 = step;
	_step_p10 = step;
	if ( _wire != nullptr ) {
		_wire->start_communication();
		_wire->write_bytes( MCP41_WRITE_POT11, step );
		_wire->finish_communication();
	}
}

//----------------------------------------------------------------
