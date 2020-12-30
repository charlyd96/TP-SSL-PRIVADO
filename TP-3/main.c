#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

int main()
{
	TOKEN token;

	do {
		token = yylex();
		switch (token) {

		case IDENTIFICADOR:
			printf("Token: identificador - lexema: %s\n", yytext);
			break;

		case CONSTANTE:
			printf("Token: constante - lexema: %s\n", yytext);
			break;

		case PUNTUACION:
		case OPERADOR:
			printf("Token: %c\n", yytext[0]); //Lo imprimo como char
			break;

		case RESERVADA:
			printf("Token: %s\n", yytext);
			break;

		case ASIGNACION:
			printf("Token: asignacion");
			break;
		}
	} while (token != FDT);

	printf("fin");
	return EXIT_SUCCESS;
}
