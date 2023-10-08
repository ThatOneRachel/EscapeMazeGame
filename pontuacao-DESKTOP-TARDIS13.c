#include <time.h>
#include "mapa.h"
#include "movimentos.h"
#include "raylib.h"
#define AUMENTOL 109
#define AUMENTOH 91
#define MIN 0
#define MAX 1

void gera_item_bau (Mapa *mapa, int *flag_chave)
{
    //modificações feitas por Raquel em 30/9:
    //
    int l, c;
    //int contador; //pra saber a quantidade de baus que tem
    char bau = 'C';
    char chave = 'K'; //tipos diferentes de coisas que pode ter dentro dos baús
    char bomba = 'B';
    char gema = 'G';
    char ametista = '!';
    char safira = '@';
    char rubi = '#';
    char anel = '$';
    char coroa = '%';

    // percorre a matriz
    for (l = 0; l < mapa->local_mapa.linha; l++)
    {
        for (c = 0; c < mapa->local_mapa.coluna; c++)
        {
            //  se encontrar um baú, 50/50 de chance de ter uma chave nele
            if (mapa-> matriz_mapa[l][c] == bau)
            {
                /// caso coloque uma chave
                if (sorteia ( ) == 1 && *flag_chave != 1)
                {
                    mapa-> matriz_mapa[l][c] = chave;
                    *flag_chave = 1;
                }

                /// caso não coloque
                else if (sorteia ( ) == 1 ){
                    // recebe uma gema
                    mapa-> matriz_mapa[l][c] = gema;
                    if (sorteia( ) && sorteia( ) == 1){
                        if (mapa->fase == 2) mapa->caixinha.interior = anel;
                        else mapa->caixinha.interior = safira;
                    }

                    else if (sorteia( ) && sorteia ( ) == 0){
                        if (mapa->fase == 3) mapa->caixinha.interior = coroa;
                        else mapa->caixinha.interior = rubi;
                    }
                    else mapa->caixinha.interior = ametista;

                }
                else
                    // ou uma bomba
                    mapa-> matriz_mapa[l][c] = bomba;
            }
        }
    }
     if (*flag_chave != 1)
                {
                    for (l = 0; l < mapa->local_mapa.linha; l++)
                    {
                        for (c = 0; c < mapa->local_mapa.coluna; c++)
                        {
                            //  se encontrar um baú, 50/50 de chance de ter uma chave nele
                            if (mapa-> matriz_mapa[l][c] == bau)
                            {
                                mapa->matriz_mapa[l][c] = chave;
                                break;
                            }
                        }
                    }
                }
}


int sorteia (void)
{

    int sorteio = MIN + (rand() % (MAX - MIN + 1));
    printf("\nsorteio: %d\n", sorteio);
    return sorteio;
}


//modificação feita por Raquel em 30/9
//terminar isso aqui
void abre_bau (Mapa *mapa, int *flag_chave, int *flag)
{
    int x_jog, y_jog;
    int retorno;
    char ametista = '!';
    char safira = '@';
    char rubi = '#';
    char anel = '$';
    char coroa = '%';
    localiza_jogador(mapa);
    x_jog = mapa->jogador.pos_jog.linha;
    y_jog = mapa->jogador.pos_jog.coluna;
    printf("\nentrou na abre_bau\n");
    printf("%c", mapa->local_direita);

    if (mapa->local_direita == 'K' ||
            mapa->local_direita == 'G' ||
            mapa->local_direita == 'B' ||
            mapa->local_esquerda == 'K'||
            mapa->local_esquerda == 'G'||
            mapa->local_esquerda == 'B')
    {
        printf("abriu caixinhaa");
        if (mapa->local_direita == 'K' || mapa->local_esquerda == 'K')
        {
            mapa->jogador.tem_chave = 1;
            printf("pegou chave");
        }
        if (mapa->local_direita == 'G' || mapa->local_esquerda == 'G')
        {
            if (mapa->caixinha.interior == ametista) mapa->jogador.pontos += 50;
            if (mapa->caixinha.interior == safira) mapa->jogador.pontos += 100;
            if (mapa->caixinha.interior == rubi) mapa->jogador.pontos += 150;
            if (mapa->caixinha.interior == anel) mapa->jogador.pontos += 200;
            if (mapa->caixinha.interior == coroa) mapa->jogador.pontos += 300;
            printf("pontuacao atual: %d", mapa->jogador.pontos);
        }
        if (mapa->local_direita == 'B' || mapa->local_esquerda == 'B') {
            retorno = jog_diminui_vida(mapa);
            printf("%d", mapa->jogador.qnt_vida);
            if (mapa->jogador.qnt_vida > 0 && retorno == 1){
                if (mapa->fase == 1){
                    morte(mapa, flag);
                    mapa->matriz_mapa[6][2] = 'D';
                }
                if (mapa->fase == 2){
                    morte(mapa, flag);
                    mapa->matriz_mapa[8][3] = 'D';
                }
                if (mapa->fase == 3){
                    morte(mapa, flag);
                    mapa->matriz_mapa[5][5] = 'D';
                }
            }
            else if (retorno == 0){
                while(!IsKeyPressed(KEY_ENTER)){
                BeginDrawing();
                DrawText("GAME OVER", 250, 250, 100, RED);
                DrawText("Aperte ENTER para sair", 250, 400, 50, RED);
                EndDrawing();


                }
            exit(0);
            }

        }
    }
}

void morte(Mapa *mapa, int *flag){
    Texture2D ladrao = LoadTexture ("protag.png");
    int morte_bomb = 0;

    if (*flag != 0){
        localiza_jogador(mapa);
        mapa->matriz_mapa[mapa->jogador.pos_jog.linha][mapa->jogador.pos_jog.coluna] = 'B';
        *flag = 0;
    }
    else {
        mapa->matriz_mapa[mapa->jogador.pos_jog.linha][mapa->jogador.pos_jog.coluna] = ' ';
        localiza_jogador(mapa);
        morte_bomb = 1;

    }

    while(!IsKeyPressed(KEY_ENTER)){
        BeginDrawing();
        if (morte_bomb == 1)DrawTexture(ladrao, AUMENTOL*mapa->jogador.pos_jog.coluna, AUMENTOH*mapa->jogador.pos_jog.linha, WHITE);
        DrawText("VOCE MORREU!!!", 20, 100, 50, RED);
        DrawText("Aperte ENTER para continuar!", 20, 70, 30, RED);
        EndDrawing();
    }
}
