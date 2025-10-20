#ifndef GESTOR_ERRORES_H
#define GESTOR_ERRORES_H

#include <iostream>

class GestorErrores {
public:
    static void errorLexico(int posicion, char caracter);
    static void errorSintactico(int posicion, int estado, int token);
    static void errorArchivo(const char* nombreArchivo);
    static void errorSemantico(const std::string& variable, const std::string& mensaje);
};

#endif