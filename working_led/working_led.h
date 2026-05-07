//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// working_led
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "pico/stdlib.h"

#include <cstdint>

//----------------------------------------------------------------

/*! working_led_init()
 * \brief initialise une diode de travail.
 * \param gpio gpio de la diode de travail
 * \param period période de clignotement en millisecondes
 * \param cycle rapport cyclique entre 0.0f et 1.0f
 */
void working_led_init( uint gpio, uint32_t period, float cycle );

//----------------------------------------------------------------

/*! working_led_set_period()
 * \brief configure la période de la diode de travail.
 * \param period période de clignotement en millisecondes
 */
void working_led_set_period( uint32_t period );

//----------------------------------------------------------------

/*! working_led_set_cycle()
 * \brief configure la période de la diode de travail.
 * \param cycle rapport cyclique entre 0.0f et 1.0f
 */
void working_led_set_cycle( float cycle );

//----------------------------------------------------------------

/*! working_led_start()
 * \brief démarre une période de la diode de travail.
 */
void working_led_start();

//----------------------------------------------------------------

/*! working_led_tick()
 * \brief mise à jour régulière du statut de la diode de travail.
 */
void working_led_tick();

//----------------------------------------------------------------

/*! working_led_get_led()
 * \brief retourne l'état de la diode de travail.
 * \return état de la diode de travail
 */
bool working_led_get_led();

//----------------------------------------------------------------

/*! working_led_put_led()
 * \brief écrit l'état de la diode de travail.
 * \param on état de la diode de travail
 */
void working_led_put_led( bool on );

//----------------------------------------------------------------

/*! working_led_set_led()
 * \brief allume la diode de travail.
 */
void working_led_set_led();

//----------------------------------------------------------------

/*! working_led_clr_led()
 * \brief éteint la diode de travail.
 */
void working_led_clr_led();

//----------------------------------------------------------------

/*! working_led_xor_led()
 * \brief toggle la diode de travail.
 */
void working_led_xor_led();

//----------------------------------------------------------------
