#include "coordenadas.h"
#include "jogador.h"
#include "mapa.h"
#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#define NOME_ARQUIVO "jogo.dat"

void arq_salva_jogo(Mapa mapa, int escada, int xaux, Porta porta_main, int flag)
{
    FILE *arquivo;
    int l;

    //escrevendo
    arquivo = fopen(NOME_ARQUIVO,"wb");
    if (arquivo == NULL)
        printf("Não conseguiu abrir o arquivo\n\n");
    else
    {
        //salvamento da estrutura mapa
        printf("\nArquivo aberto com sucesso\n\n");
        fwrite(&mapa.local_mapa, sizeof(Localizacao), 1, arquivo);
        fwrite(&mapa.escada, sizeof(int), 1, arquivo);
        fwrite(&mapa.portal, sizeof(Porta),1, arquivo);
        fwrite(&mapa.caixinha, sizeof(Caixa),1, arquivo);
        fwrite(&mapa.jogador, sizeof(Jogador), 1, arquivo);
        fwrite(&mapa.cor, sizeof(Color), 1, arquivo);
        fwrite(&mapa.local_direita, sizeof(char), 1, arquivo);
        fwrite(&mapa.local_esquerda, sizeof(char), 1, arquivo);
        fwrite(&mapa.local_cima, sizeof(char), 1, arquivo);
        fwrite(&mapa.local_baixo, sizeof(char), 1, arquivo);
        fwrite(&mapa.fase, sizeof(int), 1, arquivo);

        //salvamento de outras flags igualmente necessárias
        fwrite(&escada, sizeof(int), 1, arquivo);
        fwrite(&xaux, sizeof(int), 1, arquivo);
        fwrite(&porta_main, sizeof(Porta), 1, arquivo);
        fwrite(&flag, sizeof(int), 1, arquivo);

        //escreve a matriz do mapa no arquivo
        for (l = 0; l < mapa.local_mapa.linha; l++)
        {
            fwrite(mapa.matriz_mapa[l], mapa.local_mapa.linha, 1, arquivo);
        }

        fclose(arquivo);

        printf("\nArquivo Salvo\n\n");
    }

}

void arq_recupera_jogo (Mapa *mapa_oficial, int *escada_oficial, int *xaux_oficial, Porta *portal, int *flag_oficial)

{
    FILE *arquivo;
    int l, c;
    Mapa mapa;
    int escada;
    int xaux;
    Porta porta_main;
    int flag;

    //lendo
    arquivo = fopen(NOME_ARQUIVO,"rb");

    if (arquivo == NULL)
        printf("Não conseguiu abrir o arquivo\n");
    else
    {
        printf("\nArquivo lido com sucesso\n");

        //leitura da estrutura mapa
        fread(&mapa.local_mapa, sizeof(Localizacao), 1, arquivo);
        fread(&mapa.escada, sizeof(int), 1, arquivo);
        fread(&mapa.portal, sizeof(Porta),1, arquivo);
        fread(&mapa.caixinha, sizeof(Caixa),1, arquivo);
        fread(&mapa.jogador, sizeof(Jogador), 1, arquivo);
        fread(&mapa.cor, sizeof(Color), 1, arquivo);
        fread(&mapa.local_direita, sizeof(char), 1, arquivo);
        fread(&mapa.local_esquerda, sizeof(char), 1, arquivo);
        fread(&mapa.local_cima, sizeof(char), 1, arquivo);
        fread(&mapa.local_baixo, sizeof(char), 1, arquivo);
        fread(&mapa.fase, sizeof(int), 1, arquivo);

        //leitura das outras flags salvas
        fread(&escada, sizeof(int), 1, arquivo);
        fread(&xaux, sizeof(int), 1, arquivo);
        fread(&porta_main, sizeof(Porta), 1, arquivo);
        fread(&flag, sizeof(int), 1, arquivo);

        //leitura da matriz do mapa
        for (l = 0; l < mapa.local_mapa.linha; l++){
            fread(mapa.matriz_mapa[l], mapa.local_mapa.linha, 1, arquivo);
        }

        fclose(arquivo);
        *mapa_oficial = mapa;
        *escada_oficial = escada;
        *xaux_oficial = xaux;
        *portal = porta_main;
        *flag_oficial = flag;

        printf("\nArquivo Recuperado\n");
    }

}

