//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// v_reference_count
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico.h"
#include <cstdint>
#include <memory>

//----------------------------------------------------------------

class v_reference_count {

private:

	uint8_t _reference_count;

public:

	inline v_reference_count(): _reference_count( 0 ) {}
	inline v_reference_count( uint8_t reference_count ): _reference_count( reference_count ) {}
	inline v_reference_count( bool retained ): _reference_count( retained ? 1 : 0 ) {}

	inline v_reference_count( v_reference_count& that ): _reference_count( 0 ) {}

protected:

	virtual ~v_reference_count();

public:

	inline uint8_t get_reference_count() const { return _reference_count; }

	inline void retain() { ++_reference_count; }

	bool release();

};

//----------------------------------------------------------------
