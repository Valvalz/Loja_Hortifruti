#ifndef PRODUTO_H
#define PRODUTO_H

#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura Produto
typedef struct {
    int id_produto;
    float preco;
    char nome[50];
    int quantidade;
} Produto;

// Definição da estrutura Indice, usada para indexação dos produtos
typedef struct {
    int id_produto;
    long int endereco;
} Indice;

// Declarações das funções para cadastro e consulta de produtos
void menuProduto(); // Declara a função aqui
void cadastrar_produto(FILE *arquivo, FILE *indice);
void consultar_produto(FILE *arquivo, FILE *indice);

#endif


