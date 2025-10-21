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
    tTransicion[0][KW_SETUP]=1;
    tTransicion[0][COMENTARIO]=0;    // Saltar comentarios
    tTransicion[0][KW_LOOP]=4;      // Algunos archivos pueden empezar directo con circuito
    tTransicion[0][FIN_ARCHIVO]=23;  // Aceptar archivo vacío o solo comentarios
    
    // CONFIGURACIÓN
    tTransicion[1][DOSPUNTOS]=2;
    
    // Estado 2: Dentro de configuración
    tTransicion[2][KW_PIN]=3;        // numpin
    tTransicion[2][KW_FLOAT]=3;      // decimal
    tTransicion[2][CONFIGURAR]=7;
    tTransicion[2][KW_END]=10;       // Fin de configuración
    
    // Declaración numpin/decimal
    tTransicion[3][VAR]=4;
    tTransicion[4][IGUAL]=5;
    tTransicion[5][NUM]=6;
    tTransicion[5][VAR]=6;           // Aceptar variables también (como A0)
    tTransicion[6][PCOMA]=2;         // Volver al estado de configuración
    
    // Configurar pines
    tTransicion[7][APARENTESIS]=8;
    tTransicion[8][NUM]=9;
    tTransicion[8][VAR]=9;
    tTransicion[9][COMA]=11;
    tTransicion[11][SALIDA]=12;
    tTransicion[12][CPARENTESIS]=13;
    tTransicion[13][PCOMA]=2;        // Volver a configuración
    
    // CIRCUITO después de fin de configuración
    tTransicion[10][KW_LOOP]=14;
    tTransicion[14][DOSPUNTOS]=15;
    
    // Estado 15: Dentro de circuito
    tTransicion[15][ENCENDER]=16;
    tTransicion[15][APAGAR]=16;
    tTransicion[15][ESPERAR]=19;
    tTransicion[15][KW_INT]=24;      // declaración numero
    tTransicion[15][KW_FLOAT]=24;    // declaración decimal
    tTransicion[15][KW_IF]=27;       // estructura si
    tTransicion[15][KW_END]=22;      // Fin de circuito
    
    // Instrucciones encender/apagar
    tTransicion[16][APARENTESIS]=17;
    tTransicion[17][NUM]=18;
    tTransicion[17][VAR]=18;
    tTransicion[18][CPARENTESIS]=20;
    tTransicion[20][PCOMA]=15;       // Volver a circuito
    
    // esperar
    tTransicion[19][APARENTESIS]=21;
    tTransicion[21][NUM]=18;
    tTransicion[21][VAR]=18;
    
    // Declaración de variables en circuito
    tTransicion[24][VAR]=25;
    tTransicion[25][IGUAL]=26;
    
    // Asignaciones
    tTransicion[26][NUM]=20;
    tTransicion[26][VAR]=20;
    
    // leer_sensor
    tTransicion[26][LEER_SENSOR]=28;
    tTransicion[28][APARENTESIS]=29;
    tTransicion[29][VAR]=30;
    tTransicion[30][CPARENTESIS]=20;
    
    // Expresiones aritméticas
    tTransicion[20][POR]=31;
    tTransicion[20][MAS]=31;
    tTransicion[20][MENOS]=31;
    tTransicion[31][NUM]=20;
    tTransicion[31][VAR]=20;
    
    // Estructura SI
    tTransicion[27][DOSPUNTOS]=32;
    tTransicion[32][VAR]=33;
    tTransicion[33][MAYOR]=34;
    tTransicion[33][MENOR]=34;
    tTransicion[34][VAR]=35;
    tTransicion[34][NUM]=35;
    tTransicion[35][DOSPUNTOS]=36;
    
    // Cuerpo del SI
    tTransicion[36][ENCENDER]=16;
    tTransicion[36][APAGAR]=16;
    tTransicion[36][KW_END]=37;      // fin del si
    
    // SINO
    tTransicion[37][KW_ELSE]=38;     // sino
    tTransicion[38][DOSPUNTOS]=39;
    
    // Cuerpo del SINO
    tTransicion[39][ENCENDER]=16;
    tTransicion[39][APAGAR]=16;
    tTransicion[39][KW_END]=40;      // fin del sino
    tTransicion[40][PCOMA]=15;       // Volver a circuito
    
    // Estados finales aceptables
    tTransicion[22][FIN_ARCHIVO]=23; // Estado final completo
    
    // Aceptar fin de archivo desde estados válidos
    tTransicion[0][FIN_ARCHIVO]=23;
    tTransicion[10][FIN_ARCHIVO]=23;
    tTransicion[15][FIN_ARCHIVO]=23;
    tTransicion[37][FIN_ARCHIVO]=23;
    tTransicion[40][FIN_ARCHIVO]=23;
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