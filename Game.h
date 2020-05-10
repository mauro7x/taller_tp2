#ifndef __GAME_H__
#define __GAME_H__

//-----------------------------------------------------------------------------
#include <string>
#include <vector>

#include "Thread.h"
#include "WorkersConfig.h"
#include "MapParser.h"
#include "ResourceQueue.h"
#include "Inventory.h"
#include "Counter.h"

#include "Recipes.h"
#include "Resources.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

class Game {
    private:
        // config files
        WorkersConfig workers_config;
        MapParser map;
        
        // game static stuff
        InventoryProtected inventory;
        CounterProtected points;
        ResourceQueue farmers_source, lumberjacks_source, miners_source;
        Recipe cooks_recipe, carpenters_recipe, blacksmiths_recipe;

        // threads
        std::vector<Thread*> gatherers, producers;
        int total_gatherers;
        int total_producers;       

        // thread methods
        void spawnWorkers();
        void spawnGatherers(const int &n, ResourceQueue& source);
        void spawnProducers(const int &n, int profitForProducing,
                            const Recipe& recipe);
        void startThreads(const int &n, std::vector<Thread*>& threads);
        void joinThreads(const int &n, std::vector<Thread*>& threads);
        void freeThreads(const int &n, std::vector<Thread*>& threads);

        // resource methods
        void distributeResources();
        void closeResourceQueues();

        // general methods
        void forceFinish();
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
