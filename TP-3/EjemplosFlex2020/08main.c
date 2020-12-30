#include <stdio.h>
#include <stdlib.h>
#include "08scanner.h"

int main()
{
	int identificadores = 0;
	int constantes = 0;
	int numerales = 0;
	int errores = 0;
	TOKEN token;

	do {
		token = yylex();
		switch (token) {
		case ID:
			identificadores++;
			puts("identificador");
			break;
		case CTE:
			constantes++;
			puts("constante entera");
			break;
		case NUMERAL:
			numerales++;
			puts("numeral");
			break;
		case ERROR:
			errores++;
			puts("error");
			break;
		}
	} while (token != FDT);

	puts("----");
	puts("Totales:");
	printf("Identificadores %d\n", identificadores);
	printf("Constantes enteras %d\n", constantes);
	printf("Numerales %d\n", numerales);
	printf("Errores %d\n", errores);
	return EXIT_SUCCESS;
}
