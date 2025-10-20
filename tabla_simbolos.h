#ifndef TABLA_SIMBOLOS_H
#define TABLA_SIMBOLOS_H

#include "tokens.h"
#include <iostream>
#include <string>
#include <list>

class Atributos{
    public:
        std::string lexema;
        int token;
        std::string tipo;
        std::string valor;
        std::string estado;
        
        Atributos(){
            lexema="";
            token=-999;
            tipo="";
            valor=null;
            estado="";
        }
        
        Atributos(std::string lex,int tok,std::string tip,std::string val,std::string est){
            lexema=lex;
            token=tok;
            tipo=tip;
            valor=val;
            estado=est;
        }
        
        void Mostrar(){
            std::cout<<"Tipo("<<tipo<<") \t";
            std::cout<<"Lexema("<<lexema<<") \t";
            std::cout<<"Token("<<token<<") \t";
            std::cout<<"Valor("<<valor<<") \t";
            std::cout<<"Estado("<<estado<<")"<<std::endl;
        }
};

class TablaSimbolos{
    private:
        std::list<Atributos> tabla;
        
    public:
        void Insertar(std::string lex,int tok,std::string tip,std::string val,std::string est){
            Atributos attr(lex,tok,tip,val,est);
            tabla.push_back(attr);
        }
        
        bool ActualizarValor(std::string lex,std::string val){
            for (auto &item:tabla){
                if(item.lexema == lex){
                    item.valor = val;
                    return true;
                }
            }
            return false;
        }
        
        bool ActualizarTipo(std::string lex,std::string tipo){
            for (auto &item:tabla){
                if(item.lexema == lex){
                    item.tipo = tipo;
                    return true;
                }
            }
            return false;
        }
        
        bool ActualizarEstado(std::string lex,std::string est){
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
        
        bool Buscar(std::string lex,Atributos& attr){
            for (auto item:tabla){
                if(item.lexema == lex){
                    attr=item;
                    return true;
                }
            }
            return false;
        }
        
        bool BuscarPClave(std::string lex,Atributos& attr){
            for (auto item:tabla){
                if(item.lexema == lex && item.tipo == "pclave"){
                    attr=item;
                    return true;
                }
            }
            return false;
        }
        
        std::list<Atributos> getTabla(){
            return tabla;
        }
        
        void InicializarPalabrasClave(){
            Insertar("estadisticas",ESTADISTICAS,"pclave",vacio,vacio);
            Insertar("(",APARENTESIS,"pclave",vacio,vacio);
            Insertar(")",CPARENTESIS,"pclave",vacio,vacio);
            Insertar("{",ALLAVE,"pclave",vacio,vacio);
            Insertar("}",CLLAVE,"pclave",vacio,vacio);
            Insertar("=",IGUAL,"pclave",vacio,vacio);
            Insertar(";",PCOMA,"pclave",vacio,vacio);
            Insertar(".",PUNTO,"pclave",vacio,vacio);
            Insertar("promedio",PROMEDIO,"pclave",vacio,vacio);
            Insertar("desviacionest",DESVIACIONEST,"pclave",vacio,vacio);
            Insertar("varianza",VARIANZA,"pclave",vacio,vacio);
            Insertar("frecuencia",FRECUENCIA,"pclave",vacio,vacio);
            Insertar(",",COMA,"pclave",vacio,vacio);
            Insertar("datomayor",DATOMAYOR,"pclave",vacio,vacio);
            Insertar("datomenor",DATOMENOR,"pclave",vacio,vacio);
            Insertar("media",MEDIA,"pclave",vacio,vacio);
            Insertar("moda",MODA,"pclave",vacio,vacio);
            Insertar("rango",RANGO,"pclave",vacio,vacio);
            Insertar("sesgo",SESGO,"pclave",vacio,vacio);
            Insertar("curtosis",CURTOSIS,"pclave",vacio,vacio);
            Insertar("leer",LEER,"pclave",vacio,vacio);
        }
};

#endif