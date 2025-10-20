#ifndef ANALIZADOR_SINTACTICO_H
#define ANALIZADOR_SINTACTICO_H

#include "analizador_lexico.h"
#include "automata_sintactico.h"
#include "gestor_errores.h"

class AnalizadorSintactico{
    private:
        AnalizadorLexico& lexico;
        AutomataSintactico automata;
        
    public:
        AnalizadorSintactico(AnalizadorLexico& analex) : lexico(analex) {}
        
        bool analizar(){
            lexico.reiniciar();
            automata.reiniciar();
            
            std::cout << "\n=== ANALISIS SINTACTICO ===" << std::endl;
            int token=0;
            
            while(true){
                token=lexico.getToken();
                std::cout << "Estado: " << automata.getEstado() << ", Token: " << token << std::endl;
                
                if(token==FIN){
                    if(automata.esEstadoFinal()){
                        std::cout << "Analisis sintactico EXITOSO" << std::endl;
                        return true;
                    } else {
                        GestorErrores::Error(2000);
                        GestorErrores::ErrorEstadoFinal(automata.getEstado());
                        return false;
                    }
                }
                
                int nuevoEstado = automata.transicion(token);
                std::cout << "Transicion: " << automata.getEstado() << std::endl;
                
                if(nuevoEstado==ERROR_TOKEN){
                    GestorErrores::Error(400);
                    GestorErrores::ErrorTransicion(automata.getEstado(), token);
                    return false;
                }
            }
        }
};

#endif