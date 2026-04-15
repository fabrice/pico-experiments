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
	return static_cast< bool >( value );
}

//----------------------------------------------------------------

constexpr char operator""_c( unsigned long long value ) {
	return static_cast< char >( value );
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

constexpr int16_t operator""_i16( unsigned long long value ) {
	return static_cast< int16_t >( value );
}

//----------------------------------------------------------------

constexpr uint32_t operator""_u32( unsigned long long value ) {
	return static_cast< uint32_t >( value );
}

//----------------------------------------------------------------

constexpr int32_t operator""_i32( unsigned long long value ) {
	return static_cast< int32_t >( value );
}

//----------------------------------------------------------------

constexpr size_t operator""_uz( unsigned long long value ) {
	return static_cast< size_t >( value );
}

//----------------------------------------------------------------
