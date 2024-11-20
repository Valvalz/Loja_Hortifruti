#ifndef FORNECEDOR_H
#define FORNECEDOR_H

#define TAM_NOME 100
#define TAM_CNPJ 20
#define TAM_TELEFONE 15
#define TAM_ENDERECO 200
#define TAM_EMAIL 100

// Estrutura para armazenar informações do fornecedor
typedef struct {
    int id; // Identificador do fornecedor
    char nome_fantasia[TAM_NOME]; // Nome fantasia do fornecedor
    char nome_empresa[TAM_NOME]; // Nome da empresa do fornecedor
    char cnpj[TAM_CNPJ]; // CNPJ do fornecedor
    char telefone[TAM_TELEFONE]; // Telefone do fornecedor
    char endereco[TAM_ENDERECO]; // Endereço do fornecedor
    char email[TAM_EMAIL]; // Email do fornecedor
} Fornecedor;

// Protótipos das funções
void adicionarFornecedor(Fornecedor fornecedor);
void listarFornecedores();
int removerFornecedor(int id);
void carregarFornecedoresArquivo();
void salvarFornecedoresArquivo();

#endif // FORNECEDOR_H
