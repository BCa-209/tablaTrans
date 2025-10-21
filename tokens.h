#ifndef TOKENS_H
#define TOKENS_H

// Enumeración de tokens para el lenguaje de sistemas embebidos
#define KW_SETUP        1
#define KW_LOOP         2
#define KW_END          3
#define KW_PIN          4
#define KW_FLOAT        5
#define KW_INT          6
#define SALIDA          7
#define CONFIGURAR      8
#define ENCENDER        9
#define APAGAR          10
#define ESPERAR         11
#define KW_FOR          12
#define KW_TIME         13
#define KW_IF           14
#define KW_ELSE         15
#define LEER_SENSOR     16
#define INTENSIDAD      17
#define CONFIGURAR_PIN  18

// NUEVOS TOKENS PARA SERVO Y SENSOR ULTRASÓNICO
#define INCLUIR         35
#define LIBRERIA        36
#define ENTRADA         37
#define SERVO           38
#define CONECTAR        39
#define ESTADO          40
#define PULSO           41
#define TRIGGER         42
#define ECHO            43
#define PUNTO           44

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