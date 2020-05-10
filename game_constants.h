#ifndef __GAME_CONSTANTS_H__
#define __GAME_CONSTANTS_H__

//-----------------------------------------------------------------------------

/**
 * game_constants.h: se incluyen en este archivo las constantes de
 * configuración del juego, para poder modificarlas de así desearlo y no
 * hardcodear valores en el código.
*/

// Tiempos de trabajo de cada worker
#define GATHERER_SLEEP_TIME_US 50000
#define PRODUCER_SLEEP_TIME_US 60000

// Puntos de beneficio ganados por cada productor
#define COOK_PROFIT 5
#define CARPENTER_PROFIT 2
#define BLACKSMITH_PROFIT 3

//-----------------------------------------------------------------------------
#endif // __GAME_CONSTANTS_H__
