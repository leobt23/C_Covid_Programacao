/*
 * Leonardo Rafael Amado Brito
 * Numero: 2016017310
 */

#include "configuracao.h"

// DISTRIBUI AS PESSOAS POR SALAS

void emparelhamento(Local *l, ppessoas p, int tamSala) { // Associa as pessoas às salas
    int numRandom;
    ppessoas aux = p; //cria um auxiliar para a lista ligada das pessoas
    plocal novo;

    if (aux == NULL)
        printf("Lista Vazia\n");
    while (aux != NULL) { //Enquanto a lista não chega ao fim
        numRandom = intUniformRnd(0, tamSala - 1); // gera um numero random da sala
        aux->lista = &l[numRandom];
        aux = aux->prox; //avançar na lista de pessoas    }
    }

}

void mostraEmparelhamento(ppessoas p) { // Mostra o resultado do emparelhamento na consola

    if (p == NULL)
        printf("Lista Vazia\n");
    else {
        printf("\n");
        while (p != NULL) {
            printf("%s\t%d\t%c\t%d\t", p->id, p->idade, p->estado, p->diasDoente);
            printf("---> Sala %d\n", p->lista->id);
            p = p->prox;
        }
        printf("\n");
    }
}

// TAXA DE DISSEMINACAO

int contaPessoasSala(ppessoas p, int idSala) { // Conta o numero de uma sala
    int contador = 0;
    ppessoas aux = p;

    if (p == NULL)
        printf("Lista Vazia\n");
    while (aux != NULL) {
        if (aux->lista->id == idSala)
            contador++;
        aux = aux->prox;
    }
    return contador;
}

int numPessoasAInfetar(int nPessoasSala) { // Devolve o numero de pessoas que vao ficar infetadas
    int contador = 0;
    for (int i = 0; i < nPessoasSala; i++) {
        if (probEvento(0.05) == 1)
            contador++;
    }
    return contador;
}

void taxaDisseminacao(ppessoas p) { // Funcao que executa a taxa de disseminacao
    int idSala, nPessoasSala, numRandom, nPessoasAInfetar, contador = 1;
    ppessoas aux = p, aux2 = p;

    if (p == NULL)
        printf("Lista Vazia\n");
    while (aux != NULL) {
        if (aux->estado == 'D') {
            idSala = aux->lista->id;
            nPessoasSala = contaPessoasSala(p, idSala); ////////
            nPessoasAInfetar = numPessoasAInfetar(nPessoasSala);
            if (nPessoasAInfetar > 0) {
                for (int i = 0; i < nPessoasAInfetar; i++) {
                    numRandom = intUniformRnd(1, nPessoasSala);
                    while (aux2 != NULL) {
                        if (contador == numRandom && aux2->lista->id == idSala) {
                            if (aux2->estado == 'S') {
                                aux2->estado = 'D';
                                aux2->diasDoente = 0;
                                printf("\nA pessoa %s foi infetada\n", aux2->id);
                                break;
                            }
                        }
                        if (contador != numRandom && aux2->lista->id == idSala)
                            contador++;
                        aux2 = aux2->prox;
                    }
                }
            }

        }
        aux = aux->prox;
    }
}



// TAXA DE IMUNIDADE

int taxaImunidade() {
    if (probEvento(0.2) == 1)
        return 1;
    else
        return 0;
}

// PROBABILIDADE DE RECUPERACAO

int probRecuperacao(ppessoas p) {
    float probIdade;
    ppessoas aux = p;

    if (p == NULL)
        printf("Lista Vazia\n");
    while (aux != NULL) {
        if (aux->estado == 'D') {
            probIdade = (float) 1 / (aux->idade);
            if (probEvento(probIdade) == 1) {
                if (taxaImunidade() == 1) {
                    aux->estado = 'I';
                    aux->diasDoente = 0;
                } else {
                    aux->estado = 'S';
                    aux->diasDoente = 0;
                }
            }
        }
        aux = aux->prox;
    }
}

// DURACAO DA INFECAO

void duracaoInfecao(ppessoas p) {
    int nDias;
    ppessoas aux = p;

    if (p == NULL)
        printf("Lista Vazia\n");
    while (aux != NULL) {
        if (aux->estado == 'D') {
            nDias = 5 + ((aux->idade) / 10);
            if (aux->diasDoente >= nDias) {
                aux->diasDoente = 0;
                aux->estado = 'S';
            }
        }
        aux = aux->prox;
    }
}

// AVANCA 1 ITERACAO

void incrementaDias(ppessoas p) { // Incrementa os dias das pessoas doentes
    ppessoas aux = p;

    if (p == NULL)
        printf("Lista Vazia\n");
    while (aux != NULL) {
        if (aux->estado == 'D')
            aux->diasDoente++;
        aux = aux->prox;
    }
}

void avancaIteracao(ppessoas p) { // Avanca uma iteracao 
    duracaoInfecao(p);
    probRecuperacao(p);
    taxaDisseminacao(p);
    incrementaDias(p);
}