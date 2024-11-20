#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fornecedor.h"

#define MAX_FORNECEDORES 100

// Definindo cores para mensagens
#define COR_ERRO "\033[1;31m"   // Vermelho forte
#define COR_SUCESSO "\033[1;32m" // Verde forte
#define COR_RESET "\033[0m"      // Resetar cor
#define COR_VERDE "\033[0;32m"
#define COR_VERMELHA "\033[0;31m"
#define COR_AMARELA "\033[0;33m"
#define COR_CIANO "\033[0;36m"
#define COR_RESET "\033[0m"

Fornecedor fornecedores[MAX_FORNECEDORES];
int numFornecedores = 0;

// Protótipos das funções
void adicionarFornecedorMenu();
void listarFornecedores();
void salvarFornecedoresArquivo();
void carregarFornecedoresArquivo();
int buscarFornecedor(int id);
int removerFornecedor(int id);
void cadastrarFornecedor(Fornecedor *fornecedor);
void lerFornecedor(Fornecedor *fornecedor);
void gerarRelatorioFornecedores();
void excluirRelatorioFornecedores(); // Função para gerar relatório

void menuFornecedor() {
    carregarFornecedoresArquivo(); // Carrega fornecedores ao iniciar o menu

    int opcao;
    do {
        printf("\n");
        printf(COR_CIANO "==============================================================\n" COR_RESET);
        printf(COR_CIANO "|                     Menu Fornecedores                      |\n" COR_RESET);
        printf(COR_CIANO "==============================================================\n" COR_RESET);
        printf(COR_VERDE "| (1). Adicionar Fornecedor  |  (2). Listar Fornecedores     |\n" COR_RESET);
        printf(COR_VERDE "|                                                            |\n" COR_RESET);
        printf(COR_VERDE "| (3). Remover Fornecedor    |  (4). Relatorio Fornecedores  |\n" COR_RESET);
        printf(COR_VERDE "|                                                            |\n" COR_RESET);
        printf(COR_VERDE "| (5). Excluir Relatorio     |  (0). Sair                    |\n" COR_RESET); 
        printf(COR_VERDE "|                                                            |\n" COR_RESET);
        printf(COR_CIANO "==============================================================\n" COR_RESET);
        printf("\n\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                adicionarFornecedorMenu();
                break;
            case 2:
                listarFornecedores();
                break;
            case 3: {
                int id;
                printf("Digite o ID do fornecedor a remover: ");
                scanf("%d", &id);
                if (removerFornecedor(id)) {
                    printf(COR_SUCESSO "Fornecedor removido com sucesso.\n" COR_RESET);
                } else {
                    printf(COR_ERRO "Fornecedor não encontrado.\n" COR_RESET);
                }
                break;
            }
            case 4:
                gerarRelatorioFornecedores(); // Chama a função de relatório
                break;

                 case 5:
                excluirRelatorioFornecedores(); // Chama a função de excluir relatório
                break;
            case 0:
                printf("Saindo do menu...\n");
                break;
            default:
                printf(COR_ERRO "Opcao invalida!\n" COR_RESET);
        }
    } while (opcao != 0);
}

void gerarRelatorioFornecedores() {
    printf(COR_CIANO "=====================================\n" COR_RESET);
    printf(COR_CIANO "         Relatorio de Fornecedores   \n" COR_RESET);
    printf(COR_CIANO "=====================================\n" COR_RESET);
    if (numFornecedores == 0) {
        printf(COR_VERMELHA "Nenhum fornecedor cadastrado.\n" COR_RESET);
        return;
    }
    for (int i = 0; i < numFornecedores; i++) {
        printf(COR_AMARELA "ID: %d\n" COR_RESET, fornecedores[i].id);
        printf("Nome Fantasia: %s\n", fornecedores[i].nome_fantasia);
        printf("Nome da Empresa: %s\n", fornecedores[i].nome_empresa);
        printf("CNPJ: %s\n", fornecedores[i].cnpj);
        printf("Telefone: %s\n", fornecedores[i].telefone);
        printf("Endereco: %s\n", fornecedores[i].endereco);
        printf("Email: %s\n", fornecedores[i].email);
        printf(COR_CIANO "-------------------------------------\n" COR_RESET);
    }
}



// Definição da função
void excluirRelatorioFornecedores() {
    if (remove("relatorio_fornecedores.txt") == 0) {
        printf("Relatório de fornecedores excluído com sucesso!\n");
    } else {
        printf("Erro ao excluir o relatorio. O arquivo pode nao existir.\n");
    }
}

void adicionarFornecedorMenu() {
    Fornecedor fornecedor;
    printf("Cadastro de Fornecedor\n");
    lerFornecedor(&fornecedor);
    fornecedor.id = numFornecedores + 1; // Define ID automaticamente
    adicionarFornecedor(fornecedor);
}

void adicionarFornecedor(Fornecedor fornecedor) {
    if (numFornecedores < MAX_FORNECEDORES) {
        fornecedores[numFornecedores++] = fornecedor;
        salvarFornecedoresArquivo();
        printf(COR_SUCESSO "Fornecedor cadastrado com sucesso!\n" COR_RESET);
    } else {
        printf(COR_ERRO "Erro: Número máximo de fornecedores atingido.\n" COR_RESET);
    }
}

void listarFornecedores() {
    printf("=====================================\n");
    printf("         Lista de Fornecedores      \n");
    printf("=====================================\n");
    for (int i = 0; i < numFornecedores; i++) {
        printf("ID: %d\nNome Fantasia: %s\nNome da Empresa: %s\nCNPJ: %s\nTelefone: %s\nEndereco: %s\nEmail: %s\n\n",
               fornecedores[i].id, fornecedores[i].nome_fantasia, fornecedores[i].nome_empresa,
               fornecedores[i].cnpj, fornecedores[i].telefone, fornecedores[i].endereco, fornecedores[i].email);
    }
    printf("=====================================\n");
}

int buscarFornecedor(int id) {
    for (int i = 0; i < numFornecedores; i++) {
        if (fornecedores[i].id == id) {
            return i; // Retorna o índice do fornecedor encontrado
        }
    }
    return -1; // Retorna -1 se o fornecedor não for encontrado
}

int removerFornecedor(int id) {
    int indice = buscarFornecedor(id);
    if (indice != -1) {
        for (int i = indice; i < numFornecedores - 1; i++) {
            fornecedores[i] = fornecedores[i + 1]; // Desloca os fornecedores para preencher o espaço
        }
        numFornecedores--;
        salvarFornecedoresArquivo();
        return 1;
    }
    return 0;
}

void salvarFornecedoresArquivo() {
    FILE *file = fopen("fornecedores.txt", "w");
    if (file == NULL) {
        perror(COR_ERRO "Erro ao abrir arquivo de fornecedores." COR_RESET);
        return;
    }
    for (int i = 0; i < numFornecedores; i++) {
        fprintf(file, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n",
                fornecedores[i].id, fornecedores[i].nome_fantasia, fornecedores[i].nome_empresa,
                fornecedores[i].cnpj, fornecedores[i].telefone, fornecedores[i].endereco, fornecedores[i].email);
    }
    fclose(file);
    printf(COR_SUCESSO "Fornecedores salvos com sucesso!\n" COR_RESET);
}

void carregarFornecedoresArquivo() {
    FILE *file = fopen("fornecedores.txt", "r");
    if (file == NULL) {
        printf(COR_ERRO "Arquivo de fornecedores não encontrado.\n" COR_RESET);
        return;
    }
    numFornecedores = 0;
    while (fscanf(file, "%d\n", &fornecedores[numFornecedores].id) == 1) {
        fgets(fornecedores[numFornecedores].nome_fantasia, TAM_NOME, file);
        strtok(fornecedores[numFornecedores].nome_fantasia, "\n"); // Remover nova linha
        fgets(fornecedores[numFornecedores].nome_empresa, TAM_NOME, file);
        strtok(fornecedores[numFornecedores].nome_empresa, "\n");
        fgets(fornecedores[numFornecedores].cnpj, TAM_CNPJ, file);
        strtok(fornecedores[numFornecedores].cnpj, "\n");
        fgets(fornecedores[numFornecedores].telefone, TAM_TELEFONE, file);
        strtok(fornecedores[numFornecedores].telefone, "\n");
        fgets(fornecedores[numFornecedores].endereco, TAM_ENDERECO, file);
        strtok(fornecedores[numFornecedores].endereco, "\n");
        fgets(fornecedores[numFornecedores].email, TAM_EMAIL, file);
        strtok(fornecedores[numFornecedores].email, "\n");
        numFornecedores++;
    }
    fclose(file);
    printf(COR_SUCESSO "Fornecedores carregados com sucesso!\n" COR_RESET);
}

void lerFornecedor(Fornecedor *fornecedor) {
    printf("Nome Fantasia: ");
    getchar(); // Para consumir o '\n' restante no buffer
    fgets(fornecedor->nome_fantasia, TAM_NOME, stdin);
    strtok(fornecedor->nome_fantasia, "\n");  // Remove o '\n'

    printf("Nome da Empresa: ");
    fgets(fornecedor->nome_empresa, TAM_NOME, stdin);
    strtok(fornecedor->nome_empresa, "\n");

    printf("CNPJ: ");
    fgets(fornecedor->cnpj, TAM_CNPJ, stdin);
    strtok(fornecedor->cnpj, "\n");

    printf("Telefone: ");
    fgets(fornecedor->telefone, TAM_TELEFONE, stdin);
    strtok(fornecedor->telefone, "\n");

    printf("Endereco: ");
    fgets(fornecedor->endereco, TAM_ENDERECO, stdin);
    strtok(fornecedor->endereco, "\n");

    printf("Email: ");
    fgets(fornecedor->email, TAM_EMAIL, stdin);
    strtok(fornecedor->email, "\n");
}

