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
	_i2c_instance( nullptr ),
	_address( address ),
	_transaction( false ) {
	_i2c_instance = i2c_get_instance( i2c_num );
}

//----------------------------------------------------------------

wire_i2c::~wire_i2c() {
}

//----------------------------------------------------------------

void wire_i2c::io_init( uint scl_gpio, uint sda_gpio, uint bitrate ) {
	i2c_init( _i2c_instance, bitrate );
    gpio_set_function( scl_gpio, GPIO_FUNC_I2C );
    gpio_set_function( sda_gpio, GPIO_FUNC_I2C );
}

//----------------------------------------------------------------

void wire_i2c::set_bitrate( uint bitrate ) {
	i2c_set_baudrate( _i2c_instance, bitrate );
}

//----------------------------------------------------------------

void wire_i2c::start_transaction() {
	_transaction = true;
}

//----------------------------------------------------------------

int wire_i2c::write_bytes( const uint8_t* bytes, size_t length ) {
	return i2c_write_blocking( _i2c_instance, _address, bytes, length, _transaction );
}

//----------------------------------------------------------------

int wire_i2c::read_bytes( uint8_t* bytes, size_t* length ) {
	*length = i2c_read_blocking( _i2c_instance, _address, bytes, *length, _transaction );
	return *length;
}

//----------------------------------------------------------------

void wire_i2c::finish_transaction() {
	_transaction = false;
}

//----------------------------------------------------------------
