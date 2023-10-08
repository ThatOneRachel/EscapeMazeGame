#ifndef JOGADOR_H
#define JOGADOR_H
#include "coordenadas.h"

typedef struct {
    Localizacao pos_jog;
    char nome[10];
    int tem_chave; //flag pra ver se ele tem chave ou não
    int pontos; //pontuação dele
    int qnt_vida;
    int num_jog;
}Jogador;

Localizacao jog_inicializa(int x, int y);
int pontuacao_inicializa(int pontos);
int vida_inicializa(int qnt_vida);



#endif // JOGADOR_H
