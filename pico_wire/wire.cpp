//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// wire
//
//----------------------------------------------------------------

#include "wire.h"

//----------------------------------------------------------------

wire::~wire() {
}

//----------------------------------------------------------------

void wire::start() {
}

//----------------------------------------------------------------

int wire::write_bytes( uint8_t byte1 ) {
	return this->write_bytes( &byte1, sizeof(byte1) );
}

//----------------------------------------------------------------

int wire::write_bytes( uint8_t byte1, uint8_t byte2 ) {
	uint8_t buffer[] = { byte1, byte2 };
	return this->write_bytes( buffer, sizeof(buffer) );
}

//----------------------------------------------------------------

int wire::write_bytes( uint8_t byte1, uint8_t byte2, uint8_t byte3 ) {
	uint8_t buffer[] = { byte1, byte2, byte3 };
	return this->write_bytes( buffer, sizeof(buffer) );
}

//----------------------------------------------------------------

int wire::write_bytes( uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4 ) {
	uint8_t buffer[] = { byte1, byte2, byte3, byte4 };
	return this->write_bytes( buffer, sizeof(buffer) );
}

//----------------------------------------------------------------

int wire::write_bytes( uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4, uint8_t byte5 ) {
	uint8_t buffer[] = { byte1, byte2, byte3, byte4, byte5 };
	return this->write_bytes( buffer, sizeof(buffer) );
}

//----------------------------------------------------------------

void wire::finish() {
}

//----------------------------------------------------------------
