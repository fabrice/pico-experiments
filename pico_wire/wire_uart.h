//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// wire_uart
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico/stdlib.h"

#include "wire.h"

#include "hardware/uart.h"

//----------------------------------------------------------------

class wire_uart;
using wire_uart_ptr = wire_uart*;

using uart_ptr = uart_inst_t*;

//----------------------------------------------------------------

class wire_uart : public virtual wire {

private:

	uart_ptr _uart_instance { nullptr };

public:

	wire_uart() = delete;
	wire_uart( uint uart_num );
	virtual ~wire_uart() override;

	void io_init( uint tx_gpio, uint rx_gpio, uint bitrate );

	virtual void set_bitrate( uint bitrate ) override;

	virtual int write_bytes( const uint8_t* bytes, size_t length ) override;

	virtual int read_bytes( uint8_t* bytes, size_t* length ) override;

};

//----------------------------------------------------------------
