//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// ee24lc02b
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware_i2c_plus.h"

//----------------------------------------------------------------

class ee24lc02b;
using ee24lc02b_ref = ee24lc02b*;

//----------------------------------------------------------------

constexpr uint8_t EE24LC02B_ADDRESS = 0x50;

constexpr uint16_t EE24LC02B_MEMORY_SIZE = 256;
constexpr uint8_t EE24LC02B_PAGE_SIZE = 8;

constexpr uint8_t EE24LC02B_I2C_FREQUENCY = 8;

//----------------------------------------------------------------

class ee24lc02b {

private:

	i2c_ref wire;
	uint8_t address;

	uint8_t gpio_dir;
	uint8_t gpio_pull_up;

public:

	ee24lc02b();
	ee24lc02b( i2c_ref wire, uint8_t address );

public:

	~ee24lc02b();

	void write_byte( uint8_t address, uint8_t data );

	uint8_t read_byte( uint8_t address );
	void read_bytes( uint8_t address, uint8_t buffer[], uint16_t length );

	void fill( uint8_t data );

	void erase();

};

//----------------------------------------------------------------
