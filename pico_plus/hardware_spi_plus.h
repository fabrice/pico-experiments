//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// hardware_spi_plus
//
//----------------------------------------------------------------

#pragma once
#ifndef _HARDWARE_SPI_PLUS_H
#define _HARDWARE_SPI_PLUS_H

//----------------------------------------------------------------

#include "hardware/spi.h"

//----------------------------------------------------------------
// hardware/spi

using spi_ptr = spi_inst_t*;

//----------------------------------------------------------------

static inline spi_inst_t* spi_get_instance( uint num ) {
    invalid_params_if( HARDWARE_SPI, num >= NUM_SPIS );
	return SPI_INSTANCE( num );
}

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
