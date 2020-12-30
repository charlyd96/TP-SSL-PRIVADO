#include "scanner.h"

int main (void){

    int cantidadIdentificadores=0;
    int cantidadConstantes=0;
    int cantidadNumerales=0;
    int cantidadErrores=0;
    inicializarTabla();
    tipoToken tokenObtenido;

    do {
        tokenObtenido = scanner();

        switch (tokenObtenido){

            case CONSTANTE: 
                cantidadConstantes++;
                printf("Constante entera\n");
                break;
            
            case IDENTIFICADOR: 
                cantidadIdentificadores++;
                printf("Identificador\n");
                break;
            
            case NUMERAL: 
                cantidadNumerales++;
                printf("Numeral\n");
                break;
            
            case ERROR: 
                cantidadErrores++;
                printf("Error\n");
                break;
            

            default: ; //Sólo para eliminar el warning
        }
    } while (tokenObtenido != FINAL_ARCHIVO);

    printf("********Fin archivo********\nTotales:\n");
    printf("Identificadores: %d\n", cantidadIdentificadores);
    printf("Constantes: %d\n", cantidadConstantes);
    printf("Numerales: %d\n", cantidadNumerales);
    printf("Errores: %d\n", cantidadErrores);

    return 0;
}
