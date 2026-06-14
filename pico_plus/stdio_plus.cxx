//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// stdio_plus
//
//----------------------------------------------------------------

#include "stdio_plus.h"

#include "pico/stdio.h"
#include "pico/stdio_usb.h"
#include "pico/time.h"

//----------------------------------------------------------------

/*! stdio_usb_wait()
 * \brief attend que la console soit connectée au maximum timeout millisecondes.
 * \param timeout attente maximale en millisecondes
 * \return stdio_usb_connected()
 * \author Didier Moullet, 2026
 * \author Fabrice de Chambrier, 2026
 */
bool stdio_usb_wait( uint timeout ) {
	absolute_time_t deadline = make_timeout_time_ms( timeout );
	while ( !stdio_usb_connected() && !time_reached( deadline ) ) {
		sleep_ms( 100 );
	}

	return stdio_usb_connected();
}

//----------------------------------------------------------------
