#ifndef ANALIZADOR_LEXICO_H
#define ANALIZADOR_LEXICO_H

#include "tabla_simbolos.h"
#include "gestor_errores.h"
#include <cctype>
#include <cstring>

class AnalizadorLexico{
    private:
        int i;
        char cad[1000];
        std::string numero;
        std::string variable;
        std::string cadena;
        TablaSimbolos& ts;
        
    public:
        AnalizadorLexico(char input[100], TablaSimbolos& tabla) : ts(tabla){
            strcpy(cad,input);
            i=0;
        }
        
        bool iselement(char c){
            char elements[] = "(){}=,;.'";
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
                return FIN;
            }
            
            if(isalpha(cad[i])){
                char tmp[100];
                int tmp_cont=0;
                while(isalpha(cad[i]) || isdigit(cad[i])){
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
            
            if(isdigit(cad[i])){
                char tmp[100];
                int tmp_cont=0;
                while(isdigit(cad[i]) || cad[i]=='.'){
                    tmp[tmp_cont]=cad[i];
                    tmp_cont++;
                    i++;
                }
                tmp[tmp_cont]='\0';
                numero=tmp;
                return NUM;
            }
            
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
            
            if(cad[i]=='\''){
                char tmp[100];
                int tmp_cont=0;
                i++;
                while(cad[i]!='\'' && cad[i]!='\0'){
                    tmp[tmp_cont++]=cad[i];
                    i++;
                }
                tmp[tmp_cont]='\0';
                cadena=tmp;
                if(cad[i]=='\'') i++;
                return CADENA;
            }
            
            i++;
            return ERROR_TOKEN;
        }
        
        bool analizar(){
            i=0;
            int token=0;
            std::cout << "=== ANALISIS LEXICO ===" << std::endl;
            while(true){
                token=getToken();
                if(token==FIN){
                    std::cout << "Fin del archivo alcanzado" << std::endl;
                    return true;
                }
                else if(token==VAR){
                    Atributos attr;
                    if(!ts.Buscar(variable,attr)){
                        ts.Insertar(variable,VAR,"var",null,null);
                        std::cout << "Variable reconocida: " << variable << std::endl;
                    }
                }
                else if(token==ERROR_TOKEN){
                    GestorErrores::Error(100, i);
                    return false;
                }
            }
        }
        
        void reiniciar(){
            i=0;
        }
};

#endif