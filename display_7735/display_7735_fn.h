//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// display ST7735
// st7735
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico/stdlib.h"

//----------------------------------------------------------------

class display_7735;

//----------------------------------------------------------------
// fonctions

display_7735* display_7735_init( uint8_t spi_num, uint reset_gpio );

//----------------------------------------------------------------
// properties

uint16_t display_7735_get_width( const display_7735* that );
uint16_t display_7735_get_height( const display_7735* that );

uint16_t display_7735_get_column_count( const display_7735* that );
uint16_t display_7735_get_line_count( const display_7735* that );

//----------------------------------------------------------------
// configuration

void display_7735_set_on( display_7735* that, bool on );
void display_7735_set_brightness( display_7735* that, uint8_t brightness );
void display_7735_set_brightness_db( display_7735* that, float brightness_db );

void display_7735_set_lico( display_7735* that, uint8_t line, uint8_t column );

//----------------------------------------------------------------
// text

void display_7735_print( display_7735* that, const char* text );
void display_7735_print( display_7735* that, const char* text, uint8_t line, uint8_t column );

void display_7735_print_left( display_7735* that, const char* text, uint8_t line );
void display_7735_print_center( display_7735* that, const char* text, uint8_t line );
void display_7735_print_right( display_7735* that, const char* text, uint8_t line );

void display_7735_printf( display_7735* that, const char* format, ... );

void display_7735_print( display_7735* that, char character );
void display_7735_print( display_7735* that, char character, uint8_t line, uint8_t column );

void display_7735_print_glyph( display_7735* that, const uint8_t glyph[6] );

//----------------------------------------------------------------
// graphics

void display_7735_draw_pixmap( display_7735* that, const uint8_t* pixmap, uint16_t length, int16_t x, int16_t y, int16_t width, int16_t height );
void display_7735_draw_bitmap( display_7735* that, const uint8_t* bitmap, uint16_t length, int16_t x, int16_t y, int16_t width, int16_t height );

//----------------------------------------------------------------
// finishes

void display_7735_erase( display_7735* that );
void display_7735_erase_line( display_7735* that, uint8_t line );
void display_7735_erase_character( display_7735* that, uint8_t line, uint8_t column );

//----------------------------------------------------------------

void display_7735_deinit( display_7735*& that );

//----------------------------------------------------------------
