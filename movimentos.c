
#define LINHAS 20
#define COLUNAS 25
#define AUMENTOL 109
#define AUMENTOH 91
#include "movimentos.h"
#include "raylib.h"

/// Função para encontrar o jogador
void localiza_jogador(Mapa *mapa)
{
    int ctl = 0, ctc = 0, linhas, colunas, jog_x, jog_y;

    //atualização de variáveis de localização
    linhas = mapa->local_mapa.linha;
    colunas = mapa->local_mapa.coluna;
    jog_x = mapa->jogador.pos_jog.linha;
    jog_y = mapa->jogador.pos_jog.coluna;


    //percorre a matriz para achar o jogador
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
    //atualização de variáveis de localização
    mapa->jogador.pos_jog.linha = jog_x;
    mapa->jogador.pos_jog.coluna = jog_y;
    }
}

/// Movimentação lateral
void movimenta_lado(Mapa *mapa, int locomocao, int direcao, int *xaux,  int *flag, Porta *portal)
{
    int x_jog, y_jog, yaux, fport = 0;
    int queda = 0;
    char tbdir, tbesq;
    Caixa caixinha;

    //localiza o jogador
    localiza_jogador(mapa);

    //atualizção das variáveis
    x_jog = mapa->jogador.pos_jog.linha;
    y_jog = mapa->jogador.pos_jog.coluna;


    //flag que diz se está ou não em cima de uma porta
    if (portal->num_porta != ' ')
        fport = 1;

    if (mapa->matriz_mapa[x_jog][y_jog+direcao] == '1'||mapa->matriz_mapa[x_jog][y_jog+direcao] == '2')
        portal->num_porta = mapa->matriz_mapa[x_jog][y_jog+direcao]; //se o local ao lado for uma porta, *porta ganha o valor do local

    //se tiver uma parede ao seu lado, então não pode se mover
    if (mapa->matriz_mapa[x_jog][y_jog+direcao] == 'X') locomocao = 0;

    //caso contrário, à princípio ele pode se mover
    else locomocao = 1;

    //se não tiver uma parede ao lado
    if (locomocao == 1)
    {
        //guarda as variávais antes de haver qualquer tipo de locomoção
        tbdir = mapa->local_direita;
        printf("tbdir:%c\n", tbdir);
        tbesq = mapa->local_esquerda;
        printf("tbesq: %c\n", tbesq);

        //salva a posição prévia e a seguinte do jogador
        mapa->local_direita = mapa->matriz_mapa[x_jog][y_jog + abs(direcao)];
        mapa->local_esquerda = mapa->matriz_mapa[x_jog][y_jog - abs(direcao)];
        mapa->local_cima = mapa->matriz_mapa[x_jog - abs(direcao)][y_jog];
        mapa->local_baixo = mapa->matriz_mapa[x_jog + abs(direcao)][y_jog];

        printf("mapa local direita %c\n", mapa->local_direita);
        printf("mapa local esquerda %c\n", mapa->local_esquerda);

        //se houver uma escada acima, coloca uma escada onde o jogador estava
        if (mapa->matriz_mapa[x_jog-1][y_jog] == 'H') mapa->matriz_mapa[x_jog][y_jog] = 'H';

        //movimento ao passar por um baú
        else if (mapa->matriz_mapa[x_jog][y_jog+direcao] == 'C' ||
                 mapa->matriz_mapa[x_jog][y_jog+direcao] == 'K' ||
                 mapa->matriz_mapa[x_jog][y_jog+direcao] == 'G' ||
                 mapa->matriz_mapa[x_jog][y_jog+direcao] == 'B')
        {
            *xaux = x_jog;
            yaux = y_jog+direcao;
            mapa->matriz_mapa[x_jog][y_jog] = ' ';
        }
        //senão, coloca espaço
        else mapa->matriz_mapa[x_jog][y_jog] = ' ';

        //e ele se move para lado
        y_jog = y_jog + direcao;
        mapa->matriz_mapa[x_jog][y_jog] = 'D';

        //condições relacionadas às flags do baú
       // printf("%d", *flag);
        if (*flag == 1)
        {
            if (direcao == -1 && (tbdir == 'K'||tbdir == 'G'||tbdir == 'B'))
            {
                printf("entrou: %c", tbdir);
                mapa->matriz_mapa[x_jog][y_jog-direcao] = tbdir;
            }

            else if (direcao == 1 && (tbdir == 'K'||tbdir == 'G'||tbdir == 'B')){
                mapa->matriz_mapa[x_jog][y_jog+direcao] = tbesq;
                printf("%c", tbesq);
            }
            *flag = 0;
            *xaux = 0;
        }

        if (*xaux != 0) //se xaux for dirente de zero (ou seja, tiver uma coordenada),
            *flag = 1; //*flag recebe 1

        //se não tiver chão abaixo, então ele deve continuar caindo
        if (mapa->matriz_mapa[x_jog+1][y_jog] == ' ')
        {
            //atualização das variáveis de localização
            mapa->jogador.pos_jog.linha = x_jog;
            mapa->jogador.pos_jog.coluna = y_jog;

            queda = cair(mapa, direcao);

        }
    }

    //se ele estiver em cima de uma porta
    if (fport == 1)
    {
        //a posição ao lado do jogador recebe o caracter da porta
        mapa->matriz_mapa[x_jog][y_jog-direcao] = portal->num_porta;

        //e as flags da porta são atualizadas
        fport = 0;
        portal->num_porta = ' ';

    }
    //atualização das variáveis de localização
    mapa->jogador.pos_jog.linha = x_jog;
    mapa->jogador.pos_jog.coluna = y_jog;

    mapa->local_cima = mapa->matriz_mapa[x_jog - abs(direcao)][y_jog];
    mapa->local_baixo = mapa->matriz_mapa[x_jog + abs(direcao)][y_jog];

    //controle das vidas do jogador
    if (queda >= 3){
        jog_diminui_vida(mapa);
        morte(mapa, flag);
    }

        /*mapa->local_direita = mapa->matriz_mapa[x_jog][y_jog + abs(direcao)];
        mapa->local_esquerda = mapa->matriz_mapa[x_jog][y_jog - abs(direcao)];
        mapa->local_cima = mapa->matriz_mapa[x_jog - abs(direcao)][y_jog];
        mapa->local_baixo = mapa->matriz_mapa[x_jog + abs(direcao)][y_jog];

        printf("mapa local direita %c\n", mapa->local_direita);
        printf("mapa local esquerda %c\n", mapa->local_esquerda);*/

}


///Função da gravidade
int cair(Mapa *mapa, int direcao)
{
    int cont = 0;
    int x_jog, y_jog;

    //atualização das variáveis de localização
    x_jog = mapa->jogador.pos_jog.linha;
    y_jog = mapa->jogador.pos_jog.coluna;

    mapa->matriz_mapa[x_jog][y_jog] = ' ';

    //ele vai cair, portanto a posição atual dele vai e tornar branco
    while (mapa->matriz_mapa[x_jog+1][y_jog] == ' ')
    {
        x_jog++;
        cont++;

    }
    //o jogador atinge o chão
    mapa->matriz_mapa[x_jog][y_jog] = 'D';

    //atualização das variáveis de localização
    mapa->jogador.pos_jog.linha = x_jog;
    mapa->jogador.pos_jog.coluna = y_jog;
    return cont;
}



/// Movimento vertical

void movimenta_cima(Mapa *mapa, int *escada, int direcao, int *xaux, Porta *portal, int *flag)
{
    int x_jog, y_jog, x_porta, y_porta, yaux;

    //atualização das variáveis de localização
    x_jog = mapa->jogador.pos_jog.linha;
    y_jog = mapa->jogador.pos_jog.coluna;

    x_porta = portal->local_porta.linha;
    y_porta = portal->local_porta.coluna;

    // localiza o jogador
    localiza_jogador(mapa);

    /// Condição para passar de fase
    if (mapa->jogador.tem_chave == 1 && (mapa->local_direita == 'P' || mapa->local_esquerda == 'P'))
    {
        proxima_fase(mapa);
        arq_salva_jogo(*mapa, *escada, *xaux, *portal, *flag);
    }

    //atualização das variáveis de movimento
    mapa->local_direita = mapa->matriz_mapa[x_jog][y_jog + abs(direcao)];
    mapa->local_esquerda = mapa->matriz_mapa[x_jog][y_jog - abs(direcao)];
    mapa->local_cima = mapa->matriz_mapa[x_jog - abs(direcao)][y_jog];
    mapa->local_baixo = mapa->matriz_mapa[x_jog + abs(direcao)][y_jog];

    /// Caso porta
    if ((portal->num_porta != ' '))
    {

        //busca a outra porta do par
        busca_porta(mapa, portal);

        //atualização das variáveis de localização
        x_porta = portal->local_porta.linha;
        y_porta = portal->local_porta.coluna;

        //jogador passa a estar na posição da porta
        mapa->matriz_mapa[x_porta][y_porta] = 'D';

        //posição do jogador volta a ser uma porta
        mapa->matriz_mapa[x_jog][y_jog] = portal->num_porta;


    }


    else
    {
        /// Caso escada
        if (direcao == -1)
        {
            //casos nos quais o movimento é bloqueado
            if (mapa->matriz_mapa[x_jog-1][y_jog] != 'H' &&
                    mapa->matriz_mapa[x_jog][y_jog+1] != 'X' &&
                    mapa->matriz_mapa[x_jog][y_jog-1] != 'X')
                *escada = 0;

            else if (mapa->matriz_mapa[x_jog+1][y_jog] == 'X' &&
                     mapa->matriz_mapa[x_jog-1][y_jog] != 'H') *escada = 0;

            //casos nos quais o movimento é permitido
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
            //caso no qual o movimento é bloqueado
            if (mapa->matriz_mapa[x_jog+1][y_jog] != 'H') *escada = 0;

            //casos nos quais o movimento é permitido
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
        //controle dos itens de dentro da caixa
        if (mapa->matriz_mapa[x_jog][y_jog+direcao] == 'C' ||
                mapa->matriz_mapa[x_jog][y_jog+direcao] == 'K' ||
                mapa->matriz_mapa[x_jog][y_jog+direcao] == 'B' ||
                mapa->matriz_mapa[x_jog][y_jog+direcao] == 'G')
        {
            *xaux = x_jog;
            yaux = y_jog+direcao;
            mapa->matriz_mapa[x_jog][y_jog] = 'D';
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

    //atualização das variáveis de localização
    mapa->jogador.pos_jog.linha = x_jog;
    mapa->jogador.pos_jog.coluna = y_jog;

    portal->local_porta.linha = x_porta;
    portal->local_porta.coluna = y_porta;

    //atualização das variáveis de movimento
    mapa->local_direita = mapa->matriz_mapa[x_jog][y_jog + abs(direcao)];
    mapa->local_esquerda = mapa->matriz_mapa[x_jog][y_jog - abs(direcao)];
    mapa->local_cima = mapa->matriz_mapa[x_jog - abs(direcao)][y_jog];
    mapa->local_baixo = mapa->matriz_mapa[x_jog + abs(direcao)][y_jog];

}

void busca_porta(Mapa *mapa, Porta *portal)
{
    int ctl, ctc;
    int linhas, colunas, x_porta, y_porta;

    //atualização das variáveis de localização
    linhas = mapa->local_mapa.linha;
    colunas = mapa->local_mapa.coluna;
    x_porta = portal->local_porta.linha;
    y_porta = portal->local_porta.coluna;

    //percorre a matriz em busca do caracter da porta
    for (ctl = 0; ctl < linhas; ctl++)
    {
        for (ctc = 0; ctc < colunas; ctc++)
        {
            if (mapa->matriz_mapa[ctl][ctc] == portal->num_porta)
            {
                x_porta = ctl;
                y_porta = ctc;
            }
        }
    }
    //atualização das variáveis de localização
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

    /// Fase 2
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
    /// Fase 3
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
    /// Fim de jogo
    if (mapa->fase == 4)
        tela_final(mapa);
}
