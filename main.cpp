#include <iostream>
#include <fstream>
#include <cstring>
#include "tabla_simbolos.h"
#include "analizador_lexico.h"
#include "analizador_sintactico.h"
#include "automata_sintactico.h"
#include "gestor_errores.h"
#include "tokens.h"
using namespace std;

bool crearArchivoSemaforo(){
    ofstream archivo("semaforo.emb");
    if (!archivo.is_open()){
        cout << "Error: No se pudo crear el archivo semaforo.emb" << endl;
        return false;
    }
    
    archivo << "# algoritmo semaforo (comentario)\n";
    archivo << "\n";
    archivo << "configuracion:\n";
    archivo << "    numpin led_rojo = 13;\n";
    archivo << "    numpin led_amarillo = 12;\n";
    archivo << "    numpin led_verde = 11;\n";
    archivo << "    \n";
    archivo << "    configurar (13, salida);\n";
    archivo << "    configurar (12, salida);\n";
    archivo << "    configurar (11, salida);\n";
    archivo << "fin\n";
    archivo << "\n";
    archivo << "circuito:\n";
    archivo << "    \n";
    archivo << "    encender(led_rojo); \n";
    archivo << "    esperar(5000);\n";
    archivo << "    apagar(led_verde);\n";
    archivo << "    \n";
    archivo << "    encender(12);\n";
    archivo << "    esperar(2000);\n";
    archivo << "    apagar(12);\n";
    archivo << "    \n";
    archivo << "    encender(13);\n";
    archivo << "    esperar(5000);\n";
    archivo << "    apagar(13);\n";
    archivo << "    \n";
    archivo << "    encender(12);\n";
    archivo << "    esperar(1000);\n";
    archivo << "    apagar(12);\n";
    archivo << "fin\n";
    
    archivo.close();
    cout << "Archivo 'semaforo.emb' creado automaticamente" << endl;
    return true;
}

bool leerArchivoSemaforo(char buffer[]){
    ifstream archivo("semaforo.emb");
    if (!archivo.is_open()){
        cout << "No se pudo abrir el archivo semaforo.emb" << endl;
        return false;
    }
    archivo.get(buffer, 9999, '\0');
    archivo.close();
    cout << "Archivo 'semaforo.emb' cargado exitosamente" << endl;
    return true;
}

int main(){
    char codigo[10000];
    
    cout << "=== ANALIZADOR DE LENGUAJE PARA SISTEMAS EMBEBIDOS ===" << endl;
    cout << "Archivo: semaforo.emb" << endl;
    
    if(!leerArchivoSemaforo(codigo)){
        cout << "Creando archivo semaforo.emb..." << endl;
        if(!crearArchivoSemaforo()){
            return 1;
        }
        if(!leerArchivoSemaforo(codigo)){
            return 1;
        }
    }
    
    cout << "Contenido cargado (" << strlen(codigo) << " caracteres)" << endl;
    cout << "\n=== CONTENIDO DEL ARCHIVO ===" << endl;
    cout << codigo << endl;
    cout << "===============================" << endl;
    
    // Inicializar componentes
    TablaSimbolos ts;
    ts.InicializarPalabrasClave();
    
    AnalizadorLexico lexico(codigo, ts);
    
    cout << "\nIniciando analisis lexico..." << endl;
    
    if(lexico.analizar()){
        cout << "\nAnalisis Lexico: EXITOSO" << endl;
        cout << "\n=== TABLA DE SIMBOLOS ===" << endl;
        ts.Mostrar();
        
        // Análisis sintáctico
        AnalizadorSintactico sintactico(lexico);
        
        cout << "\nIniciando analisis sintactico..." << endl;
        if(sintactico.analizar()){
            cout << "\nAnalisis Sintactico: EXITOSO" << endl;
        } else {
            cout << "\nAnalisis Sintactico: FALLIDO" << endl;
        }
    } else {
        cout << "\nAnalisis Lexico: FALLIDO" << endl;
    }

    cout << "\nPresione una tecla para continuar . . .";
    cin.get();
    return 0;
}   