//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// mcp3221
//
//----------------------------------------------------------------

#include "mcp3221.h"

#include "pico/stdlib.h"
#include "hardware_i2c_plus.h"

//----------------------------------------------------------------

mcp3221* mcp3221::make( uint i2c_num, uint8_t address ) {
	auto wire = wire_i2c::make( i2c_num, address );
	auto that = new mcp3221( wire );

	return that;
}

//----------------------------------------------------------------

mcp3221::mcp3221( wire* wire ):
		_wire { wire } {
}

//----------------------------------------------------------------

mcp3221::~mcp3221() noexcept {
	if ( _wire != nullptr ) {
		delete _wire;
		_wire = nullptr;
	}
}

//----------------------------------------------------------------

void mcp3221::start_adc() {
	if ( _wire == nullptr ) return;

	_wire->start_communication();
	_wire->write_bytes( 0 );
	_wire->finish_communication();
}

//----------------------------------------------------------------

uint16_t mcp3221::read_adc() {
	if ( _wire == nullptr ) return 0;

	_wire->start_transaction();
	size_t rlength = 2;
	uint8_t data[2] { 0 };
	int result = _wire->read_bytes( data, &rlength );
	_wire->finish_transaction();
	_adc = (static_cast< uint16_t >( data[0] ) << 8) | (static_cast< uint16_t >( data[1] ) << 0);

	return _adc;
}

//----------------------------------------------------------------
