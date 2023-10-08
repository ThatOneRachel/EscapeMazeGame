#define LINHAS 20
#define COLUNAS 25
#ifndef MOVIMENTOS_H
#define MOVIMENTOS_H
#include "mapa.h"
void localiza_jogador(Mapa *mapa);

void movimenta_lado(Mapa *mapa, int locomocao, int direcao, int *xaux,  int *flag, Porta *portal);

int cair(Mapa *mapa, int direcao);

void movimenta_cima(Mapa *mapa, int *escada, int direcao, int *xaux, Porta *portal, int *flag);

void busca_porta(Mapa *mapa, Porta *portal);

void proxima_fase(Mapa *mapa);


#endif // MOVIMENTOS_H


