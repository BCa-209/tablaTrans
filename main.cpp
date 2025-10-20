#include <iostream>
#include <fstream>
#include <cstring>
#include "tabla_simbolos.h"
#include "analizador_lexico.h"
#include "analizador_sintactico.h"

bool crearArchivoEjemplo(){
    std::ofstream archivo("estadisticos1.est");
    if (!archivo.is_open()){
        std::cout << "Error: No se pudo crear el archivo estadisticos1.est" << std::endl;
        return false;
    }
    
    archivo << "estadisticas()\n";
    archivo << "{\n";
    archivo << "    a=10;\n";
    archivo << "    b=5;\n";
    archivo << "    c=19;\n";
    archivo << "    d=20;\n";
    archivo << "    desviacionest(2,3,15,a);\n";
    archivo << "    media(c,d,b,20);\n";
    archivo << "}\n";
    
    archivo.close();
    std::cout << "Archivo 'estadisticos1.est' creado automaticamente" << std::endl;
    return true;
}

bool leerArchivo(const char direccion[], char buffer[]){
    std::ifstream archivo(direccion);
    if (!archivo.is_open()){
        std::cout << "No se pudo abrir el archivo " << direccion << std::endl;
        std::cout << "Creando archivo de ejemplo..." << std::endl;
        return false;
    }
    archivo.get(buffer, 999, '\0');
    archivo.close();
    std::cout << "Archivo cargado exitosamente" << std::endl;
    return true;
}

int main(){
    char codigo[1000];
    
    std::cout << "=== ANALIZADOR DE LENGUAJE ESTADISTICO ===" << std::endl;
    
    if(!leerArchivo("estadisticos1.est", codigo)){
        if(!crearArchivoEjemplo()){
            return 1;
        }
        if(!leerArchivo("estadisticos1.est", codigo)){
            return 1;
        }
    }
    
    std::cout << "Contenido: " << codigo << std::endl;
    
    // Inicializar componentes
    TablaSimbolos ts;
    ts.InicializarPalabrasClave();
    
    AnalizadorLexico lexico(codigo, ts);
    AnalizadorSintactico sintactico(lexico);
    
    std::cout << "\nIniciando analisis..." << std::endl;
    
    if(lexico.analizar()){
        std::cout << "\nAnalisis Lexico: EXITOSO" << std::endl;
        ts.Mostrar();
        
        if(sintactico.analizar()){
            std::cout << "\nAnalisis Sintactico: EXITOSO" << std::endl;
        } else {
            std::cout << "\nAnalisis Sintactico: FALLIDO" << std::endl;
        }
    } else {
        std::cout << "\nAnalisis Lexico: FALLIDO" << std::endl;
    }

    std::cout << "\nPresione una tecla para continuar . . .";
    std::cin.get();
    return 0;
}