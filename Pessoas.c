/*
 * Leonardo Rafael Amado Brito
 * Numero: 2016017310
 */

#include "Pessoas.h"

void mostraPessoas(ppessoas p) { // Mostra na consola as Pessoas

    ppessoas aux = p;
    if (aux == NULL)
        printf("Lista Vazia\n");
    else {
        printf("\n");
        while (aux != NULL) {
            printf("%s\t%d\t%c\t%d\t\n", aux->id, aux->idade, aux->estado, aux->diasDoente);
            aux = aux->prox;
        }
        printf("\n");
    }
}

Pessoas* LerDadosPessoas(int *total2) { // Passa os dados do ficheiro binario para uma lista ligada
    int linha[200];
    Pessoas *p = NULL, *aux = NULL, *aux2 = NULL;
    char fichPessoas[20];
    int h = 0;
    FILE *f;

    printf("Nome do ficheiro: ");
    scanf("%s", &fichPessoas);

    aux = (Pessoas*) malloc(sizeof (Pessoas));
    if (aux == NULL) {
        printf("Erro na alocacao de memoria");
        *total2 = 0;
        return NULL;
    }

    f = fopen(fichPessoas, "rt");
    if (f == NULL) {
        printf("Erro ao abrir o ficheiro");
        return NULL;
    }

    while (fscanf(f, " %s %d %c", &aux->id, &aux->idade, &aux->estado) == 3) {

        if (aux->estado != 'D') {
            aux->diasDoente = 0;
        } else {
            fscanf(f, "%d", &aux->diasDoente);
        }

        aux->lista = NULL;

        if (p == NULL && aux2 == NULL) {
            p = aux;
            aux2 = aux;
        } else {
            aux2 -> prox = aux;
            aux2 = aux2 -> prox;
        }
        aux2 -> prox = NULL;

        aux = (Pessoas*) malloc(sizeof (Pessoas));

        h++;
    }

    *total2 = h;

    fclose(f);
    return p;
}

void freePessoas(ppessoas p) { // Liberta as pessoas todas no final do programa
    ppessoas auxp;

    while (p != NULL) {
        auxp = p;
        p = p->prox;
        free(auxp);
    }
}