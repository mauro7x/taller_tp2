#include "WorkersConfig.h"

//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <fstream>

#include "Exception.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

WorkersConfig::WorkersConfig(std::string filepath) {
    try {
        parseFile(filepath);
    } catch(const Exception& e) {
        throw e;
    }
}


void WorkersConfig::parseFile(std::string filepath) {
    std::ifstream config_file;
    config_file.open(filepath);
    if (!config_file.is_open()) {
        throw(Exception(INPUT_ERROR, "Error: no se pudo abrir el archivo. "
                        "Función: WorkersConfig::parseFile()"));
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
                        "Función: WorkersConfig::parseFile()"));
    }
}


void WorkersConfig::setWorkerQuantity(std::string worker,
                                      std::string quantity) {
    if (!isValueValid(worker)) {
        throw(Exception(INPUT_ERROR, "Error: input desconocido. "
                        "Función: WorkersConfig::setWorkerQuantity()"));
    }

    if (isValueSet(worker)) {
        throw(Exception(INPUT_ERROR, "Error: trabajador repetido. "
                        "Función: WorkersConfig::setWorkerQuantity()"));
    }

    workers[worker] = std::stoi(quantity);
}


bool WorkersConfig::isValueValid(std::string value) const {
    return(value == FARMERS || value == LUMBERJACKS || value == MINERS ||
           value == COOKS || value == CARPENTERS || value == BLACKSMITHS);
}


bool WorkersConfig::isValueSet(std::string value) const {
    return (workers.count(value) > 0);
}


bool WorkersConfig::areAllValuesSet() const {
    return (isValueSet(FARMERS) && isValueSet(LUMBERJACKS) &&
            isValueSet(MINERS) && isValueSet(COOKS) &&
            isValueSet(CARPENTERS) && isValueSet(BLACKSMITHS));
}


int WorkersConfig::getTotalWorkers() {
    return (workers[FARMERS] + workers[LUMBERJACKS] + workers[MINERS] +
            workers[COOKS] + workers[CARPENTERS] + workers[BLACKSMITHS]);
}


int WorkersConfig::getFarmers() {
    return workers[FARMERS];
}


int WorkersConfig::getLumberjacks() {
    return workers[LUMBERJACKS];
}


int WorkersConfig::getMiners() {
    return workers[MINERS];
}


int WorkersConfig::getCooks() {
    return workers[COOKS];
}


int WorkersConfig::getCarpenters() {
    return workers[CARPENTERS];
}


int WorkersConfig::getBlacksmiths() {
    return workers[BLACKSMITHS];
}


WorkersConfig::~WorkersConfig() {

}


//-----------------------------------------------------------------------------
