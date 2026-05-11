//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// temperature sensor
// mcp9800
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico/stdlib.h"

#include "wire_i2c.h"
#include "hardware_i2c_plus.h"

//----------------------------------------------------------------

constexpr uint8_t MCP9800_ADDRESS { 0x49 }; // 0x92 >> 1

//----------------------------------------------------------------

class mcp9800 {

private:

	wire* _wire { nullptr };
	uint8_t _address { MCP9800_ADDRESS };

	uint8_t _config { 0b01100000 };
	float _lo_temperature { 75.0f };
	float _hi_temperature { 80.0f };
	float _temperature { 0.0f };

public:

	static mcp9800* make( uint i2c_num, uint8_t address );

	mcp9800() = delete;
	mcp9800( wire* wire );

	~mcp9800() noexcept;

	void read_configuration();

	bool get_oneshot() const { return !!(_config & 0b10000000); }
	void set_oneshot( bool oneshot );

	uint8_t get_adc_resolution() const { return ((_config & 0b01100000) >> 5) + 9; }
	void set_adc_resolution( uint8_t bits );

	uint8_t get_fault_queue() const { return ((_config & 0b00011000) >> 3); }
	void set_fault_queue( uint8_t faults );

	bool get_alert_polarity() const { return !!(_config & 0b00000100); }
	void set_alert_polarity( bool high );

	bool get_interrupt_enabled() const { return !!(_config & 0b00000010); }
	void set_interrupt_enabled( bool enabled );

	bool get_shutdown() const { return !!(_config & 0b00000001); }
	void set_shutdown( bool shutdown );

	void read_lo_temperature();
	void read_hi_temperature();

	float get_lo_temperature() const { return _lo_temperature; }
	void set_lo_temperature( float temperature );

	float get_hi_temperature() const { return _hi_temperature; }
	void set_hi_temperature( float temperature );

	void read_temperature();
	float get_temperature() const { return _temperature; }

};

//----------------------------------------------------------------
