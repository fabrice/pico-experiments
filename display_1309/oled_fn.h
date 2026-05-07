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

//----------------------------------------------------------------
// functions

OLED* oled_init( uint8_t i2c_num, uint8_t address, uint reset_gpio );

//----------------------------------------------------------------
// properties

uint16_t oled_get_width( const OLED* that );
uint16_t oled_get_height( const OLED* that );

uint16_t oled_get_column_count( const OLED* that );
uint16_t oled_get_line_count( const OLED* that );

//----------------------------------------------------------------
// configuration

void oled_set_on( OLED* that, bool on );
void oled_set_orientation( OLED* that, uint8_t orientation );
void oled_set_dark_mode( OLED* that, bool mode );
void oled_set_brightness( OLED* that, uint8_t brightness );
void oled_set_brightness_db( OLED* that, float brightness_db );

void oled_set_lico( OLED* that, uint8_t line, uint8_t column );

//----------------------------------------------------------------
// text

void oled_print( OLED* that, const char* text );
void oled_print( OLED* that, const char* text, uint8_t line, uint8_t column );

void oled_print_left( OLED* that, const char* text, uint8_t line );
void oled_print_center( OLED* that, const char* text, uint8_t line );
void oled_print_right( OLED* that, const char* text, uint8_t line );

void oled_printf( OLED* that, const char* format, ... );

void oled_print( OLED* that, char character );
void oled_print( OLED* that, char character, uint8_t line, uint8_t column );

void oled_print_glyph( OLED* that, const uint8_t glyph[6] );

//----------------------------------------------------------------
// graphics

/**
 * oled_draw_yx_bytemap
 * \param that display instance
 * \param yx_bytemap byte array, vertical bytes, lsb first (on top)
 * \param length must be 1024 bytes
 */
void oled_draw_yx_bytemap( OLED* that, const uint8_t* yx_bytemap, uint16_t length );

//----------------------------------------------------------------
// finishes

void oled_erase( OLED* that );
void oled_erase_line( OLED* that, uint8_t line );
void oled_erase_character( OLED* that, uint8_t line, uint8_t column );

//----------------------------------------------------------------

void oled_deinit( OLED*& that );

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
