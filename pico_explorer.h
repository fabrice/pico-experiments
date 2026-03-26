//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
//----------------------------------------------------------------

#pragma once
#ifndef _PICO_EXPLORER_H
#define _PICO_EXPLORER_H

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
const uint BUTTON_UP_GPIO = 10;
const uint BUTTON_RIGHT_GPIO = 11;
const uint BUTTON_DOWN_GPIO = 14;
const uint BUTTON_LEFT_GPIO = 15;

// LEDs
const uint LEDS_GPIO = 1;

// Display
const uint DISPLAY_CS_GPIO = 17;
const uint DISPLAY_DC_GPIO = 3;
const uint DISPLAY_RES_GPIO = 6;
const uint DISPLAY_BKL_GPIO = 2;

// Buzzer
const uint BUZZER_GPIO = 27;

// DHT11
const uint DHT_GPIO = 0;

// Relay
const uint RELAY_GPIO = 28;

// UART0
const uint UART_TX_GPIO = 12;
const uint UART_RX_GPIO = 13;

// SPI0
const uint SPI_MISO_GPIO = 16;
const uint SPI_MOSI_GPIO = 19;
const uint SPI_SCLK_GPIO = 18;

// I2C0
const uint I2C_SDA_GPIO = 4;
const uint I2C_SCL_GPIO = 5;

// Servos
const uint SERVO_1_GPIO = 7;
const uint SERVO_2_GPIO = 8;
const uint SERVO_3_GPIO = 9;
const uint SERVO_4_GPIO = 20;


//----------------------------------------------------------------

#endif

//----------------------------------------------------------------
