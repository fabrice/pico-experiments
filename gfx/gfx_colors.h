//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// gfx_colors
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "gfx_types.h"

#include "gfx_color_casts.h"

#include "gfx_color_bit.h"
#include "gfx_color_rgb.h"
#include "gfx_color_argb.h"
#include "gfx_color_gray.h"
#include "gfx_color_hsb.h"

#include "gfx_color_rgb.cxx"
#include "gfx_color_argb.cxx"
#include "gfx_color_gray.cxx"

//----------------------------------------------------------------

template class gfx_color_rgb< bool >;
template class gfx_color_rgb< uint8_t >;
template class gfx_color_rgb< float >;

//----------------------------------------------------------------

template class gfx_color_argb< bool >;
template class gfx_color_argb< uint8_t >;
template class gfx_color_argb< float >;

//----------------------------------------------------------------

template class gfx_color_gray< bool >;
template class gfx_color_gray< uint8_t >;
template class gfx_color_gray< float >;

//----------------------------------------------------------------
