#ifndef MAPA_H
#define MAPA_H
#define LINHAS 30
#define COLUNAS 270
#include "coordenadas.h"
#include "raylib.h"
#include "jogador.h"


typedef struct {
    char num_porta;
    Localizacao local_porta;
} Porta;

typedef struct {
    int flag_bau;
    char interior;
} Caixa;



typedef struct{
    char matriz_mapa[LINHAS][COLUNAS];
    Localizacao local_mapa;
    int escada;
    Porta portal;
    Caixa caixinha;
    Jogador jogador;
    Color cor;
    char local_direita;
    char local_esquerda;
    char local_cima;
    char local_baixo;
    int fase;

} Mapa;

void mapa_carrega(Mapa *mapa);

void mapa_carrega_n2(Mapa *mapa);

void mapa_carrega_n3(Mapa *mapa);

void tela_final(Mapa *mapa);

void gera_item_bau (Mapa *mapa, int *flag_chave);

int sorteia (void);

void abre_bau (Mapa *mapa, int *flag_chave, int *flag);

int jog_diminui_vida(Mapa *mapa);

void morte(Mapa *mapa, int *flag);

#endif // MAPA_H
