#include <stdio.h>
#include "finalizar.h"

#define COR_VERDE "\033[0;32m"
#define COR_VERMELHA "\033[0;31m"
#define COR_AMARELA "\033[0;33m"
#define COR_CINZA "\033[0;37m"
#define COR_RESET "\033[0m"
#define COR_ROXO "\033[0;35m"
#define COR_BRANCO "\033[1;37m"

// Função para salvar o histórico de vendas
void salvar_historico(Carrinho *carrinho, float total) {
    FILE *historico = fopen("historico_vendas.txt", "a"); // Abre o arquivo para adicionar novas vendas
    if (!historico) {
        printf(COR_VERMELHA "Erro ao abrir o arquivo de historico.\n" COR_RESET);
        return;
    }

    // Registra a data e hora da venda (pode-se adicionar uma função para isso)
    fprintf(historico, "\n=====================================\n");
    fprintf(historico, "       ** HISTORICO DE VENDAS **    \n");
    fprintf(historico, "=====================================\n");

    // Escreve os detalhes dos produtos comprados
    for (int i = 0; i < carrinho->numItens; i++) {
        fprintf(historico, "%d. %-20s - R$ %.2f\n", i + 1, carrinho->itens[i].nome, carrinho->itens[i].preco);
    }

    // Escreve o total da venda
    fprintf(historico, "\nTOTAL: R$ %.2f\n", total);
    fprintf(historico, "=====================================\n");

    fclose(historico); // Fecha o arquivo de histórico
}

// Função para exibir o histórico de vendas
void exibir_historico() {
    FILE *historico = fopen("historico_vendas.txt", "r"); // Abre o arquivo para leitura
    if (!historico) {
        printf(COR_VERMELHA "Erro ao abrir o arquivo de historico.\n" COR_RESET);
        return;
    }

    char linha[256];
    printf("\n%sHistorico de Vendas:%s\n", COR_ROXO, COR_RESET);
    printf("%s=====================================%s\n", COR_ROXO, COR_RESET);

    while (fgets(linha, sizeof(linha), historico)) {
        printf("%s", linha);
    }

    fclose(historico); // Fecha o arquivo de histórico
}

// Função para limpar o histórico de vendas
void limpar_historico() {
    // Abre o arquivo de histórico em modo de escrita ("w"), o que apaga o conteúdo existente.
    FILE *historico = fopen("historico_vendas.txt", "w"); 
    if (!historico) {
        printf(COR_VERMELHA "Erro ao abrir o arquivo de historico para limpeza.\n" COR_RESET);
        return;
    }

    // Sobrescreve o arquivo, apagando seu conteúdo
    fprintf(historico, "Historico de Vendas Limpo.\n");

    fclose(historico); // Fecha o arquivo após limpar
    printf(COR_VERDE "Historico de vendas limpo com sucesso!\n" COR_RESET);
}


// Função para finalizar a venda
void finalizar(Carrinho *carrinho) {
    if (carrinho->numItens == 0) {
        printf(COR_VERMELHA "O carrinho esta vazio. Nao ha vendas para finalizar.\n" COR_RESET);
        return;
    }

    float total = 0.0;
    printf("\n%sItens Comprados:%s\n", COR_CINZA, COR_RESET);
    printf("%s=====================================%s\n", COR_CINZA, COR_RESET);

    for (int i = 0; i < carrinho->numItens; i++) {
        printf("%d. %-20s - R$ %.2f\n", i + 1, carrinho->itens[i].nome, carrinho->itens[i].preco);
        total += carrinho->itens[i].preco;
    }

    printf("\n%sTotal a Pagar:%s R$ %.2f\n", COR_AMARELA, COR_RESET, total);

    char confirmacao;
    printf(COR_AMARELA "Deseja finalizar a venda? (s/n): " COR_RESET);
    scanf(" %c", &confirmacao);

    if (confirmacao != 's' && confirmacao != 'S') {
        printf(COR_VERDE "Operacao de finalizacao cancelada.\n" COR_RESET);
        return;
    }

    // Salva o histórico da venda no arquivo
    salvar_historico(carrinho, total);

    printf("\n%s=====================================%s\n", COR_VERDE, COR_RESET);
    printf("%s   VENDA FINALIZADA COM SUCESSO!%s\n", COR_VERDE, COR_RESET);
    printf("%s=====================================%s\n", COR_VERDE, COR_RESET);

    // Limpa o carrinho após a venda
    carrinho->numItens = 0;

    // Exibe o histórico de vendas
    exibir_historico();

    printf("\n%sObrigado por sua compra! Volte sempre!%s\n", COR_VERDE, COR_RESET);
}

