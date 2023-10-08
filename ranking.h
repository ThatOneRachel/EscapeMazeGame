#ifndef RANKING_H
#define RANKING_H

#define NUM_JOG 5
#include "jogador.h"
#include "mapa.h"

typedef struct {
    int pontos;
    char nome[10]
} Ranking;

void salva_ranking (Ranking ranque[NUM_JOG], int num_jog, Mapa mapa);

void imprime_ranking (Ranking ranque[NUM_JOG]);

void concatenador (Ranking ranque[NUM_JOG], int num_jog);

void ordenamento_bolha (Ranking ranque[NUM_JOG], int num_jog, Ranking novoJogador);
#endif // RANKING_H
