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
	spi_instance( nullptr ),
	chip_select_gpio( 0 ) {
}

//----------------------------------------------------------------

wire_spi::wire_spi( uint spi_num, uint chip_select_gpio ):
	spi_instance( nullptr ),
	chip_select_gpio( chip_select_gpio ) {
	this->spi_instance = spi_get_instance( spi_num );

	gpio_init( this->chip_select_gpio );
	gpio_set_dir( this->chip_select_gpio, GPIO_OUT );
	gpio_put( this->chip_select_gpio, 1 );
}

//----------------------------------------------------------------

wire_spi::~wire_spi() {
	gpio_put( this->chip_select_gpio, 0 );
	gpio_deinit( this->chip_select_gpio );
}

//----------------------------------------------------------------

void wire_spi::io_init( uint sclk_gpio, uint miso_gpio, uint mosi_gpio, uint bitrate ) {
    spi_init( spi_instance, bitrate );
    gpio_set_function( sclk_gpio, GPIO_FUNC_SPI );
    gpio_set_function( miso_gpio, GPIO_FUNC_SPI );
    gpio_set_function( mosi_gpio, GPIO_FUNC_SPI );
}

//----------------------------------------------------------------

void wire_spi::set_bitrate( uint bitrate ) {
	spi_set_baudrate( this->spi_instance, bitrate );
}

//----------------------------------------------------------------

void wire_spi::start() {
	gpio_put( this->chip_select_gpio, 0 );
}

//----------------------------------------------------------------

int wire_spi::write_bytes( const uint8_t* bytes, size_t length ) {
	return spi_write_blocking( this->spi_instance, bytes, length );
}

//----------------------------------------------------------------

int wire_spi::read_bytes( uint8_t* bytes, size_t* length ) {
	*length = spi_read_blocking( this->spi_instance, *bytes, bytes, *length );
	return *length;
}

//----------------------------------------------------------------

void wire_spi::finish() {
	gpio_put( this->chip_select_gpio, 1 );
}

//----------------------------------------------------------------
