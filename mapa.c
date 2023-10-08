#define MAPA_L 30
#define MAPA_C 120
#define ALTTELA 1000
#define LARGTELA 1100
#define AUMENTOL 109
#define AUMENTOH 91
#include "coordenadas.h"
#include "jogador.h"
#include "mapa.h"
#include <string.h>

/// Carrega o mapa da primeira fase
void mapa_carrega(Mapa *mapa)
{
    char porta;
    int escada;

    strcpy(mapa->matriz_mapa[0], "XXXXXXXXXX");
    strcpy(mapa->matriz_mapa[1], "XK    C2 X");
    strcpy(mapa->matriz_mapa[2], "XXH  XXXXX");
    strcpy(mapa->matriz_mapa[3], "X1H    1 X");
    strcpy(mapa->matriz_mapa[4], "XXX HXHX X");
    strcpy(mapa->matriz_mapa[5], "X   H H  X");
    strcpy(mapa->matriz_mapa[6], "X D H HC2X");
    strcpy(mapa->matriz_mapa[7], "X HXX XXXX");
    strcpy(mapa->matriz_mapa[8], "X H     PX");
    strcpy(mapa->matriz_mapa[9], "XXXXXXXXXX");

    mapa->local_mapa.linha = 10;
    mapa->local_mapa.coluna = 10;

    mapa->fase = 1;

    mapa->jogador.pos_jog = jog_inicializa(6, 2);
    mapa->jogador.qnt_vida = vida_inicializa(3);
}

/// Carrega o mapa da segunda fase
void mapa_carrega_n2(Mapa *mapa)
{
    char porta;
    int escada;

    strcpy(mapa->matriz_mapa[0], "XXXXXXXXXX");
    strcpy(mapa->matriz_mapa[1], "XC      2X");
    strcpy(mapa->matriz_mapa[2], "XXH   HXXX");
    strcpy(mapa->matriz_mapa[3], "X2H   H  X");
    strcpy(mapa->matriz_mapa[4], "XXH   HC1X");
    strcpy(mapa->matriz_mapa[5], "X H   XXXX");
    strcpy(mapa->matriz_mapa[6], "X H C X 1X");
    strcpy(mapa->matriz_mapa[7], "XXXXXXXHXX");
    strcpy(mapa->matriz_mapa[8], "XP D C H X");
    strcpy(mapa->matriz_mapa[9], "XXXXXXXXXX");

    mapa->local_mapa.linha = 10;
    mapa->local_mapa.coluna = 10;

    mapa->jogador.pos_jog = jog_inicializa(8, 3);

    mapa->fase = 2;

}

/// Carrega o mapa da terceira fase
void mapa_carrega_n3(Mapa *mapa)
{
    char porta;
    int escada;

    strcpy(mapa->matriz_mapa[0], "XXXXXXXXXX");
    strcpy(mapa->matriz_mapa[1], "X C      X");
    strcpy(mapa->matriz_mapa[2], "XXXXHXXHXX");
    strcpy(mapa->matriz_mapa[3], "X 1 HXCHCX");
    strcpy(mapa->matriz_mapa[4], "XHXXXXXXXX");
    strcpy(mapa->matriz_mapa[5], "XHCXD  2 X");
    strcpy(mapa->matriz_mapa[6], "XXXXXXXXXX");
    strcpy(mapa->matriz_mapa[7], "X        X");
    strcpy(mapa->matriz_mapa[8], "XP2  C  1X");
    strcpy(mapa->matriz_mapa[9], "XXXXXXXXXX");

    mapa->local_mapa.linha = 10;
    mapa->local_mapa.coluna = 10;

    mapa->jogador.pos_jog = jog_inicializa(5, 5);

    mapa->fase = 3;
}

/// Tela de fim de jogo
void tela_final(Mapa *mapa){
    strcpy(mapa->matriz_mapa[0], "XXXXXXXXXX");
    strcpy(mapa->matriz_mapa[1], "X        X");
    strcpy(mapa->matriz_mapa[2], "X        X");
    strcpy(mapa->matriz_mapa[3], "X        X");
    strcpy(mapa->matriz_mapa[4], "X        X");
    strcpy(mapa->matriz_mapa[5], "X        X");
    strcpy(mapa->matriz_mapa[6], "X        X");
    strcpy(mapa->matriz_mapa[7], "X        X");
    strcpy(mapa->matriz_mapa[8], "X D      X");
    strcpy(mapa->matriz_mapa[9], "XXXXXXXXXX");

    mapa->local_mapa.linha = 10;
    mapa->local_mapa.coluna = 10;

    mapa->jogador.pos_jog = jog_inicializa(8, 2);

    mapa->fase = 4;
}
