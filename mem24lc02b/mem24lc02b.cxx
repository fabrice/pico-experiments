//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// eeprom 256 bytes I2C
// mem24lc02
//
//----------------------------------------------------------------

#include "mem24lc02b.h"

#include "wire_i2c.h"

#include "pico/stdlib.h"
#include "hardware_i2c_plus.h"

#include <cstring>
#include <algorithm>

//----------------------------------------------------------------

constexpr uint32_t EE24LC02B_WRITE_CYCLE { 5 }; // ms

//----------------------------------------------------------------

mem24lc02b* mem24lc02b::make( uint i2c_num, uint8_t address ) {
	auto wire = wire_i2c::make( i2c_num, address );
	return new mem24lc02b( wire );
}

//----------------------------------------------------------------

mem24lc02b::mem24lc02b( wire* wire ):
		_wire { wire } {
}

//----------------------------------------------------------------

mem24lc02b::~mem24lc02b() noexcept {
	if ( _wire != nullptr ) {
		delete _wire;
		_wire = nullptr;
	}
}

//----------------------------------------------------------------

void mem24lc02b::write_byte( uint8_t address, uint8_t data ) const {
	if ( _wire == nullptr ) return;

	_wire->write_bytes( address, data );
	sleep_ms( EE24LC02B_WRITE_CYCLE );
}

//----------------------------------------------------------------

void mem24lc02b::write_page( uint8_t address, uint8_t data[8] ) const {
	if ( _wire == nullptr ) return;

	address -= address % EE24LC02B_PAGE_SIZE;

	uint8_t buffer[9] { 0 };
	buffer[0] = address;
	std::copy_n( data, 8, buffer + 1 );
	_wire->write_bytes( buffer, sizeof(buffer) );
	sleep_ms( EE24LC02B_WRITE_CYCLE );
}

//----------------------------------------------------------------

uint8_t mem24lc02b::read_byte( uint8_t address ) const {
	if ( _wire == nullptr ) return PICO_ERROR_IO;

	_wire->start_transaction();
	int result = _wire->write_bytes( address );
	if ( result < PICO_OK ) {
		_wire->finish_transaction();
		return result;
	}

	uint8_t data;
	size_t length = 1;
	_wire->follow_transaction();
	result = _wire->read_bytes( &data, &length );
	_wire->finish_transaction();
	if ( result < PICO_OK ) return result;

	return data;
}

//----------------------------------------------------------------

void mem24lc02b::read_page( uint8_t address, uint8_t data[8] ) const {
	if ( _wire == nullptr ) return;

	address -= address % EE24LC02B_PAGE_SIZE;

	_wire->start_transaction();
	int result = _wire->write_bytes( address );
	if ( result < PICO_OK ) {
		_wire->finish_transaction();
		return;
	}

	size_t length = EE24LC02B_PAGE_SIZE;
	_wire->follow_transaction();
	result = _wire->read_bytes( data, &length );
	_wire->finish_transaction();
}

//----------------------------------------------------------------

void mem24lc02b::read_bytes( uint8_t address, uint8_t data[], uint16_t length ) const {
	if ( _wire == nullptr ) return;

	_wire->start_transaction();
	int result = _wire->write_bytes( address );
	if ( result < PICO_OK ) {
		_wire->finish_transaction();
		return;
	}

	size_t rlength = length;
	_wire->follow_transaction();
	result = _wire->read_bytes( data, &rlength );
	_wire->finish_transaction();
}

//----------------------------------------------------------------

void mem24lc02b::fill( uint8_t data ) const {
	if ( _wire == nullptr ) return;

	uint8_t buffer[EE24LC02B_PAGE_SIZE + 1] { 0 };
	memset( buffer + 1, data, EE24LC02B_PAGE_SIZE );

	for ( uint16_t address = 0 ; address < EE24LC02B_MEMORY_SIZE ; address += EE24LC02B_PAGE_SIZE ) {
		buffer[0] = (uint8_t)address;
		int result = _wire->write_bytes( buffer, EE24LC02B_PAGE_SIZE + 1 );
		sleep_ms( EE24LC02B_WRITE_CYCLE );
		if ( result < PICO_OK ) break;
	}
}

//----------------------------------------------------------------

void mem24lc02b::erase() const {
	this->fill( 0x00 );
}

//----------------------------------------------------------------
