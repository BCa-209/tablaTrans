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
            
            // INCLUIR LIBRERIA
            tTransicion[50][LIBRERIA] = 51;
            tTransicion[51][CADENA] = 52;        // "servo.h"
            tTransicion[52][PCOMA] = 0;          // Volver al estado inicial
            
            // CONFIGURACIÓN (estados existentes expandidos)
            tTransicion[1][DOSPUNTOS] = 2;
            
            // Estado 2: Dentro de configuración - EXPANDIDO
            tTransicion[2][KW_PIN] = 3;
            tTransicion[2][KW_FLOAT] = 3;
            tTransicion[2][KW_INT] = 3;
            tTransicion[2][CONFIGURAR] = 7;
            tTransicion[2][SERVO] = 53;          // declaración servo
            tTransicion[2][KW_END] = 10;
            
            // Declaración servo
            tTransicion[53][VAR] = 54;
            tTransicion[54][PCOMA] = 2;          // servo puerta;
            
            // Configurar pines - EXPANDIDO para ENTRADA
            tTransicion[7][APARENTESIS] = 8;
            tTransicion[8][NUM] = 9;
            tTransicion[8][VAR] = 9;
            tTransicion[9][COMA] = 11;
            tTransicion[11][SALIDA] = 12;
            tTransicion[11][ENTRADA] = 12;       // entrada también válida
            tTransicion[12][CPARENTESIS] = 13;
            tTransicion[13][PCOMA] = 2;
            
            // Llamadas a métodos con punto (conectar.puerta, estado.puerta)
            tTransicion[2][CONECTAR] = 55;
            tTransicion[2][ESTADO] = 55;
            tTransicion[55][PUNTO] = 56;         // . (punto)
            tTransicion[56][VAR] = 57;           // puerta
            tTransicion[57][APARENTESIS] = 58;
            tTransicion[58][NUM] = 59;
            tTransicion[58][VAR] = 59;
            tTransicion[59][CPARENTESIS] = 60;
            tTransicion[60][PCOMA] = 2;
            
            // ... (estados existentes para circuito se mantienen)
            
            // Estado 15: Dentro de circuito - EXPANDIDO
            tTransicion[15][ENCENDER] = 16;
            tTransicion[15][APAGAR] = 16;
            tTransicion[15][ESPERAR] = 19;
            tTransicion[15][KW_INT] = 24;
            tTransicion[15][KW_FLOAT] = 24;
            tTransicion[15][KW_IF] = 27;
            tTransicion[15][PULSO] = 61;         // pulso.echo
            tTransicion[15][ESTADO] = 55;        // estado.puerta en circuito
            tTransicion[15][KW_END] = 22;
            
            // pulso.echo
            tTransicion[61][PUNTO] = 62;
            tTransicion[62][ECHO] = 63;
            tTransicion[63][PCOMA] = 15;
            
            // Expresiones aritméticas más complejas
            tTransicion[20][POR] = 31;
            tTransicion[20][MAS] = 31;
            tTransicion[20][MENOS] = 31;
            tTransicion[20][DIVIDIDO] = 31;
            tTransicion[31][NUM] = 20;
            tTransicion[31][VAR] = 20;
            
            // Estados finales aceptables (expandir)
            tTransicion[22][FIN_ARCHIVO] = 23;
            tTransicion[0][FIN_ARCHIVO] = 23;
            tTransicion[10][FIN_ARCHIVO] = 23;
            tTransicion[15][FIN_ARCHIVO] = 23;
            tTransicion[37][FIN_ARCHIVO] = 23;
            tTransicion[40][FIN_ARCHIVO] = 23;
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
                estado == 37 || estado == 40 || estado == 0;
        }
        
        void reiniciar(){
            estado = 0;
        }
        
        int getEstado(){
            return estado;
        }
};

#endif