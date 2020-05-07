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
        this->parseFile(filepath);
    } catch(const Exception& e) {
        throw e;
    }
}


WorkersConfig::~WorkersConfig() {

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
            this->setWorkerQuantity(worker_type, worker_n);
        } catch(const Exception& e) {
            config_file.close();
            throw e;
        }       
    }

    config_file.close();
    if (!this->areAllValuesSet()) {
        throw(Exception(INPUT_ERROR, "Error: archivo incompleto. "
                        "Función: WorkersConfig::parseFile()"));
    }
}


void WorkersConfig::setWorkerQuantity(std::string worker,
                                      std::string quantity) {
    if (!this->isValueValid(worker)) {
        throw(Exception(INPUT_ERROR, "Error: input desconocido. "
                        "Función: WorkersConfig::setWorkerQuantity()"));
    }

    if (this->isValueSet(worker)) {
        throw(Exception(INPUT_ERROR, "Error: trabajador repetido. "
                        "Función: WorkersConfig::setWorkerQuantity()"));
    }

    this->workers[worker] = std::stoi(quantity);
}


bool WorkersConfig::isValueValid(std::string value) const {
    return(value == FARMERS || value == LUMBERJACKS || value == MINERS ||
           value == COOKS || value == CARPENTERS || value == BLACKSMITHS);
}


bool WorkersConfig::isValueSet(std::string value) const {
    return (this->workers.count(value) > 0);
}


bool WorkersConfig::areAllValuesSet() const {
    return (this->isValueSet(FARMERS) && this->isValueSet(LUMBERJACKS) &&
            this->isValueSet(MINERS) && this->isValueSet(COOKS) &&
            this->isValueSet(CARPENTERS) && this->isValueSet(BLACKSMITHS));
}


int WorkersConfig::getFarmers() {
    return this->workers[FARMERS];
}


int WorkersConfig::getLumberjacks() {
    return this->workers[LUMBERJACKS];
}


int WorkersConfig::getMiners() {
    return this->workers[MINERS];
}


int WorkersConfig::getCooks() {
    return this->workers[COOKS];
}


int WorkersConfig::getCarpenters() {
    return this->workers[CARPENTERS];
}


int WorkersConfig::getBlacksmiths() {
    return this->workers[BLACKSMITHS];
}


//-----------------------------------------------------------------------------
