#ifndef GESTOR_ERRORES_H
#define GESTOR_ERRORES_H

#include <iostream>
using namespace std;

class GestorErrores{
    public:
        static void Error(int nroError, int posicion = -1){
            cout << "Error " << nroError << ": ";
            switch(nroError){
                case 100:
                    cout << "Caracter no reconocido en posicion " << posicion;
                    break;
                case 400:
                    cout << "Error de sintaxis en posicion " << posicion;
                    break;
                case 2000:
                    cout << "Fin inesperado del archivo";
                    break;
                default:
                    cout << "Error desconocido";
            }
            cout << endl;
        }
        
        static void ErrorTransicion(int estado, int token){
            cout << "Error en transicion desde estado " << estado << " con token " << token << endl;
        }
        
        static void ErrorEstadoFinal(int estado){
            cout << "Estado final: " << estado << " (se esperaba estado de aceptacion)" << endl;
        }
};

#endif