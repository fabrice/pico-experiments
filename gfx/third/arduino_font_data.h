//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include <cstddef>
#include <cstdint>

//----------------------------------------------------------------

struct arduino_gfx_font_data {
  int width { 0 };
  int height { 0 };
  const uint8_t** data { nullptr };
};

using arduino_gfx_font_data_ptr = arduino_gfx_font_data*;

//----------------------------------------------------------------
