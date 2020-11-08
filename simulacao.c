/*
 * Leonardo Rafael Amado Brito
 * Numero: 2016017310
 */

#include "simulacao.h"

// ADICIONA DOENTE

int verificaLocal(int idlocal, Local arrayLocal[], int tamLocal) { // Verifica se o local tem capacidade para receber pessoas
    int i;
    for (i = 0; i < tamLocal; i++) {
        if (idlocal == arrayLocal[i].id) {
            if (arrayLocal[i].capacidade > 0)
                return 1;
            else
                return 0;
        }
    }
    return 0;
}

int pesquisaSala(int idLocal, Local arrayLocal[], int tamLocal) { // Encontra a sala que procuramos
    int i;
    for (i = 0; i < tamLocal; i++) {
        if (idLocal == arrayLocal[i].id)
            return i;
    }
}

void emparelhaDoente(int idLocal, Local arrayLocal[], int tamLocal, ppessoas novo) { // Associa a pessoa doente ao local

    int posSala = pesquisaSala(idLocal, arrayLocal, tamLocal);

    novo->lista = &arrayLocal[posSala];

}

int validaId(ppessoas p, char* idP) { // Verifica se o ID existe
    ppessoas aux = p;

    if (p == NULL)
        printf("Lista Vazia\n");
    while (aux != NULL) {

        if (strcmp(idP, aux->id) == 0)
            return 0;
        aux = aux->prox;
    }
    return 1;
}

ppessoas adicionaDoente(ppessoas p, Local arrayLocal[], int tamArray) { // Adiciona um doente a uma sala
    int idDoLocal;
    ppessoas novo = NULL;
    ppessoas aux = p;
    novo = (Pessoas*) malloc(sizeof (Pessoas));
    do {
        printf("\nId pessoa: ");
        scanf("%s", &novo->id);
    } while (validaId(p, novo->id) == 0);
    do {
        printf("\nIdade: ");
        scanf("%d", &novo->idade);
    } while (novo->idade <= 0);
    do {
        printf("\nNumero de dias de infecao: ");
        scanf("%d", &novo->diasDoente);
    } while (novo->diasDoente < 0 || novo->diasDoente >= (5 + (novo->idade) / 10));
    do {
        printf("\nId do local");
        scanf("%d", &idDoLocal);
    } while (verificaLocal(idDoLocal, arrayLocal, tamArray) == 0); // funcao verificaLocal       mandar array local
    novo->estado = 'D';
    novo->prox = NULL;
    // 
    //emparelhar
    emparelhaDoente(idDoLocal, arrayLocal, tamArray, novo);

    if (p == NULL)
        printf("Lista Vazia\n");
    while (aux->prox != NULL)
        aux = aux->prox;
    aux->prox = novo;

    return p;
}

// TRANSFERE PESSOAS

int verificaIds(Local arrayLocal[], int tam, int idOrigem, int idDestino, ppessoas p) {
    int i, k, flag = 0;
    ppessoas aux = p;

    if (p == NULL)
        printf("Lista Vazia\n");
    while (aux != NULL) {
        if (aux->lista->id == idOrigem)
            for (int j = 0; j < 3; j++)
                if (aux->lista->liga[j] == idDestino)
                    flag = 1;
        if (flag != 1 && aux->lista->id == idOrigem)
            return 0;
        aux = aux->prox;
    }

    for (i = 0; i < tam; i++) {
        if (arrayLocal[i].id == idOrigem)
            for (k = 0; k < tam; k++) {
                if (arrayLocal[k].id == idDestino)
                    return 1;
            }
    }
    return 0;
}

int verificaNumPessoas(int numPessoas, Local arrayLocal[], int tamArray, ppessoas p, int idDestino, int idOrigem, int *nPessoasOrigem, int *nPessoasDestino) {
    // Verifica o numero de pessoas na sala de origem e a de destino e atualiza a capacidade
    int capacidadeDestino;
    plocal salaOrigem = NULL, salaDestino = NULL;
    ppessoas aux = p;

    if (idOrigem == idDestino)
        return 0;

    if (p == NULL)
        printf("Lista Vazia\n");
    while (aux != NULL) {
        if (aux->lista->id == idOrigem)
            (*nPessoasOrigem)++;
        if (aux->lista->id == idDestino)
            (*nPessoasDestino)++;
        aux = aux->prox;
    }

    for (int i = 0; i < tamArray; i++) {
        if (arrayLocal[i].id == idDestino) {
            capacidadeDestino = arrayLocal[i].capacidade;
            salaDestino = &arrayLocal[i];
        }
        if (arrayLocal[i].id == idOrigem)
            salaOrigem = &arrayLocal[i];
    }

    if (*nPessoasOrigem < numPessoas || numPessoas > capacidadeDestino) {
        return 0;
    } else {
        salaDestino->capacidade -= numPessoas;
        salaOrigem->capacidade += numPessoas;
        return 1;

    }
}

ppessoas transferePessoas(ppessoas p, Local arrayLocal[], int tamArray, int totalPessoas) { // Transfere pessoas para outro local
    int i, idOrigem, idDestino, j, numPessoas, numRandom, k, posId, nPessoasOrigem = 0, nPessoasDestino = 0;
    ppessoas aux = p;

    do {
        printf("Id do local de origem: "); // Pede id do local de origem e de destino
        scanf("%d", &idOrigem);
        printf("Id do local de destino: ");
        scanf("%d", &idDestino);
    } while (verificaIds(arrayLocal, tamArray, idOrigem, idDestino, p) == 0); //Verifica se os ids existem

    do {
        printf("Numero de pessoas: "); //Pede o numero de pessoas  
        scanf("%d", &numPessoas);
    } while (verificaNumPessoas(numPessoas, arrayLocal, tamArray, p, idDestino, idOrigem, &nPessoasOrigem, &nPessoasDestino) == 0); // Numero de pessoas menor do que as que existem na sala
    for (i = 0; i < numPessoas; i++) { //Percorrer caso a cso de pessoas
        numRandom = intUniformRnd(0, nPessoasOrigem - 1); //Gerar um numero random
        if (p == NULL)
            printf("Lista Vazia\n");
        while (aux != NULL) { //Encontar a pessoa random
            int contador = 0;
            if (aux->lista->id == idOrigem) {
                if (contador == numRandom)
                    break;
                contador++;
            }
            aux = aux->prox;
        }
        for (k = 0; k < tamArray; k++) {
            if (arrayLocal[k].id == idDestino)
                posId = k;
        }
        aux->lista = &arrayLocal[posId]; //Associar o novo local à pessoa
        nPessoasOrigem--;
    }
    return p;
}

// APRESENTA ESTATISTICA

float taxas(ppessoas p, char estado, int nPessoasTotal) { //Funcao generica para calcular taxas
    int contador = 0;
    float taxa;
    ppessoas aux = p;

    if (p == NULL)
        printf("Lista Vazia\n");
    while (aux != NULL) {
        if (aux->estado == estado) {
            contador++;
        }
        aux = aux->prox;
    }

    taxa = (float) contador / nPessoasTotal * 100;

    return taxa;
}

void percorrePessoasPorSala(ppessoas p, Local arrayLocal[], int i) { //Mostra as pessoas por sala
    ppessoas aux = p;

    if (p == NULL)
        printf("Lista Vazia\n");
    while (aux != NULL) {
        if (aux->lista->id == arrayLocal[i].id) {
            printf("%s\t%d\t%c\t%d\n", aux->id, aux->idade, aux->estado, aux->diasDoente);

        }
        aux = aux->prox;
    }
}

void estatistica(ppessoas p, int nPessoasTotal, Local arrayLocal[], int nSalasTotal) { // Apresenta estatistica
    ppessoas aux = p;

    if (aux == NULL)
        printf("Lista Vazia\n");
    else {
        for (int i = 0; i < nSalasTotal; i++) {
            printf("Sala %d: \n", i + 1);
            percorrePessoasPorSala(p, arrayLocal, i);
            printf("\n\n");
        }
    }

    float tDoente, tImune, tSaudavel, tNaoInfetados;
    tDoente = taxas(p, 'D', nPessoasTotal);
    printf("\nDoentes: %.2f", tDoente);
    tImune = taxas(p, 'I', nPessoasTotal);
    printf("\nImunes: %.2f", tImune);
    tSaudavel = taxas(p, 'S', nPessoasTotal);
    printf("\nSaudaveis: %.2f\n\n", tSaudavel);
    tNaoInfetados = tImune + tSaudavel;
    printf("\nNao infetados: %.2f\n\n", tNaoInfetados);
}

// APRESENTA RELATORIOS FINAIS

int relatorioInfo(ppessoas p, int nPessoasTotal) { // Imprime no ficheiro texto o relatorio "Report"

    FILE *f;

    f = fopen("report.txt", "wt");
    if (f == NULL) {
        printf("Erro ao abrir o ficheiro");
        return 0;
    }

    float tDoente, tImune, tSaudavel, tNaoInfetados;
    tDoente = taxas(p, 'D', nPessoasTotal);
    fprintf(f, "\nDoentes: %.2f", tDoente);
    tImune = taxas(p, 'I', nPessoasTotal);
    fprintf(f, "\nImunes: %.2f", tImune);
    tSaudavel = taxas(p, 'S', nPessoasTotal);
    fprintf(f, "\nSaudaveis: %.2f", tSaudavel);
    tNaoInfetados = tImune + tSaudavel;
    fprintf(f, "\nNao infetados: %.2f", tNaoInfetados);

    printf("\nO relatorio com dados dos programa foi adicionado com sucesso\n");
    fclose(f);
}

int relatorioPopulacao(ppessoas p) { // Imprime no ficheiro texto o relatório com as informacoes da populacao

    char nomeFich[20];
    FILE *f;

    printf("Nome do ficheiro para guardar a populacao: ");
    scanf("%s", &nomeFich);

    f = fopen(nomeFich, "wt");
    if (f == NULL) {
        printf("Erro ao abrir o ficheiro");
        return 0;
    }

    ppessoas aux = p;
    if (aux == NULL)
        printf("Lista Vazia\n");
    else {
        if (p == NULL)
            printf("Lista Vazia\n");
        while (aux != NULL) {
            fprintf(f, "%s\t%d\t%c\t%d\t\n", aux->id, aux->idade, aux->estado, aux->diasDoente);
            aux = aux->prox;
        }
    }
    printf("O relatorio %s foi adicionado com sucesso", nomeFich);

    fclose(f);
}

Pessoas* atualizaUndo(ppessoas arrayUndo[], int tam, ppessoas p) {
    ppessoas auxArray = NULL, primeiraPessoa = NULL, ultimaPessoa = NULL;
    ppessoas aux = p;

    for (int i = 2; 0 < i; i--) {
        arrayUndo[i] = arrayUndo[i - 1];
    }

    while (aux != NULL) { // Copiar a info da lista principal para a primeira posicao do array de Listas ligadas
        auxArray = malloc(sizeof (Pessoas));
        if (auxArray == NULL)
            printf("Lista a NULL");

        strcpy(auxArray->id, aux->id);
        auxArray->idade = aux->idade;
        auxArray->estado = aux->estado;
        auxArray->diasDoente = aux->diasDoente;
        auxArray->lista = aux->lista;

        if (primeiraPessoa == NULL) {
            primeiraPessoa = auxArray;
            ultimaPessoa = auxArray;
        } else {
            ultimaPessoa->prox = auxArray;
            ultimaPessoa = ultimaPessoa->prox;
        }
        ultimaPessoa->prox = NULL;
        aux = aux->prox;
    }
    return primeiraPessoa;
}

void mostraArrayLista(ppessoas p, ppessoas arrayUndo[]) {
    ppessoas aux = p;
    ppessoas auxArray;

    for (int i = 0; i < 3; i++) {
        auxArray = arrayUndo[i];
        while (auxArray != NULL) {
            printf("Id: %s\tIdade: %d\tEstado: %c\tDias doente: %d\n", auxArray->id, auxArray->idade, auxArray->estado, auxArray->diasDoente);
            auxArray = auxArray->prox;
        }
    }
}

Pessoas* undo(ppessoas arrayUndo[], int tam, ppessoas p) {
    int it, contador = 0;
    
    for (int j = 0; j < 3; j++) {
        if (arrayUndo[j] != NULL) {
            contador++;
        }
    }

    do {
        printf("Numero de iteracoes a atrasar");
        scanf("%d", &it);
    } while (contador < it || (it < 1 && it > 3));

    p = arrayUndo[it - 1];
    return p;
}

