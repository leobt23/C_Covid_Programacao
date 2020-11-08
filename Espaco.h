/*
 * Leonardo Rafael Amado Brito
 * Numero: 2016017310
 */

#ifndef ESPACO_H
#define ESPACO_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>


typedef struct Sala Local, *plocal;

struct Sala {
    int id; // id numérico do local
    int capacidade; // capacidade máxima
    int liga[3]; // id das ligações (-1 nos casos não usados)
};

void mostra_local(Local *esp, int total);
Local* lerDadosLocal(int *total);

#endif /* ESPACO_H */

