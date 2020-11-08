/*
 * Leonardo Rafael Amado Brito
 * Numero: 2016017310
 */

#include "Espaco.h"
#include "Pessoas.h"
#include "configuracao.h"
#include "simulacao.h"
#include "utils.h"

int menu() {
    int i;
    puts("--------------------------------------------");
    puts("----- Simulacao Da Propagacao Do Virus -----");
    puts("--------------------------------------------");
    puts("\n");
    puts("----- Fase De Preparacao -----");
    puts("1 - Abre Ficheiro Dos Locais");
    puts("2 - Abre Ficheiro Das Pessoas");
    puts("3 - Distribuicao De Pessoas Por Sala");
    puts("--------- Simulacao ----------");
    puts("4 - Adiciona Doente");
    puts("5 - Transfere Pessoas");
    puts("6 - Avanca iteracao");
    puts("7 - Imprime Relatorio");
    puts("8 - Undo");
    puts("9 - Terminar");
    puts("Escolha uma opcao: ");
    do {
        scanf("%d", &i);
    } while (i < 1 || i > 9);
    return i;
}

int main(int argc, char** argv) {
    int i;
    void initRandom(); // Inicia gerador de numeros aleatorios

    // LOCAIS
    Local *loc = NULL; // Array de Salas
    int total = 0; // Numero total de salas


    // PESSOAS
    ppessoas pes = NULL; // Lista de pessoas
    int total2 = 0; // Numero total de pessoas

    // UNDO
    int tamUndo = 3;
    ppessoas arrayUndo[3] = {NULL, NULL, NULL};


    //MENU
    do {
        i = menu();
        switch (i) {

            case 1:
                loc = lerDadosLocal(&total);
                mostra_local(loc, total);
                break;
            case 2:
                pes = LerDadosPessoas(&total2);
                mostraPessoas(pes);
                break;
            case 3:
                emparelhamento(loc, pes, total);
                mostraEmparelhamento(pes);
                break;
            case 4:
                pes = adicionaDoente(pes, loc, total);
                mostraEmparelhamento(pes);
                break;
            case 5:
                pes = transferePessoas(pes, loc, total, total2);
                mostraEmparelhamento(pes);
                break;
            case 6:
                avancaIteracao(pes);
                arrayUndo[0] = atualizaUndo(arrayUndo,tamUndo,pes);
                estatistica(pes, total2, loc, total);
                //mostraArrayLista(pes, arrayUndo);
                break;
            case 7:
                relatorioInfo(pes, total2);
                relatorioPopulacao(pes);
                break;
            case 8:
                pes = undo(arrayUndo, tamUndo, pes);
                mostraPessoas(pes);
                //mostraArrayLista(pes);
                break;                
        }
    } while (i != 9);

    free(loc);
    freePessoas(pes); // limpar posicao a posicao
    return 0;
}

