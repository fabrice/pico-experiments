//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// cfpt_mono_6x8
//
//----------------------------------------------------------------

#pragma once

#include <cstdint>
#include <array>

//----------------------------------------------------------------

extern const uint8_t cfpt_mono_6x8[256][5];

using array_of_5_bytes = std::array< uint8_t, 5 >;
extern const std::array< array_of_5_bytes, 256 > cfpt_mono_6x8_array;

//----------------------------------------------------------------
