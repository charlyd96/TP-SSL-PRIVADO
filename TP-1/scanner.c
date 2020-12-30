#include <ctype.h>
#include <string.h>
#include "scanner.h"

// Declaración de la matriz que representa la tabla de transición (es global)
tipoEstado tabla[9][6];

// Retorna el tipo de token reconocido en el archivo
tipoToken scanner() 
{                       
    char caracter;
    tipoCaracter tcaracter;
    tipoEstado tEstado;
    caracter = getchar();
    tcaracter = clasificarCaracter(caracter);
    tEstado = tabla[ESTADO_INICIAL ][tcaracter];

// Mientras no haya reconocido ningun Token, sigo analizando caracteres en el archivo
    while(!estadoAceptor(tEstado)){
        caracter = getchar();
        tcaracter = clasificarCaracter(caracter);
        tEstado = tabla[tEstado][tcaracter];
    }

    // Una vez que reconocí un Token, determino cuál es evaluando en qué estado terminé
    switch(tEstado){

        case ESTADO_CONSTANTE_RECONOCIDA:
            // Vuelvo a poner el caracter leído para no perderlo (próximo token)
            ungetc(caracter,stdin); 
            return CONSTANTE;
            break;
        
        case ESTADO_IDENTIFICADOR_RECONOCIDO:
            ungetc(caracter,stdin);
            return IDENTIFICADOR;
            break;
        
        case ESTADO_NUMERAL_RECONOCIDO: 
            // En este caso no hace falta porque no hay estado "reconociendo numeral". No requiere centinela
            return NUMERAL;
            break;
        
        case ESTADO_ERROR_RECONOCIDO:
            ungetc(caracter,stdin);
            return ERROR;
            break;

        case ESTADO_EOF:
            return FINAL_ARCHIVO;
            break;

        default:; //Sólo para eliminar el warning
    }
    
    return -1; //Sólo para eliminar el warning, nunca va a salir por acá
}

// Retorna el tipo de caracter recibido
tipoCaracter clasificarCaracter(char unCaracter) 
{
    if(isalpha(unCaracter))
        return(CARACTER_LETRA);

    if (isdigit(unCaracter))
        return(CARACTER_DIGITO); 
                 
    if (isspace(unCaracter))
        return(CARACTER_ESPACIO);

    if(unCaracter == '#')
        return(CARACTER_NUMERAL);

    if(unCaracter == EOF)
        return CARACTER_FIN;

    return(OTRO);
}

// Inicializa la tabla de transición

void inicializarTabla(void) 
{
    tabla[ESTADO_INICIAL][CARACTER_DIGITO] = ESTADO_RECONOCIENDO_CONSTANTE; //1
    tabla[ESTADO_INICIAL][CARACTER_LETRA] = ESTADO_RECONOCIENDO_IDENTIFICADOR; //2
    tabla[ESTADO_INICIAL][CARACTER_NUMERAL] = ESTADO_NUMERAL_RECONOCIDO; //6
    tabla[ESTADO_INICIAL][OTRO] = ESTADO_RECONOCIENDO_ERROR; //3
    tabla[ESTADO_INICIAL][CARACTER_ESPACIO] = ESTADO_INICIAL; //0
    tabla[ESTADO_INICIAL][CARACTER_FIN] = ESTADO_EOF; //8

    tabla[ESTADO_RECONOCIENDO_CONSTANTE][CARACTER_DIGITO] = ESTADO_RECONOCIENDO_CONSTANTE; //1
    tabla[ESTADO_RECONOCIENDO_CONSTANTE][CARACTER_LETRA] = ESTADO_CONSTANTE_RECONOCIDA; //4
    tabla[ESTADO_RECONOCIENDO_CONSTANTE][CARACTER_NUMERAL] = ESTADO_CONSTANTE_RECONOCIDA; //4
    tabla[ESTADO_RECONOCIENDO_CONSTANTE][OTRO] = ESTADO_CONSTANTE_RECONOCIDA; //4
    tabla[ESTADO_RECONOCIENDO_CONSTANTE][CARACTER_ESPACIO] = ESTADO_CONSTANTE_RECONOCIDA; //4
    tabla[ESTADO_RECONOCIENDO_CONSTANTE][CARACTER_FIN] = ESTADO_CONSTANTE_RECONOCIDA; //4

    tabla[ESTADO_RECONOCIENDO_IDENTIFICADOR][CARACTER_DIGITO] = ESTADO_RECONOCIENDO_IDENTIFICADOR; //2
    tabla[ESTADO_RECONOCIENDO_IDENTIFICADOR][CARACTER_LETRA] = ESTADO_RECONOCIENDO_IDENTIFICADOR; //2
    tabla[ESTADO_RECONOCIENDO_IDENTIFICADOR][CARACTER_NUMERAL] = ESTADO_IDENTIFICADOR_RECONOCIDO; //5
    tabla[ESTADO_RECONOCIENDO_IDENTIFICADOR][OTRO] = ESTADO_IDENTIFICADOR_RECONOCIDO; //5
    tabla[ESTADO_RECONOCIENDO_IDENTIFICADOR][CARACTER_ESPACIO] = ESTADO_IDENTIFICADOR_RECONOCIDO; //2
    tabla[ESTADO_RECONOCIENDO_IDENTIFICADOR][CARACTER_FIN] = ESTADO_IDENTIFICADOR_RECONOCIDO; //2

    tabla[ESTADO_RECONOCIENDO_ERROR][CARACTER_DIGITO] = ESTADO_ERROR_RECONOCIDO; //7
    tabla[ESTADO_RECONOCIENDO_ERROR][CARACTER_LETRA] = ESTADO_ERROR_RECONOCIDO; //7
    tabla[ESTADO_RECONOCIENDO_ERROR][CARACTER_NUMERAL] = ESTADO_ERROR_RECONOCIDO; //7
    tabla[ESTADO_RECONOCIENDO_ERROR][OTRO] = ESTADO_RECONOCIENDO_ERROR; //3
    tabla[ESTADO_RECONOCIENDO_ERROR][CARACTER_ESPACIO] = ESTADO_ERROR_RECONOCIDO; //7
    tabla[ESTADO_RECONOCIENDO_ERROR][CARACTER_FIN] = ESTADO_ERROR_RECONOCIDO; //7
}

// Determina si el estado actual es aceptor o no
int estadoAceptor(tipoEstado estadoActual)
{    
    if(
       estadoActual == ESTADO_INICIAL ||
       estadoActual == ESTADO_CONSTANTE_RECONOCIDA || 
       estadoActual == ESTADO_IDENTIFICADOR_RECONOCIDO|| 
       estadoActual == ESTADO_NUMERAL_RECONOCIDO ||
       estadoActual == ESTADO_ERROR_RECONOCIDO ||
       estadoActual == ESTADO_EOF 
       )
       return 1;
    else return 0;
}