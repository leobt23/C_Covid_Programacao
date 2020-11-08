/*
 * Leonardo Rafael Amado Brito
 * Numero: 2016017310
 */

#ifndef PESSOAS_H
#define PESSOAS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "Espaco.h"

typedef struct pess Pessoas, *ppessoas;

struct pess {
    char id[50];
    int idade;
    char estado;
    int diasDoente;
    ppessoas prox;
    plocal lista;
};

void mostraPessoas(ppessoas p);
Pessoas* LerDadosPessoas(int *total2);
void freePessoas(ppessoas p);


#endif /* PESSOAS_H */

