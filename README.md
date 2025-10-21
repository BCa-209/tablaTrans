# tablaTrans
Flujo:

ARCHIVO → LÉXICO → TOKENS → SINTÁCTICO → AUTÓMATA → RESULTADO
               ↓           ↓           ↓
          TablaSímbolos  Errores    TablaSímbolos


g++ main.cpp analizador_lexico.h analizador_sintactico.h automata_sintactico.h gestor_errores.h tabla_simbolos.h tokens.h -o ejecutable


rm ejecutable.exe
g++ main.cpp -o ejecutable