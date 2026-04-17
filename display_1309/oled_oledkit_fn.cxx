//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// API de compatibilité avec l'OLEDKit 8051
//
//----------------------------------------------------------------

#include "oled_oledkit_fn.h"

#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "wire_i2c.h"

#include "oled.h"

#include <cstdio>
#include <cstring>

//----------------------------------------------------------------

static OLED* oled = nullptr;

//----------------------------------------------------------------

void OLEDKitInit( void* oled ) {
	if ( oled != nullptr ) return;

	::oled = (OLED*)oled;
}

//----------------------------------------------------------------

void OLEDKitInit( uint8_t i2c_num, uint reset_gpio ) {
	if ( oled != nullptr ) return;

	oled = OLED::make( i2c_num, reset_gpio );
}

//----------------------------------------------------------------

void OLEDKitSendMessage( const char* text, uint8_t line, uint8_t column ) {
	if ( oled == nullptr ) return;

	oled->print( text, line, column );
}

//----------------------------------------------------------------

void OLEDKitSendMessageINT( const char* text, int value, uint8_t line, uint8_t column ) {
	if ( oled == nullptr ) return;

	oled->set_lico( line, column );
	oled->printf( "%s:%+6d", text, value );
}

//----------------------------------------------------------------

void OLEDKitSendINT( int value, uint8_t line, uint8_t column ) {
	if ( oled == nullptr ) return;

	oled->set_lico( line, column );
	oled->printf( "%+6d", value );
}

//----------------------------------------------------------------

void OLEDKitPrintInfo() {
	if ( oled == nullptr ) return;

	EffacerEcran();
	AfficherChaineAZTCentreLi( "OLEDKit_compat", 1 );
	OLEDKitSendMessageINT( "version ", 100, 7, 3 );
}

//----------------------------------------------------------------

void OLEDKitPrintImage( const uint8_t* image ) {
	if ( oled == nullptr ) return;

	oled->draw_yx_bytemap( image, SSD1309_WIDTH * SSD1309_HEIGHT / 8 );
}

//----------------------------------------------------------------

void OLEDDisplayFlip( uint8_t flip ) {
	if ( oled == nullptr ) return;

	oled->set_orientation( !!flip );
}

//----------------------------------------------------------------

void OLEDSetBrightness( uint8_t brightness ) {
	if ( oled == nullptr ) return;

	oled->set_brightness( brightness );
}

//----------------------------------------------------------------

void OLEDLibDelay1ms( uint32_t time ) {
	if ( oled == nullptr ) return;

	sleep_ms( time );
}

//----------------------------------------------------------------

void AfficherCaractere( char caractere ) {
	if ( oled == nullptr ) return;

	oled->print( caractere );
}

//----------------------------------------------------------------

void AfficherGlyph( const uint8_t glyph[6] ) {
	if ( oled == nullptr ) return;

	oled->print_glyph( glyph );
}

//----------------------------------------------------------------

void AfficheImage( const uint8_t* image ) {
	if ( oled == nullptr ) return;

	oled->draw_yx_bytemap( image, SSD1309_WIDTH * SSD1309_HEIGHT / 8 );
}

//----------------------------------------------------------------

void AfficherByte( uint8_t byte ) {
	if ( oled == nullptr ) return;

	oled->get_wire()->write_bytes( /*WRITE_DATA*/0x40, byte );
}

//----------------------------------------------------------------

void SelectPosLiCo( uint8_t line, uint8_t column ) {
	if ( oled == nullptr ) return;

	oled->set_lico( line, column );
}

//----------------------------------------------------------------

void SelectPosCaractLiCo( uint8_t line, uint8_t column ) {
	if ( oled == nullptr ) return;

	oled->set_lico( line, column );
}

//----------------------------------------------------------------

void AfficherChaineAZT( const char* texte ) {
	if ( oled == nullptr ) return;

	oled->print( texte );
}

//----------------------------------------------------------------

void AfficherChaineAZTCentreLi( const char* texte, uint8_t ligne ) {
	if ( oled == nullptr ) return;

	oled->print_center( texte, ligne );
}

//----------------------------------------------------------------

void EffacerEcran() {
	if ( oled == nullptr ) return;

	oled->erase();
}

//----------------------------------------------------------------

void OLEDKitDeinit() {
	if ( oled == nullptr ) return;

	delete oled;
	oled = nullptr;
}

//----------------------------------------------------------------
