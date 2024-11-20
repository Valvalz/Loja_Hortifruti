#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"

// Definições de cores
#define COR_VERDE "\033[0;32m"
#define COR_VERMELHA "\033[0;31m"
#define COR_AMARELA "\033[0;33m"
#define COR_RESET "\033[0m"

// Protótipos das funções
void remover_produto(FILE *arquivo, FILE *indice);   // Declarando a função remover_produto
void exibir_menu();
void abrir_arquivos(FILE **arquivo, FILE **indice);
void fechar_arquivos(FILE *arquivo, FILE *indice);
void cadastrar_produto(FILE *arquivo, FILE *indice);
void consultar_produto(FILE *arquivo, FILE *indice);
void gerar_relatorio_produtos(FILE *arquivo);         // Função para gerar relatório de produtos
void excluir_relatorio_produtos();                    // Declarando a função excluir_relatorio_produtos

// Função que exibe o menu de produtos e gerencia as operações
void menuProduto() {
    FILE *arquivo;
    FILE *indice;
    int opcao;

    abrir_arquivos(&arquivo, &indice);
    if (!arquivo || !indice) return; // Se não conseguir abrir os arquivos, sai da função

    // Loop do menu principal
    do {
        exibir_menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_produto(arquivo, indice);
                break;
            case 2:
                fclose(arquivo);
                abrir_arquivos(&arquivo, &indice); // Reabre os arquivos para leitura
                if (!arquivo) return; // Se não conseguir abrir, sai da função
                consultar_produto(arquivo, indice);
                fclose(arquivo);
                abrir_arquivos(&arquivo, &indice); // Reabre para futuras operações
                break;
            case 3:
                remover_produto(arquivo, indice);
                break;
            case 4:
                gerar_relatorio_produtos(arquivo); // Geração do relatório
                break;
            case 5:
                excluir_relatorio_produtos();      // Excluir o relatório
                break;
            case 0:
                printf(COR_VERDE "Saindo...\n" COR_RESET);
                break;
            default:
                printf(COR_VERMELHA "Opcao invalida! Tente novamente.\n" COR_RESET);
        }
    } while (opcao != 0);

    fechar_arquivos(arquivo, indice);
}

// Função para exibir o menu
void exibir_menu() {
    // Definindo cores
    #define COR_MENU "\033[0;36m"     // Ciano
    #define COR_TITULO "\033[1;33m"   // Amarelo forte
    #define COR_RESET "\033[0m"       // Resetar cor

    // Animação de entrada
    printf(COR_MENU "==================================================\n");
    printf(COR_TITULO "|                Menu de Produtos                |\n");
    printf(COR_MENU "==================================================\n");
    
    printf(COR_RESET "| [1] Cadastrar Produto  | [2] Consultar Produto |\n");
    printf(COR_RESET "|                                                |\n");
    printf(COR_RESET "| [3] Remover Produto    | [4] Gerar Relatorio   |\n");
    printf(COR_RESET "|                                                |\n");
    printf(COR_RESET "| [5] Excluir Relatorio  | [0] Sair              |\n");
    printf(COR_MENU "==================================================\n");
    
    printf("\n");
    // Impressão de um toque extra
    printf(COR_TITULO "Escolha uma opcao e pressione Enter\n" COR_RESET);
    printf(COR_MENU "==================================================\n\n");
} 

// Função para abrir os arquivos
void abrir_arquivos(FILE **arquivo, FILE **indice) {
    *arquivo = fopen("produtos.bin", "ab+");
    if (*arquivo == NULL) {
        printf(COR_VERMELHA "Erro ao abrir o arquivo de produtos!\n" COR_RESET);
        return;
    }
    *indice = fopen("produtos.idx", "ab+");
    if (*indice == NULL) {
        printf(COR_VERMELHA "Erro ao abrir o arquivo de índice!\n" COR_RESET);
        fclose(*arquivo);
        return;
    }
}

// Função para fechar os arquivos
void fechar_arquivos(FILE *arquivo, FILE *indice) {
    fclose(arquivo);
    fclose(indice);
}

// Função para gerar o relatório de produtos
void gerar_relatorio_produtos(FILE *arquivo) {
    Produto produto;
    FILE *relatorio = fopen("relatorio_produtos.txt", "w");
    
    if (!relatorio) {
        printf(COR_VERMELHA "Erro ao criar o arquivo de relatório!\n" COR_RESET);
        return;
    }

    // Rewind no arquivo de produtos para garantir que começamos do início
    rewind(arquivo);

    fprintf(relatorio, "==================================================\n");
    fprintf(relatorio, "                Relatório de Produtos            \n");
    fprintf(relatorio, "==================================================\n");
    fprintf(relatorio, "|  ID    |        Nome        | Preco   | Quantidade |\n");
    fprintf(relatorio, "==================================================\n");

    // Lê e grava todos os produtos cadastrados no arquivo de relatório
    while (fread(&produto, sizeof(Produto), 1, arquivo)) {
        fprintf(relatorio, "| %-6d | %-18s | %-7.2f | %-10d |\n", produto.id_produto, produto.nome, produto.preco, produto.quantidade);
    }

    fprintf(relatorio, "==================================================\n");

    fclose(relatorio);

    printf(COR_VERDE "Relatório de produtos gerado com sucesso!\n" COR_RESET);
}

// Função para excluir o relatório de produtos
void excluir_relatorio_produtos() {
    if (remove("relatorio_produtos.txt") == 0) {
        printf(COR_VERDE "Relatorio excluido com sucesso!\n" COR_RESET);
    } else {
        printf(COR_VERMELHA "Erro ao excluir o relatorio. O arquivo pode nao existir.\n" COR_RESET);
    }
}

// Função para cadastrar um produto e gravá-lo no arquivo binário e no índice
void cadastrar_produto(FILE *arquivo, FILE *indice) {
    Produto produto;
    Indice idx;
    int id_existente = 0;
    int nome_existente = 0;

    // Coleta informações do produto
    printf("Digite o ID do produto: ");
    scanf("%d", &produto.id_produto);
    printf("\n");

    // Verificar se o ID já existe
    rewind(indice); // Reseta o ponteiro do arquivo de índice
    while (fread(&idx, sizeof(Indice), 1, indice)) {
        if (idx.id_produto == produto.id_produto) {
            id_existente = 1;
            break;
        }
    }
    
    if (id_existente) {
        printf(COR_VERMELHA "Erro: Ja existe um produto com esse ID!\n" COR_RESET);
        return;
    }

    // Coleta o nome do produto e verifica se já existe
    printf("Digite o nome do produto: ");
    scanf(" %[^\n]", produto.nome);
    printf("\n");

    rewind(arquivo); // Reseta o ponteiro do arquivo de produtos
    while (fread(&produto, sizeof(Produto), 1, arquivo)) {
        if (strcmp(produto.nome, produto.nome) == 0) {
            nome_existente = 1;
            break;
        }
    }

    if (nome_existente) {
        printf(COR_VERMELHA "Erro: Ja existe um produto com esse nome!\n" COR_RESET);
        return;
    }

    // Coleta as outras informações do produto
    printf("Digite o preco do produto: ");
    scanf("%lf", &produto.preco);
    printf("Digite a quantidade do produto: ");
    scanf("%d", &produto.quantidade);
    printf("\n");

    // Grava o produto no arquivo
    fseek(arquivo, 0, SEEK_END);
    fwrite(&produto, sizeof(Produto), 1, arquivo);
    printf(COR_VERDE "Produto cadastrado com sucesso!\n" COR_RESET);

    // Atualiza o índice com o produto
    idx.id_produto = produto.id_produto;
    idx.endereco = ftell(arquivo) - sizeof(Produto);
    fwrite(&idx, sizeof(Indice), 1, indice);
}

// Função para remover produto
void remover_produto(FILE *arquivo, FILE *indice) {
    // Implementação do remover produto
}
void consultar_produto(FILE *arquivo, FILE *indice) {
    int id_produto;
    Produto produto;
    Indice idx;
    int encontrado = 0;

    // Solicita o ID do produto ao usuário
    printf("Digite o ID do produto para consulta: ");
    scanf("%d", &id_produto);

    // Busca o índice do produto
    rewind(indice); // Reposiciona o ponteiro do arquivo índice no início
    while (fread(&idx, sizeof(Indice), 1, indice)) {
        if (idx.id_produto == id_produto) {
            // Produto encontrado no índice
            fseek(arquivo, idx.endereco, SEEK_SET); // Posiciona o ponteiro do arquivo de produtos
            fread(&produto, sizeof(Produto), 1, arquivo); // Lê o produto encontrado
            encontrado = 1;
            break;
        }
    }

    // Exibe as informações do produto encontrado
    if (encontrado) {
        printf("\nProduto encontrado:\n");
        printf("ID: %d\n", produto.id_produto);
        printf("Nome: %s\n", produto.nome);
        printf("Preco: %.2f\n", produto.preco);
        printf("Quantidade: %d\n\n", produto.quantidade);
    } else {
        printf("Produto não encontrado.\n");
    }
}