//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// experiments
//
//----------------------------------------------------------------

#include "pico/stdlib.h"
#include "pico/printf.h"

#include "pwm.h"
#include "wire_spi.h"
#include "oled.h"
#include "oled_fn.h"
#include "rotary_encoder.h"
#include "display_7735.h"
#include "mcp23008.h"
#include "memory_24lc02b.h"

#include "hardware/i2c.h"
#include "hardware/clocks.h"

#include "std_plus.h"
#include "math_plus.h"

#include <cstring>

#include "gfx.h"
#include "gfx/fonts/cfpt_mono_6x8.h"
#include "gfx/img/cfpt_128_160.h"
#include "gfx/third/arduino_font_5x7.c"
#include "gfx/third/FreeMono9pt7b.h"
#include "gfx/third/FreeSans9pt7b.h"

//----------------------------------------------------------------

// UART

constexpr uint UART_TX_GPIO { 12 };
constexpr uint UART_RX_GPIO { 13 };

// OLED

constexpr uint I2C0_SDA_GPIO { 4 };
constexpr uint I2C0_SCL_GPIO { 5 };

constexpr uint OLED_RESET_GPIO { 7 };

// TFT ST7735

constexpr uint SPI0_SCLK_GPIO { 18 };
constexpr uint SPI0_MISO_GPIO { 16 };
constexpr uint SPI0_MOSI_GPIO { 19 };

constexpr uint ST7735_CS_GPIO { 17 };
constexpr uint ST7735_RESET_GPIO { 6 };
constexpr uint ST7735_DC_GPIO { 3 };
constexpr uint ST7735_BACKLIGHT_GPIO { 2 };

//----------------------------------------------------------------

/*
 -----------------------------       -----------------------
|  .  |  .  |  .  |  .  |  .  |     |  .  |  .  |  .  |  .  |
|  0  |  2  |  4  | SDA | VCC |     | VCC | SDA | SCL | GND |
|  .  |  .  |  .  |  .  |  .  |      -----------------------
| GND |  1  |  3  | RST | SCL |
 -----------------------------
|
| display
*/

/*

Pico :
4 : SDA
5 : SCL
7 : RST

*/


//----------------------------------------------------------------

void io_init() {
    stdio_init_all();

	// UART0

	gpio_init( UART_TX_GPIO );
	gpio_set_function( UART_TX_GPIO, GPIO_FUNC_UART );

	gpio_init( UART_RX_GPIO );
	gpio_set_function( UART_RX_GPIO, GPIO_FUNC_UART );

	// OLED

	gpio_init( OLED_RESET_GPIO );
    gpio_set_dir( OLED_RESET_GPIO, GPIO_OUT );
    gpio_put( OLED_RESET_GPIO, true );

	// TFT ST7735

    gpio_init( ST7735_BACKLIGHT_GPIO );
    gpio_set_dir( ST7735_BACKLIGHT_GPIO, GPIO_OUT );
    gpio_put( ST7735_BACKLIGHT_GPIO, false );

    gpio_init( ST7735_RESET_GPIO );
    gpio_set_dir( ST7735_RESET_GPIO, GPIO_OUT );
    gpio_put( ST7735_RESET_GPIO, false );
}

//----------------------------------------------------------------

#define ENABLE_OLED_1309 0
#define ENABLE_TFT_7735 1
#define ENABLE_TFT_7735_DELETION 1
#define ENABLE_EXPANDER_MCP23008 0

//----------------------------------------------------------------

int main() {
	//set_sys_clock_48mhz();
	io_init();

	//--------------------
	// oled
	auto display_wire_i2c = new wire_i2c( 0, SSD1309_ADDRESS );
	display_wire_i2c->io_init( I2C0_SDA_GPIO, I2C0_SCL_GPIO, 1.5e6 );
	oled_ptr display_oled { nullptr };
	if ( ENABLE_OLED_1309 ) display_oled = new OLED( display_wire_i2c, OLED_RESET_GPIO );
	if ( is_not_null( display_oled ) ) display_oled->draw_logo();

	//--------------------
	// display_7735
	auto display_wire_spi = new wire_spi( 0, ST7735_CS_GPIO );
	display_wire_spi->io_init( SPI0_SCLK_GPIO, SPI0_MISO_GPIO, SPI0_MOSI_GPIO, 8e6 );
	display_7735_ptr display_tft { nullptr };
	if ( ENABLE_TFT_7735 ) display_tft = new display_7735( display_wire_spi, ST7735_RESET_GPIO, ST7735_DC_GPIO, ST7735_BACKLIGHT_GPIO );
	if ( is_not_null( display_tft ) ) display_tft->set_foreground_color( 28, 186, 111 );
	if ( is_not_null( display_tft ) ) display_tft->set_background_color( 0, 0, 0 );
	if ( is_not_null( display_tft ) ) display_tft->draw_bitmap( 0, 0, 128, 160, cfpt_logo_128_160, sizeof( cfpt_logo_128_160 ) );

	sleep_ms( 2500 );

	if ( is_not_null( display_oled )  ) display_oled->erase();
	if ( is_not_null( display_tft ) ) display_tft->erase();

	sleep_ms( 250 );

	if ( is_not_null( display_oled ) ) display_oled->print_aligned( "Hello OLED", 1, '^' );
	if ( is_not_null( display_tft ) ) display_tft->fill_screen( (31 << 11) | ( 0 << 5) | ( 0 << 0) );
	sleep_ms( 250 );
	if ( is_not_null( display_tft ) ) display_tft->fill_screen( ( 0 << 11) | (63 << 5) | ( 0 << 0) );
	sleep_ms( 250 );
	if ( is_not_null( display_tft ) ) display_tft->fill_screen( ( 0 << 11) | ( 0 << 5) | (31 << 0) );
	sleep_ms( 250 );
	if ( is_not_null( display_oled ) ) display_oled->print( '0', 0, 20 );
	if ( is_not_null( display_oled ) ) display_oled->print( '1', 1, 20 );
	if ( is_not_null( display_oled ) ) display_oled->print( '2', 2, 20 );
	if ( is_not_null( display_oled ) ) display_oled->print( '3', 3, 20 );
	if ( is_not_null( display_oled ) ) display_oled->print( '4', 4, 20 );
	if ( is_not_null( display_oled ) ) display_oled->print( '5', 5, 20 );
	if ( is_not_null( display_oled ) ) display_oled->print( '6', 6, 20 );
	if ( is_not_null( display_oled ) ) display_oled->print( "012345678901234567890", 7, 0 );

	if ( is_not_null( display_tft ) ) display_tft->fill_screen( 0, 0, 0 );
	if ( is_not_null( display_tft ) ) display_tft->set_foreground_color( 255, 255, 255 );
	if ( is_not_null( display_tft ) ) display_tft->set_background_color( 0, 0, 0 );
	if ( is_not_null( display_tft ) ) display_tft->set_lico( 4, 0 );
	if ( is_not_null( display_tft ) ) display_tft->print_center( 4, "Hello ST7735" );

	sleep_ms( 1000 );

	auto canvas = new gfx_canvas( display_tft->get_width(), display_tft->get_height(), 24 );
	if ( is_not_null( display_tft ) ) {
		canvas->set_foreground_color( gfx_color_rgb( 200_u8, 0_u8, 0_u8 ) );
		canvas->draw_point( 6, 6 );
		canvas->draw_point( 6, 159-6 );
		canvas->draw_point( 127-6, 6 );
		canvas->draw_point( 127-6, 159-6 );
		canvas->set_foreground_color( gfx_color_rgb( 0_u8, 200_u8, 0_u8 ) );
		canvas->draw_rectangle( 5, 5, 127-5, 159-5 );
		canvas->set_foreground_color( gfx_color_rgb( 200_u8, 200_u8, 0_u8 ) );
		canvas->set_spot( 7, 7 );
		canvas->draw_line_to( 7, 159-7 );
		canvas->draw_line_to( 127-7, 159-7 );
		canvas->draw_line_to( 127-7, 7 );
		canvas->draw_line_to( 7, 7 );
		canvas->set_foreground_color( gfx_color_rgb( 0_u8, 200_u8, 200_u8 ) );
		canvas->draw_circle( 64, 80, 32 );
		canvas->set_spot( 15, 15 );
		canvas->draw_line_to( 127-15, 159-15 );
		canvas->set_spot( 15, 159-15 );
		canvas->draw_line_to( 127-15, 15 );
		canvas->fill_circle( 50, 100, 20, 0b1111 );
		std::vector< uint16_t > pixmap = canvas->make_pixmap_565();
		display_tft->draw_pixmap( 0, 0, 128, 160, (const uint8_t*) pixmap.data(), pixmap.size() * sizeof(uint16_t) );

		sleep_ms( 1000 );
	}
	//--------------------
	// font
	gfx_font_ptr bitfont = gfx_font::make_gfx_font_from_glyphmap( &cfpt_mono_6x8_array[0][0], 0, 255, 6, 8, true, true );
	gfx_font::print_gfx_font_asciiart( bitfont, "cfpt_6_8" );
	gfx_font::print_gfx_font_files( bitfont, "cfpt_6_8" );
	gfx_font::print_gfx_font_array( bitfont, "cfpt_6_8" );

	canvas->set_font( bitfont );

	canvas->erase();
	canvas->set_spot( 2, 60 );
	canvas->print_center( "Hello àäéèëîûüµú¿?" );

	if ( is_not_null( display_tft ) ) {
		std::vector< uint16_t > pixmap = canvas->make_pixmap_565();
		display_tft->draw_pixmap( 0, 0, 128, 160, (const uint8_t*) pixmap.data(), pixmap.size() * sizeof(uint16_t) );
	}

	bitfont->release();
	bitfont = nullptr;

	//--------------------
	// expander
	auto expander_wire = new wire_i2c( 0, MCP23008_ADDRESS );
	mcp23008_ref expander { nullptr };
	if ( ENABLE_EXPANDER_MCP23008 ) expander = new mcp23008( expander_wire, 0xff, 0x00 );
	if ( is_not_null( expander ) ) expander->gpio_put_all( 0x00 );
	if ( is_not_null( expander ) ) expander->gpio_set_dir( 0, GPIO_OUT );
	if ( is_not_null( expander ) ) expander->gpio_set_pull_up( 0, false );
	if ( is_not_null( expander ) ) expander->gpio_set_dir( 1, GPIO_OUT );
	if ( is_not_null( expander ) ) expander->gpio_set_pull_up( 1, false );
	if ( is_not_null( expander ) ) expander->gpio_set_dir( 2, GPIO_OUT );
	if ( is_not_null( expander ) ) expander->gpio_set_pull_up( 2, false );
	if ( is_not_null( expander ) ) expander->gpio_set_dir( 3, GPIO_OUT );
	if ( is_not_null( expander ) ) expander->gpio_set_pull_up( 3, true );
	if ( is_not_null( expander ) ) expander->gpio_put_all( 0xa5 );

	sleep_ms( 1000 );

	if ( is_not_null( expander ) ) expander->gpio_put( 0, true );
	if ( is_not_null( display_oled ) ) display_oled->erase( 0 );
	if ( is_not_null( display_oled ) ) display_oled->erase( 7, 9 );

	uint8_t glyph[] { 0x44, 0x80, 0x90, 0x80, 0x44, 0x00 };
	if ( is_not_null( display_oled ) ) display_oled->set_lico( 5, 5 );
	if ( is_not_null( display_oled ) ) display_oled->print_glyph( glyph );
	if ( is_not_null( display_oled ) ) display_oled->set_lico( 5, 7 );
	if ( is_not_null( display_oled ) ) display_oled->print( "àéîöûµ" );

	if ( is_not_null( display_oled ) ) display_oled->set_lico( 6, 2 );
	if ( is_not_null( display_oled ) ) display_oled->printf( "value: %.2f V", (float)3.1415926 );

	sleep_ms( 250 );
	if ( is_not_null( display_tft ) ) display_tft->erase( 4 );
	sleep_ms( 2500 );
	if ( is_not_null( display_tft ) ) display_tft->set_foreground_color( 255, 255, 255 );
	if ( is_not_null( display_tft ) ) display_tft->draw_bitmap( 0, 0, 128, 160, cfpt_logo_128_160, sizeof( cfpt_logo_128_160 ) );
	if ( is_not_null( display_tft ) ) display_tft->set_brightness_db( -30 );
	if ( is_not_null( expander ) ) expander->gpio_put( 0, false );

	sleep_ms( 10000 );
	if ( is_not_null( display_oled ) ) display_oled->set_brightness( 0 );
	sleep_ms( 10000 );
	if ( is_not_null( expander ) ) expander->gpio_put( 0, true );

	//--------------------
	// PWM
	auto backlight = new pwm( ST7735_BACKLIGHT_GPIO, 120.0f, 0.5f );
	backlight->set_enabled();
	for ( int level = -50 ; level <= 0 ; ++ level ) {
		backlight->set_duty_db( (float)level );
		sleep_ms( 100 );
	}
	backlight->set_duty( 0 );
	sleep_ms( 1000 );
	backlight->set_duty( 1 );
	sleep_ms( 1000 );
	backlight->set_channel_enabled( false, 0 );
	sleep_ms( 1000 );
	if ( is_not_null( expander ) ) expander->gpio_put( 0, false );

//	oled->set_on( false );
//	tft->set_on( false );

	if ( is_not_null( display_oled ) ) {
		delete display_oled;
		display_oled = nullptr;
	}
	backlight->set_channel_enabled( true, 1 );
	if ( is_not_null( display_tft ) ) {
		display_tft->set_brightness_db( -10.0f );
		display_tft->erase();
		if ( ENABLE_TFT_7735_DELETION ) {
			delete display_tft;
			display_tft = nullptr;
			delete backlight;
			backlight = nullptr;
		}
	}
	if ( is_not_null( expander ) ) {
		delete expander;
		expander = nullptr;
	}

	//--------------------
	// encoder
	auto encoder = new rotary_encoder( 10, 11, 14 );

	//--------------------
	// forever
	while( true ) {
		int8_t rotation = encoder->use_rotation();
		if ( rotation != 0 ) {
			printf( "rotation ! \n" );
		}

		bool click = encoder->use_click();
		if ( click ) {
			printf( "click ! \n" );
		}

		if ( !gpio_get( 10 ) ) {
			if ( is_not_null( display_tft ) ) display_tft->print_center( 5, "  up  " );
		}
		if ( !gpio_get( 11 ) ) {
			if ( is_not_null( display_tft ) ) display_tft->print_center( 5, "right " );
		}

		if ( !gpio_get( 14 ) ) {
			if ( is_not_null( display_tft ) ) display_tft->print_center( 5, " down " );
		}

//		tight_loop_contents();
		sleep_ms( 100 );
	}

	return PICO_OK;
}

//----------------------------------------------------------------
