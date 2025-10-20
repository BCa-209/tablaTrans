#ifndef ANALIZADOR_SINTACTICO_H
#define ANALIZADOR_SINTACTICO_H

#include "analizador_lexico.h"
#include "automata_sintactico.h"

class AnalizadorSintactico {
private:
    AnalizadorLexico& lexico;
    AutomataSintactico automata;
    
public:
    AnalizadorSintactico(AnalizadorLexico& analex);
    bool analizar();
};

#endif