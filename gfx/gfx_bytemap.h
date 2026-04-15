//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_bytemap
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "gfx_types.h"

//----------------------------------------------------------------

bool bytemap_get_bit( const gfx_bytemap_data& bytemap, size_t index );
void bytemap_set_bit( gfx_bytemap_data& bytemap, size_t index, bool bit );
void bytemap_set_bit( gfx_bytemap_data& bytemap, size_t index );
void bytemap_clr_bit( gfx_bytemap_data& bytemap, size_t index );
void bytemap_xor_bit( gfx_bytemap_data& bytemap, size_t index );

//----------------------------------------------------------------

inline bool bytemap_get_bit( const gfx_bytemap_data& bytemap, size_t index ) {
	return !!(bytemap[ index / 8 ] & (0b10000000 >> (index % 8)));
}

//----------------------------------------------------------------

inline void bytemap_set_bit( gfx_bytemap_data& bytemap, size_t index, bool bit ) {
	if ( bit ) bytemap_set_bit( bytemap, index );
	else bytemap_clr_bit( bytemap, index );
}

//----------------------------------------------------------------

inline void bytemap_set_bit( gfx_bytemap_data& bytemap, size_t index ) {
	bytemap[ index / 8 ] |= (0b10000000 >> (index % 8));
}

//----------------------------------------------------------------

inline void bytemap_clr_bit( gfx_bytemap_data& bytemap, size_t index ) {
	bytemap[ index / 8 ] &= ~(0b10000000 >> (index % 8));
}

//----------------------------------------------------------------

inline void bytemap_xor_bit( gfx_bytemap_data& bytemap, size_t index ) {
	bytemap[ index / 8 ] ^= (0b10000000 >> (index % 8));
}

//----------------------------------------------------------------
