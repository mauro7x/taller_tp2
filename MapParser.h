#ifndef __MAP_PARSER_H__
#define __MAP_PARSER_H__

//-----------------------------------------------------------------------------
#include <string>
#include <fstream>
#include <unordered_map> 

#include "Resources.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
typedef std::unordered_map<char, Resource> ResourceMapper;

#define NO_MORE_RESOURCES INVALID
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------


/**
 * Parser del mapa. Lee desde un archivo (cuya ruta se recibe) y parsea la
 * lectura en RECURSOS. Cuando no hay más recursos, devuelve el recurso
 * INVALID (NO_MORE_RESOURCES).
*/
class MapParser {
    private:
        std::ifstream file;
        ResourceMapper resource_mapper;

        /** 
         * Descripcion: se fija si el recurso que se leyó del archivo
         * es válido.
         * Parametros: char constante que representa al recurso leído.
         * Retorno: TRUE si es válido, FALSE si no.
        */
        bool isResourceValid(const char resource) const;

    public:
        /** 
         * Descripcion: constructor. Abre el archivo especificado por la
         * ruta. Si no se puede, lanza una excepción.
         * Parametros: ruta constante al archivo.
        */
        explicit MapParser(const std::string filepath);


        /** 
         * Deshabilitamos el constructor por copia y su operador.
        */
        MapParser(const MapParser&) = delete;
        MapParser& operator=(const MapParser&) = delete;


        /** 
         * Descripcion: extrae el siguiente recurso del mapa.
         * Parametros: referencia al recurso a copiar.
         * Retorno: -
         * 
         * En caso de que no hayan mas, se retorna el recurso INVALID (0).
        */
        void operator>>(Resource& r);


        /** 
         * Descripcion: destructor.
        */
        ~MapParser();
};

//-----------------------------------------------------------------------------
#endif // __MAP_PARSER_H__
