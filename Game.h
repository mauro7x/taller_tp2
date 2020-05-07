#ifndef __GAME_H__
#define __GAME_H__

//-----------------------------------------------------------------------------
#include <string>
#include <vector>

#include "Thread.h"

#include "WorkersConfig.h"
#include "MapParser.h"
#include "BlockingQueue.h"
#include "Inventory.h"
#include "Counter.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

class Game {
    private:
        // config files
        WorkersConfig workers_config;
        MapParser map;
        
        // game static stuff
        Inventory inventory;
        BlockingQueue<int> farmers_source;
        BlockingQueue<int> lumberjacks_source;
        BlockingQueue<int> miners_source;
        CounterProtected points;

        // threads
        int total_workers;
        std::vector<Thread*> workers;

        // methods

    public:
        Game(std::string workers_path, std::string map_path);
        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;

        void run();

        ~Game();
};

//-----------------------------------------------------------------------------
#endif // __GAME_H__
