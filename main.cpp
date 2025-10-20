#include "analizador_lexico.h"
#include "analizador_sintactico.h"
#include "gestor_errores.h"
#include <fstream>

int main() {
    // 1. Inicializar componentes
    TablaSimbolos ts;
    ts.InicializarPalabrasClave();  // Nuevo método para cargar palabras clave
    
    // 2. Cargar código
    char codigo[1000];
    // ... cargar desde archivo o usar string literal
    
    // 3. Análisis léxico
    AnalizadorLexico lexico(codigo, ts);
    if(!lexico.analizar()) {
        return 1;
    }
    
    // 4. Análisis sintáctico  
    AnalizadorSintactico sintactico(lexico);
    if(!sintactico.analizar()) {
        return 1;
    }
    
    // 5. Mostrar resultados
    ts.Mostrar();
    
    return 0;
}