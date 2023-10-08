#ifndef SALVARJOGO_H
#define SALVARJOGO_H

void arq_salva_jogo(Mapa mapa, int escada, int xaux, Porta porta_main, int flag);

void arq_recupera_jogo (Mapa *mapa, int *escada, int *xaux, Porta *porta_main, int *flag);

#endif // SALVARJOGO_H
