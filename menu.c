#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#define ALTTELA 1000
#define LARGTELA 1100
#define BABY_BLUE (Color){217, 234, 255, 255}
#define SPECIAL_SILVER (Color){177, 180, 177, 255}
#define OPCOES 4
#define TAMANHO_FONTE 60

int desenha_menu (int *escolha)
{

    int x = (LARGTELA -  MeasureText("CARREGAR JOGO",TAMANHO_FONTE))/2; //retorna o espaço em branco e divide por 2 para saber onde começar
    int y = 300;
    int opcao = 1;

    //visual padrão
    DrawText("NOVO JOGO\n", x, y, TAMANHO_FONTE, BABY_BLUE);
    DrawText("CARREGAR JOGO", x, (y + 80), TAMANHO_FONTE, BABY_BLUE);
    DrawText("RANKING PONTOS\n", x, y + (80 * 2), TAMANHO_FONTE, BABY_BLUE);
    DrawText("SAIR\n", x, y + (80 * 3), TAMANHO_FONTE, BABY_BLUE);

    //variação da cor de acordo com o apertar do teclado
    if (*escolha == 0){
        DrawText("NOVO JOGO\n", x, y, TAMANHO_FONTE, SPECIAL_SILVER);
        if (IsKeyPressed(KEY_ENTER))
            opcao = 2;
    }

    else if (*escolha == 1){
        DrawText("CARREGAR JOGO\n", x, (y + 80), TAMANHO_FONTE, SPECIAL_SILVER);
        if (IsKeyPressed(KEY_ENTER))
            opcao = 3;
    }
    else if (*escolha == 2){
        DrawText("RANKING PONTOS\n", x, y + (80 * 2), TAMANHO_FONTE, SPECIAL_SILVER);
        if (IsKeyPressed(KEY_ENTER))
            opcao = 4;
    }
    else {
        DrawText("SAIR\n", x, y + (80 * 3), TAMANHO_FONTE, SPECIAL_SILVER);
        if (IsKeyPressed(KEY_ENTER)){
            opcao = 5;
            exit(0);
        }
    }
//retorna a opção para a main com o intuito de escolher qual ação o programa devera tomar
return opcao;
}
