//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// literals_plus
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include <cstdint>

//----------------------------------------------------------------

constexpr bool operator""_bit( unsigned long long value ) {
	return !!value;
}

//----------------------------------------------------------------

constexpr uint8_t operator""_u8( unsigned long long value ) {
	return static_cast< uint8_t >( value );
}

//----------------------------------------------------------------

constexpr int8_t operator""_i8( unsigned long long value ) {
	return static_cast< int8_t >( value );
}

//----------------------------------------------------------------

constexpr uint16_t operator""_u16( unsigned long long value ) {
	return static_cast< uint16_t >( value );
}

//----------------------------------------------------------------

constexpr uint32_t operator""_u32( unsigned long long value ) {
	return static_cast< uint32_t >( value );
}

//----------------------------------------------------------------
