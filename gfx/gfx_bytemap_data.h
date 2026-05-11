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

#include <algorithm>

#include "gfx_types.h"

//----------------------------------------------------------------

class gfx_bytemap_data: public std::vector< uint8_t > {

public:

	gfx_bytemap_data() = default;
	gfx_bytemap_data( size_t size ): std::vector< uint8_t >( size ) {}
	gfx_bytemap_data( size_t size, uint8_t data ): std::vector< uint8_t >( size, data ) {}
	gfx_bytemap_data( const gfx_bytemap_data& that ) = default;
	gfx_bytemap_data( gfx_bytemap_data&& that ) = default;
	gfx_bytemap_data( std::initializer_list< uint8_t > list ): std::vector< uint8_t >( list ) {}
	gfx_bytemap_data& operator=( const gfx_bytemap_data& rhs ) = default;

	~gfx_bytemap_data() noexcept = default;

	bool get_bit( size_t index ) const {
		return !!((*this)[ index / 8 ] & (0b10000000 >> (index % 8)));
	}

	void set_bit( size_t index, bool bit ) {
		if ( bit ) this->set_bit( index );
		else this->clr_bit( index );
	}

	void set_bit( size_t index ) {
		(*this)[ index / 8 ] |= (0b10000000 >> (index % 8));
	}
	void clr_bit( size_t index ) {
		(*this)[ index / 8 ] &= ~(0b10000000 >> (index % 8));
	}
	void xor_bit( size_t index ) {
		(*this)[ index / 8 ] ^= (0b10000000 >> (index % 8));
	}

	void fill( uint8_t data ) {
		std::ranges::fill( (*this), data );
	}

	bool is_empty() const {
		return !std::ranges::any_of( (*this), []( uint8_t byte ) -> bool { return byte != 0; } );
	}

};

//----------------------------------------------------------------
