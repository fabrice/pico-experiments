//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// eeprom 256 bytes
// memory_24lc02b
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware_i2c_plus.h"

//----------------------------------------------------------------

class memory_24lc02b;
using memory_24lc02b_ref = memory_24lc02b*;

//----------------------------------------------------------------

constexpr uint8_t EE24LC02B_ADDRESS = 0x50;

constexpr uint16_t EE24LC02B_MEMORY_SIZE = 256;
constexpr uint8_t EE24LC02B_PAGE_SIZE = 8;

constexpr uint8_t EE24LC02B_I2C_FREQUENCY = 8;

//----------------------------------------------------------------

class memory_24lc02b {

private:

	i2c_ref _wire;
	uint8_t _address;

	uint8_t _gpio_dir;
	uint8_t _gpio_pull_up;

public:

	memory_24lc02b();
	memory_24lc02b( i2c_ref wire, uint8_t address );

public:

	~memory_24lc02b();

	void write_byte( uint8_t address, uint8_t data );

	void write_page( uint8_t address, uint8_t data[8] );

	uint8_t read_byte( uint8_t address );
	void read_page( uint8_t address, uint8_t data[8] );
	void read_bytes( uint8_t address, uint8_t buffer[], uint16_t length );

	void fill( uint8_t data );

	void erase();

};

//----------------------------------------------------------------
