%{
#include <stdio.h>
#include <strings.h>
#include "parser.h"
char msgError[100];
%}
%option outfile="scanner.c"
%option header-file="scanner.h"
%option yylineno


letra           [[:alpha:]]
digito          [0-9]
letraDigito     [[:alnum:]]
espacio         [[:space:]]
operador        [+\-*/]
puntuacion      [\(\),;]
invalido        [[:^alnum:]]{-}[[:space:]]{-}[programa|fin-prog|declarar|leer|escribir]{-}[+\-*/]{-}[\(\),;]
 //invalido        [^letraDigito]{-}[^espacio]{-}[reservada]{-}[operador]{-}[puntuacion]   ---- Esto no funciona


%%
"programa"              {yylval = strdup(yytext); return PROGRAMA;}
"declarar"              {yylval = strdup(yytext); return DECLARAR;}
"leer"                  {yylval = strdup(yytext); return LEER;}
"escribir"              {yylval = strdup(yytext); return ESCRIBIR;}
"fin-prog"              {yylval = strdup(yytext); return FINPROG;}

{digito}+               {yylval = strdup(yytext); return CONSTANTE;}
{letra}{letraDigito}*   {yylval = strdup(yytext); return IDENTIFICADOR;}
{puntuacion}            return yytext[0];
{operador}+             return yytext[0];
"<-"                    {yylval = strdup(yytext); return ASIGNACION;}

{espacio}+              |
##.*                    ; //No hago nada: comentario, espacio o salto de linea

{digito}+({letraDigito}|{invalido})*  {
                                       yylexerrs++; 
                                       sprintf(msgError,"Error lexico - constante invalido: %s", yytext);
                                       yyerror(msgError);
                                      }

{letra}({invalido}|{letraDigito})*     {
                                       yylexerrs++; 
                                       sprintf(msgError,"Error lexico - identificador invalido: %s", yytext);
                                       yyerror(msgError);
                                       }

                                      
{invalido}+                           {
                                       yylexerrs++; 
                                       sprintf(msgError,"Error lexico - cadena invalida: %s", yytext);
                                       yyerror(msgError);
                                      }

%%