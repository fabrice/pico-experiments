//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// écran OLED école
// SSD1309
// proof of concept
//
//----------------------------------------------------------------

#pragma once
#ifndef _OLED_FN_H
#define _OLED_FN_H

//----------------------------------------------------------------

#include "pico/stdlib.h"

//----------------------------------------------------------------

class OLED;
using oled_ref = OLED*;

//----------------------------------------------------------------
// fonctions

oled_ref oled_init( uint8_t i2c_num, uint8_t address, uint reset_gpio );

//----------------------------------------------------------------

uint16_t oled_get_width( oled_ref oled );
uint16_t oled_get_height( oled_ref oled );

uint16_t oled_get_column_count( oled_ref oled );
uint16_t oled_get_line_count( oled_ref oled );

void oled_set_on( oled_ref oled, bool on );
void oled_set_orientation( oled_ref oled, uint8_t orientation );
void oled_set_dark_mode( oled_ref oled, bool mode );
void oled_set_brightness( oled_ref oled, uint8_t brightness );

void oled_set_lico( oled_ref oled, uint8_t line, uint8_t column );

void oled_print( oled_ref oled, const char* const text );
void oled_print( oled_ref oled, const char* const text, uint8_t line, uint8_t column );
void oled_print_center( oled_ref oled, const char* const text, uint8_t line );

void oled_printf( oled_ref oled, const char* format, ... );

void oled_print( oled_ref oled, char character );
void oled_print( oled_ref oled, char character, uint8_t line, uint8_t column );

void oled_print_glyph( oled_ref oled, uint8_t glyph[6] );

void oled_draw_bitmap( oled_ref oled, int16_t x, int16_t y, int16_t width, int16_t height, uint8_t* bitmap, uint16_t length );

void oled_erase( oled_ref oled );
void oled_erase_line( oled_ref oled, uint8_t line );
void oled_erase_character( oled_ref oled, uint8_t line, uint8_t column );

//----------------------------------------------------------------

void oled_deinit( oled_ref& oled );

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
