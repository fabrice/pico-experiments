//----------------------------------------------------------------

// loosely based on Arduino String
// https://github.com/arduino/ArduinoCore-API/blob/master/api/String.h

//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include <cstdint>
#include <string>

//----------------------------------------------------------------

class String {

private:

	std::string _string;

public:

	String() = default;

	String( const String& text ): _string { text._string } {}
	String( const String& text, size_t length ): _string { text._string, length } {}

	String( String&& text ): _string { text._string } { text._string.clear(); }

	String( const std::string& text ): _string { text } {}
	String( std::string&& text ): _string { text } { text.clear(); }

	String( const char* text ): _string { text } {}
	String( const char* text, size_t length ): _string { text, length } {}

	explicit String( char character ): _string { character } {}
	explicit String( int value, uint8_t base = 10 );
	explicit String( unsigned int value, uint8_t base = 10 );
	explicit String( float value, uint8_t decimals = 3 );

	~String() = default;

	size_t get_length() const { return _string.length(); }
	size_t length() const { return _string.length(); }

	size_t get_capacity() const { return _string.capacity(); }
	size_t capacity() const { return _string.capacity(); }

	bool is_empty() const { return _string.empty(); }
	bool empty() const { return _string.empty(); }

	String& operator=( const String& rhs ) { _string = rhs._string; return (*this); }
	String& operator=( String&& rhs ) { _string = rhs._string; rhs._string.clear(); return (*this); }
	String& operator=( const char* rhs ) { _string = rhs; return (*this); }

	String& operator+=( const String& rhs ) { _string += rhs._string; return (*this); }
	String& operator+=( String&& rhs ) { _string += rhs._string; rhs._string.clear(); return (*this); }
	String& operator+=( const char* rhs ) { _string += rhs; return (*this); }

	friend String operator+( const String& lhs, const String& rhs ) { return String( lhs._string + rhs._string ); }
	friend String operator+( const String& lhs, const char* rhs ) { String text( lhs ); text += rhs; return text; }

	friend std::strong_ordering operator<=>( String& lhs, String& rhs ) { return lhs._string <=> rhs._string; }
	friend std::strong_ordering operator<=>( String& lhs, const char* rhs ) { return lhs._string <=> rhs; }
	friend std::strong_ordering operator<=>( const char* lhs, String& rhs ) { return lhs <=> rhs._string; }

	friend bool operator==( String& lhs, String& rhs ) { return (lhs <=> rhs) == 0; }
	friend bool operator==( String& lhs, const char* rhs ) { return (lhs <=> rhs) == 0; }
	friend bool operator==( const char* lhs, String& rhs ) { return (lhs <=> rhs) == 0; }

	friend bool operator<=( String& lhs, String& rhs ) { return (lhs <=> rhs) <= 0; }
	friend bool operator<=( String& lhs, const char* rhs ) { return (lhs <=> rhs) <= 0; }
	friend bool operator<=( const char* lhs, String& rhs ) { return (lhs <=> rhs) <= 0; }

	friend bool operator>=( String& lhs, String& rhs ) { return (lhs <=> rhs) >= 0; }
	friend bool operator>=( String& lhs, const char* rhs ) { return (lhs <=> rhs) >= 0; }
	friend bool operator>=( const char* lhs, String& rhs ) { return (lhs <=> rhs) >= 0; }

	friend bool operator<( String& lhs, String& rhs ) { return (lhs <=> rhs) < 0; }
	friend bool operator<( String& lhs, const char* rhs ) { return (lhs <=> rhs) < 0; }
	friend bool operator<( const char* lhs, String& rhs ) { return (lhs <=> rhs) < 0; }

	friend bool operator>( String& lhs, String& rhs ) { return (lhs <=> rhs) > 0; }
	friend bool operator>( String& lhs, const char* rhs ) { return (lhs <=> rhs) > 0; }
	friend bool operator>( const char* lhs, String& rhs ) { return (lhs <=> rhs) > 0; }

	char operator[]( size_t index ) const { return _string[ index ]; }
	char& operator[]( size_t index ) { return _string[ index ]; }

	const char* c_str() const { return _string.c_str(); }

};

//----------------------------------------------------------------
