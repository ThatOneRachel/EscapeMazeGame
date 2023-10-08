
#define LINHAS 20
#define COLUNAS 25
#define AUMENTOL 109
#define AUMENTOH 91
#include "movimentos.h"
#include "raylib.h"

void localiza_jogador(Mapa *mapa)
{
    //printf("entrou localiza jogador");
    int ctl = 0, ctc = 0, linhas, colunas, jog_x, jog_y;
    //declacação de variáveis
    linhas = mapa->local_mapa.linha;
    colunas = mapa->local_mapa.coluna;
    jog_x = mapa->jogador.pos_jog.linha;
    jog_y = mapa->jogador.pos_jog.coluna;


    ///Percorre a matriz para achar o jogador
    for (ctl = 0; ctl < linhas; ctl++)
    {
        for (ctc = 0; ctc < colunas; ctc++)
        {
            if (mapa->matriz_mapa[ctl][ctc] == 'D')
            {
                jog_x = ctl;
                jog_y = ctc;
            }
        }
    }
    mapa->jogador.pos_jog.linha = jog_x;
    mapa->jogador.pos_jog.coluna = jog_y;
}

///Movimentação lateral
void movimenta_lado(Mapa *mapa, int locomocao, int direcao, int *xaux,  int *flag, Porta *portal, Texturas text)
{
    printf("entrou movimenta lado");

    int x_jog, y_jog, yaux, fport = 0;
    int queda = 0;
    char tbdir, tbesq;
    int retorno;
    //pega os valores de mapa blah bka lbfkdba e coloca em variaveis menores pra ficar mais legível e por preguiça minha mesm
    Caixa caixinha;

    ///localiza o jogador
    localiza_jogador(mapa);
    x_jog = mapa->jogador.pos_jog.linha;
    y_jog = mapa->jogador.pos_jog.coluna;
    printf("%d %d", x_jog, y_jog);

    ///questionamento da existência da porta
    printf("porta: %c", *portal);

    /// flag que diz se está ou não em cima de uma porta
    if (portal->num_porta != ' ')
    {
        printf("\nta na portaaAAA");
        fport = 1;
    }

    if (mapa->matriz_mapa[x_jog][y_jog+direcao] == '1'||mapa->matriz_mapa[x_jog][y_jog+direcao] == '2')
        portal->num_porta = mapa->matriz_mapa[x_jog][y_jog+direcao]; //se o local ao lado for uma porta, *porta ganha o valor do local

    ///Se tiver uma parede, então não pode se mover
    if (mapa->matriz_mapa[x_jog][y_jog+direcao] == 'X') locomocao = 0;
    //caso contrário, pode se mover
    else locomocao = 1;
    if (locomocao == 1)
    {
        tbdir = mapa->local_direita;
        tbesq = mapa->local_esquerda;
        //pega onde o jogador vai e onde ele estava antes de se mover
        mapa->local_direita = mapa->matriz_mapa[x_jog][y_jog + abs(direcao)];
        mapa->local_esquerda = mapa->matriz_mapa[x_jog][y_jog - abs(direcao)];
        mapa->local_cima = mapa->matriz_mapa[x_jog - abs(direcao)][y_jog];
        mapa->local_baixo = mapa->matriz_mapa[x_jog + abs(direcao)][y_jog];
        //Se for uma escada em cima, coloca uma escada ao se mover
        if (mapa->matriz_mapa[x_jog-1][y_jog] == 'H') mapa->matriz_mapa[x_jog][y_jog] = 'H';

        //Parte CERTA pro baú (provavelmente, pq a prate principal fica na função movimenta_cima
        else if (mapa->matriz_mapa[x_jog][y_jog+direcao] == 'C' ||
                 mapa->matriz_mapa[x_jog][y_jog+direcao] == 'K' ||
                 mapa->matriz_mapa[x_jog][y_jog+direcao] == 'G' ||
                 mapa->matriz_mapa[x_jog][y_jog+direcao] == 'B')
        {
            *xaux = x_jog;
            yaux = y_jog+direcao;
            mapa->matriz_mapa[x_jog][y_jog] = ' ';
        }
        //Senão, coloca espaço
        else mapa->matriz_mapa[x_jog][y_jog] = ' ';
        //o trequinho do jogador aumenta  e ele se move
        y_jog = y_jog + direcao;
        mapa->matriz_mapa[x_jog][y_jog] = 'D';

        ///Aqui é onde o treco do baú funciona
        if (*flag == 1)
        {
            if (direcao == -1 && (tbdir == 'K'||tbdir == 'G'||tbdir == 'B'))
                mapa->matriz_mapa[x_jog][y_jog-direcao] = tbdir;
            else if (direcao == 1 && (tbdir == 'K'||tbdir == 'G'||tbdir == 'B'))
                mapa->matriz_mapa[x_jog][y_jog+direcao] = tbesq;
            *flag = 0;
            *xaux = 0;
        }

        if (*xaux != 0) *flag = 1; //Se xaux for dirente de zero (ou seja, tiver uma coordenada), *flag recebe 1

        //Se não tiver chão embaixo, então ele cai
        if (mapa->matriz_mapa[x_jog+1][y_jog] == ' ')
        {
            //trecho padrão pra funfar
            mapa->jogador.pos_jog.linha = x_jog;
            mapa->jogador.pos_jog.coluna = y_jog;

            queda = cair(mapa, direcao, text);

        }
    }

    //flag sendo usada para o bem da humanidade
    if (fport == 1)
    {
        mapa->matriz_mapa[x_jog][y_jog-direcao] = portal->num_porta;
        fport = 0;
        portal->num_porta = ' ';

    }
    //atualiza o valor de mapa blah balh bkasbh
    mapa->jogador.pos_jog.linha = x_jog;
    mapa->jogador.pos_jog.coluna = y_jog;

    /*mapa->local_direita = mapa->matriz_mapa[x_jog][y_jog + abs(direcao)];
    mapa->local_esquerda = mapa->matriz_mapa[x_jog][y_jog - abs(direcao)];*/
    mapa->local_cima = mapa->matriz_mapa[x_jog - abs(direcao)][y_jog];
    mapa->local_baixo = mapa->matriz_mapa[x_jog + abs(direcao)][y_jog];
    if (queda >= 3){
        morte(mapa, flag);
        retorno = jog_diminui_vida(mapa);
        printf("vida: %d", mapa->jogador.qnt_vida);
        printf("retorno: %d", retorno);

        if (retorno == 0){
            while(!IsKeyPressed(KEY_ENTER)){
                BeginDrawing();
                DrawText("GAME OVER", 250, 250, 100, RED);
                DrawText("Aperte ENTER para sair", 250, 400, 50, RED);
                EndDrawing();
                exit(0);
            }
        }

    }
}


///Função da gravidade
int cair(Mapa *mapa, int direcao, Texturas text)
{
    int cont = 0;
    int x_jog, y_jog;

    x_jog = mapa->jogador.pos_jog.linha;
    y_jog = mapa->jogador.pos_jog.coluna;

    mapa->matriz_mapa[x_jog][y_jog] = ' ';

    //ele vai cair, portanto a posição atual dele vai e tornar branco
    while (mapa->matriz_mapa[x_jog+1][y_jog] == ' ')
    {
        x_jog++;
        cont++;

    }
    mapa->matriz_mapa[x_jog][y_jog] = 'D';

    mapa->jogador.pos_jog.linha = x_jog;
    mapa->jogador.pos_jog.coluna = y_jog;
    return cont;
}



///Movimento vertical

void movimenta_cima(Mapa *mapa, int *escada, int direcao, int *xaux, Porta *portal, int *flag)
{
    int x_jog, y_jog, x_porta, y_porta, yaux;


    x_jog = mapa->jogador.pos_jog.linha;
    y_jog = mapa->jogador.pos_jog.coluna;

    x_porta = portal->local_porta.linha;
    y_porta = portal->local_porta.coluna;

    // localiza o jogador
    localiza_jogador(mapa);

    printf("ele estava em uma porta? %c\n", portal->num_porta);


    //pega onde o jogador vai e onde ele estava antes de se mover


    printf("\nflag da chave %d\n", mapa->jogador.tem_chave);
    printf("\ndireita: %c",  mapa->local_direita);
    printf("\nesquerda: %c", mapa->local_esquerda);

    /// Condição para passar de fase
    if (mapa->jogador.tem_chave == 1 && (mapa->local_direita == 'P' || mapa->local_esquerda == 'P'))
    {
        proxima_fase(mapa);
        arq_salva_jogo(*mapa, *escada, *xaux, *portal, *flag);
    }
    mapa->local_direita = mapa->matriz_mapa[x_jog][y_jog + abs(direcao)];
    mapa->local_esquerda = mapa->matriz_mapa[x_jog][y_jog - abs(direcao)];
    mapa->local_cima = mapa->matriz_mapa[x_jog - abs(direcao)][y_jog];
    mapa->local_baixo = mapa->matriz_mapa[x_jog + abs(direcao)][y_jog];

    /// Caso porta
    if ((portal->num_porta != ' '))
    {

        // busca a outra porta do par
        printf("%c", portal->num_porta);

        busca_porta(mapa, portal);
        // jogador passa a estar na posição da porta
        x_porta = portal->local_porta.linha;
        y_porta = portal->local_porta.coluna;

        printf("%d %d", x_porta, y_porta);
        mapa->matriz_mapa[x_porta][y_porta] = 'D';
        // posição do jogador volta a ser uma porta
        mapa->matriz_mapa[x_jog][y_jog] = portal->num_porta;


    }


    else
    {
        ///caso escada
        ///Melhorar isso aqui pra ficar mais otimizado
        if (direcao == -1)
        {
            ///zero bloqueia movimento!!!
            if (mapa->matriz_mapa[x_jog-1][y_jog] != 'H' &&
                    mapa->matriz_mapa[x_jog][y_jog+1] != 'X' &&
                    mapa->matriz_mapa[x_jog][y_jog-1] != 'X')
                *escada = 0;

            else if (mapa->matriz_mapa[x_jog+1][y_jog] == 'X' &&
                     mapa->matriz_mapa[x_jog-1][y_jog] != 'H') *escada = 0;

            else *escada = 1;

            if (*escada == 1)
            {
                x_jog--;
                mapa->matriz_mapa[x_jog][y_jog] = 'D';
                mapa->matriz_mapa[x_jog+1][y_jog] = 'H';
            }
        }
        if (direcao == 1)
        {
            if (mapa->matriz_mapa[x_jog+1][y_jog] != 'H') *escada = 0;
            else *escada = 1;
            if (*escada == 1)
            {
                if (mapa->matriz_mapa[x_jog-1][y_jog] != 'H' &&
                        mapa->matriz_mapa[x_jog][y_jog+1] != 'X' &&
                        mapa->matriz_mapa[x_jog][y_jog-1] != 'X')
                    mapa->matriz_mapa[x_jog][y_jog] = ' ';
                else mapa->matriz_mapa[x_jog][y_jog] = 'H';
                x_jog++;
                mapa->matriz_mapa[x_jog][y_jog] = 'D';
            }
        }
        ///Aqui fica o que realmente faz funcionar a questão da caixa
        if (mapa->matriz_mapa[x_jog][y_jog+direcao] == 'C' ||
                mapa->matriz_mapa[x_jog][y_jog+direcao] == 'K' ||
                mapa->matriz_mapa[x_jog][y_jog+direcao] == 'B' ||
                mapa->matriz_mapa[x_jog][y_jog+direcao] == 'G')
        {
            printf("caixinha");
            *xaux = x_jog;
            yaux = y_jog+direcao;
            mapa->matriz_mapa[x_jog][y_jog] = 'D';
            printf("%d %d", *xaux, yaux);
        }

        if (*flag == 1)
        {
            if (direcao == -1)
                mapa->matriz_mapa[x_jog][y_jog-direcao] = mapa->local_direita;
            else
                mapa->matriz_mapa[x_jog][y_jog+direcao] = mapa->local_esquerda;
            *flag = 0;
            *xaux = 0;
        }
    }

    mapa->jogador.pos_jog.linha = x_jog;
    mapa->jogador.pos_jog.coluna = y_jog;

    portal->local_porta.linha = x_porta;
    portal->local_porta.coluna = y_porta;

    mapa->local_direita = mapa->matriz_mapa[x_jog][y_jog + abs(direcao)];
    mapa->local_esquerda = mapa->matriz_mapa[x_jog][y_jog - abs(direcao)];
    mapa->local_cima = mapa->matriz_mapa[x_jog - abs(direcao)][y_jog];
    mapa->local_baixo = mapa->matriz_mapa[x_jog + abs(direcao)][y_jog];

}


///Função para achar a localização da outra cara metade da laranja da porta
void busca_porta(Mapa *mapa, Porta *portal)
{
    int ctl, ctc;
    int linhas, colunas, x_porta, y_porta;

    linhas = mapa->local_mapa.linha;
    colunas = mapa->local_mapa.coluna;
    x_porta = portal->local_porta.linha;
    y_porta = portal->local_porta.coluna;


    for (ctl = 0; ctl < linhas; ctl++)
    {
        for (ctc = 0; ctc < colunas; ctc++)
        {
            if (mapa->matriz_mapa[ctl][ctc] == portal->num_porta)
            {
                printf("encontrei a porta");
                x_porta = ctl;
                y_porta = ctc;
            }
        }
    }
    printf ("A porta esta em x:%d, y:%d\n", x_porta, y_porta);
    mapa->local_mapa.linha = linhas;
    mapa->local_mapa.coluna = colunas;
    portal->local_porta.linha = x_porta;
    portal->local_porta.coluna = y_porta;
}

void proxima_fase(Mapa *mapa)
{
    int flag_chave = 0;
    int cl, cc;
    mapa->fase++;
    mapa->jogador.tem_chave = 0;
    if (mapa->fase == 2)
    {
        mapa_carrega_n2(mapa);
        mapa->cor = GREEN;
        gera_item_bau(mapa, &flag_chave);
        for (cl = 0; cl < mapa->local_mapa.linha; cl++)
        {
            for (cc = 0; cc < mapa->local_mapa.coluna; cc++)
            {
                printf("%c", mapa->matriz_mapa[cl][cc]);
            }
            printf("\n");
        }
    }
    if (mapa->fase == 3)
    {
        mapa_carrega_n3(mapa);
        mapa->cor = PINK;
        gera_item_bau(mapa, &flag_chave);



        for (cl = 0; cl < mapa->local_mapa.linha; cl++)
        {
            for (cc = 0; cc < mapa->local_mapa.coluna; cc++)
            {
                printf("%c", mapa->matriz_mapa[cl][cc]);
            }
            printf("\n");
        }
    }
    if (mapa->fase == 4)
    {
        tela_final(mapa);
        printf("\nJogador %s", mapa->jogador.nome);
        printf("\npontucao: %d", mapa->jogador.pontos);
        printf("cabouuuuuuuu");
    }
}
