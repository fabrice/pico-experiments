//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// wire_i2c
//
//----------------------------------------------------------------

#pragma once
#ifndef _WIRE_I2C_H
#define _WIRE_I2C_H

//----------------------------------------------------------------

#include "pico/stdlib.h"

#include "wire.h"

#include "hardware/i2c.h"

//----------------------------------------------------------------

class wire_i2c;
using wire_i2c_ref = wire_i2c*;

using i2c_ref = i2c_inst_t*;

//----------------------------------------------------------------

class wire_i2c : public virtual wire {

private:

	i2c_inst_t* i2c_instance;
	uint8_t address;

public:

	wire_i2c( uint i2c_num, uint8_t address );
	virtual ~wire_i2c() override;

	void io_init( uint scl_gpio, uint sda_gpio, uint bitrate );

	virtual void set_bitrate( uint bitrate ) override;

	virtual int write_bytes( const uint8_t* bytes, size_t length ) override;

	virtual int read_bytes( uint8_t* bytes, size_t* length ) override;

};

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
