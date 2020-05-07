#include "MapParser.h"

//-----------------------------------------------------------------------------
#include <string>

#include "Exception.h"
#include "resources.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

MapParser::MapParser(std::string filepath) {
    resource_mapper = ResourceMapper({{'M', WOOD}, {'T', WHEAT}, {'C', COAL},
                       {'H', IRON}});
    file.open(filepath);
    if (!file.is_open()) {
        throw(Exception(INPUT_ERROR, "Error: no se pudo abrir el archivo. "
                        "Función: MapParser::MapParser()."));
    }
}


bool MapParser::isResourceValid(char resource) const {
    return (resource_mapper.count(resource) > 0);
}


Resource MapParser::popResource() {
    char resource;

    if (file.get(resource)) {
        if (resource == '\n') {
            file.get(resource);
        }
        if (!isResourceValid(resource)) {
            throw(Exception(INPUT_ERROR, "Error: recurso desconocido. "
                        "Función: MapParser::popResource()."));
        }
        return resource_mapper[resource];
    } else {
        return NO_MORE_RESOURCES;
    }
}


MapParser::~MapParser() {
    file.close();
}


//-----------------------------------------------------------------------------
