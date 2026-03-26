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
#include "hardware/i2c.h"

#include "oled.h"

#include <cstdio>
#include <cstring>

//----------------------------------------------------------------

static oled_ref oled = nullptr;

//----------------------------------------------------------------

void OLEDKitInit( void* oled ) {
	if ( oled != nullptr ) return;

	::oled = (oled_ref)oled;
}

//----------------------------------------------------------------

void OLEDKitInit( uint8_t i2c_num ) {
	if ( oled != nullptr ) return;

	oled = new OLED( i2c_get_instance( i2c_num ), SSD1309_ADDRESS, 0 );
}

//----------------------------------------------------------------

void OLEDKitSendMessage( const char text[], uint8_t line, uint8_t column ) {
	if ( oled == nullptr ) return;

	oled->print( (const char*)text, line, column );
}

//----------------------------------------------------------------

void OLEDKitSendMessageINT( const char text[], int value, uint8_t line, uint8_t column ) {
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

void OLEDKitPrintImage( unsigned char image[] ) {
	if ( oled == nullptr ) return;

	oled->draw_bitmap( 0, 0, SSD1309_WIDTH, SSD1309_HEIGHT, image, SSD1309_WIDTH * SSD1309_HEIGHT / 8 );
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

void AfficherGlyph( unsigned char glyph[] ) {
	if ( oled == nullptr ) return;

	oled->print_glyph( glyph );
}

//----------------------------------------------------------------

void AfficheImage( unsigned char image[] ) {
	if ( oled == nullptr ) return;

	oled->draw_bitmap( 0, 0, SSD1309_WIDTH, SSD1309_HEIGHT, image, SSD1309_WIDTH * SSD1309_HEIGHT / 8 );
}

//----------------------------------------------------------------

void AfficherByte( uint8_t byte ) {
	if ( oled == nullptr ) return;

	i2c_ref wire = oled->get_i2c();
	uint8_t address = oled->get_address();
	i2c_write_bytes_blocking( wire, address, /*WRITE_DATA*/0x40, byte );
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

void AfficherChaineAZT( const char texte[] ) {
	if ( oled == nullptr ) return;

	oled->print( (const char*)texte );
}

//----------------------------------------------------------------

void AfficherChaineAZTCentreLi( const char texte[], uint8_t ligne ) {
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
