#include <string.h>
#include "symbol.h"
t_list *tablaSimbolos;

bool buscarIdentificador(char *identificador)
{
    for (int i = 0; i< tablaSimbolos->elements_count; i++)
    {
        char *identificadorLista = list_get(tablaSimbolos, i);
        if(!strcmp(identificadorLista, identificador))
        return true;
        else return false;
    }
}

void agregarIdentificador(char *identificador)
{
    list_add(tablaSimbolos, identificador);
}