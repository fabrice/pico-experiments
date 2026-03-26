//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// math_plus
//
//----------------------------------------------------------------

#pragma once
#ifndef _MATH_PLUS_H
#define _MATH_PLUS_H

//----------------------------------------------------------------

#include <cmath>

//----------------------------------------------------------------
// fonctions

template< typename number_t >
inline bool isbetween( number_t x, number_t min, number_t max ) {
	return
		((min <= max) && (x >= min) && (x <= max)) ||
		((min >= max) && (x <= min) && (x >= max));
}

//----------------------------------------------------------------

inline bool isbetween( int32_t x, int32_t min, int32_t max ) {
	return
		((min <= max) && (x >= min) && (x <= max)) ||
		((min >= max) && (x <= min) && (x >= max));
}

//----------------------------------------------------------------

inline bool isbetween( float x, float min, float max ) {
	return
		((min <= max) && (x >= min) && (x <= max)) ||
		((min >= max) && (x <= min) && (x >= max));
}

//----------------------------------------------------------------
// https://www.arduino.cc/reference/en/language/functions/math/constrain/

template< typename number_t >
inline number_t constrain( number_t x, number_t min, number_t max ) {
	return (x > min) ? ((x < max) ? x : max) : min;
}

//----------------------------------------------------------------

inline int32_t constrain( int32_t x, int32_t min, int32_t max ) {
	return (x > min) ? ((x < max) ? x : max) : min;
}

//----------------------------------------------------------------

inline float constrain( float x, float min, float max ) {
	return (x > min) ? ((x < max) ? x : max) : min;
}

///----------------------------------------------------------------
// https://www.arduino.cc/reference/en/language/functions/math/map/

template< typename number_t >
inline number_t map( number_t x, number_t in_min, number_t in_max, number_t out_min, number_t out_max ) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//----------------------------------------------------------------

inline int32_t map( int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max ) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//----------------------------------------------------------------

inline float map( float x, float in_min, float in_max, float out_min, float out_max ) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//----------------------------------------------------------------

inline uint16_t pack( uint8_t byte1, uint8_t byte0 ) {
	return ((uint16_t)byte1 << 8) | ((uint16_t)byte0 << 0); 
}

//----------------------------------------------------------------

inline uint32_t pack( uint8_t byte2, uint8_t byte1, uint8_t byte0 ) {
	return ((uint32_t)byte2 << 16) | ((uint32_t)byte1 << 8) | ((uint32_t)byte0 << 0); 
}

//----------------------------------------------------------------

inline uint32_t pack( uint8_t byte3, uint8_t byte2, uint8_t byte1, uint8_t byte0 ) {
	return ((uint32_t)byte3 << 24) | ((uint32_t)byte2 << 16) | ((uint32_t)byte1 << 8) | ((uint32_t)byte0 << 0); 
}

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
