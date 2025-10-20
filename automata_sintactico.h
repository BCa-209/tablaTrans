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
            
            // Estado 0: Inicio - aceptar CONFIGURACION y saltar comentarios
            tTransicion[0][CONFIGURACION]=1;
            tTransicion[0][COMENTARIO]=0;    // Saltar comentarios
            tTransicion[0][CIRCUITO]=4;      // Algunos archivos pueden empezar directo con circuito
            
            // CONFIGURACIÓN
            tTransicion[1][DOSPUNTOS]=2;
            
            // Estado 2: Dentro de configuración
            tTransicion[2][NUMPIN]=3;
            tTransicion[2][CONFIGURAR]=7;
            tTransicion[2][FIN]=10; // Fin de configuración
            
            // Declaración numpin
            tTransicion[3][VAR]=4;
            tTransicion[4][IGUAL]=5;
            tTransicion[5][NUM]=6;
            tTransicion[6][PCOMA]=2; // Volver al estado de configuración
            
            // Configurar pines
            tTransicion[7][APARENTESIS]=8;
            tTransicion[8][NUM]=9;
            tTransicion[8][VAR]=9;
            tTransicion[9][COMA]=11;
            tTransicion[11][SALIDA]=12;
            tTransicion[12][CPARENTESIS]=13;
            tTransicion[13][PCOMA]=2; // Volver a configuración
            
            // CIRCUITO después de fin de configuración
            tTransicion[10][CIRCUITO]=14;
            tTransicion[14][DOSPUNTOS]=15;
            
            // Estado 15: Dentro de circuito
            tTransicion[15][ENCENDER]=16;
            tTransicion[15][APAGAR]=16;
            tTransicion[15][ESPERAR]=19;
            tTransicion[15][FIN]=22; // Fin de circuito - ESTADO FINAL
            
            // Instrucciones encender/apagar
            tTransicion[16][APARENTESIS]=17;
            tTransicion[17][NUM]=18;
            tTransicion[17][VAR]=18;
            tTransicion[18][CPARENTESIS]=20;
            tTransicion[20][PCOMA]=15; // Volver a circuito
            
            // esperar
            tTransicion[19][APARENTESIS]=21;
            tTransicion[21][NUM]=18; // Usar mismo camino que encender/apagar
            
            // Estados finales aceptables
            tTransicion[22][FIN_ARCHIVO]=23; // Estado final completo
            
            // También aceptar fin de archivo desde varios estados
            tTransicion[0][FIN_ARCHIVO]=23;
            tTransicion[10][FIN_ARCHIVO]=23;
            tTransicion[15][FIN_ARCHIVO]=23;
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
            // Estados finales aceptables
            return estado == 22 || estado == 23 || estado == 10 || estado == 15;
        }
        
        void reiniciar(){
            estado = 0;
        }
        
        int getEstado(){
            return estado;
        }
};

#endif