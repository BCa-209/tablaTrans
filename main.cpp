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

bool crearArchivoTemperatura(){
    ofstream archivo("temperatura.emb");
    if (!archivo.is_open()){
        cout << "Error: No se pudo crear el archivo temperatura.emb" << endl;
        return false;
    }
    
    archivo << "# ================================================\n";
    archivo << "# CONTROL DE TEMPERATURA CON VENTILADOR\n";
    archivo << "# Sistema de enfriamiento proporcional\n";
    archivo << "# ================================================\n\n";
    
    archivo << "configuracion:\n";
    archivo << "    numpin sensor_temperatura = A0;\n";
    archivo << "    numpin motor_ventilador = 9;\n";
    archivo << "    decimal temperatura_maxima = 30.0;\n";
    archivo << "    \n";
    archivo << "    configurar(motor_ventilador, salida);\n";
    archivo << "fin\n\n";
    
    archivo << "circuito:\n";
    archivo << "    # Leer sensor de temperatura (LM35)\n";
    archivo << "    numero lectura = leer_sensor(sensor_temperatura);\n";
    archivo << "    decimal temperatura = lectura * 0.48828125;\n";
    archivo << "    \n";
    archivo << "    si:\n";
    archivo << "        temperatura > temperatura_maxima:\n";
    archivo << "        encender(motor_ventilador);\n";
    archivo << "    fin\n";
    archivo << "    sino:\n";
    archivo << "        apagar(motor_ventilador);\n";
    archivo << "    fin\n";
    archivo << "    \n";
    archivo << "    esperar(1000);\n";
    archivo << "fin\n";
    
    archivo.close();
    cout << "Archivo 'temperatura.emb' creado automaticamente" << endl;
    return true;
}

bool leerArchivoSemaforo(char buffer[]){
    ifstream archivo("temperatura.emb");
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
        if(!crearArchivoTemperatura()){
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