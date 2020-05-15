#include "MapParser.h"

//-----------------------------------------------------------------------------
#include <string>
#include <fstream>
#include <unordered_map> 

#include "Exception.h"
#include "Resources.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// API Pública

MapParser::MapParser(const std::string filepath) {
    resource_mapper.insert({{'M', WOOD}, {'T', WHEAT},
                           {'C', COAL}, {'H', IRON}});
    file.open(filepath);
    if (!file.is_open()) {
        throw(Exception(INPUT_ERROR, "Error: no se pudo abrir el archivo. "
                        "Función: MapParser::MapParser()."));
    }
}


bool MapParser::isResourceValid(const char resource) const {
    return (resource_mapper.count(resource) > 0);
}


void MapParser::operator>>(Resource& r) {
    char resource;
    if (file >> std::skipws >> resource) {
        if (!isResourceValid(resource)) {
            throw(Exception(INPUT_ERROR, "Error: recurso desconocido. "
                        "Función: MapParser::popResource()."));
        }
        r = resource_mapper[resource];
    } else {
        r = NO_MORE_RESOURCES;
    }
}


MapParser::~MapParser() {
    file.close();
}


//-----------------------------------------------------------------------------
