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

	mutable uint8_t _reference_count { uint8_t(0) };

public:

	v_reference_count() = default;
	v_reference_count( uint8_t reference_count ): _reference_count { reference_count } {}
	v_reference_count( bool retained ): _reference_count { retained ? uint8_t(1) : uint8_t(0) } {}

	v_reference_count( v_reference_count& that ): _reference_count { uint8_t(0) } {}

protected:

	virtual ~v_reference_count();

public:

	inline uint8_t get_reference_count() const { return _reference_count; }

	inline void retain() const { ++_reference_count; }

	bool release();

};

//----------------------------------------------------------------
