/*
 * Leonardo Rafael Amado Brito
 * Numero: 2016017310
 */
#include "Espaco.h"

void mostra_local(Local *esp, int total) { // Mostra as carecteristicas dos locais
    for (int i = 0; i < total; i++) {
        printf("\n ID >> %d", esp[i].id);
        printf("\n Capacidade %d", esp[i].capacidade);
        for (int j = 0; j < 3; j++)
            printf("\n Contem a ligacao %d", esp[i].liga[j]);
        printf("\n\n");
    }
}

Local* lerDadosLocal(int *total) { // Passa a informacao do ficheiro para um array dinamico
    FILE *f;
    Local *p = NULL;
    Local aux;
    char fichLocais[20];

    printf("Nome do ficheiro: ");
    scanf("%s", &fichLocais);

    f = fopen(fichLocais, "rb");
    if (f == NULL) {
        printf("Erro ao abrir o ficheiro");
        *total = 0;
        return NULL;
    }

    int h = 0;
    p = (Local*) malloc(sizeof (Local));

    if (p == NULL) {
        printf("Erro na alocacao da memoria\n");
        *total = 0;
        return NULL;
    }

    while (fread(&aux, sizeof (Local), 1, f) == 1) {
        if (h == 0) {
            p[h] = aux;
        } else {

            p = realloc(p, sizeof (Local) * ((h + 1)));
            if (p == NULL) {
                printf("Erro na realocacao de memoria");
                return NULL;
            }
            p[h] = aux;
        }
        h++;

    }
    *total = h;

    fclose(f);
    return p;
}
