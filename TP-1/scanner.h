#pragma once
#include <stdio.h>

static int pepe;
typedef enum{
    CONSTANTE,
    IDENTIFICADOR,
    NUMERAL,
    ERROR,
    FINAL_ARCHIVO
} tipoToken;

typedef enum{
    CARACTER_DIGITO,
    CARACTER_LETRA,
    CARACTER_NUMERAL,
    CARACTER_ESPACIO,
    OTRO,
    CARACTER_FIN
} tipoCaracter;

typedef enum{
    ESTADO_INICIAL,                     //0-
    ESTADO_RECONOCIENDO_CONSTANTE,      //1
    ESTADO_RECONOCIENDO_IDENTIFICADOR,  //2
    ESTADO_RECONOCIENDO_ERROR,          //3
    ESTADO_CONSTANTE_RECONOCIDA,        //4+
    ESTADO_IDENTIFICADOR_RECONOCIDO,    //5+
    ESTADO_NUMERAL_RECONOCIDO,          //6+
    ESTADO_ERROR_RECONOCIDO,            //7+
    ESTADO_EOF,                         //8+
} tipoEstado;

tipoToken scanner(void);
tipoCaracter clasificarCaracter(char unCaracter);
void inicializarTabla(void);
int estadoAceptor(tipoEstado estadoActual);

