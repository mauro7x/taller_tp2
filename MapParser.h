#ifndef __MAP_PARSER_H__
#define __MAP_PARSER_H__

//-----------------------------------------------------------------------------
#include <string>
#include <fstream>
#include <unordered_map> 

#include "resources.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
typedef std::unordered_map<char, int> ResourceMapper;

#define NO_MORE_RESOURCES 0
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

class MapParser {
    private:
        std::ifstream file;
        ResourceMapper resource_mapper;
        bool isResourceValid(char resource) const;

    public:
        MapParser(std::string filepath);
        MapParser(const MapParser&) = delete;
        MapParser& operator=(const MapParser&) = delete;
        Resource popResource();
        ~MapParser();
};

//-----------------------------------------------------------------------------
#endif // __MAP_PARSER_H__
