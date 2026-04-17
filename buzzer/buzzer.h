//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// buzzer
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico/stdlib.h"

#include "pwm.h"

#include <vector>

//----------------------------------------------------------------

struct buzzer_note_data;
using buzzer_melody_data = std::vector< buzzer_note_data >;

//----------------------------------------------------------------

class buzzer {

public:

	// music notes

	static constexpr float C4 { 261.6 };
	static constexpr float Cd4 { 277.2 };
	static constexpr float D4 { 293.7 };
	static constexpr float Dd4 { 311.1 };
	static constexpr float E4 { 329.6 };
	static constexpr float F4 { 349.2 };
	static constexpr float Fd4 { 370.0 };
	static constexpr float G4 { 392.0 };
	static constexpr float Gd4 { 415.3 };
	static constexpr float A4 { 440.0 };
	static constexpr float Ad4 { 466.2 };
	static constexpr float B4 { 493.9 };

	static constexpr float C5 { 523.3 };
	static constexpr float Cd5 { 554.4 };
	static constexpr float D5 { 587.3 };
	static constexpr float Dd5 { 622.3 };
	static constexpr float E5 { 659.3 };
	static constexpr float F5 { 698.5 };
	static constexpr float Fd5 { 740.0 };
	static constexpr float G5 { 784.0 };
	static constexpr float Gd5 { 830.6 };
	static constexpr float A5 { 880.0 };
	static constexpr float Ad5 { 932.3 };
	static constexpr float B5 { 987.8 };

	static constexpr float BASE_NOTE { C5 };

private:

	pwm* _pwm { nullptr };

public:

	buzzer() = delete;
	buzzer( uint gpio );
	buzzer( pwm* pwm );

	~buzzer();

	float get_frequency() const;
	void set_frequency( float frequency );
	void set_enabled( bool enabled );

	void play_note( float frequency, uint16_t play_ms, uint16_t pause_ms = 0 );
	void play_melody( const buzzer_melody_data melody );

};

//----------------------------------------------------------------
