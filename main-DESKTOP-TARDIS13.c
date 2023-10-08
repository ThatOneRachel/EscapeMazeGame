#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "mapa.h"
#include "movimentos.h"
#include "jogador.h"
#include "ranking.h"
#define LINHAS 20
#define COLUNAS 25
#define ALTTELA 910
#define LARGTELA 1090
#define AUMENTOL 109
#define AUMENTOH 91
#define TAMANHO_FONTE 40
#define MAX_INPUT_CHARS 10
#define NUM_JOG 5
#define SPECIAL_SILVER (Color){177, 180, 177, 255}
int main()
{

    ///Área da declaração de variáveis
    Mapa mapa;
    mapa.jogador.pontos = 0;
    //variáveis que funcionam principalmente como locais
    int l, c, cl, cc, escolha = 0, opcao = 1;
    char vida[5];
    char pontos[5];
    //variáveis que funcionam principalmente para o funcionamento das funções
    int x_jog, y_jog, stairs, locomocao = 0, xaux = 0, flag = 0, direcao;
    Porta porta_main;
    porta_main.num_porta = ' ';
    int flag_chave;
    Ranking ranque[NUM_JOG];
    int num_jog;
    Texturas text;
    //variáveis para a animação do portal
    int fotoatualp = 0;
    int contfoto = 0;
    int velocidadeframe = 6;
    //variáveis para a coleta do nome do personagem
    Rectangle textBox = {LARGTELA/2.0f - 100, 180, 225, 50 };
    int letra_cont = 0;
    int pode_entrar = 0;
    int tecla;

    //texturas e estruturas para a animação
    InitWindow(LARGTELA, ALTTELA, "Jogo");

    InitAudioDevice();

    Texture2D tijolo = LoadTexture("tijolochao.png");
    Texture2D escada = LoadTexture("escada.png");
    Texture2D bau = LoadTexture("bau.png");
    Texture2D portal = LoadTexture ("portaloficial.png");
    Texture2D ladrao = LoadTexture ("protag.png");
    Texture2D ladraoesq = LoadTexture("protagesq.png");
    Texture2D ladraoescada = LoadTexture ("protagescada.png");
    Texture2D background = LoadTexture ("background.png");
    Texture2D fundomenu = LoadTexture("tardisblue.png");

    Rectangle fotoatualprec = {0.0f, 0.0f, (float)portal.width/10, (float)portal.height};

    //variáveis para o carregamento de trilha sonora
    Music musicajogo = LoadMusicStream("another one bites the dust - 8bit.mp3");
    SetTargetFPS(60);

    ///Carregamento do mapa
    mapa.fase = 0;
    printf("\nfase: %d\n", mapa.fase);
    if (mapa.fase == 0) {
        mapa_carrega(&mapa);
        gera_item_bau (&mapa, &flag_chave);
        mapa.cor = WHITE;
    }
    PlayMusicStream(musicajogo);

    ///Loop do funcionamento da tela
    while(!WindowShouldClose())
    {
        if (mapa.fase != 4) UpdateMusicStream(musicajogo);
        //if (mapa.fase ==4)


        ///Animação do portal
        contfoto++;
        if (contfoto >= (60/velocidadeframe))
        {
            contfoto = 0;
            fotoatualp++;
            if (fotoatualp > 9) fotoatualp = 0;
            fotoatualprec.x = (float)fotoatualp*(float)portal.width/10;
        }

        ///Encontrar o Jogador
        localiza_jogador(&mapa);
        mapa.jogador.num_jog = 1;
        ///Começo do desenho na tela
        BeginDrawing();

        ClearBackground(WHITE);

        switch(opcao){
        case 1:
            if (IsKeyPressed(KEY_UP)){
                escolha--;
                if (escolha < 0) escolha = 3;
            }
            if (IsKeyPressed(KEY_DOWN)){
                escolha++;
                if(escolha > 3) escolha = 0;
            }
            DrawTexture(fundomenu, 0.f, 0.f, WHITE);
            opcao = desenha_menu(&escolha);
            if (opcao == 2) mapa.jogador.nome[0] = '\0';
            EndDrawing();
            break;

        case 2:

            //quando inicia o jogo, colocar o nome do jogador
            while(pode_entrar == 0){
                tecla = GetCharPressed();
                while (tecla > 0){
                    if ((tecla >= 32) && (tecla <= 125) && (letra_cont < MAX_INPUT_CHARS)){
                        mapa.jogador.nome[letra_cont] = (char)tecla;
                        mapa.jogador.nome[letra_cont+1] = '\0';
                        letra_cont++;
                    }
                    tecla = GetCharPressed();
                }
                if (IsKeyPressed(KEY_BACKSPACE)){
                    letra_cont--;
                    if(letra_cont < 0)letra_cont = 0;
                    mapa.jogador.nome[letra_cont] = '\0';
                }
                BeginDrawing();
                    DrawTexture(fundomenu, 0.f, 0.f, WHITE);
                    DrawText("Escreva o nome do jogador", (int)textBox.x-150, (int)textBox.y, 40, SPECIAL_SILVER);
                    DrawText(mapa.jogador.nome, (int)textBox.x + 5, (int)textBox.y + 30, 40, SPECIAL_SILVER);
                if (IsKeyPressed(KEY_ENTER)) pode_entrar = 1;
                EndDrawing();
            }


            ///Interface visual do jogos
            DrawTexture(background, 0.f, 0.f, WHITE);

            //Imprimir cada coisa específica para cada pedaço da matriz
            for (cl = 0; cl < mapa.local_mapa.linha; cl++)
            {
                for (cc = 0; cc < mapa.local_mapa.coluna; cc++)
                {
                    if (mapa.matriz_mapa[cl][cc] == 'X') DrawTexture(tijolo, AUMENTOL*cc, AUMENTOH*cl, WHITE);
                    if (mapa.matriz_mapa[cl][cc] == 'H') DrawTexture(escada, AUMENTOL*cc, AUMENTOH*cl, WHITE);
                    if (mapa.matriz_mapa[cl][cc] == 'C' ||
                        mapa.matriz_mapa[cl][cc] == 'K' ||
                        mapa.matriz_mapa[cl][cc] == 'B' ||
                        mapa.matriz_mapa[cl][cc] == 'G') DrawTexture(bau, AUMENTOL*cc, AUMENTOH*cl, WHITE);
                    if (mapa.matriz_mapa[cl][cc] == '1' || mapa.matriz_mapa[cl][cc] == '2')
                    {
                        Vector2 posicaop = {AUMENTOL*cc, AUMENTOH*cl};
                        DrawTextureRec(portal, fotoatualprec, posicaop, mapa.cor);
                    }
                    if (mapa.matriz_mapa[cl][cc] == 'D')
                    {
                        //COnsertar o bug dps
                        if (mapa.local_cima == 'H' ||
                            (mapa.local_cima == ' ' &&
                             mapa.local_baixo == 'H' &&
                             (mapa.local_direita == 'X' || mapa.local_esquerda == 'X')))DrawTexture(ladraoescada, AUMENTOL*cc, AUMENTOH*cl, WHITE);
                        else {
                            if (direcao == -1)DrawTexture(ladraoesq, AUMENTOL*cc, AUMENTOH*cl, WHITE);
                            else DrawTexture(ladrao, AUMENTOL*cc, AUMENTOH*cl, WHITE);
                        }
                    }
                    if (mapa.jogador.tem_chave == 1 && mapa.matriz_mapa[cl][cc] == 'P'){
                        Vector2 posicaop = {AUMENTOL*cc, AUMENTOH*cl};
                        DrawTextureRec(portal, fotoatualprec, posicaop, RED);
                    }
                }
            }
            //desenha na tela as informações do jogador
            DrawText("Vida: ", 20, 20, 50, mapa.cor);
            sprintf(vida, "%d", mapa.jogador.qnt_vida);
            DrawText(vida, 150, 20, 50, mapa.cor);

            DrawText("Pontos: ", 300, 20, 50, mapa.cor);
            sprintf(pontos, "%d", mapa.jogador.pontos);
            DrawText(pontos, 500, 20, 50, mapa.cor);

            if (mapa.fase == 4){
                DrawText("PARABENS!!! VOCE ZEROU O JOGO!!!", 100, 200, 50, SPECIAL_SILVER);
                DrawText ("Agora", 440, 250, 40, SPECIAL_SILVER);
                DrawText(mapa.jogador.nome, 600, 250, 40, SPECIAL_SILVER);
                DrawText("Podera fugir do manicomio chamado Brasil!", 180, 300, 40, SPECIAL_SILVER);
                DrawText("Pressione 'esq' para sair", 400, 400, 30, SPECIAL_SILVER);
            }

            //movimentação do personagem
            if (IsKeyPressed(KEY_RIGHT))
            {
                //a direcao não está diretamnete como paremetro por causa da animação do personagem
                direcao = 1;
                movimenta_lado(&mapa, 1, direcao, &xaux, &flag, &porta_main, text);
            } //a flag funciona para ver se tem a caixa ou não
            if (IsKeyPressed(KEY_LEFT))
            {
                direcao = -1;
                movimenta_lado(&mapa, 1, direcao, &xaux, &flag, &porta_main, text);
            }
            if (IsKeyPressed(KEY_UP))movimenta_cima(&mapa, &stairs, -1, &xaux, &porta_main, &flag);
            if (IsKeyPressed(KEY_DOWN))movimenta_cima (&mapa, &stairs, 1, &xaux, &porta_main, &flag);
            if (IsKeyPressed(KEY_O))abre_bau(&mapa, &flag_chave, &flag);
            if (IsKeyPressed(KEY_S))arq_salva_jogo(mapa, stairs, xaux, porta_main, flag);
            if (IsKeyPressed(KEY_T))salva_ranking(ranque, 1, mapa);

            ///Terminar desenho na tela
            EndDrawing();
            break;
        case 3:
            arq_recupera_jogo(&mapa, &stairs, &xaux, &porta_main, &flag);
            opcao = 2;
            break;
        case 4:
            printf("ranking tambem em progresso");
            return 0;
            break;
        }
    }
    UnloadMusicStream(musicajogo);
    return 0;
}
