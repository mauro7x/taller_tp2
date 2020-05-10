#include "WorkersConfig.h"

//-----------------------------------------------------------------------------
#include <string>
#include <fstream>
#include <unordered_map> 

#include "Exception.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

WorkersConfig::WorkersConfig(const std::string filepath) {
    try {
        parseFile(filepath);
    } catch(const Exception& e) {
        throw e;
    }
}


void WorkersConfig::parseFile(const std::string filepath) {
    std::ifstream config_file;
    config_file.open(filepath);
    if (!config_file.is_open()) {
        throw(Exception(INPUT_ERROR, "Error: no se pudo abrir el archivo. "
                        "Función: WorkersConfig::parseFile()."));
    }

    std::string worker_type;
    std::string worker_n;
    while (std::getline(config_file, worker_type, '=')) {
        std::getline(config_file, worker_n);
        try{
            setWorkerQuantity(worker_type, worker_n);
        } catch(const Exception& e) {
            config_file.close();
            throw e;
        }       
    }

    config_file.close();
    if (!areAllValuesSet()) {
        throw(Exception(INPUT_ERROR, "Error: archivo incompleto. "
                        "Función: WorkersConfig::parseFile()."));
    }
}


void WorkersConfig::setWorkerQuantity(const std::string worker,
                                      const std::string quantity) {
    if (!isValueValid(worker)) {
        throw(Exception(INPUT_ERROR, "Error: input desconocido. "
                        "Función: WorkersConfig::setWorkerQuantity()."));
    }

    if (isValueSet(worker)) {
        throw(Exception(INPUT_ERROR, "Error: trabajador repetido. "
                        "Función: WorkersConfig::setWorkerQuantity()"));
    }

    quantities[worker] = std::stoi(quantity);
}


bool WorkersConfig::isValueValid(const std::string value) const {
    return(value == FARMERS || value == LUMBERJACKS || value == MINERS ||
           value == COOKS || value == CARPENTERS || value == BLACKSMITHS);
}


bool WorkersConfig::isValueSet(const std::string value) const {
    return (quantities.count(value) > 0);
}


bool WorkersConfig::areAllValuesSet() const {
    return (isValueSet(FARMERS) && isValueSet(LUMBERJACKS) &&
            isValueSet(MINERS) && isValueSet(COOKS) &&
            isValueSet(CARPENTERS) && isValueSet(BLACKSMITHS));
}


int WorkersConfig::getTotalGatherers() const {
    return (quantities.at(FARMERS) + quantities.at(LUMBERJACKS) +
            quantities.at(MINERS));
}


int WorkersConfig::getTotalProducers() const {
    return (quantities.at(COOKS) + quantities.at(CARPENTERS) +
            quantities.at(BLACKSMITHS));
}


int WorkersConfig::getFarmers() const {
    return quantities.at(FARMERS);
}


int WorkersConfig::getLumberjacks() const {
    return quantities.at(LUMBERJACKS);
}


int WorkersConfig::getMiners() const {
    return quantities.at(MINERS);
}


int WorkersConfig::getCooks() const {
    return quantities.at(COOKS);
}


int WorkersConfig::getCarpenters() const {
    return quantities.at(CARPENTERS);
}


int WorkersConfig::getBlacksmiths() const {
    return quantities.at(BLACKSMITHS);
}


WorkersConfig::~WorkersConfig() {}


//-----------------------------------------------------------------------------
