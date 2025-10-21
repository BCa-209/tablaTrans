#ifndef ANALIZADOR_LEXICO_H
#define ANALIZADOR_LEXICO_H

#include "tabla_simbolos.h"
#include "gestor_errores.h"
#include <cctype>
#include <cstring>
#include <iostream>
using namespace std;

class AnalizadorLexico{
    private:
        int i;
        char cad[1000];
        string numero;
        string variable;
        string cadena;
        TablaSimbolos& ts;
        
    public:
        AnalizadorLexico(char input[1000], TablaSimbolos& tabla) : ts(tabla){
            strcpy(cad,input);
            i=0;
        }
        
        bool iselement(char c){
            char elements[] = "(){}=,;.'\":><+-*/";
            for(int j=0; elements[j]!='\0'; j++){
                if(elements[j]==c)
                    return true;
            }
            return false;
        }
        
        int getToken(){
            while(cad[i]==' ' || cad[i]=='\n' || cad[i]=='\t'){
                i++;
            }
            
            if(cad[i]=='\0'){
                return FIN_ARCHIVO;
            }
            
            // Reconocer comentarios CORREGIDO
            if(cad[i]=='#'){
                // ES UN COMENTARIO - consumir hasta el final de línea
                while(cad[i]!='\n' && cad[i]!='\0'){
                    i++;
                }
                return COMENTARIO;
            }
            
            // Reconocer identificadores y palabras clave
            if(isalpha(cad[i]) || cad[i]=='_'){
                char tmp[100];
                int tmp_cont=0;
                while(isalpha(cad[i]) || isdigit(cad[i]) || cad[i]=='_'){
                    tmp[tmp_cont]=cad[i];
                    tmp_cont++;
                    i++;
                }
                tmp[tmp_cont]='\0';
                
                Atributos attr;
                if(ts.BuscarPClave(tmp,attr)){
                    return attr.token;
                }
                variable=tmp;
                return VAR;
            }
            
            // Reconocer números (enteros y decimales)
            if(isdigit(cad[i])){
                char tmp[100];
                int tmp_cont=0;
                bool tienePunto = false;
                while(isdigit(cad[i]) || cad[i]=='.'){
                    if(cad[i]=='.') {
                        if(tienePunto) break; // Solo un punto permitido
                        tienePunto = true;
                    }
                    tmp[tmp_cont]=cad[i];
                    tmp_cont++;
                    i++;
                }
                tmp[tmp_cont]='\0';
                numero=tmp;
                return NUM;
            }
            
            // Reconocer delimitadores y operadores
            if(iselement(cad[i])){
                char tmp[2];
                tmp[0]=cad[i];
                tmp[1]='\0';
                
                Atributos attr;
                if(ts.BuscarPClave(tmp,attr)){
                    i++;
                    return attr.token;
                }
                i++;
                return ERROR_TOKEN;
            }
            
            i++;
            return ERROR_TOKEN;
        }
        
        bool analizar(){
            i=0;
            int token=0;
            cout << "=== ANALISIS LEXICO ===" << endl;
            while(true){
                token=getToken();
                if(token==FIN_ARCHIVO){
                    cout << "Fin del archivo alcanzado" << endl;
                    return true;
                }
                else if(token==VAR){
                    Atributos attr;
                    if(!ts.Buscar(variable,attr)){
                        ts.Insertar(variable,VAR,"variable",vacio,vacio);
                        cout << "Variable reconocida: " << variable << endl;
                    }
                    else {
                        cout << "Palabra clave reconocida: " << variable << endl;
                    }
                }
                else if(token==NUM){
                    cout << "Numero reconocido: " << numero << endl;
                }
                else if(token==COMENTARIO){
                    cout << "Comentario reconocido y omitido" << endl;
                }
                else if(token==ERROR_TOKEN){
                    GestorErrores::Error(100, i);
                    return false;
                }
                else {
                    // Mostrar token reconocido
                    Atributos attr;
                    // Buscar en tabla de símbolos para obtener el nombre
                    for(auto item : ts.getTabla()){
                        if(item.token == token && item.tipo == "pclave"){
                            cout << "Token reconocido: " << token << " (" << item.lexema << ")" << endl;
                            break;
                        }
                    }
                }
            }
        }
        
        void reiniciar(){
            i=0;
        }
        
        // Métodos para obtener valores
        string getVariable() { return variable; }
        string getNumero() { return numero; }
        string getCadena() { return cadena; }
};

#endif