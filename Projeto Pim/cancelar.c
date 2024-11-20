// cancelar_venda.c
#include <stdio.h>
#include "carrinho.h"
#include "produto.h"

// Definicao de cores
#define COR_VERDE "\033[0;32m"
#define COR_VERMELHA "\033[0;31m"
#define COR_AMARELA "\033[0;33m"
#define COR_RESET "\033[0m"

// Funcao para cancelar um item especifico no carrinho
void cancelarVenda(Carrinho *carrinho) {
    if (carrinho->numItens == 0) {
        printf(COR_VERMELHA "O carrinho esta vazio. Nao ha nada para cancelar.\n" COR_RESET);
        return;
    }

    visualizarCarrinho(carrinho); // Exibe o carrinho para escolher qual item remover
    int indice;

    printf(COR_AMARELA "== Digite o numero do item que deseja remover do carrinho =: " COR_RESET);
    scanf("%d", &indice);

    if (indice < 1 || indice > carrinho->numItens) {
        printf(COR_VERMELHA "Indice invalido.\n" COR_RESET);
        return;
    }

    // Confirmacao antes de remover o item
    char confirmacao;
    printf("\n");
    printf(COR_AMARELA "Tem certeza de que deseja remover o item %d? (s/n): " COR_RESET, indice);
    scanf(" %c", &confirmacao);

    if (confirmacao != 's' && confirmacao != 'S') {
        printf(COR_VERDE "Operacao de remocao cancelada.\n" COR_RESET);
        return;
    }

    // Remove o item, ajustando os itens restantes
    for (int i = indice - 1; i < carrinho->numItens - 1; i++) {
        carrinho->itens[i] = carrinho->itens[i + 1];
    }
    carrinho->numItens--; // Reduz o numero de itens no carrinho

    // Mensagem de sucesso ao remover o item
    printf(COR_VERDE ":: Item removido do carrinho com sucesso ::\n" COR_RESET);

    // Exibe o estado atualizado do carrinho
    printf(COR_AMARELA "\nEstado atual do carrinho:\n" COR_RESET);
    if (carrinho->numItens == 0) {
        printf(COR_VERMELHA "O carrinho esta vazio.\n" COR_RESET);
    } else {
        for (int i = 0; i < carrinho->numItens; i++) {
            printf("%d. %s - R$ %.2f\n", i + 1, carrinho->itens[i].nome, carrinho->itens[i].preco);
        }
    }
}
