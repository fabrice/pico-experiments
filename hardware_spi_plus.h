//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// hardware_spi_plus.h
//
//----------------------------------------------------------------

#pragma once
#ifndef _HARDWARE_SPI_PLUS_H
#define _HARDWARE_SPI_PLUS_H

//----------------------------------------------------------------

#include "pico.h"
#include "hardware/spi.h"


//----------------------------------------------------------------
// hardware/spi

typedef spi_inst_t* spi_ref;

//----------------------------------------------------------------

static inline spi_inst_t* spi_get_instance( uint num ) {
    invalid_params_if( HARDWARE_SPI, num >= NUM_SPIS );
	return SPI_INSTANCE( num );
}

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
