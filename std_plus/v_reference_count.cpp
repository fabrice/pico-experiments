//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// v_reference_count
//
//----------------------------------------------------------------


#include "v_reference_count.h"

//----------------------------------------------------------------

v_reference_count::~v_reference_count() {
	if ( _reference_count > 1 ) printf( "v_reference_count::~v_reference_count : _reference_count = %d \n", (int) _reference_count );
}

//----------------------------------------------------------------

bool v_reference_count::release() {
	if ( _reference_count > 0 ) --_reference_count;
	if ( _reference_count == 0 ) { delete this; return true; }
	return false;
}

//----------------------------------------------------------------
