//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// neopixels
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico/stdlib.h"
#include "hardware/pio.h"

//----------------------------------------------------------------

class neopixels {

public:

	static constexpr uint8_t FORMAT_RGB { 11 };
	static constexpr uint8_t FORMAT_GRB { 12 };
	static constexpr uint8_t FORMAT_RGBW { 21 };
	static constexpr uint8_t FORMAT_GRBW { 22 };

	static constexpr uint8_t BRIGHTNESS_FULL { 255 };
	static constexpr uint8_t BRIGHTNESS_HALF { 77 };

	static constexpr uint64_t RESET_TIME { 50 };

private:

	uint _gpio { 255 };
	uint8_t _format { FORMAT_RGB };
	size_t _count { 0 };

	PIO _pio { nullptr };
	uint _pio_state_machine { 0 };
	uint _pio_offset { 0 };

public:

	static neopixels* make( uint gpio );
	static neopixels* make( uint gpio, uint8_t format, size_t count );

	neopixels( uint gpio, uint8_t format, size_t count );

	~neopixels();

	void start() const { this->send_reset(); }

	void send_reset() const;

	// one
	void send_rgb( uint8_t red, uint8_t green, uint8_t blue ) const;
	void send_rgbw( uint8_t red, uint8_t green, uint8_t blue, uint8_t white ) const;
	void send_white( uint8_t white ) const;
	void send_black() const;

	// many
	void send_many_rgb( size_t count, uint8_t red, uint8_t green, uint8_t blue ) const;
	void send_many_rgbw( size_t count, uint8_t red, uint8_t green, uint8_t blue, uint8_t white ) const;
	void send_many_white( size_t count, uint8_t white ) const;
	void send_many_black( size_t count ) const;

	// all
	void send_all_rgb( uint8_t red, uint8_t green, uint8_t blue ) const;
	void send_all_rgbw( uint8_t red, uint8_t green, uint8_t blue, uint8_t white ) const;
	void send_all_white( uint8_t white ) const;
	void send_all_black() const;

	void finish() const { this->send_reset(); }

};

//----------------------------------------------------------------
