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

bool crearArchivoPuerta(){
    ofstream archivo("puerta.emb");
    if (!archivo.is_open()){
        cout << "Error: No se pudo crear el archivo puerta.emb" << endl;
        return false;
    }
    
    archivo << "# ================================================\n";
    archivo << "# PUERTA DE GARAGE AUTOMATICA\n";
    archivo << "# Parpadea 5 veces y hace pausa larga\n";
    archivo << "# ================================================\n\n";
    
    archivo << "incluir libreria \"servo.h\"\n\n";
    
    archivo << "configuracion:\n";
    archivo << "    numpin trigger = 9;\n";
    archivo << "    numpin echo = 10;\n";
    archivo << "    numpin servo_pin = 6;\n\n";
    
    archivo << "    configurar (trigger,salida);\n";
    archivo << "    configurar (echo,entrada);\n\n";
    
    archivo << "    decimal distancia_maxima = 20.0;\n\n";
    
    archivo << "    servo puerta;\n";
    archivo << "    conectar.puerta(servo_pin);\n";
    archivo << "    estado.puerta(0);\n";
    archivo << "fin\n\n";
    
    archivo << "circuito:\n";
    archivo << "    apagar(trigger);\n";
    archivo << "    esperar(2);\n";
    archivo << "    encender(trigger);\n";
    archivo << "    esperar(10);\n";
    archivo << "    apagar(trigger);\n\n";
    
    archivo << "    numero duracion = pulso.echo;\n";
    archivo << "    numero distancia = duracion * 0.034/2;\n\n";
    
    archivo << "    si:\n";
    archivo << "        distancia < distancia_maxima:\n";
    archivo << "        estado.puerta(90);\n";
    archivo << "    fin\n";
    archivo << "    sino:\n";
    archivo << "        estado.puerta(0);\n";
    archivo << "    fin\n";
    archivo << "fin";
    
    archivo.close();
    
    // Verificar que se escribió correctamente
    ifstream verificar("puerta.emb");
    if (!verificar.is_open()) {
        cout << "Error: No se pudo verificar el archivo creado" << endl;
        return false;
    }
    
    string linea;
    int lineCount = 0;
    while (getline(verificar, linea)) {
        lineCount++;
    }
    verificar.close();
    
    cout << "Archivo 'puerta.emb' creado automaticamente con " << lineCount << " lineas" << endl;
    return lineCount > 0;
}

bool leerArchivoPuerta(char buffer[]){
    ifstream archivo("puerta.emb");
    if (!archivo.is_open()){
        cout << "No se pudo abrir el archivo puerta.emb" << endl;
        return false;
    }
    archivo.get(buffer, 9999, '\0');
    archivo.close();
    cout << "Archivo 'puerta.emb' cargado exitosamente" << endl;
    return true;
}

int main(){
    char codigo[10000];
    
    cout << "=== ANALIZADOR DE LENGUAJE PARA SISTEMAS EMBEBIDOS ===" << endl;
    cout << "Archivo: puerta.emb" << endl;
    
    if(!leerArchivoPuerta(codigo)){
        cout << "Creando archivo puerta.emb..." << endl;
        if(!crearArchivoPuerta()){
            return 1;
        }
        if(!leerArchivoPuerta(codigo)){
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