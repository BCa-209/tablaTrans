#ifndef ANALIZADOR_LEXICO_H
#define ANALIZADOR_LEXICO_H

#include "tabla_simbolos.h"

class AnalizadorLexico {
private:
    int i;
    char cad[1000];
    std::string variable;
    std::string numero;
    std::string cadena;
    TablaSimbolos& ts;  // Referencia a tabla compartida
    
public:
    AnalizadorLexico(char input[100], TablaSimbolos& tabla);
    int getToken();
    bool iselement(char c);
    bool analizar();
};

#endif