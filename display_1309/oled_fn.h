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
using oled_ptr = OLED*;

//----------------------------------------------------------------
// fonctions

oled_ptr oled_init( uint8_t i2c_num, uint8_t address, uint reset_gpio );

//----------------------------------------------------------------

uint16_t oled_get_width( const oled_ptr oled );
uint16_t oled_get_height( const oled_ptr oled );

uint16_t oled_get_column_count( const oled_ptr oled );
uint16_t oled_get_line_count( const oled_ptr oled );

void oled_set_on( oled_ptr oled, bool on );
void oled_set_orientation( oled_ptr oled, uint8_t orientation );
void oled_set_dark_mode( oled_ptr oled, bool mode );
void oled_set_brightness( oled_ptr oled, uint8_t brightness );
void oled_set_brightness_db( oled_ptr oled, float brightness_db );

void oled_set_lico( oled_ptr oled, uint8_t line, uint8_t column );

void oled_print( oled_ptr oled, const char* text );
void oled_print( oled_ptr oled, const char* text, uint8_t line, uint8_t column );
void oled_print_left( oled_ptr oled, const char* text, uint8_t line );
void oled_print_center( oled_ptr oled, const char* text, uint8_t line );
void oled_print_right( oled_ptr oled, const char* text, uint8_t line );

void oled_printf( oled_ptr oled, const char* format, ... );

void oled_print( oled_ptr oled, char character );
void oled_print( oled_ptr oled, char character, uint8_t line, uint8_t column );

void oled_print_glyph( oled_ptr oled, const uint8_t glyph[6] );

void oled_draw_bitmap( oled_ptr oled, int16_t x, int16_t y, int16_t width, int16_t height, const uint8_t* bitmap, uint16_t length );

void oled_erase( oled_ptr oled );
void oled_erase_line( oled_ptr oled, uint8_t line );
void oled_erase_character( oled_ptr oled, uint8_t line, uint8_t column );

//----------------------------------------------------------------

void oled_deinit( oled_ptr& oled );

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
