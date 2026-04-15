//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// API de compatibilité avec l'OLEDKit 8051
//
//----------------------------------------------------------------

#pragma once
#ifndef _OLED_OLEDKit_FN_H
#define _OLED_OLEDKit_FN_H

//----------------------------------------------------------------

#include "pico/stdlib.h"

//----------------------------------------------------------------

void OLEDKitInit( void* oled );
[[deprecated]] void OLEDKitInit( uint8_t i2c_num, uint reset_gpio = 0 );

//----------------------------------------------------------------

void OLEDKitSendMessage( const char* text, uint8_t line, uint8_t column );
void OLEDKitSendMessageINT( const char* text, int value, uint8_t line, uint8_t column );
void OLEDKitSendINT( int value, uint8_t line, uint8_t column );

void OLEDKitPrintInfo();
void OLEDKitPrintImage( const uint8_t* image );

void OLEDDisplayFlip( uint8_t flip );
void OLEDSetBrightness( uint8_t brightness );
void OLEDLibDelay1ms( uint32_t time );

void AfficherCaractere( char caractere );
void AfficherGlyph( const uint8_t glyph[6] );
void AfficheImage( const uint8_t* image );
void AfficherByte( uint8_t byte );

void SelectPosLiCo( uint8_t line, uint8_t column );
void SelectPosCaractLiCo( uint8_t line, uint8_t column );

void AfficherChaineAZT( const char* texte );
void AfficherChaineAZTCentreLi( const char* texte, uint8_t ligne );

void EffacerEcran();

//----------------------------------------------------------------

void OLEDKitDeinit();

//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
