/** TP2 - Taller de Programación I
 * Alumno: Mauro Parafati
 * Padrón: 102749
 * Cuatrimestre y Año: 1C 2020
 * 
 * Repositorio: https://github.com/mauro7x/taller_tp2
*/

//-----------------------------------------------------------------------------
#include <iostream>

#include "Counter.h"
#include "WorkersConfig.h"
#include "Exception.h"

//-----------------------------------------------------------------------------


// ----------------------------------------------------------------------------

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <workers.txt> <map.txt>\n";
        return USAGE_ERROR;
    }

    std::string workers_path = argv[1]; 
    std::string map_path = argv[2];
    
    try {        
        WorkersConfig workers_config(workers_path);
        CounterProtected points(0);



        


    } catch(const Exception& e) {
        std::cerr << e.what() << '\n';
        return e.getErrorCode();
    }
    
    return 0;
}

// ----------------------------------------------------------------------------
