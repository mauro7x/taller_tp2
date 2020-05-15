#include "WorkersConfig.h"

//-----------------------------------------------------------------------------
#include <string>
#include <fstream>
#include <unordered_map> 

#include "Exception.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Métodos privados

void WorkersConfig::_parseFile(const std::string filepath) {
    std::ifstream config_file;
    config_file.open(filepath);
    if (!config_file.is_open()) {
        throw(Exception(INPUT_ERROR, "Error: no se pudo abrir el archivo. "
                        "Función: WorkersConfig::_parseFile()."));
    }

    std::string worker_type;
    std::string worker_n;
    while (std::getline(config_file, worker_type, '=')) {
        std::getline(config_file, worker_n);
        try{
            _setWorkerQuantity(worker_type, worker_n);
        } catch(const Exception& e) {
            config_file.close();
            throw e;
        }       
    }

    config_file.close();
    if (!_areAllValuesSet()) {
        throw(Exception(INPUT_ERROR, "Error: archivo incompleto. "
                        "Función: WorkersConfig::_parseFile()."));
    }
}


void WorkersConfig::_setWorkerQuantity(const std::string worker,
                                      const std::string quantity) {
    if (!_isValueValid(worker)) {
        throw(Exception(INPUT_ERROR, "Error: input desconocido. "
                        "Función: WorkersConfig::_setWorkerQuantity()."));
    }

    if (_isValueSet(worker)) {
        throw(Exception(INPUT_ERROR, "Error: trabajador repetido. "
                        "Función: WorkersConfig::_setWorkerQuantity()"));
    }

    quantities[worker] = std::stoi(quantity);
}


bool WorkersConfig::_isValueValid(const std::string value) const {
    return(value == FARMERS || value == LUMBERJACKS || value == MINERS ||
           value == COOKS || value == CARPENTERS || value == BLACKSMITHS);
}


bool WorkersConfig::_isValueSet(const std::string value) const {
    return (quantities.count(value) > 0);
}


bool WorkersConfig::_areAllValuesSet() const {
    return (_isValueSet(FARMERS) && _isValueSet(LUMBERJACKS) &&
            _isValueSet(MINERS) && _isValueSet(COOKS) &&
            _isValueSet(CARPENTERS) && _isValueSet(BLACKSMITHS));
}


//-----------------------------------------------------------------------------
// API Pública

WorkersConfig::WorkersConfig(const std::string filepath) {
    try {
        _parseFile(filepath);
    } catch(const Exception& e) {
        throw e;
    }
}


int WorkersConfig::getTotalGatherers() const {
    return (quantities.at(FARMERS) + quantities.at(LUMBERJACKS) +
            quantities.at(MINERS));
}


int WorkersConfig::getTotalProducers() const {
    return (quantities.at(COOKS) + quantities.at(CARPENTERS) +
            quantities.at(BLACKSMITHS));
}


int WorkersConfig::operator[](const std::string& worker) const {
    return quantities.at(worker);
}


WorkersConfig::~WorkersConfig() {}


//-----------------------------------------------------------------------------
