#ifndef TABLA_SIMBOLOS_H
#define TABLA_SIMBOLOS_H

#include "tokens.h"
#include <iostream>
#include <list>
#include <string>

class Atributos {
public:
    std::string lexema;
    int token;
    std::string tipo;
    std::string valor;
    std::string estado;
    // Constructores y métodos...
};

class TablaSimbolos {
private:
    std::list<Atributos> tabla;
public:
    void Insertar(std::string lex, int tok, std::string tip, 
                  std::string val, std::string est);
    bool Buscar(std::string lex, Atributos& attr);
    bool BuscarPClave(std::string lex, Atributos& attr);
    void Mostrar();
    // Otros métodos...
};

#endif