#ifndef AUTOMATA_SINTACTICO_H
#define AUTOMATA_SINTACTICO_H

#include "tokens.h"
#include <iostream>
using namespace std;

class AutomataSintactico{
    private:
        int tTransicion[50][50];
        int estado;
        
    public:
        AutomataSintactico(){
            estado = 0;
            InicializarTransiciones();
        }
        
        void InicializarTransiciones(){
            // Inicializar toda la tabla con ERROR_TOKEN
            for(int ii=0;ii<50;ii++){
                for(int jj=0;jj<50;jj++){
                    tTransicion[ii][jj]=ERROR_TOKEN;
                }
            }

            // ========== GRAMÁTICA SIMPLIFICADA ==========
            
            // Estado 0: Inicio - aceptar INCLUIR y CONFIGURACION
            tTransicion[0][INCLUIR] = 50;        // Nueva transición para "incluir"
            tTransicion[0][KW_SETUP] = 1;
            tTransicion[0][COMENTARIO] = 0;
            tTransicion[0][KW_LOOP] = 4;
            tTransicion[0][FIN_ARCHIVO] = 23;
            
            // INCLUIR LIBRERIA - CORREGIDO
    tTransicion[50][LIBRERIA] = 51;
    tTransicion[51][CADENA] = 52;        // "servo.h"
    tTransicion[52][PCOMA] = 0;          // Volver al estado inicial
    
    // Declaraciones con asignación
    tTransicion[3][VAR] = 70;
    tTransicion[70][IGUAL] = 71;
    tTransicion[71][NUM] = 72;
    tTransicion[72][PCOMA] = 2;
    
    // Declaración decimal con asignación
    tTransicion[2][KW_FLOAT] = 73;
    tTransicion[73][VAR] = 74;
    tTransicion[74][IGUAL] = 75;
    tTransicion[75][NUM] = 76;
    tTransicion[76][PCOMA] = 2;
    
    // Estructura SI-SINO expandida
    tTransicion[15][KW_IF] = 27;
    tTransicion[27][DOSPUNTOS] = 28;
    tTransicion[28][VAR] = 29;
    tTransicion[29][MENOR] = 30;
    tTransicion[29][MAYOR] = 30;
    tTransicion[30][VAR] = 31;
    tTransicion[30][NUM] = 31;
    tTransicion[31][DOSPUNTOS] = 32;
    tTransicion[32][ESTADO] = 33;
    tTransicion[33][PUNTO] = 34;
    tTransicion[34][VAR] = 35;
    tTransicion[35][APARENTESIS] = 36;
    tTransicion[36][NUM] = 37;
    tTransicion[36][VAR] = 37;
    tTransicion[37][CPARENTESIS] = 38;
    tTransicion[38][PCOMA] = 39;
    tTransicion[39][KW_END] = 40;
    tTransicion[40][KW_ELSE] = 41;
    tTransicion[41][DOSPUNTOS] = 42;
    tTransicion[42][ESTADO] = 43;
    tTransicion[43][PUNTO] = 44;
    tTransicion[44][VAR] = 45;
    tTransicion[45][APARENTESIS] = 46;
    tTransicion[46][NUM] = 47;
    tTransicion[46][VAR] = 47;
    tTransicion[47][CPARENTESIS] = 48;
    tTransicion[48][PCOMA] = 49;
    tTransicion[49][KW_END] = 15;
    
    // Estados finales adicionales
    tTransicion[52][FIN_ARCHIVO] = 23;
    tTransicion[72][FIN_ARCHIVO] = 23;
    tTransicion[76][FIN_ARCHIVO] = 23;
    tTransicion[49][FIN_ARCHIVO] = 23;
        }
        
        int transicion(int token){
            cout << "Transicion desde estado " << estado << " con token " << token << endl;
            int nuevoEstado = tTransicion[estado][token];
            if(nuevoEstado != ERROR_TOKEN){
                estado = nuevoEstado;
                cout << "Nuevo estado: " << estado << endl;
            } else {
                cout << "ERROR: No hay transicion desde estado " << estado << " con token " << token << endl;
            }
            return nuevoEstado;
        }
        
        bool esEstadoFinal(){
            // Estados finales aceptables (expandidos)
            return estado == 22 || estado == 23 || estado == 10 || estado == 15 || 
                estado == 37 || estado == 40 || estado == 0 || estado == 52 ||
                estado == 72 || estado == 76 || estado == 49;
        }
        
        void reiniciar(){
            estado = 0;
        }
        
        int getEstado(){
            return estado;
        }
};

#endif