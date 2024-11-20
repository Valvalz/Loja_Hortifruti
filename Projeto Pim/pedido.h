// pedido.h
#ifndef PEDIDO_H
#define PEDIDO_H

#include "produto.h"  // Para manipulação de produtos no pedido
#include <stdio.h>

#define MAX_ITENS_PEDIDO 100

typedef struct {
    int id;
    Produto itens[MAX_ITENS_PEDIDO];
    int numItens;
    float total;
} Pedido;

// Funções para manipular pedidos
void inicializarPedidos();
void cadastrarPedido(Pedido pedido);
void listarPedidos();
int buscarPedido(int id);
int removerPedido(int id);
void atualizarPedido(int id, Produto produto, int quantidade);
void salvarPedidosNoArquivo();
void carregarPedidosDoArquivo();

#endif // PEDIDO_H
