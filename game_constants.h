#ifndef __GAME_CONSTANTS_H__
#define __GAME_CONSTANTS_H__

#include "resources.h"

//-----------------------------------------------------------------------------
// Tiempos de trabajo
#define GATHERER_SLEEP_TIME_US 50000
#define PRODUCER_SLEEP_TIME_US 60000

//-----------------------------------------------------------------------------
// PRODUCTORES
// Puntos de beneficio ganados por cada productor
#define COOK_PROFIT 5
#define CARPENTER_PROFIT 2
#define BLACKSMITH_PROFIT 3

// Recetas
#define COOK_RECIPE {{WHEAT, 2}, {WOOD, 0}, {IRON, 0}, {COAL, 1}}
#define CARPENTER_RECIPE {{WHEAT, 0}, {WOOD, 3}, {IRON, 1}, {COAL, 0}}
#define BLACKSMITH_RECIPE {{WHEAT, 0}, {WOOD, 0}, {IRON, 2}, {COAL, 2}}


//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#endif // __GAME_CONSTANTS_H__
