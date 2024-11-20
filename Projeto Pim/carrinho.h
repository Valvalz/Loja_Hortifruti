#ifndef CARRINHO_H
#define CARRINHO_H

#include "produto.h"

// Definição da constante para o máximo de itens no carrinho
#define MAX_CARRINHO 100

// Estrutura para representar um item no carrinho
typedef struct {
    Produto itens[MAX_CARRINHO]; // Array de produtos
    int numItens;                // Número atual de itens no carrinho
} Carrinho;

// Funções para gerenciar o carrinho
void adicionarAoCarrinho(Carrinho *carrinho, Produto *produtos, int numProdutos);
void visualizarCarrinho(Carrinho *carrinho);
float calcularTotal(Carrinho *carrinho);
void menuCarrinho(Carrinho *carrinho);

#endif // CARRINHO_H
