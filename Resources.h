#ifndef __RESOURCES_H__
#define __RESOURCES_H__

//-----------------------------------------------------------------------------

/**
 * Se encapsula en este archivo la implementación de los RECURSOS.
 * Decidí utilizar un ENUM en vez de crear una clase, pues no veo
 * comportamiento asociado que justifique su diseño. En caso de querer
 * refactorizar y agregar comportamiento, este encapsulamiento permite
 * hacerlo sin tocar el resto del código.
 * 
 * VALORES:
 *      INVALID (0): Valor especial que no es un recurso valido.
 *      WHEAT (1):   Trigo.
 *      WOOD (2):    Madera.
 *      IRON (3):    Hierro.
 *      COAL (4):    Carbón.
 * 
 * Notar que todos los recursos válidos son > a 0. Esto se puede utilizar para
 * búcles con condicion de corte: while (resource) {...}, ya que cuando resource
 * sea invalido, el while terminará.
*/
typedef int Resource;
enum Resources {INVALID, WHEAT, WOOD, IRON, COAL};

//-----------------------------------------------------------------------------
#endif // __RESOURCES_H__
