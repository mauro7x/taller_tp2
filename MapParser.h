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

class MapParser {
    private:
        std::ifstream file;
        ResourceMapper resource_mapper;
        bool isResourceValid(const char resource) const;

    public:
        explicit MapParser(const std::string filepath);
        MapParser(const MapParser&) = delete;
        MapParser& operator=(const MapParser&) = delete;
        Resource popResource();
        ~MapParser();
};

//-----------------------------------------------------------------------------
#endif // __MAP_PARSER_H__
