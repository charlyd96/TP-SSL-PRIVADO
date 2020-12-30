#include <stdio.h>
#include <stdlib.h>
#include "scanner.h" // header generado por flex
#include "parser.h"

extern int yynerrs;
int yylexerrs = 0; // Variable de errores que uso en flex

int main() {

	
	switch( yyparse() ){
	case 0:
		puts("Compilación terminada con éxito");
		printf("Errores sintácticos: %d\nErrores léxicos: %d\n", yynerrs, yylexerrs);
		return 0;
	case 1:
		puts("Error de compilación"); 
		printf("Errores sintácticos: %d\nErrores léxicos: %d\n", yynerrs, yylexerrs);
		return 1;
	case 2:
		puts("Memoria insuficiente"); 
		return 2;
	}
	return 0;
}

/* Informa la ocurrencia de un error. */
void yyerror(const char *s){
	printf("línea #%d: %s\n", yylineno, s);
	return;
}