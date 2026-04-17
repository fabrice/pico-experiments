//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_font
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico/stdlib.h"

#include "gfx_types.h"
#include "gfx_geometry.h"
#include "gfx_glyph.h"

#include "math_plus.h"
#include "v_reference_count.h"

#include "fonts/gfx_font_data.h"

#include "third/arduino_font_data.h"
#include "third/adafruit_font_data.h"
#include "third/FreeMono_12pt_7b.h"

#include <vector> // https://cppreference.com/w/cpp/container/vector.html
#include <map> // https://cppreference.com/w/cpp/container/map.html

//----------------------------------------------------------------

using gfx_font_glyph_map = std::map< char, gfx_glyph >;

//----------------------------------------------------------------

class gfx_font : public virtual v_reference_count {

public:

	gfx_dxy_t _x_advance { 0 };
	gfx_dxy_t _y_advance { 0 };
	gfx_font_glyph_map _glyphs {};

public:

	[[nodiscard]]
	static gfx_font* make_gfx_font_from_glyphmap( const uint8_t* glyphmap, uint8_t first_glyph, uint8_t last_glyph, gfx_xy_t width, gfx_xy_t height, bool lsb_first = true, bool invert = false );

	[[nodiscard]]
	static gfx_font* make_gfx_font_from_arduino( const arduino_gfx_font_data* arduinofont );

	[[nodiscard]]
	static gfx_font* make_gfx_font_from_adafruit( const adafruit_gfx_font_data* adafont );

	static void print_gfx_font_files( const gfx_font* font, const char* font_name );
	static void print_gfx_font_array( const gfx_font* font, const char* font_name, bool lsb_first = true, bool invert = false );
	static void print_gfx_font_asciiart( const gfx_font* font, const char* font_name );

	gfx_font();
	gfx_font( gfx_dxy_t y_advance );
	gfx_font( const gfx_font_data& font_data );

	virtual ~gfx_font() override;

	inline gfx_dxy_t get_x_advance() const { return _x_advance; }
	void set_x_advance_from_glyphs();
	inline gfx_dxy_t get_y_advance() const { return _y_advance; }

	inline const gfx_font_glyph_map& get_glyph_map() const { return _glyphs; }

	bool has_glyph( char character ) const {
		return _glyphs.contains( character );
	}

	gfx_glyph get_glyph( char character ) const {
		if ( _glyphs.contains( character ) ) {
			return _glyphs.at( character );
		}
		else {
			return gfx_glyph();
		}
	}

	void set_glyph( gfx_glyph& glyph ) {
		_glyphs[ glyph.get_character() ] = glyph;
	}

	void set_glyph( char character, gfx_glyph& glyph ) {
		_glyphs[ character ] = glyph;
	}

	gfx_wh_t get_text_width( std::string text ) const;

};

//----------------------------------------------------------------
