#ifndef __RECIPES_H__
#define __RECIPES_H__

//-----------------------------------------------------------------------------
#include <unordered_map>

#include "Resources.h"

typedef std::unordered_map<Resource, int> Recipe;
//-----------------------------------------------------------------------------

/**
 * Se encapsulan en este archivo la implementación de las RECETAS, así como
 * los valores de las mismas.
 * 
 * Se decidió utilizar un HashMap para su implementación pues no veo necesario
 * diseñar una nueva clase, ya que no hay comportamiento asociado (más allá del
 * que me proporciona un HashMap).
*/

// Recetas de cada productor
#define COOK_RECIPE {{WHEAT, 2}, {WOOD, 0}, {IRON, 0}, {COAL, 1}}
#define CARPENTER_RECIPE {{WHEAT, 0}, {WOOD, 3}, {IRON, 1}, {COAL, 0}}
#define BLACKSMITH_RECIPE {{WHEAT, 0}, {WOOD, 0}, {IRON, 2}, {COAL, 2}}

//-----------------------------------------------------------------------------
#endif // __RECIPES_H__
