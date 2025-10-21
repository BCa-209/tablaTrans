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
                if(token == KW_SETUP) cout << " (KW_SETUP)";
                if(token == KW_LOOP) cout << " (KW_LOOP)";
                if(token == KW_END) cout << " (KW_END)";
                if(token == KW_PIN) cout << " (KW_PIN)";
                if(token == KW_FLOAT) cout << " (KW_FLOAT)";
                if(token == KW_INT) cout << " (KW_INT2)";
                if(token == KW_FOR) cout << " (KW_FOR)";
                if(token == KW_TIME) cout << " (KW_TIMES)";
                if(token == KW_IF) cout << " (KW_IF)";
                if(token == KW_ELSE) cout << " (KW_ELSE)";
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