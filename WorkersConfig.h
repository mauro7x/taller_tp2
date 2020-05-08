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
        std::unordered_map<std::string, int> quantities;

        void parseFile(const std::string filepath);
        void setWorkerQuantity(const std::string worker,
                               const std::string quantity);
        bool isValueValid(const std::string value) const;
        bool isValueSet(const std::string value) const;
        bool areAllValuesSet() const;

    public:
        WorkersConfig(const std::string filepath);
        WorkersConfig(const WorkersConfig&) = delete;
        WorkersConfig& operator=(const WorkersConfig&) = delete;
        
        int getTotalGatherers() const;
        int getTotalProducers() const;
        int getFarmers() const;
        int getLumberjacks() const;
        int getMiners() const;
        int getCooks() const;
        int getCarpenters() const;
        int getBlacksmiths() const;

        ~WorkersConfig();
};

//-----------------------------------------------------------------------------
#endif // __WORKERS_CONFIG_H__
