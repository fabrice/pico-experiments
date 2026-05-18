//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// API de compatibilité avec l'OLEDKit 8051
//
//----------------------------------------------------------------

#include "oled_oledkit_fn.h"

#include "wire_i2c.h"

#include "oled.h"

#include <cstdio>
#include <cstring>

//----------------------------------------------------------------

namespace local {

OLED* oled = nullptr;

}

//----------------------------------------------------------------

void OLEDKitInit( void* oled ) {
	if ( local::oled != nullptr ) return;

	local::oled = static_cast< OLED* >( oled );
}

//----------------------------------------------------------------

void OLEDKitInit( uint8_t i2c_num, uint reset_gpio ) {
	if ( local::oled != nullptr ) return;

	local::oled = OLED::make( i2c_num, reset_gpio );
}

//----------------------------------------------------------------

void OLEDKitPrintInfo() {
	if ( local::oled == nullptr ) return;

	EffacerEcran();
	AfficherChaineAZTCentreLi( "OLEDKit_compat", 1 );
	OLEDKitSendMessageINT( "version ", 100, 7, 3 );
}

//----------------------------------------------------------------

void OLEDDisplayFlip( uint8_t flip ) {
	if ( local::oled == nullptr ) return;

	local::oled->set_orientation( !!flip );
}

//----------------------------------------------------------------

void OLEDSetBrightness( uint8_t brightness ) {
	if ( local::oled == nullptr ) return;

	local::oled->set_brightness( brightness );
}

//----------------------------------------------------------------

void OLEDLibDelay1ms( uint32_t time ) {
	if ( local::oled == nullptr ) return;

	sleep_ms( time );
}

//----------------------------------------------------------------

void SelectPosLiCo( uint8_t line, uint8_t column ) {
	if ( local::oled == nullptr ) return;

	local::oled->set_cursor( line, column );
}

//----------------------------------------------------------------

void SelectPosCaractLiCo( uint8_t line, uint8_t column ) {
	if ( local::oled == nullptr ) return;

	local::oled->set_cursor( line, column );
}

//----------------------------------------------------------------

void OLEDKitSendMessage( const char* text, uint8_t line, uint8_t column ) {
	if ( local::oled == nullptr ) return;

	local::oled->print( text, line, column );
}

//----------------------------------------------------------------

void OLEDKitSendMessageINT( const char* text, int value, uint8_t line, uint8_t column ) {
	if ( local::oled == nullptr ) return;

	local::oled->set_cursor( line, column );
	local::oled->printf( "%s:%+6d", text, value );
}

//----------------------------------------------------------------

void OLEDKitSendINT( int value, uint8_t line, uint8_t column ) {
	if ( local::oled == nullptr ) return;

	local::oled->set_cursor( line, column );
	local::oled->printf( "%+6d", value );
}

//----------------------------------------------------------------

void AfficherChaineAZT( const char* texte ) {
	if ( local::oled == nullptr ) return;

	local::oled->print( texte );
}

//----------------------------------------------------------------

void AfficherChaineAZTCentreLi( const char* texte, uint8_t ligne ) {
	if ( local::oled == nullptr ) return;

	local::oled->print_center( texte, ligne );
}

//----------------------------------------------------------------

void AfficherCaractere( char caractere ) {
	if ( local::oled == nullptr ) return;

	local::oled->print( caractere );
}

//----------------------------------------------------------------

void AfficherGlyph( const uint8_t glyph[6] ) {
	if ( local::oled == nullptr ) return;

	local::oled->print_glyph( glyph );
}

//----------------------------------------------------------------

void OLEDKitPrintImage( const uint8_t* image ) {
	if ( local::oled == nullptr ) return;

	local::oled->draw_yx_bytemap( image, SSD1309_WIDTH * SSD1309_HEIGHT / 8 );
}

//----------------------------------------------------------------

void AfficheImage( const uint8_t* image ) {
	if ( local::oled == nullptr ) return;

	local::oled->draw_yx_bytemap( image, SSD1309_WIDTH * SSD1309_HEIGHT / 8 );
}

//----------------------------------------------------------------

void AfficherByte( uint8_t byte ) {
	if ( local::oled == nullptr ) return;

	local::oled->get_wire()->write_bytes( /*WRITE_DATA*/0x40, byte );
}

//----------------------------------------------------------------

void EffacerEcran() {
	if ( local::oled == nullptr ) return;

	local::oled->erase();
}

//----------------------------------------------------------------

void OLEDKitDeinit() {
	if ( local::oled == nullptr ) return;

	delete local::oled;
	local::oled = nullptr;
}

//----------------------------------------------------------------
