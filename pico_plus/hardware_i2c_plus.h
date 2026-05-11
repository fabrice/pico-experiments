//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// hardware_i2c_plus
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "hardware/i2c.h"

//----------------------------------------------------------------
// hardware/i2c

using pico_i2c_ptr = i2c_inst_t*;

//----------------------------------------------------------------

inline int i2c_write_bytes_blocking( i2c_inst_t* i2c, uint8_t addr, uint8_t byte1 ) {
	return i2c_write_blocking( i2c, addr, &byte1, 1, false );
}

//----------------------------------------------------------------

inline int i2c_write_bytes_blocking( i2c_inst_t* i2c, uint8_t addr, uint8_t byte1, uint8_t byte2 ) {
	uint8_t buffer[] { byte1, byte2 };
	return i2c_write_blocking( i2c, addr, buffer, sizeof(buffer), false );
}

//----------------------------------------------------------------

inline int i2c_write_bytes_blocking( i2c_inst_t* i2c, uint8_t addr, uint8_t byte1, uint8_t byte2, uint8_t byte3 ) {
	uint8_t buffer[] { byte1, byte2, byte3 };
	return i2c_write_blocking( i2c, addr, buffer, sizeof(buffer), false );
}

//----------------------------------------------------------------

inline int i2c_write_bytes_blocking( i2c_inst_t* i2c, uint8_t addr, uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4 ) {
	uint8_t buffer[] { byte1, byte2, byte3, byte4 };
	return i2c_write_blocking( i2c, addr, buffer, sizeof(buffer), false );
}

//----------------------------------------------------------------
