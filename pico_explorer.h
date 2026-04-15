//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico.h"
#include "pico/stdlib.h"

//----------------------------------------------------------------
/*
						  ---------
				  0 [01]-|   usb   |-[40] VBUS
				  1 [02]-|         |-[39] VSYS
				GND [03]-|         |-[38] GND
				  2 [04]-|         |-[37] 3.3 EN
				  3 [05]-|  00     |-[36] 3.3 OUT
		  I2C SCA 4 [06]-|  00     |-[35] ADC VREF
		  I2C SCL 5 [07]-|         |-[34]
				GND [08]-|         |-[33] GND | AGND
	  DISPLAY RES 6 [09]-|  +++++  |-[32]
				  7 [10]-|  +++++  |-[31]
				  8 [11]-|  +++++  |-[30] RUN
				  9 [12]-|  +++++  |-[29]
				GND [13]-|         |-[28] GND
					[14]-|         |-[27]
					[15]-|  Pico2  |-[26]
					[16]-|         |-[25]
					[17]-|         |-[24]
				GND [18]-|         |-[23] GND
					[19]-|         |-[22]
					[20]-|  debug  |-[21]
						  ---------
*/
//----------------------------------------------------------------

// Buttons
constexpr uint BUTTON_UP_GPIO { 10 };
constexpr uint BUTTON_RIGHT_GPIO { 11 };
constexpr uint BUTTON_DOWN_GPIO { 14 };
constexpr uint BUTTON_LEFT_GPIO { 15 };

// LEDs
constexpr uint LEDS_GPIO { 1 };

// Display
constexpr uint DISPLAY_CS_GPIO { 17 };
constexpr uint DISPLAY_DC_GPIO { 3 };
constexpr uint DISPLAY_RES_GPIO { 6 };
constexpr uint DISPLAY_BKL_GPIO { 2 };

// Buzzer
constexpr uint BUZZER_GPIO { 27 };

// DHT11
constexpr uint DHT_GPIO { 0 };

// Relay
constexpr uint RELAY_GPIO { 28 };

// UART0
constexpr uint UART_TX_GPIO { 12 };
constexpr uint UART_RX_GPIO { 13 };

// I2C0
constexpr uint I2C0_SDA_GPIO { 4 };
constexpr uint I2C0_SCL_GPIO { 5 };

// SPI0
constexpr uint SPI0_MISO_GPIO { 16 };
constexpr uint SPI0_MOSI_GPIO { 19 };
constexpr uint SPI_SCLK_GPIO { 18 };

// Servos
constexpr uint SERVO_1_GPIO { 7 };
constexpr uint SERVO_2_GPIO { 8 };
constexpr uint SERVO_3_GPIO { 9 };
constexpr uint SERVO_4_GPIO { 20 };


//----------------------------------------------------------------
// MicroChip PKSERIAL-I2C1

constexpr uint mcp9800_ADDRESS { 0x49 };
constexpr uint mcp3221_ADDRESS { 0x4d };

//----------------------------------------------------------------
