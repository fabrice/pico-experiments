//----------------------------------------------------------------
//
// Raspberry Pico
// Target : PicoSDK C/C++
//
// ui_leds_fn
//
//----------------------------------------------------------------

#pragma once

//----------------------------------------------------------------

#include "ui_leds.h"

#include <cstdint>

//----------------------------------------------------------------

class ui_leds;

//----------------------------------------------------------------

/*! ui_leds_init()
 * \brief crée des LEDs virtuelles pilotables à l'écran.
 * \return PICO_OK ou un code d'erreur
 */
int ui_leds_init();

//----------------------------------------------------------------

/*! ui_leds_set_title()
 * \brief écrit un titre à l'écran.
 * \param text texte à afficher
 */
void ui_leds_set_title( const std::string_view& text );

//----------------------------------------------------------------

/*! ui_leds_set_message()
 * \brief écrit un message à l'écran.
 * \param text texte à afficher
 */
void ui_leds_set_message( const std::string_view& text );

//----------------------------------------------------------------

/*! ui_leds_get_led_count()
 * \brief retourne le nombre de diodes.
 * \return nombre de diodes
 */
[[nodiscard]]
uint ui_leds_get_led_count();

//----------------------------------------------------------------

/*! ui_leds_get_leds()
 * \brief retourne l'état des diodes.
 * \return état des diodes, LSB -> diode 0
 */
[[nodiscard]]
uint32_t ui_leds_get_leds();

//----------------------------------------------------------------

/*! ui_leds_get_led()
 * \brief retourne l'état de la diode num.
 * \param num numéro de diode ou bit
 * \return état de la diode num
 */
bool ui_leds_get_led( uint num );

//----------------------------------------------------------------

/*! ui_leds_put_leds()
 * \brief écrit l'état des diodes.
 * \param bits état des diodes, LSB -> diode 0
 */
void ui_leds_put_leds( uint32_t leds );

//----------------------------------------------------------------

/*! ui_leds_put_led()
 * \brief écrit l'état de la diode num.
 * \param num numéro de la diode ou bit
 * \param on état de la diode num
 */
void ui_leds_put_led( uint num, bool on );

//----------------------------------------------------------------

/*! ui_leds_set_led()
 * \brief allume la diode num.
 * \param num numéro de la diode ou bit
 */
void ui_leds_set_led( uint num );

//----------------------------------------------------------------

/*! ui_leds_clr_led()
 * \brief éteint la diode num.
 * \param num numéro de la diode ou bit
 */
void ui_leds_clr_led( uint num );

//----------------------------------------------------------------

/*! ui_leds_xor_led()
 * \brief toggle la diode num.
 * \param num numéro de la diode ou bit
 */
void ui_leds_xor_led( uint num );

//----------------------------------------------------------------

/*! ui_leds_set_color()
 * \brief règle la couleur d'affichage des diodes.
 * \param red rouge allumé ou éteint
 * \param green vert allumé ou éteint
 * \param blue bleu allumé ou éteint
 */
void ui_leds_set_color( bool red, bool green, bool blue );

//----------------------------------------------------------------

void ui_leds_deinit();

//----------------------------------------------------------------
