#ifndef TOKENS_H
#define TOKENS_H

// Enumeración de tokens para el lenguaje de sistemas embebidos
#define ALGORITMO       0
#define CONFIGURACION   1
#define CIRCUITO        2
#define FIN             3
#define NUMPIN          4
#define DECIMAL         5
#define NUMERO          6
#define SALIDA          7
#define CONFIGURAR      8
#define ENCENDER        9
#define APAGAR          10
#define ESPERAR         11
#define REPETIR         12
#define VECES           13
#define SI              14
#define SINO            15
#define LEER_SENSOR     16
#define INTENSIDAD      17
#define CONFIGURAR_PIN  18

// Operadores y delimitadores
#define IGUAL           19
#define PCOMA           20
#define COMA            21
#define APARENTESIS     22
#define CPARENTESIS     23
#define DOSPUNTOS       24
#define MAYOR           25
#define MENOR           26
#define MAS             27
#define MENOS           28
#define POR             29
#define DIVIDIDO        30

// Identificadores y literales
#define VAR             31
#define NUM             32
#define CADENA          33
#define COMENTARIO      34

#define FIN_ARCHIVO     666
#define ERROR_TOKEN     999

#define null "NULL"
#define vacio "-"
#define asignado "asignado"

#endif