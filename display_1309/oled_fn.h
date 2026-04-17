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

uint16_t oled_get_width( const OLED* oled );
uint16_t oled_get_height( const OLED* oled );

uint16_t oled_get_column_count( const OLED* oled );
uint16_t oled_get_line_count( const OLED* oled );

void oled_set_on( OLED* oled, bool on );
void oled_set_orientation( OLED* oled, uint8_t orientation );
void oled_set_dark_mode( OLED* oled, bool mode );
void oled_set_brightness( OLED* oled, uint8_t brightness );
void oled_set_brightness_db( OLED* oled, float brightness_db );

void oled_set_lico( OLED* oled, uint8_t line, uint8_t column );

void oled_print( OLED* oled, const char* text );
void oled_print( OLED* oled, const char* text, uint8_t line, uint8_t column );
void oled_print_left( OLED* oled, const char* text, uint8_t line );
void oled_print_center( OLED* oled, const char* text, uint8_t line );
void oled_print_right( OLED* oled, const char* text, uint8_t line );

void oled_printf( OLED* oled, const char* format, ... );

void oled_print( OLED* oled, char character );
void oled_print( OLED* oled, char character, uint8_t line, uint8_t column );

void oled_print_glyph( OLED* oled, const uint8_t glyph[6] );

/**
 * oled_draw_yx_bytemap
 * \param oled display instance
 * \param yx_bytemap byte array, vertical, lsb first
 * \param length must be 1024 bytes
 */
void oled_draw_yx_bytemap( OLED* oled, const uint8_t* yx_bytemap, uint16_t length );

void oled_erase( OLED* oled );
void oled_erase_line( OLED* oled, uint8_t line );
void oled_erase_character( OLED* oled, uint8_t line, uint8_t column );

//----------------------------------------------------------------

void oled_deinit( OLED*& oled );

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
