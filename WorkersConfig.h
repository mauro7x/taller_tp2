#ifndef __WORKERS_CONFIG_H__
#define __WORKERS_CONFIG_H__

//-----------------------------------------------------------------------------
#include <string>
#include <unordered_map> 
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#define FARMERS "Agricultores"
#define LUMBERJACKS "Leniadores"
#define MINERS "Mineros"
#define COOKS "Cocineros"
#define CARPENTERS "Carpinteros"
#define BLACKSMITHS "Armeros"
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

class WorkersConfig {
    private:
        std::unordered_map<std::string, int> workers;

        void parseFile(std::string filepath);
        void setWorkerQuantity(std::string worker, std::string quantity);
        bool isValueValid(std::string value) const;
        bool isValueSet(std::string value) const;
        bool areAllValuesSet() const;

    public:
        WorkersConfig(std::string filepath);
        ~WorkersConfig();

        int getFarmers();
        int getLumberjacks();
        int getMiners();
        int getCooks();
        int getCarpenters();
        int getBlacksmiths();

        WorkersConfig(const WorkersConfig&) = delete;
        WorkersConfig& operator=(const WorkersConfig&) = delete;
};

//-----------------------------------------------------------------------------
#endif // __WORKERS_CONFIG_H__
