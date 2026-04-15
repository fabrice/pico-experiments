//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_font : cfpt_mono_6x8
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "gfx_font_data.h"

#include "gfx_glyph.h"
#include "gfx_font.h"

//----------------------------------------------------------------
// https://www.charset.org/charsets/iso-8859-1
// https://www.charset.org/charsets/windows-1252
// https://www.ascii-code.com/

extern const gfx_font_data cfpt_mono_6x8_font_data;
extern const uint8_t cfpt_mono_6x8_array[256][6];

//----------------------------------------------------------------
