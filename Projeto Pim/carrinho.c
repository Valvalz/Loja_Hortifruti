#include <stdio.h>
#include <stdlib.h>
#include "carrinho.h"
#include "produto.h"

// Definição de cores
#define COR_VERDE "\033[0;32m"
#define COR_VERMELHA "\033[0;31m"
#define COR_AMARELA "\033[0;33m"
#define COR_CIANO "\033[0;36m"
#define COR_RESET "\033[0m"

// Função para adicionar produtos ao carrinho
int carregarProdutos(Produto **produtos) {
    FILE *arquivo = fopen("produtos.bin", "rb");
    if (arquivo == NULL) {
        printf(COR_VERMELHA "Erro ao abrir o arquivo de produtos para leitura!\n" COR_RESET);
        return 0;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    rewind(arquivo);

    int numProdutos = tamanho / sizeof(Produto);
    *produtos = malloc(numProdutos * sizeof(Produto));
    fread(*produtos, sizeof(Produto), numProdutos, arquivo);
    fclose(arquivo);

    return numProdutos;
}

void adicionarAoCarrinho(Carrinho *carrinho, Produto *produtos, int numProdutos) {
    if (numProdutos == 0) {
        printf(COR_VERMELHA "Nenhum produto disponivel para adicionar ao carrinho.\n" COR_RESET);
        return;
    }

    int escolhaProduto;
    int quantidade;

    printf("\n" COR_CIANO "Produtos disponiveis:\n" COR_RESET);
    printf("-------------------------------------------------------------------------------\n");
    printf(COR_AMARELA "| %-3s | %-30s | %-10s | %-18s |\n", "ID", "Nome", "Preco", "Em Estoque");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < numProdutos; i++) {
        printf("| %-3d | %-30s | R$ %-9.2f| %-18d |\n", 
               i + 1, produtos[i].nome, produtos[i].preco, produtos[i].quantidade);
    }

    printf("-------------------------------------------------------------------------------\n");

    printf(COR_CIANO "\nEscolha o numero do produto que deseja adicionar ao carrinho: " COR_RESET);
    scanf("%d", &escolhaProduto);

    if (escolhaProduto >= 1 && escolhaProduto <= numProdutos) {
        printf(COR_CIANO "Quantos itens voce deseja adicionar? " COR_RESET);
        scanf("%d", &quantidade);

        if (quantidade > 0 && quantidade <= produtos[escolhaProduto - 1].quantidade) {
            for (int i = 0; i < quantidade && carrinho->numItens < MAX_CARRINHO; i++) {
                carrinho->itens[carrinho->numItens] = produtos[escolhaProduto - 1];
                carrinho->numItens++;
            }
            produtos[escolhaProduto - 1].quantidade -= quantidade;
            printf(COR_VERDE "\n%d produto(s) adicionado(s) ao carrinho com sucesso!\n" COR_RESET, quantidade);
        } else {
            printf(COR_VERMELHA "Quantidade invalida ou acima do estoque!\n" COR_RESET);
        }
    } else {
        printf(COR_VERMELHA "Escolha invalida! Tente novamente.\n" COR_RESET);
    }
}

// Função para visualizar o carrinho
void visualizarCarrinho(Carrinho *carrinho) {
    printf("\n" COR_CIANO "Carrinho de compras:\n" COR_RESET);

    if (carrinho->numItens == 0) {
        printf(COR_VERMELHA "O carrinho esta vazio.\n" COR_RESET);
        return;
    }

    printf("---------------------------------------------------------------\n");
    printf(COR_AMARELA "| %-3s | %-30s | %-10s |\n", "ID", "Nome", "Preco");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < carrinho->numItens; i++) {
        printf("| %-3d | %-30s | R$ %-9.2f |\n", 
               i + 1, carrinho->itens[i].nome, carrinho->itens[i].preco);
    }

    printf("---------------------------------------------------------------\n");
}

// Função para calcular o total do carrinho
float calcularTotal(Carrinho *carrinho) {
    float total = 0.0;
    for (int i = 0; i < carrinho->numItens; i++) {
        total += carrinho->itens[i].preco;
    }
    return total;
}

// Função para gerenciar o menu do carrinho
void menuCarrinho(Carrinho *carrinho) {
    Produto *produtos;
    int numProdutos = carregarProdutos(&produtos);
    
    if (numProdutos == 0) {
        printf(COR_VERMELHA "Nenhum produto disponivel.\n" COR_RESET);
        return;
    }

    int opcao;
    do {
        printf("\n");
        printf(COR_CIANO "==========================================================\n" COR_RESET);
        printf(COR_CIANO "|                  🛒 Menu do Carrinho                 |\n" COR_RESET);
        printf(COR_CIANO "==========================================================\n" COR_RESET);
        printf(COR_VERDE "| (1) Adicionar ao Carrinho  |  (2) Visualizar Carrinho  |\n" COR_RESET);
        printf(COR_VERDE "|                                                        |\n" COR_RESET);
        printf(COR_VERDE "| (3) Calcular Total         |  (0) Sair                 |\n" COR_RESET);
        printf(COR_VERDE "|                                                        |\n" COR_RESET);
        printf(COR_CIANO "==========================================================\n" COR_RESET);
        printf("\n\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\n");
                adicionarAoCarrinho(carrinho, produtos, numProdutos);
                break;
            case 2:
                printf("\n");
                visualizarCarrinho(carrinho);
                break;
            case 3:
                printf("\nTotal do Carrinho: R$ %.2f\n", calcularTotal(carrinho));
                break;
            case 0:
                printf(COR_AMARELA "Saindo do menu do carrinho... Obrigado pela visita!\n" COR_RESET);
                break;
            default:
                printf(COR_VERMELHA "Opcao invalida! Tente novamente.\n" COR_RESET);
        }
    } while (opcao != 0);

    free(produtos); // Libere a memória alocada
}
