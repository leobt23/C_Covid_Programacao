/*
 * Leonardo Rafael Amado Brito
 * Numero: 2016017310
 */

#ifndef CONFIGURACAO_H
#define CONFIGURACAO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "Espaco.h"
#include "Pessoas.h"



void emparelhamento(Local *l, ppessoas p, int tamSala);
void mostraEmparelhamento(ppessoas p);
int contaPessoasSala(ppessoas p, int idSala);
int numPessoasAInfetar(int nPessoasSala);
void taxaDisseminacao(ppessoas p);
int taxaImunidade();
int probRecuperacao(ppessoas p);
void duracaoInfecao(ppessoas p);


#endif /* CONFIGURACAO_H */

