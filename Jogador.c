#include "jogador.h"
#include "coordenadas.h"
#include "mapa.h"
#include <string.h>
#include <stdio.h>

Localizacao jog_inicializa(int x, int y){
    Jogador jogador;
    jogador.pos_jog = localizacao_cria(x, y);
    return jogador.pos_jog;
}

int pontuacao_inicializa(int pontos){
    pontos = 0;
    return pontos;
}
int vida_inicializa(int qnt_vida){
    qnt_vida = 3;
    return qnt_vida;
}


int jog_diminui_vida(Mapa *mapa){
    //se a vida for maior que 1, então pode ir diminuindo enquanto ele for entrando na função
    if (mapa->jogador.qnt_vida > 1)
    {
        mapa->jogador.qnt_vida -= 1;
        return 1;
    }
    else return 0;
}
