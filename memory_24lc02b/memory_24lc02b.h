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
#include "wire.h"

//----------------------------------------------------------------

class memory_24lc02b;
using memory_24lc02b_ptr = memory_24lc02b*;

//----------------------------------------------------------------

constexpr uint8_t EE24LC02B_ADDRESS { 0x50 };

constexpr uint16_t EE24LC02B_MEMORY_SIZE { 256 };
constexpr uint8_t EE24LC02B_PAGE_SIZE { 8 };

constexpr uint8_t EE24LC02B_I2C_FREQUENCY { 8 };

//----------------------------------------------------------------

class memory_24lc02b {

private:

	wire_ptr _wire { nullptr };
	uint8_t _address { EE24LC02B_ADDRESS };

public:

	static memory_24lc02b_ptr make( uint i2c_num, uint8_t address );

	memory_24lc02b() = delete;
	memory_24lc02b( wire_ptr wire );

public:

	~memory_24lc02b();

	void write_byte( uint8_t address, uint8_t data ) const;

	void write_page( uint8_t address, uint8_t data[8] ) const;

	uint8_t read_byte( uint8_t address ) const;
	void read_page( uint8_t address, uint8_t data[8] ) const;
	void read_bytes( uint8_t address, uint8_t data[], uint16_t length ) const;

	void fill( uint8_t data ) const;

	void erase() const;

};

//----------------------------------------------------------------
