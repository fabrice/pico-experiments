//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// wire_spi
//
//----------------------------------------------------------------

#include "wire_spi.h"

#include "hardware_spi_plus.h"

//----------------------------------------------------------------

wire_spi::wire_spi():
	_spi_instance( nullptr ),
	_chip_select_gpio( 0 ) {
}

//----------------------------------------------------------------

wire_spi::wire_spi( uint spi_num, uint chip_select_gpio ):
	_spi_instance( nullptr ),
	_chip_select_gpio( chip_select_gpio ) {
	_spi_instance = spi_get_instance( spi_num );

	gpio_init( _chip_select_gpio );
	gpio_set_dir( _chip_select_gpio, GPIO_OUT );
	gpio_put( _chip_select_gpio, true );
}

//----------------------------------------------------------------

wire_spi::~wire_spi() {
	gpio_put( _chip_select_gpio, false );
	gpio_deinit( _chip_select_gpio );
}

//----------------------------------------------------------------

void wire_spi::io_init( uint sclk_gpio, uint miso_gpio, uint mosi_gpio, uint bitrate ) {
    spi_init( _spi_instance, bitrate );
    gpio_set_function( sclk_gpio, GPIO_FUNC_SPI );
    gpio_set_function( miso_gpio, GPIO_FUNC_SPI );
    gpio_set_function( mosi_gpio, GPIO_FUNC_SPI );
}

//----------------------------------------------------------------

void wire_spi::set_bitrate( uint bitrate ) {
	spi_set_baudrate( _spi_instance, bitrate );
}

//----------------------------------------------------------------

void wire_spi::start_communication() {
	gpio_put( _chip_select_gpio, false );
}

//----------------------------------------------------------------

int wire_spi::write_bytes( const uint8_t* bytes, size_t length ) {
	return spi_write_blocking( _spi_instance, bytes, length );
}

//----------------------------------------------------------------

int wire_spi::read_bytes( uint8_t* bytes, size_t* length ) {
	*length = spi_read_blocking( _spi_instance, *bytes, bytes, *length );
	return *length;
}

//----------------------------------------------------------------

void wire_spi::finish_communication() {
	gpio_put( _chip_select_gpio, true );
}

//----------------------------------------------------------------
