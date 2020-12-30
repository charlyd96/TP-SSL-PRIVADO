%top{
#include "tokens.h"
}
%option outfile="scanner.c"
%option header-file="scanner.h"


letra           [[:alpha:]]
digito          [0-9]
letraDigito     [[:alnum:]]
espacio         [[:space:]]
operador        [+\-*/]
puntuacion      [\(\),;]
reservada       programa|fin-prog|declarar|leer|escribir         
invalido        [[:^alnum:]]{-}[[:space:]]{-}[programa|fin-prog|declarar|leer|escribir]{-}[+\-*/]{-}[\(\),;]
 //invalido        [^letraDigito]{-}[^espacio]{-}[reservada]{-}[operador]{-}[puntuacion]   ---- Esto no funciona


%%
{reservada}             return RESERVADA; //Al inicio para que tenga mas prioridad
{digito}+               return CONSTANTE;
{letra}{letraDigito}*   return IDENTIFICADOR;
{puntuacion}            return PUNTUACION;
{operador}+             return OPERADOR;
"<-"                    return ASIGNACION;

{espacio}+              |
##.*                    ; //No hago nada: comentario, espacio o salto de linea

{digito}+({letraDigito}|{invalido})*         printf("Error lexico - constante invalida: %s\n", yytext);
{letra}({invalido}|{letraDigito})*           printf("Error lexico - identificador invalido: %s\n", yytext);
{invalido}+                                  printf("Error lexico - cadena incorrecta: %s\n", yytext);



