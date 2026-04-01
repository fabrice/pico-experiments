//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// wire_spi
//
//----------------------------------------------------------------

#pragma once
#ifndef _WIRE_SPI_H
#define _WIRE_SPI_H

//----------------------------------------------------------------

#include "pico/stdlib.h"

#include "wire.h"

#include "hardware/spi.h"

//----------------------------------------------------------------

class wire_spi;
using wire_spi_ref = wire_spi*;

using spi_ref = spi_inst_t*;

//----------------------------------------------------------------

class wire_spi : public virtual wire {

private:

	spi_ref spi_instance;
	uint chip_select_gpio;

private:

	wire_spi();

public:

	wire_spi( uint spi_num, uint chip_select_gpio );
	virtual ~wire_spi() override;

	void io_init( uint sclk_gpio, uint miso_gpio, uint mosi_gpio, uint bitrate );

	virtual void set_bitrate( uint bitrate ) override;

	virtual void start_communication() override;

	virtual int write_bytes( const uint8_t* bytes, size_t length ) override;

	virtual int read_bytes( uint8_t* bytes, size_t* length ) override;

	virtual void finish_communication() override;

};

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
