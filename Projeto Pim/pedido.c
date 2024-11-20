// pedido.c
#include "pedido.h"
#include <string.h>
#include <stdio.h>

#define ARQUIVO_PEDIDOS "pedidos.txt"

// Definindo cores para mensagens
#define COR_ERRO "\033[1;31m"   // Vermelho forte
#define COR_SUCESSO "\033[1;32m" // Verde forte
#define COR_RESET "\033[0m"      // Resetar cor

static Pedido pedidos[MAX_ITENS_PEDIDO];
static int numPedidos = 0;

// Inicializa a lista de pedidos e carrega dados do arquivo
void inicializarPedidos() {
    numPedidos = 0;
    carregarPedidosDoArquivo();
}

// Cadastra um novo pedido
void cadastrarPedido(Pedido pedido) {
    if (numPedidos < MAX_ITENS_PEDIDO) {
        pedidos[numPedidos++] = pedido;
        salvarPedidosNoArquivo();
        printf(COR_SUCESSO "Pedido cadastrado com sucesso!\n" COR_RESET);
    } else {
        printf(COR_ERRO ":: Capacidade máxima de pedidos atingida ::\n" COR_RESET);
    }
}

// Lista todos os pedidos
void listarPedidos() {
    printf("=====================================\n");
    printf("         Lista de Pedidos           \n");
    printf("=====================================\n");
    for (int i = 0; i < numPedidos; i++) {
        printf("Pedido ID: %d | Total: %.2f | Itens: %d\n",
               pedidos[i].id, pedidos[i].total, pedidos[i].numItens);
    }
    printf("=====================================\n");
}

// Busca um pedido pelo ID
int buscarPedido(int id) {
    for (int i = 0; i < numPedidos; i++) {
        if (pedidos[i].id == id) {
            return i; // Retorna o índice do pedido encontrado
        }
    }
    return -1; // Retorna -1 se o pedido não for encontrado
}

// Remove um pedido pelo ID
int removerPedido(int id) {
    int indice = buscarPedido(id);
    if (indice != -1) {
        for (int i = indice; i < numPedidos - 1; i++) {
            pedidos[i] = pedidos[i + 1]; // Desloca os pedidos para preencher o espaço
        }
        numPedidos--;
        salvarPedidosNoArquivo();
        printf(COR_SUCESSO "Pedido removido com sucesso!\n" COR_RESET);
        return 1;
    }
    printf(COR_ERRO " :: Pedido não encontrado ::\n" COR_RESET);
    return 0;
}

// Atualiza um pedido adicionando um produto
void atualizarPedido(int id, Produto produto, int quantidade) {
    int indice = buscarPedido(id);
    if (indice != -1 && pedidos[indice].numItens < MAX_ITENS_PEDIDO) {
        pedidos[indice].itens[pedidos[indice].numItens++] = produto;
        pedidos[indice].total += produto.preco * quantidade;
        salvarPedidosNoArquivo();
        printf(COR_SUCESSO "Pedido atualizado com sucesso!\n" COR_RESET);
    } else {
        printf(COR_ERRO ":: Pedido não encontrado ou quantidade máxima de itens excedida ::\n" COR_RESET);
    }
}

// Salva todos os pedidos no arquivo
void salvarPedidosNoArquivo() {
    FILE *arquivo = fopen(ARQUIVO_PEDIDOS, "w");
    if (arquivo == NULL) {
        printf(COR_ERRO ":: Erro ao salvar pedidos ::\n" COR_RESET);
        return;
    }

    fprintf(arquivo, "%d\n", numPedidos);
    for (int i = 0; i < numPedidos; i++) {
        fprintf(arquivo, "%d %.2f %d\n", pedidos[i].id, pedidos[i].total, pedidos[i].numItens);
        for (int j = 0; j < pedidos[i].numItens; j++) {
            fprintf(arquivo, "%d %.2f %d\n", pedidos[i].itens[j].id_produto, pedidos[i].itens[j].preco, pedidos[i].itens[j].quantidade);
        }
    }

    fclose(arquivo);
    printf(COR_SUCESSO "Pedidos salvos com sucesso!\n" COR_RESET);
}

// Carrega os pedidos do arquivo
void carregarPedidosDoArquivo() {
    FILE *arquivo = fopen(ARQUIVO_PEDIDOS, "r");
    if (arquivo == NULL) {
        printf(COR_ERRO ":: Arquivo de pedidos não encontrado. Iniciando vazio ::\n" COR_RESET);
        return;
    }

    fscanf(arquivo, "%d\n", &numPedidos);
    for (int i = 0; i < numPedidos; i++) {
        fscanf(arquivo, "%d %f %d\n", &pedidos[i].id, &pedidos[i].total, &pedidos[i].numItens);
        for (int j = 0; j < pedidos[i].numItens; j++) {
            fscanf(arquivo, "%d %f %d\n", &pedidos[i].itens[j].id_produto, &pedidos[i].itens[j].preco, &pedidos[i].itens[j].quantidade);
        }
    }

    fclose(arquivo);
    printf(COR_SUCESSO "Pedidos carregados com sucesso!\n" COR_RESET);
}
