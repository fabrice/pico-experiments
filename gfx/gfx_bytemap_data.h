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

class gfx_bytemap_data {

private:

	std::vector< uint8_t > _bits;

public:

	gfx_bytemap_data() = default;
	gfx_bytemap_data( size_t size ): _bits( size ) {}
	gfx_bytemap_data( size_t size, uint8_t data ): _bits( size, data ) {}
	gfx_bytemap_data( const gfx_bytemap_data& that ) = default;
	gfx_bytemap_data( gfx_bytemap_data&& that ) = default;
	gfx_bytemap_data( std::initializer_list< uint8_t > list ): _bits( list ) {}
	gfx_bytemap_data& operator=( const gfx_bytemap_data& rhs ) = default;

	~gfx_bytemap_data() noexcept = default;

	uint8_t get_byte( size_t index ) const {
		return _bits[ index ];
	}

	void set_byte( size_t index, uint8_t byte ) {
		_bits[ index ] = byte;
	}

	bool get_bit( size_t index ) const {
		return !!(_bits[ index / 8 ] & (0b10000000 >> (index % 8)));
	}

	void set_bit( size_t index, bool bit ) {
		if ( bit ) this->set_bit( index );
		else this->clr_bit( index );
	}

	void set_bit( size_t index ) {
		_bits[ index / 8 ] |= (0b10000000 >> (index % 8));
	}
	void clr_bit( size_t index ) {
		_bits[ index / 8 ] &= ~(0b10000000 >> (index % 8));
	}
	void xor_bit( size_t index ) {
		_bits[ index / 8 ] ^= (0b10000000 >> (index % 8));
	}

	void set_bits( size_t index, uint8_t bits ) {
		_bits[ index ] = bits;
	}

	void set_bits_mask( size_t index, uint8_t mask ) {
		_bits[ index ] |= mask;
	}

	void clr_bits_mask( size_t index, uint8_t mask ) {
		_bits[ index ] &= ~mask;
	}

	void xor_bits_mask( size_t index, uint8_t mask ) {
		_bits[ index ] ^= mask;
	}

private:

	uint8_t& operator[]( size_t index ) {
		return _bits[ index ];
	}

	const uint8_t& operator[]( size_t index ) const {
		return _bits[ index ];
	}

public:

	void fill( uint8_t data ) {
		std::ranges::fill( _bits, data );
	}

	bool is_empty() const {
		return !std::ranges::any_of( _bits, []( uint8_t byte ) -> bool { return byte != 0; } );
	}

	void resize( size_t size ) {
		_bits.resize( size );
	}

	void resize( size_t size, uint8_t value ) {
		_bits.resize( size, value );
	}

	void clear() noexcept {
		_bits.clear();
	}

};

//----------------------------------------------------------------
