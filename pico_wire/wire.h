//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// wire
//
//----------------------------------------------------------------

#pragma once
#ifndef _WIRE_H
#define _WIRE_H

//----------------------------------------------------------------

#include "pico/stdlib.h"

//----------------------------------------------------------------

class wire;
using wire_ref = wire*;

//----------------------------------------------------------------

class wire {

protected:

	wire() {}

public:

	virtual ~wire() = 0;

	virtual void set_bitrate( uint bitrate ) = 0;

	virtual void start_communication();
	virtual void start_transaction();

	virtual int write_bytes( const uint8_t* bytes, size_t length ) = 0;

	virtual int write_bytes( uint8_t byte1 );
	virtual int write_bytes( uint8_t byte1, uint8_t byte2 );
	virtual int write_bytes( uint8_t byte1, uint8_t byte2, uint8_t byte3 );
	virtual int write_bytes( uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4 );
	virtual int write_bytes( uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4, uint8_t byte5 );

	virtual int read_bytes( uint8_t* bytes, size_t* length ) = 0;

	virtual void finish_transaction();
	virtual void finish_communication();

};

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
