%code top{
#include <stdio.h>
#include "scanner.h"
}
%code provides{
void yyerror(const char *);
extern int yylexerrs;
}
%define parse.error verbose

%defines "parser.h"
%output "parser.c"

%token IDENTIFICADOR CONSTANTE PROGRAMA FINPROG DECLARAR LEER ESCRIBIR
%token ASIGNACION "<-"

%left '-' '+'
%left '*' '/'
%precedence NEG

%define api.value.type {char *}

%%
objetivo: 
        PROGRAMA lista-sentencias FINPROG { 
        if (yynerrs || yylexerrs) YYABORT; 
        else YYACCEPT;
        } ;

lista-sentencias: 
        lista-sentencias sentencia |  
        %empty 
        ;

sentencia: 
        DECLARAR IDENTIFICADOR ';' {printf("declarar %s\n", $2);} | 
        IDENTIFICADOR "<-" expresion ';' {puts("asignación");} | 
        LEER '(' lista-identificadores ')' ';' {puts("leer");} | 
        ESCRIBIR '(' lista-expresiones ')' ';' {puts("escribir");} | 
        error ';' ;

lista-identificadores: 
        lista-identificadores ',' IDENTIFICADOR | 
        IDENTIFICADOR ; 
  
lista-expresiones: 
        lista-expresiones ',' expresion | 
        expresion
        ;

expresion: 
        expresion '+' expresion {puts("suma");}| 
        expresion '-' expresion {puts("resta");}| 
        expresion '*' expresion {puts("multiplicación");}| 
        expresion '/' expresion {puts("división");}| 
        '-' expresion %prec NEG {puts("inversión");}| 
        IDENTIFICADOR | 
        CONSTANTE | 
        '(' expresion ')' {puts("paréntesis");}
        ;
%%