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

#include <memory>

//----------------------------------------------------------------

class v_reference_count {

private:

	uint8_t reference_count;

public:

	inline v_reference_count(): reference_count( 0 ) {};
	inline v_reference_count( uint8_t reference_count ): reference_count( reference_count ) {};
	inline v_reference_count( bool retained ): reference_count( retained ? 1 : 0 ) {};

	inline v_reference_count( v_reference_count& that ): reference_count( 0 ) {};

protected:

	inline ~v_reference_count() {}

public:

	inline uint8_t get_reference_count() const { return this->reference_count; };

	inline void retain() { ++ this->reference_count; }

	bool release() {
		if ( this->reference_count > 0 ) -- this->reference_count;
		if ( this->reference_count == 0 ) { delete this; return true; }
		return false;
	}

};

//----------------------------------------------------------------
