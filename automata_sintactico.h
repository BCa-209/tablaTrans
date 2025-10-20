#ifndef AUTOMATA_SINTACTICO_H
#define AUTOMATA_SINTACTICO_H

#include "tokens.h"

class AutomataSintactico{
    private:
        int tTransicion[100][100];
        int estado;
        
    public:
        AutomataSintactico(){
            estado = 0;
            InicializarTransiciones();
        }
        
        void InicializarTransiciones(){
            for(int ii=0;ii<100;ii++){
                for(int jj=0;jj<100;jj++){
                    tTransicion[ii][jj]=ERROR_TOKEN;
                }
            }

            // Transiciones principales
            tTransicion[0][ESTADISTICAS]=1;
            tTransicion[1][APARENTESIS]=2;
            tTransicion[2][CPARENTESIS]=3;
            tTransicion[3][ALLAVE]=4;
            
            tTransicion[4][VAR]=5;
            tTransicion[4][PROMEDIO]=6;
            tTransicion[4][DESVIACIONEST]=6;
            tTransicion[4][VARIANZA]=6;
            tTransicion[4][FRECUENCIA]=6;
            tTransicion[4][DATOMAYOR]=6;
            tTransicion[4][DATOMENOR]=6;
            tTransicion[4][MEDIA]=6;
            tTransicion[4][MODA]=6;
            tTransicion[4][RANGO]=6;
            tTransicion[4][SESGO]=6;
            tTransicion[4][CURTOSIS]=6;
            tTransicion[4][CLLAVE]=16;

            tTransicion[5][IGUAL]=7;
            tTransicion[7][LEER]=8;
            tTransicion[7][NUM]=11;
            tTransicion[7][VAR]=11;
            tTransicion[8][APARENTESIS]=9;
            tTransicion[9][CADENA]=10;
            tTransicion[10][CPARENTESIS]=11;
            tTransicion[11][PCOMA]=4;

            tTransicion[6][APARENTESIS]=12;
            tTransicion[12][VAR]=13;
            tTransicion[12][NUM]=14;
            tTransicion[13][COMA]=15;
            tTransicion[13][CPARENTESIS]=11;
            tTransicion[14][COMA]=15;
            tTransicion[14][CPARENTESIS]=11;
            tTransicion[15][VAR]=13;
            tTransicion[15][NUM]=14;
        }
        
        int transicion(int token){
            int nuevoEstado = tTransicion[estado][token];
            if(nuevoEstado != ERROR_TOKEN){
                estado = nuevoEstado;
            }
            return nuevoEstado;
        }
        
        bool esEstadoFinal(){
            return estado == 16;
        }
        
        void reiniciar(){
            estado = 0;
        }
        
        int getEstado(){
            return estado;
        }
};

#endif