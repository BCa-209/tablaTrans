#ifndef TABLA_SIMBOLOS_H
#define TABLA_SIMBOLOS_H

#include "tokens.h"
#include <iostream>
#include <string>
#include <list>
using namespace std;

class Atributos{
    public:
        string lexema;
        int token;
        string tipo;
        string valor;
        string estado;
        
        Atributos(){
            lexema="";
            token=-999;
            tipo="";
            valor=null;
            estado="";
        }
        
        Atributos(string lex,int tok,string tip,string val,string est){
            lexema=lex;
            token=tok;
            tipo=tip;
            valor=val;
            estado=est;
        }
        
        void Mostrar(){
            cout<<"Tipo("<<tipo<<") \t";
            cout<<"Lexema("<<lexema<<") \t";
            cout<<"Token("<<token<<") \t";
            cout<<"Valor("<<valor<<") \t";
            cout<<"Estado("<<estado<<")"<<endl;
        }
};

class TablaSimbolos{
    private:
        list<Atributos> tabla;
        
    public:
        void Insertar(string lex,int tok,string tip,string val,string est){
            Atributos attr(lex,tok,tip,val,est);
            tabla.push_back(attr);
        }
        
        bool ActualizarValor(string lex,string val){
            for (auto &item:tabla){
                if(item.lexema == lex){
                    item.valor = val;
                    return true;
                }
            }
            return false;
        }
        
        bool ActualizarTipo(string lex,string tipo){
            for (auto &item:tabla){
                if(item.lexema == lex){
                    item.tipo = tipo;
                    return true;
                }
            }
            return false;
        }
        
        bool ActualizarEstado(string lex,string est){
            for (auto &item:tabla){
                if(item.lexema == lex){
                    item.estado = est;
                    return true;
                }
            }
            return false;
        }
        
        void Mostrar(){
            for (auto item:tabla){
                item.Mostrar();
            }
        }
        
        bool Buscar(string lex,Atributos& attr){
            for (auto item:tabla){
                if(item.lexema == lex){
                    attr=item;
                    return true;
                }
            }
            return false;
        }
        
        bool BuscarPClave(string lex,Atributos& attr){
            for (auto item:tabla){
                if(item.lexema == lex && item.tipo == "pclave"){
                    attr=item;
                    return true;
                }
            }
            return false;
        }
        
        list<Atributos> getTabla(){
            return tabla;
        }
        
    void InicializarPalabrasClave(){
    // Palabras reservadas principales
        //Insertar("algoritmo", ALGORITMO, "pclave", vacio, vacio);
        Insertar("configuracion", KW_SETUP, "pclave", vacio, vacio);
        Insertar("Configuracion", KW_SETUP, "pclave", vacio, vacio);
        Insertar("circuito", KW_LOOP, "pclave", vacio, vacio);
        Insertar("Circuito", KW_LOOP, "pclave", vacio, vacio);
        Insertar("fin", KW_END, "pclave", vacio, vacio);
        Insertar("numpin", KW_PIN, "pclave", vacio, vacio);
        Insertar("decimal", KW_FLOAT, "pclave", vacio, vacio);
        Insertar("numero", KW_INT, "pclave", vacio, vacio);
        Insertar("salida", SALIDA, "pclave", vacio, vacio);
        
        // Funciones
        Insertar("configurar", CONFIGURAR, "pclave", vacio, vacio);
        Insertar("configurar_pin", CONFIGURAR_PIN, "pclave", vacio, vacio);
        Insertar("encender", ENCENDER, "pclave", vacio, vacio);
        Insertar("apagar", APAGAR, "pclave", vacio, vacio);
        Insertar("esperar", ESPERAR, "pclave", vacio, vacio);
        Insertar("leer_sensor", LEER_SENSOR, "pclave", vacio, vacio);
        Insertar("intensidad", INTENSIDAD, "pclave", vacio, vacio);
        
        // Estructuras de control
        Insertar("for", KW_FOR, "pclave", vacio, vacio);
        Insertar("veces", KW_TIME, "pclave", vacio, vacio);
        Insertar("if", KW_IF, "pclave", vacio, vacio);
        Insertar("else", KW_ELSE, "pclave", vacio, vacio);
        
        // Delimitadores y operadores
        Insertar("=", IGUAL, "pclave", vacio, vacio);
        Insertar(";", PCOMA, "pclave", vacio, vacio);
        Insertar(",", COMA, "pclave", vacio, vacio);
        Insertar("(", APARENTESIS, "pclave", vacio, vacio);
        Insertar(")", CPARENTESIS, "pclave", vacio, vacio);
        Insertar(":", DOSPUNTOS, "pclave", vacio, vacio);
        Insertar(">", MAYOR, "pclave", vacio, vacio);
        Insertar("<", MENOR, "pclave", vacio, vacio);
        Insertar("+", MAS, "pclave", vacio, vacio);
        Insertar("-", MENOS, "pclave", vacio, vacio);
        Insertar("*", POR, "pclave", vacio, vacio);
        Insertar("/", DIVIDIDO, "pclave", vacio, vacio);
        
        // Encabezado de algoritmo
        Insertar("#", COMENTARIO, "pclave", vacio, vacio);
    }
};

#endif