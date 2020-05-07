#ifndef __MAP_PARSER_H__
#define __MAP_PARSER_H__

//-----------------------------------------------------------------------------
#include <string>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

class MapParser {
    private:

    public:
        MapParser(std::string filepath);
        MapParser(const MapParser&) = delete;
        MapParser& operator=(const MapParser&) = delete;
        
        ~MapParser();
};

//-----------------------------------------------------------------------------
#endif // __MAP_PARSER_H__
