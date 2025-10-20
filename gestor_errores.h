#ifndef GESTOR_ERRORES_H
#define GESTOR_ERRORES_H

#include <iostream>

class GestorErrores{
    public:
        static void Error(int nroError, int posicion = -1){
            std::cout << "Error " << nroError << ": ";
            switch(nroError){
                case 100:
                    std::cout << "Caracter no reconocido en posicion " << posicion;
                    break;
                case 400:
                    std::cout << "Error de sintaxis en posicion " << posicion;
                    break;
                case 2000:
                    std::cout << "Fin inesperado del archivo";
                    break;
                default:
                    std::cout << "Error desconocido";
            }
            std::cout << std::endl;
        }
        
        static void ErrorTransicion(int estado, int token){
            std::cout << "Error en transicion desde estado " << estado << " con token " << token << std::endl;
        }
        
        static void ErrorEstadoFinal(int estado){
            std::cout << "Estado final: " << estado << " (se esperaba 16)" << std::endl;
        }
};

#endif