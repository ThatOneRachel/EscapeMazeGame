#ifndef COORDENADAS_H
#define COORDENADAS_H
typedef struct {
    int linha;
    int coluna;
} Localizacao;

Localizacao localizacao_cria(int linha, int coluna);
#endif // COORDENADAS_H
