//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// buzzer_melody_data
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "buzzer.h"

#include <cstdint>
#include <vector>

//----------------------------------------------------------------

struct buzzer_note_data;
using buzzer_melody_data = std::vector< buzzer_note_data >;

//----------------------------------------------------------------

struct buzzer_note_data {
	float frequency { buzzer::BASE_NOTE };
	uint16_t play_ms { 1000 };
	uint16_t pause_ms { 0 };
};

//----------------------------------------------------------------

const buzzer_melody_data test_melody {
	{ buzzer::E4, 400, 50 },
	{ buzzer::E4, 400, 50 },
	{ buzzer::F4, 400, 50 },
	{ buzzer::G4, 400, 50 },
	{ buzzer::G4, 400, 50 },
	{ buzzer::F4, 400, 50 },
	{ buzzer::E4, 400, 50 },
	{ buzzer::D4, 400, 50 },
	{ buzzer::C4, 800, 0 },
};

//----------------------------------------------------------------
