//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// mcp9800
//
//----------------------------------------------------------------

#include "mcp9800.h"

#include "pico/stdlib.h"
#include "hardware_i2c_plus.h"

#include <cmath>
#include <bit>

//----------------------------------------------------------------

constexpr uint8_t MCP9800_CONFIG_REGISTER { 1 };
constexpr uint8_t MCP9800_LO_LIMIT_REGISTER { 2 };
constexpr uint8_t MCP9800_HI_LIMIT_REGISTER { 3 };
constexpr uint8_t MCP9800_TEMPERATURE_REGISTER { 0 };

//----------------------------------------------------------------

mcp9800* mcp9800::make( uint i2c_num, uint8_t address ) {
	auto wire = wire_i2c::make( i2c_num, address );
	auto that = new mcp9800( wire );

	return that;
}

//----------------------------------------------------------------

mcp9800::mcp9800( wire* wire ):
		_wire { wire } {
}

//----------------------------------------------------------------

mcp9800::~mcp9800() {
	if ( _wire != nullptr ) {
		delete _wire;
		_wire = nullptr;
	}
}

//----------------------------------------------------------------

void mcp9800::read_configuration() {
	if ( _wire == nullptr ) return;

	_wire->start_communication();
	_wire->start_transaction();
	_wire->write_bytes( MCP9800_CONFIG_REGISTER );
	_wire->follow_transaction();
	size_t length = 2;
	uint8_t data[ length ] {};
	_wire->read_bytes( data, &length );
	_wire->finish_transaction();
	_wire->finish_communication();

	if ( data[ 0 ] > 0 ) _config = data[ 1 ];
}

//----------------------------------------------------------------

void mcp9800::set_oneshot( bool oneshot ) {
	if ( oneshot ) _config |= 0b10000000;
	else _config &= ~0b10000000;

	if ( _wire == nullptr ) return;

	_wire->start_communication();
	_wire->write_bytes( MCP9800_CONFIG_REGISTER, _config );
	_wire->finish_communication();
}

//----------------------------------------------------------------

void mcp9800::set_adc_resolution( uint8_t bits ) {
	if ( bits < 9 ) bits = 9;
	if ( bits > 12 ) bits = 12;

	_config = (_config & ~0b01100000) | ((bits - 9) << 5);

	if ( _wire == nullptr ) return;

	_wire->start_communication();
	_wire->write_bytes( MCP9800_CONFIG_REGISTER, _config );
	_wire->finish_communication();
}

//----------------------------------------------------------------

void mcp9800::set_fault_queue( uint8_t faults ) {
	_config = (_config & ~0b00011000) | ((faults << 3) & 0b00011000);

	if ( _wire == nullptr ) return;

	_wire->start_communication();
	_wire->write_bytes( MCP9800_CONFIG_REGISTER, _config );
	_wire->finish_communication();
}

//----------------------------------------------------------------

void mcp9800::set_alert_polarity( bool high ) {
	if ( high ) _config |= 0b00000100;
	else _config &= ~0b00000100;

	if ( _wire == nullptr ) return;

	_wire->start_communication();
	_wire->write_bytes( MCP9800_CONFIG_REGISTER, _config );
	_wire->finish_communication();
}

//----------------------------------------------------------------

void mcp9800::set_interrupt_enabled( bool enabled ) {
	if ( enabled ) _config |= 0b00000010;
	else _config &= ~0b00000010;

	if ( _wire == nullptr ) return;

	_wire->start_communication();
	_wire->write_bytes( MCP9800_CONFIG_REGISTER, _config );
	_wire->finish_communication();
}

//----------------------------------------------------------------

void mcp9800::set_shutdown( bool shutdown ) {
	if ( shutdown ) _config |= 0b00000001;
	else _config &= ~0b00000001;

	if ( _wire == nullptr ) return;

	_wire->start_communication();
	_wire->write_bytes( MCP9800_CONFIG_REGISTER, _config );
	_wire->finish_communication();
}

//----------------------------------------------------------------

void mcp9800::read_lo_temperature() {
	if ( _wire == nullptr ) return;

	_wire->start_communication();
	_wire->start_transaction();
	_wire->write_bytes( MCP9800_LO_LIMIT_REGISTER );
	_wire->follow_transaction();
	size_t length = 3;
	uint8_t data[ length ] {};
	_wire->read_bytes( data, &length );
	_wire->finish_transaction();
	_wire->finish_communication();

	if ( data[ 0 ] > 0 ) {
		_lo_temperature = static_cast< float >( std::bit_cast< int16_t, uint16_t >( (static_cast< uint16_t >( data[ 1 ] ) << 8) | static_cast< uint16_t >( data[ 0 ] ) ) ) / 256.0f;
	}
}

//----------------------------------------------------------------

void mcp9800::read_hi_temperature() {
	if ( _wire == nullptr ) return;

	_wire->start_communication();
	_wire->start_transaction();
	_wire->write_bytes( MCP9800_HI_LIMIT_REGISTER );
	_wire->follow_transaction();
	size_t length = 3;
	uint8_t data[ length ] {};
	_wire->read_bytes( data, &length );
	_wire->finish_transaction();
	_wire->finish_communication();

	if ( data[ 0 ] > 0 ) {
		_hi_temperature = static_cast< float >( std::bit_cast< int16_t, uint16_t >( (static_cast< uint16_t >( data[ 1 ] ) << 8) | static_cast< uint16_t >( data[ 0 ] ) ) ) / 256.0f;
	}
}

//----------------------------------------------------------------

void mcp9800::set_lo_temperature( float temperature ) {
	_lo_temperature = temperature;

	if ( _wire == nullptr ) return;

	const uint16_t data = std::bit_cast< uint16_t >( static_cast< int16_t >( std::round( _lo_temperature * 256.0f ) ) );

	_wire->start_communication();
	_wire->write_bytes( MCP9800_LO_LIMIT_REGISTER, static_cast< uint8_t >( (data >> 8) & 0xff ), static_cast< uint8_t >( (data >> 0) & 0xff ) );
	_wire->finish_communication();
}

//----------------------------------------------------------------

void mcp9800::set_hi_temperature( float temperature ) {
	_hi_temperature = temperature;

	if ( _wire == nullptr ) return;

	const uint16_t data = std::bit_cast< uint16_t >( static_cast< int16_t >( std::round( _hi_temperature * 256.0f ) ) );

	_wire->start_communication();
	_wire->write_bytes( MCP9800_HI_LIMIT_REGISTER, static_cast< uint8_t >( (data >> 8) & 0xff ), static_cast< uint8_t >( (data >> 0) & 0xff ) );
	_wire->finish_communication();
}

//----------------------------------------------------------------

void mcp9800::read_temperature() {
	if ( _wire == nullptr ) return;

	_wire->start_communication();
	_wire->start_transaction();
	_wire->write_bytes( MCP9800_TEMPERATURE_REGISTER );
	_wire->follow_transaction();
	size_t length = 2;
	uint8_t data[ length ] {};
	_wire->read_bytes( data, &length );
	_wire->finish_transaction();
	_wire->finish_communication();

	if ( data[ 0 ] > 0 ) {
		_temperature = static_cast< float >( std::bit_cast< int16_t, uint16_t >( (static_cast< uint16_t >( data[ 1 ] ) << 8) | static_cast< uint16_t >( data[ 0 ] ) ) ) / 256.0f;
	}
}

//----------------------------------------------------------------
