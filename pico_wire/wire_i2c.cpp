//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// wire_i2c
//
//----------------------------------------------------------------

#include "wire_i2c.h"

#include "hardware/i2c.h"

//----------------------------------------------------------------

wire_i2c::wire_i2c( uint i2c_num, uint8_t address ):
	i2c_instance( nullptr ),
	address( address ) {
	i2c_instance = i2c_get_instance( i2c_num );
}

//----------------------------------------------------------------

wire_i2c::~wire_i2c() {
}

//----------------------------------------------------------------

void wire_i2c::io_init( uint scl_gpio, uint sda_gpio, uint bitrate ) {
	i2c_init( i2c_instance, bitrate );
    gpio_set_function( scl_gpio, GPIO_FUNC_I2C );
    gpio_set_function( sda_gpio, GPIO_FUNC_I2C );
}

//----------------------------------------------------------------

void wire_i2c::set_bitrate( uint bitrate ) {
	i2c_set_baudrate( i2c_instance, bitrate );
}

//----------------------------------------------------------------

int wire_i2c::write_bytes( const uint8_t* bytes, size_t length ) {
	return i2c_write_blocking( i2c_instance, address, bytes, length, false );
}

//----------------------------------------------------------------

int wire_i2c::read_bytes( uint8_t* bytes, size_t* length ) {
	*length = i2c_read_blocking( i2c_instance, address, bytes, *length, false );
	return *length;
}

//----------------------------------------------------------------
