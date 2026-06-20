//----------------------------------------------------------------

// loosely based on Arduino String
// https://github.com/arduino/ArduinoCore-API/blob/master/api/String.h

//----------------------------------------------------------------

#include "string_plus.h"

//----------------------------------------------------------------

String::String( int value, uint8_t base ) {
	const size_t text_length = 32;
	char text[ text_length ] { 0 };
	switch ( base ) {
	case 2: {
		snprintf( text, text_length, "%b", (unsigned int)value );
		_string = text;
		break;
	}
	case 8: {
		snprintf( text, text_length, "%o", (unsigned int)value );
		_string = text;
		break;
	}
	case 16: {
		snprintf( text, text_length, "%x", (unsigned int)value );
		_string = text;
		break;
	}
	default: {
		snprintf( text, text_length, "%d", value );
		_string = text;
		break;
	}
	}
}

//----------------------------------------------------------------

String::String( unsigned int value, uint8_t base ) {
	const size_t text_length = 32;
	char text[ text_length ] { 0 };
	switch ( base ) {
	case 2: {
		snprintf( text, text_length, "%b", value );
		_string = text;
		break;
	}
	case 8: {
		snprintf( text, text_length, "%o", value );
		_string = text;
		break;
	}
	case 16: {
		snprintf( text, text_length, "%x", value );
		_string = text;
		break;
	}
	default: {
		snprintf( text, text_length, "%u", value );
		_string = text;
		break;
	}
	}
}

//----------------------------------------------------------------

String::String( float value, uint8_t decimals ) {
	const size_t format_length = 32;
	const size_t text_length = 32;

	char format[ format_length ] { 0 };
	char text[ text_length ] { 0 };
	
	snprintf( format, format_length, "%%.%uf", (unsigned int)decimals );
	snprintf( text, text_length, format, value );

	_string = text;
}

//----------------------------------------------------------------
