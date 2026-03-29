//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// mcp23008
//
//----------------------------------------------------------------

#include "mcp23008.h"

#include "pico/stdlib.h"
#include "hardware_i2c_plus.h"

//----------------------------------------------------------------

constexpr uint8_t MCP23008_IODIR = 0x00;
constexpr uint8_t MCP23008_IPOL = 0x01;
constexpr uint8_t MCP23008_GPINTEN = 0x02;
constexpr uint8_t MCP23008_DEFVAL = 0x03;
constexpr uint8_t MCP23008_INTCON = 0x04;
constexpr uint8_t MCP23008_IOCON = 0x05;
constexpr uint8_t MCP23008_GPPU = 0x06;
constexpr uint8_t MCP23008_INTF = 0x07;
constexpr uint8_t MCP23008_INTCAP = 0x08;
constexpr uint8_t MCP23008_GPIO = 0x09;
constexpr uint8_t MCP23008_OLAT = 0x0a;

//----------------------------------------------------------------

mcp23008::mcp23008():
	wire( nullptr ),
	address( MCP23008_ADDRESS ),
	gpio_dir( 0x00 ),
	gpio_pull_up( 0x00 ) {
	this->gpio_init();
}

//----------------------------------------------------------------

mcp23008::mcp23008( i2c_ref wire, uint8_t address, uint8_t gpio_dir, uint8_t gpio_pull_up ):
	wire( wire ),
	address( address ),
	gpio_dir( ~gpio_dir ),
	gpio_pull_up( gpio_pull_up ) {
	this->gpio_init();
}

//----------------------------------------------------------------

mcp23008::~mcp23008() {
	this->gpio_put_all( 0 );
}

//----------------------------------------------------------------

void mcp23008::gpio_init() {
	uint8_t buffer[] = {
		MCP23008_IODIR, // register IODIR
		gpio_dir, // IODIR
		0x00, // IPOL
		0x00, // GPINTEN
		0x00, // DEFVAL
		0x00, // INTCON
		0x00, // IOCON
		gpio_pull_up, // GPPU
		0x00, // INTF
		0x00, // GPIO
		0x00 // OLAT
	};
	i2c_write_blocking( wire, address, buffer, sizeof(buffer), false );

	i2c_write_bytes_blocking( wire, address, MCP23008_IODIR, gpio_dir );
	i2c_write_bytes_blocking( wire, address, MCP23008_GPPU, gpio_pull_up );
}

//----------------------------------------------------------------

void mcp23008::gpio_set_dir( uint8_t gpio, bool out ) {
	if ( gpio > 7 ) return;

	if ( out ) gpio_dir &= ~(1 << gpio);
	else gpio_dir |= (1 << gpio);
	i2c_write_bytes_blocking( wire, address, MCP23008_IODIR, gpio_dir );
}

//----------------------------------------------------------------

void mcp23008::gpio_set_pull_up( uint8_t gpio, bool up ) {
	if ( gpio > 7 ) return;

	if ( up ) gpio_pull_up |= (1 << gpio);
	else gpio_pull_up &= ~(1 << gpio);
	i2c_write_bytes_blocking( wire, address, MCP23008_GPPU, gpio_pull_up );
}

//----------------------------------------------------------------

uint8_t mcp23008::gpio_get_all() {
	uint8_t data = 0;
	i2c_write_bytes_blocking( wire, address, MCP23008_GPIO );
	i2c_read_blocking( wire, address, &data, sizeof( data ), false );

	return data;
}

//----------------------------------------------------------------

void mcp23008::gpio_put_all( uint8_t value ) {
	i2c_write_bytes_blocking( wire, address, MCP23008_GPIO, value );
}

//----------------------------------------------------------------

uint8_t mcp23008::gpio_get( uint8_t gpio ) {
	if ( gpio > 7 ) return 0;

	return !!(this->gpio_get_all() >> gpio);
}

//----------------------------------------------------------------

void mcp23008::gpio_put( uint8_t gpio, bool value ) {
	if ( gpio > 7 ) return;

	uint8_t data = this->gpio_get_all();

	if ( value ) data |= (1 << gpio);
	else data &= ~(1 << gpio);

	this->gpio_put_all( data );
}

//----------------------------------------------------------------
