#ifndef AUTOMATA_SINTACTICO_H
#define AUTOMATA_SINTACTICO_H

#include "tokens.h"

class AutomataSintactico {
private:
    int tTransicion[100][100];
    int estado;
    
public:
    AutomataSintactico();
    void InicializarTransiciones();
    int transicion(int estadoActual, int token);
    bool esEstadoFinal(int estado);
    void reiniciar();
};

#endif