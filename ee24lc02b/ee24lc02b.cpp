//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// mcp23008
//
//----------------------------------------------------------------

#include "ee24lc02b.h"

#include "pico/stdlib.h"
#include "hardware_i2c_plus.h"
#include <cstring>

//----------------------------------------------------------------

constexpr uint32_t EE24LC02B_WRITE_CYCLE = 5; // ms

//----------------------------------------------------------------

ee24lc02b::ee24lc02b():
	wire( nullptr ),
	address( EE24LC02B_ADDRESS ) {
}

//----------------------------------------------------------------

ee24lc02b::ee24lc02b( i2c_ref wire, uint8_t address ):
	wire( wire ),
	address( address ) {
}

//----------------------------------------------------------------

ee24lc02b::~ee24lc02b() {
}

//----------------------------------------------------------------

void ee24lc02b::write_byte( uint8_t address, uint8_t data ) {
	uint8_t buffer[] = { address, data };
	i2c_write_blocking( wire, this->address, buffer, sizeof(buffer), false );
//	i2c_write_bytes_blocking( wire, this->address, address, data );
	sleep_ms( EE24LC02B_WRITE_CYCLE );
}

//----------------------------------------------------------------

void ee24lc02b::write_page( uint8_t address, uint8_t data[8] ) {
	uint8_t buffer[9];
	buffer[0] = address % EE24LC02B_PAGE_SIZE;
	memcpy( buffer + 1, data, 8 );
	i2c_write_blocking( wire, this->address, buffer, sizeof(buffer), false );
	sleep_ms( EE24LC02B_WRITE_CYCLE );
}

//----------------------------------------------------------------

uint8_t ee24lc02b::read_byte( uint8_t address ) {
	int error = i2c_write_blocking( wire, this->address, &address, sizeof(address), true );
	if ( error < PICO_OK ) return 0;

	uint8_t data = 0;
	error = i2c_read_blocking( wire, this->address, &data, sizeof(data), false );
	return data;
}

//----------------------------------------------------------------

void ee24lc02b::read_bytes( uint8_t address, uint8_t buffer[], uint16_t length ) {
	int error = i2c_write_blocking( wire, this->address, &address, sizeof(address), true );
	if ( error < PICO_OK ) return;

	error = i2c_read_blocking( wire, this->address, buffer, length, false );
}

//----------------------------------------------------------------

void ee24lc02b::fill( uint8_t data ) {
	uint8_t buffer[EE24LC02B_PAGE_SIZE + 1];
	memset( buffer + 1, data, EE24LC02B_PAGE_SIZE );

	for ( uint16_t address = 0; address < EE24LC02B_MEMORY_SIZE; address += EE24LC02B_PAGE_SIZE ) {
		buffer[0] = (uint8_t)address;
		int error = i2c_write_blocking( wire, this->address, buffer, EE24LC02B_PAGE_SIZE + 1, false );
		if ( error < PICO_OK ) return;
		sleep_ms( EE24LC02B_WRITE_CYCLE );
	}
}

//----------------------------------------------------------------

void ee24lc02b::erase() {
	this->fill( 0x00 );
}

//----------------------------------------------------------------
