/*
 * Leonardo Rafael Amado Brito
 * Numero: 2016017310
 */

#ifndef SIMULACAO_H
#define SIMULACAO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "Espaco.h"
#include "Pessoas.h"

int verificaLocal(int idlocal, Local arrayLocal[], int tamLocal);
int pesquisaSala(int idLocal, Local arrayLocal[], int tamLocal);
void emparelhaDoente(int idLocal, Local arrayLocal[], int tamLocal, ppessoas novo);
int validaId(ppessoas p, char* idP);
ppessoas adicionaDoente(ppessoas p, Local arrayLocal[], int tamArray);
int verificaIds(Local arrayLocal[], int tam, int idOrigem, int idDestino, ppessoas p);
int verificaNumPessoas(int numPessoas, Local arrayLocal[], int tamArray, ppessoas p, int idDestino, int idOrigem, int *nPessoasOrigem, int *nPessoasDestino);
ppessoas transferePessoas(ppessoas p, Local arrayLocal[], int tamArray, int totalPessoas);
float taxas(ppessoas p, char estado, int nPessoasTotal);
void percorrePessoasPorSala(ppessoas p, Local arrayLocal[], int i);
void estatistica(ppessoas p, int nPessoasTotal, Local arrayLocal[], int nSalasTotal);
void incrementaDias(ppessoas p);
void avancaIteracao(ppessoas p);
int relatorioInfo(ppessoas p, int nPessoasTotal);
int relatorioPopulacao(ppessoas p);
Pessoas* atualizaUndo(ppessoas arrayUndo[], int tam, ppessoas p);
void mostraArrayLista(ppessoas p, ppessoas arrayUndo[]);
Pessoas* undo(ppessoas arrayUndo[], int tam, ppessoas p);

#endif /* SIMULACAO_H */

