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

#include "resources.h"
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

class Game {
    private:
        // config files
        WorkersConfig workers_config;
        MapParser map;
        
        // game static stuff
        Inventory inventory;
        BlockingQueue<Resource> farmers_source;
        BlockingQueue<Resource> lumberjacks_source;
        BlockingQueue<Resource> miners_source;
        CounterProtected points;

        // threads
        int total_gatherers;
        std::vector<Thread*> gatherers;
        int total_producers;
        std::vector<Thread*> producers;

        // thread methods
        void spawnWorkers();
        void spawnGatherers(const int &n, BlockingQueue<Resource>& source);
        void spawnProducers(const int &n); // INCOMPLETA
        void startThreads(const int &n, std::vector<Thread*>& threads);
        void joinThreads(const int &n, std::vector<Thread*>& threads);
        void freeThreads(const int &n, std::vector<Thread*>& threads);

        // resource methods
        void distributeResources();
        void closeQueues();

        // general methods
        void printResults();

    public:
        Game(std::string workers_path, std::string map_path);
        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;

        void run();

        ~Game();
};

//-----------------------------------------------------------------------------
#endif // __GAME_H__
