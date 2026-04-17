//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// buzzer
//
//----------------------------------------------------------------

#include "buzzer.h"

#include "buzzer_melody_data.h"

#include "pwm.h"

//----------------------------------------------------------------

buzzer::buzzer( uint gpio ):
	_pwm { new pwm( gpio ) } {
}

//----------------------------------------------------------------

buzzer::buzzer( pwm* pwm ):
	_pwm { pwm } {
}

//----------------------------------------------------------------

buzzer::~buzzer() {
	if ( _pwm != nullptr ) {
		_pwm->set_enabled( false, false );
		delete _pwm;
		_pwm = nullptr;
	}
}

//----------------------------------------------------------------

float buzzer::get_frequency() const {
	if ( _pwm == nullptr ) return 0.0f;

	return _pwm->get_frequency();
}

//----------------------------------------------------------------

void buzzer::set_frequency( float frequency ) {
	if ( _pwm == nullptr ) return;

	_pwm->set_frequency( frequency );
	_pwm->set_duty( 0.5f );
}

//----------------------------------------------------------------

void buzzer::set_enabled( bool enabled ) {
	if ( _pwm == nullptr ) return;

	_pwm->set_enabled( enabled, false );
}

//----------------------------------------------------------------

void buzzer::play_note( float frequency, uint16_t play_ms, uint16_t pause_ms ) {
	this->set_frequency( frequency );
	this->set_enabled( true );
	sleep_ms( play_ms );
	this->set_enabled( false );
	if ( pause_ms > 0 ) sleep_ms( pause_ms );
}

//----------------------------------------------------------------

void buzzer::play_melody( const buzzer_melody_data melody ) {
	for ( auto note : melody ) {
		this->play_note( note.frequency, note.play_ms, note.pause_ms );
	}
}
