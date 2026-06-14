//----------------------------------------------------------------

#include "neopixels.h"

//----------------------------------------------------------------

neopixels* neopixels_init( uint gpio );

void neopixels_deinit( neopixels*& that );

//----------------------------------------------------------------

/*! neopixels_start()
 * \brief commence une trame neopixels (reset).
 * \param that neopixels à piloter
 * \return PICO_OK ou un code d'erreur
 */
void neopixels_start( const neopixels* that );

/*! neopixels_finish()
 * \brief envoie un reset neopixels.
 * \param that neopixels à piloter
 */
void neopixels_send_reset( const neopixels* that );

// one

/*! neopixels_send_rgb()
 * \brief envoie une couleur à une diode neopixel.
 * \param that neopixels à piloter
 * \param red composante rouge 0..255
 * \param green composante verte 0..255
 * \param blue composante bleue 0..255
 */
void neopixels_send_rgb( const neopixels* that, uint8_t red, uint8_t green, uint8_t blue );

/*! neopixels_send_rgbw()
 * \brief envoie une couleur & blanc à une diode neopixel.
 * \param that neopixels à piloter
 * \param red composante rouge 0..255
 * \param green composante verte 0..255
 * \param blue composante bleue 0..255
 * \param white composante blanche 0..255
 */
void neopixels_send_rgbw( const neopixels* that, uint8_t red, uint8_t green, uint8_t blue, uint8_t white );

/*! neopixels_send_white()
 * \brief envoie du blanc à une diode neopixel.
 * \param that neopixels à piloter
 * \param white composante blanche 0..255
 */
void neopixels_send_white( const neopixels* that, uint8_t white );

/*! neopixels_send_black()
 * \brief éteint une diode neopixel.
 * \param that neopixels à piloter
 */
void neopixels_send_black( const neopixels* that );

// many

void neopixels_send_many_black( const neopixels* that, size_t count );

// all

void neopixels_send_all_rgb( const neopixels* that, uint8_t red, uint8_t green, uint8_t blue );
void neopixels_send_all_rgbw( const neopixels* that, uint8_t red, uint8_t green, uint8_t blue, uint8_t white );
void neopixels_send_all_white( const neopixels* that, uint8_t white );
void neopixels_send_all_black( const neopixels* that );

/*! neopixels_finish()
 * \brief termine une trame neopixels (reset).
 * \param that neopixels à piloter
 */
void neopixels_finish( const neopixels* that );

//----------------------------------------------------------------
