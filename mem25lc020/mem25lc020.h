//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// eeprom 256 bytes SPI
// mem25lc020
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware_spi_plus.h"
#include "wire.h"

//----------------------------------------------------------------

constexpr uint16_t EE25LC02_MEMORY_SIZE { 256 };
constexpr uint8_t EE24LC02B_PAGE_SIZE { 16 };

constexpr uint8_t EE25LC02_CMD_READ { 0b00000011 }; // param : address
constexpr uint8_t EE25LC02_CMD_WRITE { 0b00000010 }; // param : address, data
constexpr uint8_t EE25LC02_CMD_WRITE_DISABLE { 0b00000100 };
constexpr uint8_t EE25LC02_CMD_WRITE_ENABLE { 0b00000110 };
constexpr uint8_t EE25LC02_CMD_READ_STATUS { 0b00000101 };
constexpr uint8_t EE25LC02_CMD_WRITE_STATUS { 0b00000001 };

constexpr uint32_t EE25LC02_WRITE_CYCLE { 5 }; // ms

constexpr uint8_t EE25LC02_SPI_FREQUENCY { 10 }; // MHz

//----------------------------------------------------------------

class mem25lc020 {

private:

	wire* _wire { nullptr };

public:

	static mem25lc020* make( uint spi_num, uint gpio_cs );

	mem25lc020() = delete;
	mem25lc020( wire* wire );

	~mem25lc020() noexcept;

	void write_byte( uint8_t address, uint8_t data ) const;

	void write_page( uint8_t address, uint8_t data[16], uint8_t length ) const;

	uint8_t read_byte( uint8_t address ) const;

	void fill( uint8_t data ) const;

	void erase() const;

};

//----------------------------------------------------------------
