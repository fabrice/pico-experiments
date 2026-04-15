//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// wire_uart
//
//----------------------------------------------------------------

#include "wire_uart.h"

#include "hardware/uart.h"

//----------------------------------------------------------------

wire_uart::wire_uart( uint uart_num ):
	_uart_instance { nullptr } {

	_uart_instance = uart_get_instance( uart_num );
}

//----------------------------------------------------------------

wire_uart::~wire_uart() {
	//uart_deinit( _uart_instance );
}

//----------------------------------------------------------------

void wire_uart::io_init( uint tx_gpio, uint rx_gpio, uint bitrate ) {
	uart_init( _uart_instance, bitrate );
    gpio_set_function( tx_gpio, GPIO_FUNC_UART );
    gpio_set_function( rx_gpio, GPIO_FUNC_UART );
}

//----------------------------------------------------------------

void wire_uart::set_bitrate( uint bitrate ) {
	uart_set_baudrate( _uart_instance, bitrate );
}

//----------------------------------------------------------------

int wire_uart::write_bytes( const uint8_t* bytes, size_t length ) {
	uart_write_blocking( _uart_instance, bytes, length );

	return length;
}

//----------------------------------------------------------------

int wire_uart::read_bytes( uint8_t* bytes, size_t* length ) {
	uint8_t* dbytes = bytes;
	size_t length_max = *length;
	size_t length_rx = 0;
	while( uart_is_readable( _uart_instance ) && (length_rx <= length_max) ) {
		uart_read_blocking( _uart_instance, dbytes, 1 );
		++ dbytes;
		++ length_rx;
	}

	*length = length_rx;
	return length_rx;
}

//----------------------------------------------------------------
