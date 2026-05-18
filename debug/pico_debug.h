//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// debug
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico/stdlib.h"

#include <string_view>

//----------------------------------------------------------------

#ifndef NDEBUG

inline void debug_breakpoint() { __breakpoint(); }
void debug_message( std::string_view nature, std::string_view message );

#else

inline void debug_breakpoint() {}
inline void debug_message( std::string_view nature, std::string_view message ) {}

#endif

//----------------------------------------------------------------
