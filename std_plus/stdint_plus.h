//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// stdint_plus
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include <cstdint>

//----------------------------------------------------------------

constexpr uint8_t operator""_u8( unsigned long long value ) {
	return value;
}

//----------------------------------------------------------------

constexpr int8_t operator""_i8( unsigned long long value ) {
	return value;
}

//----------------------------------------------------------------

constexpr uint16_t operator""_u16( unsigned long long value ) {
	return value;
}

//----------------------------------------------------------------

constexpr uint32_t operator""_u32( unsigned long long value ) {
	return value;
}

//----------------------------------------------------------------
