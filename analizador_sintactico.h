#ifndef ANALIZADOR_SINTACTICO_H
#define ANALIZADOR_SINTACTICO_H

#include "analizador_lexico.h"
#include "automata_sintactico.h"
#include "gestor_errores.h"
#include <iostream>
using namespace std;

class AnalizadorSintactico{
    private:
        AnalizadorLexico& lexico;
        AutomataSintactico automata;
        
    public:
        AnalizadorSintactico(AnalizadorLexico& analex) : lexico(analex) {}
        
        bool analizar(){
            lexico.reiniciar();
            automata.reiniciar();
            
            cout << "\n=== ANALISIS SINTACTICO ===" << endl;
            int token=0;
            int tokenCount = 0;
            
            while(true){
                token=lexico.getToken();
                if(token == FIN_ARCHIVO){
                    cout << "Fin de archivo alcanzado" << endl;
                    break;
                }
                
                tokenCount++;
                cout << "Token #" << tokenCount << ": " << token;
                if(token == VAR) cout << " (VAR: " << lexico.getVariable() << ")";
                if(token == NUM) cout << " (NUM: " << lexico.getNumero() << ")";
                if(token == COMENTARIO) cout << " (COMENTARIO)";
                if(token == ALGORITMO) cout << " (ALGORITMO)";
                cout << endl;
                
                int resultado = automata.transicion(token);
                
                if(resultado == ERROR_TOKEN){
                    cout << "=== ERROR SINTACTICO ===" << endl;
                    cout << "Token actual: " << token << endl;
                    cout << "Estado actual: " << automata.getEstado() << endl;
                    cout << "TokenCount: " << tokenCount << endl;
                    GestorErrores::Error(400);
                    GestorErrores::ErrorTransicion(automata.getEstado(), token);
                    return false;
                }
            }
            
            // Verificar estado final
            if(automata.esEstadoFinal()){
                cout << "=== ANALISIS SINTACTICO EXITOSO ===" << endl;
                cout << "Estado final: " << automata.getEstado() << endl;
                return true;
            } else {
                cout << "=== ERROR EN ESTADO FINAL ===" << endl;
                cout << "Estado actual: " << automata.getEstado() << endl;
                cout << "Se esperaba estado final (22, 23, 10, o 15)" << endl;
                GestorErrores::Error(2000);
                GestorErrores::ErrorEstadoFinal(automata.getEstado());
                return false;
            }
        }
};

#endif