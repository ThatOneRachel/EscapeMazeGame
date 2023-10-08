#include <string.h>
#include <stdio.h>
#include "jogador.h"
#include "ranking.h"
#include "mapa.h"
#define NOME_TXT "ranking.txt"
void salva_ranking(Ranking ranque[5], int num_jog, Mapa mapa){
    int i;
    FILE *arquivo;
    arquivo = fopen(NOME_TXT, "w");
    if (arquivo)
    {
        num_jog++;
        fseek(arquivo, 0, SEEK_SET);
            strcpy(ranque[num_jog].nome, mapa.jogador.nome);
            ranque[num_jog].pontos = mapa.jogador.pontos;
            fprintf(arquivo, "%s\t", ranque[num_jog].nome);
            fprintf(arquivo, "%d\n", ranque[num_jog].pontos);
            fprintf(arquivo, "%d\n", num_jog);

        fclose(arquivo);
    }
    else printf("erro");
}
