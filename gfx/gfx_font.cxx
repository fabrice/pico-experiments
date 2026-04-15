//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
// CFPT Électronique
//
// gfx_font
//
//----------------------------------------------------------------

#include "gfx_font.h"

#include "gfx_glyph.h"

//----------------------------------------------------------------

gfx_font::gfx_font():
	v_reference_count { true } {
}

//----------------------------------------------------------------

gfx_font::gfx_font( gfx_dxy_t y_advance ):
	v_reference_count { true },
	_x_advance { 0 },
	_y_advance { y_advance } {
}

//----------------------------------------------------------------

gfx_font::gfx_font( const gfx_font_data& font_data ):
	v_reference_count { true },
	_x_advance { font_data.x_advance },
	_y_advance { font_data.y_advance } {
	for ( const auto& [ key, data ] : font_data.glyphs ) {
		_glyphs[ key ] = gfx_glyph( data );
	}
}

//----------------------------------------------------------------

gfx_font::~gfx_font() {
	_glyphs.clear();
}

//----------------------------------------------------------------

void gfx_font::set_x_advance_from_glyphs() {
	if ( _glyphs.size() > 0 ) {
		bool equal = true;
		gfx_dxy_t x_advance = _glyphs.begin()->second.get_x_advance();
		for ( const auto& [ character, glyph ] : _glyphs ) {
			if ( glyph.get_x_advance() != x_advance ) {
				equal = false;
				break;
			}
		}
		_x_advance = equal ? x_advance : 0;
	}
	else {
		_x_advance = 0;
	}
}

//----------------------------------------------------------------

gfx_wh_t gfx_font::get_text_width( std::string text ) const {
	gfx_wh_t width = 0;
	for ( const auto character : text ) {
		if ( this->has_glyph( character ) ) {
			const gfx_glyph& glyph = _glyphs.at( character );
			width += glyph.get_x_advance();
		}
	}

	return width;
}

//----------------------------------------------------------------

gfx_font_ptr gfx_font::make_gfx_font_from_glyphmap( const uint8_t* glyphmap, uint8_t first_glyph, uint8_t last_glyph, gfx_xy_t width, gfx_xy_t height, bool lsb_first, bool invert ) {
	if ( glyphmap == nullptr ) return nullptr;

	size_t bit_count = width * height;
	size_t byte_count = (bit_count + 7) / 8; 

	gfx_font_ptr font = new gfx_font();
	font->_y_advance = 8;

	for ( uint character = first_glyph ; character <= last_glyph ; ++ character ) {
		uint index = character - first_glyph;
		const uint8_t* glyph_bitmap = &glyphmap[ index * byte_count ];
		gfx_glyph glyph = gfx_glyph( (char)character, 0, 0, width, height, width );
		glyph.set_bitmap_yx( glyph_bitmap, byte_count, lsb_first, invert );
		//glyph.minimize();
		font->set_glyph( glyph );
	}

	font->set_x_advance_from_glyphs();

	return font;
}

//----------------------------------------------------------------

gfx_font_ptr gfx_font::make_gfx_font_from_arduino( const arduino_gfx_font_data* arduinofont ) {
	if ( arduinofont == nullptr ) return nullptr;

	gfx_font_ptr font = new gfx_font( arduinofont->width + 1 );

	for ( uint16_t character = 0 ; character <= 254 ; ++ character ) {
		const uint8_t* bitmap = arduinofont->data[ character ];
		if ( bitmap == nullptr ) continue;

		gfx_glyph glyph = gfx_glyph( character, 0, 0, arduinofont->width, arduinofont->height, arduinofont->width + 1 );
		for ( gfx_xy_t y = 0 ; y < glyph.get_height() ; ++ y ) {
			uint8_t byte = bitmap[ y ];
			for ( gfx_xy_t x = 0 ; x < glyph.get_width() ; ++ x ) {
				bool lit = byte & (0x80 >> x);
				glyph.set_pixel_lit( x, y, lit );
			}
		}
		//glyph.minimize();
		font->set_glyph( character, glyph );
	}

	font->set_x_advance_from_glyphs();

	return font;
}

//----------------------------------------------------------------

gfx_font_ptr gfx_font::make_gfx_font_from_adafruit( const adafruit_gfx_font_data* adafont ) {
	if ( adafont == nullptr ) return nullptr;

	gfx_font_ptr font = new gfx_font( adafont->yAdvance );

	for ( uint16_t character = adafont->first ; character <= adafont->last ; ++ character ) {
		const adafruit_gfx_glyph_data* adaglyph = &adafont->glyph[ character - adafont->first ];
		const uint8_t* bitmap = &adafont->bitmap[ adaglyph->bitmapOffset ];

		gfx_glyph glyph = gfx_glyph( character, adaglyph->xOffset, (int16_t)adafont->yAdvance + (int16_t)adaglyph->yOffset, adaglyph->width, adaglyph->height, adaglyph->xAdvance );
		glyph.set_bitmap_xy( bitmap, 0 );
		//glyph.minimize();
		font->set_glyph( character, glyph );
	}

	font->set_x_advance_from_glyphs();

	return font;
}

//----------------------------------------------------------------

void gfx_font::print_gfx_font_files( gfx_font_ptr font, const char* font_name ) {
	if ( font == nullptr ) return;

	printf( "//----------------------------------------------------------------\n\n" );
	printf( "// gfx_font : %s\n\n", font_name );
	printf( "//----------------------------------------------------------------\n\n" );
	printf( "#pragma once\n\n" );
	printf( "//----------------------------------------------------------------\n\n" );
	printf( "#include \"gfx_font_data.h\"\n\n" );
	printf( "//----------------------------------------------------------------\n\n" );

	printf( "// %s_font_data.h\n", font_name );
	printf( "extern const gfx_font_data %s_font_data;\n\n", font_name );

	printf( "//----------------------------------------------------------------\n\n" );

	printf( "// %s_font_data.cpp\n", font_name );
	printf( "const gfx_font_data %s_font_data {\n", font_name );
	printf( ".x_advance = %d,\n", (int)font->get_x_advance() );
	printf( ".y_advance = %d,\n", (int)font->get_y_advance() );
	printf( ".glyphs = {\n" );

	printf( "//           +-- character\n" );
	printf( "//           |     +-- left\n" );
	printf( "//           |     |     +-- top\n" );
	printf( "//           |     |     |     +-- width\n" );
	printf( "//           |     |     |     |     +-- height\n" );
	printf( "//           |     |     |     |     |     +-- x_advance\n" );
	printf( "//           |     |     |     |     |     |\n" );
	uint bitmap_offset = 0;
	for ( const auto& [ character, glyph ] : font->get_glyph_map() ) {

		printf( "{ 0x%02x , { %3u , %3u , %3u , %3u , %3u , %3u ,", (uint) character, (uint) character, (uint) glyph.get_left(), (uint) glyph.get_top(), (uint) glyph.get_width(), (uint) glyph.get_height(), (uint) glyph.get_x_advance() );

		size_t bit_count = glyph.get_dimension().get_area();
		size_t byte_count = (bit_count + 7) / 8;
		if ( bit_count > 0 ) {
			size_t bit_index = 0;
			uint8_t hex = 0;
			printf( " {" );
			for ( uint y = 0 ; y < glyph.get_height() ; ++ y ) {
				for ( uint x = 0 ; x < glyph.get_width() ; ++ x ) {
					if ( bit_index % 8 == 0 ) hex = 0;
					bool lit = glyph.get_pixel_lit( x, y );
					hex = (hex << 1) | lit;
					if ( bit_index % 8 == 7 ) printf( " 0x%02x ,", hex );
					++ bit_index;
				}
			}
			while ( bit_index % 8 > 0 ) {
				hex = hex << 1;
				if ( bit_index % 8 == 7 ) printf( " 0x%02x", hex );
				++ bit_index;
			}
			printf( " }" );
		}
		else {
			printf( " { 0 }" );
		}
		printf( " } },\n" );

		bitmap_offset += bit_count > 0 ? byte_count : 1;
	}
	printf( "}\n" );
	printf( "};\n\n" );

	printf( "//----------------------------------------------------------------\n" );
}

//----------------------------------------------------------------

void gfx_font::print_gfx_font_array( gfx_font_ptr font, const char* font_name ) {
	printf( "const uint8_t %s_font_data[][5] {\n", font_name );

	for ( const auto& [ character, glyph ] : font->get_glyph_map() ) {
		printf( "\t{ " );
		for ( gfx_xy_t x = 0 ; x < std::min( glyph.get_width(), (gfx_wh_t)5 ) ; ++ x ) {
			uint8_t byte = 0;
			for ( gfx_xy_t y = 0 ; y < std::min( glyph.get_height(), (gfx_wh_t)8 ) ; ++ y ) {
				bool lit = glyph.get_pixel_lit( x, y );
				if ( lit ) byte |= (0x01 << y);
			}
			printf( "0x%02x , ", (uint) byte );
		}
		printf( " }, // %3u\n", (uint) character );
	}
	printf( "};\n" );
}

//----------------------------------------------------------------

void gfx_font::print_gfx_font_asciiart( gfx_font_ptr font, const char* font_name ) {
	uint bit_count = 0;
	for ( const auto& [ character, glyph ] : font->get_glyph_map() ) {
		bit_count += glyph.get_dimension().get_area();
		printf( "[ '%c' 0x%x %d ]\n", (char) character, (uint) character, (int) glyph.get_dimension().get_area() );

		for ( uint y = 0 ; y < glyph.get_height() ; ++ y ) {
			for ( uint x = 0 ; x < glyph.get_width() ; ++ x ) {
				bool lit = glyph.get_pixel_lit( x, y );
				printf( "%c", (char) lit ? '#' : ' ' );
			}
			printf( "\n" );
		}
		printf( "\n" );
	}
	printf( "font : nchar %d nbits %d \n", (int)font->get_glyph_map().size(), (int) bit_count );

	printf( "\n" );
}

//----------------------------------------------------------------
