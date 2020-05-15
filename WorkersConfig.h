#ifndef __WORKERS_CONFIG_H__
#define __WORKERS_CONFIG_H__

//-----------------------------------------------------------------------------
#include <string>
#include <unordered_map> 
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 * Valores que se esperan leer del archivo. Otro valor será considerado
 * un valor ERRONEO y terminará la ejecución levantando una excepción.
*/
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

        /** 
         * Descripcion: parsea el archivo recibido por parametro.
         * Parametros: ruta constante al archivo.
         * Retorno: -
        */
        void _parseFile(const std::string filepath);


        /** 
         * Descripcion: establece la cantidad de instancias a crear
         * de un worker dado.
         * Parametros: worker y cantidad del mismo.
         * Retorno: -
        */
        void _setWorkerQuantity(const std::string worker,
                               const std::string quantity);


        /** 
         * Descripcion: se fija si un valor es válido.
         * Parametros: valor a chequear.
         * Retorno: TRUE si es válido, FALSE si no.
        */
        bool _isValueValid(const std::string value) const;


        /** 
         * Descripcion: se fija si un valor ya fue seteado anteriormente.
         * Parametros: valor a chequear.
         * Retorno: TRUE si está seteado, FALSE si no.
        */
        bool _isValueSet(const std::string value) const;


        /** 
         * Descripcion: se fija si TODOS LOS VALORES fueron seteados.
         * Parametros: -
         * Retorno: TRUE si fueron seteados, FALSE si no.
        */
        bool _areAllValuesSet() const;

    public:
        /** 
         * Descripcion: constructor. Llama a parseFile, levanta excepciones.
         * Parametros: ruta constante al archivo de configuración.
        */
        explicit WorkersConfig(const std::string filepath);


        /** 
         * Deshabilitamos el constructor por copia y su operador.
        */
        WorkersConfig(const WorkersConfig&) = delete;
        WorkersConfig& operator=(const WorkersConfig&) = delete;
        
        
        /**
         * Descripcion: devuelve la cantidad total de recolectores.
         * Parametros: -
         * Retorno: cantidad total de recolectores.
        */
        int getTotalGatherers() const;


        /**
         * Descripcion: devuelve la cantidad total de productores.
         * Parametros: -
         * Retorno: cantidad total de productores.
        */
        int getTotalProducers() const;


        /**
         * Descripcion: devuelve la cantidad de un worker determinado.
         * Parametros: worker consulta.
         * Retorno: cantidad del worker consultado.
        */
        int operator[](const std::string& worker) const;


        /**
         * Descripcion: destructor.
        */
        ~WorkersConfig();
};

//-----------------------------------------------------------------------------
#endif // __WORKERS_CONFIG_H__
