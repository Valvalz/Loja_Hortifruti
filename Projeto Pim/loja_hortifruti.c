#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h> // Para a função isalpha
#include <conio.h> // Usado para capturar teclas sem exibi-las
#include "produto.h"// Inclua o cabeçalho do produto
#include "pedido.h" // Inclua o cabeçalho de pedidos
#include "fornecedor.h"
#include "carrinho.h"
#include "cancelar.h"
#include "finalizar.h"
#include <unistd.h>  // Para usar usleep()



#define LARGURA_TELA 80
#define MAX_LOGIN 20
#define ARQUIVO_USUARIOS "usuarios.txt"
#define MAX_PRODUTOS 5000
#define MAX_SENHA 20
#define MAX_USUARIO 20

#define COR_TITULO "\033[1;33m" // Amarelo
#define COR_RESET "\033[0m"     // Reset de cor
#define COR_ERRO "\033[38;5;196m"  // Vermelho
#define COR_SUCESSO "\033[38;5;82m" // Verde
#define COR_RESET "\033[0m"        // Reset de cor
#define COR_TITULO1 "\033[1;33m"    // Amarelo

#define COR_ERRO2 "\033[38;5;196m"  // Vermelho
#define COR_SUCESSO2 "\033[38;5;82m" // Verde
#define COR_RESET2 "\033[0m"        // Reset de cor
#define COR_TITULO2 "\033[1;33m"    // Amarelo

extern void menuProduto();
extern void menuFornecedor();
extern void menuCarrinho(Carrinho *carrinho);
extern void cancelarVenda();
extern void finalizar();

// Função para verificar se uma string contém apenas letras ou números
int verificarApenasLetrasOuNumeros(const char* str, int tipo) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (tipo == 1) { // Verifica se são apenas números
            if (!isdigit(str[i])) {
                return 0; // Não é número
            }
        } else if (tipo == 2) { // Verifica se são apenas letras
            if (!isalpha(str[i])) {
                return 0; // Não é letra
            }
        }
    }
    return 1; // Retorna 1 se todos os caracteres forem válidos
}

// Função para codificar (inverter) a senha
void codificarSenha(const char *senha, char *senhaCodificada) {
    int len = strlen(senha);
    for (int i = 0; i < len; i++) {
        senhaCodificada[i] = senha[len - 1 - i]; // Inverte a string
    }
    senhaCodificada[len] = '\0'; // Adiciona o terminador nulo
}

// Função para obter a senha oculta
void obterSenhaOculta(char *senha, int max_tamanho) {
    int i = 0;
    char ch;

    printf(">> Digite a senha: ");
    while (1) {
        ch = _getch(); // Captura uma tecla sem ecoá-la na tela

        if (ch == 13) { // Enter (finaliza a entrada)
            senha[i] = '\0';
            break;
        } else if (ch == 8) { // Backspace (apaga o último caractere)
            if (i > 0) {
                i--;
                printf("\b \b"); // Apaga o último asterisco da tela
            }
        } else if (i < max_tamanho - 1) { // Aceita qualquer caractere
            senha[i++] = ch;
            printf("*"); // Mostra "*" ao invés do caractere digitado
        }
    }
    printf("\n");
}


// Função para centralizar o título ou qualquer texto
void centralizarTexto(char *texto, int larguraTela) {
    int espacos = (larguraTela - strlen(texto)) / 0.9;  // Calcular o espaço necessário para centralizar o texto

    // Imprime os espaços em branco antes do texto
    for (int i = 0; i < espacos; i++) {
        printf(" ");
    }
    
    printf("%s\n", texto); // Imprime o texto centralizado
}

// Função para exibir o início
void exibirInicio() {
    printf("\n\n");

    // Linhas com o texto "HORTIFRUTI" e cores aplicadas a cada letra
    char *linha[] = {
        "\033[38;5;196mH    H\033[0m     \033[38;5;202mOOO\033[0m      \033[38;5;214mRRRR\033[0m     \033[38;5;226mTTTTTT\033[0m    \033[38;5;46mIIIII\033[0m     \033[38;5;202mLL\033[0m       \033[38;5;202mOOO\033[0m      \033[38;5;202mOOO\033[0m      \033[38;5;51mK    K\033[0m",
        "\033[38;5;196mH    H\033[0m   \033[38;5;202mO     O\033[0m    \033[38;5;214mR   R\033[0m      \033[38;5;226mTT\033[0m        \033[38;5;46mI\033[0m       \033[38;5;202mLL\033[0m     \033[38;5;202mO     O\033[0m  \033[38;5;202mO     O\033[0m    \033[38;5;51mK   K\033[0m",
        "\033[38;5;196mH    H\033[0m   \033[38;5;202mO     O\033[0m    \033[38;5;214mR   R\033[0m      \033[38;5;226mTT\033[0m        \033[38;5;46mI\033[0m       \033[38;5;202mLL\033[0m     \033[38;5;202mO     O\033[0m  \033[38;5;202mO     O\033[0m    \033[38;5;51mK  K\033[0m",
        "\033[38;5;196mHHHHHH\033[0m   \033[38;5;202mO     O\033[0m    \033[38;5;214mRRRR\033[0m       \033[38;5;226mTT\033[0m        \033[38;5;46mI\033[0m       \033[38;5;202mLL\033[0m     \033[38;5;202mO     O\033[0m  \033[38;5;202mO     O\033[0m    \033[38;5;51mKKk\033[0m",
        "\033[38;5;196mH    H\033[0m   \033[38;5;202mO     O\033[0m    \033[38;5;214mR   R\033[0m      \033[38;5;226mTT\033[0m        \033[38;5;46mI\033[0m       \033[38;5;202mLL\033[0m     \033[38;5;202mO     O\033[0m  \033[38;5;202mO     O\033[0m    \033[38;5;51mK  K\033[0m",
        "\033[38;5;196mH    H\033[0m   \033[38;5;202mO     O\033[0m    \033[38;5;214mR    R\033[0m     \033[38;5;226mTT\033[0m        \033[38;5;46mI\033[0m       \033[38;5;202mLL\033[0m     \033[38;5;202mO     O\033[0m  \033[38;5;202mO     O\033[0m    \033[38;5;51mK   K\033[0m",
        "\033[38;5;196mH    H\033[0m     \033[38;5;202mOOO\033[0m      \033[38;5;214mR     R\033[0m    \033[38;5;226mTT\033[0m      \033[38;5;46mIIIII\033[0m     \033[38;5;202mLLLLLL\033[0m   \033[38;5;202mOOO\033[0m      \033[38;5;202mOOO\033[0m      \033[38;5;51mK    K\033[0m"
           

    };

    int numLinhas = sizeof(linha) / sizeof(linha[0]);

    // Exibe as linhas decorativas e a palavra "HORTIFRUTI" centralizadas
    centralizarTexto("_ .. _ .. _ .. _ .. _ .. _ .. _ .. _ .. _ .. _ .. _ .. _ .. _ .. _ .. _ .. _ .. _ .. _ .. _", LARGURA_TELA);

    for (int i = 0; i < numLinhas; i++) {
        centralizarTexto(linha[i], LARGURA_TELA); // Centraliza as linhas com a palavra "HORTIFRUTI"
    }

    centralizarTexto("_ .. _ .. _ .. _ .. _ .. _ .. _ .. _ .. _ .. _ .. _ .. _ .. _ .. _ .. _ .. _ .. _ .. _ .. _", LARGURA_TELA);

    // Outros textos que você queira centralizar
    printf("\n");
    centralizarTexto("      Bem-vindo a nossa loja, frescor e qualidade estao sempre ao seu alcance!", LARGURA_TELA);

    printf("\n");


   // Mensagem centralizada
   const char* mensagem = "\033[38;5;82m>>> Sistema de Login <<<\n\n\033[0m";
int espacosMensagem = (LARGURA_TELA - strlen(mensagem)) / 1.1;
printf("\n");
printf("%*s%s\n\n", espacosMensagem, "", mensagem);


// Opções do menu principal
const char* opcoes2[] = {
  "\033[38;5;255m > Login de Usuario <\033[0m",
};
for (int i = 0; i < sizeof(opcoes2) / sizeof(opcoes2[0]); i++) {
    int espacos = (LARGURA_TELA - strlen(opcoes2[i])) / 1.2;
    printf("%*s%s\n", espacos, "", opcoes2[i]);
}

const char* opcoes[] = {
    
    "\033[38;5;255m  > Criar seu Usuario <\033[0m",
};

int numOpcoes = sizeof(opcoes) / sizeof(opcoes[0]);
for (int i = 0; i < numOpcoes; i++) {
    int espacos = (LARGURA_TELA - strlen(opcoes[i])) / 1.2;
    printf("%*s%s\n", espacos, "", opcoes[i]);
}


const char* opcoes1[] = {
    "\033[38;5;1m   > Sair da Loja! <   \033[0m"  // Negrito e fundo vermelho
};
for (int i = 0; i < sizeof(opcoes1) / sizeof(opcoes1[0]); i++) {
    int espacos = (LARGURA_TELA - strlen(opcoes1[i])) / 1.2;
    printf("%*s%s\n", espacos, "", opcoes1[i]);
}


// Entrada de opção do usuário
int opcao;
printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\033[1;31m:: Digite a opcao Desejada: \033[0m");


}



// Função para exibir a mensagem de boas-vindas
void exibirBemVindo() {
   printf("\n");
    const char* bemVindo = "\033[38;5;82mBEM-VINDO A NOSSA LOJA!\033[0m";

    // Imprimindo bordas e a mensagem de boas-vindas
    printf("\n\033[1;32m"); // Cor verde e negrito
    printf("%*s*===========================*\n", (LARGURA_TELA / 2) - 11, ""); // Ajuste o espaçamento
    printf("%*s|  %s  |\n", (LARGURA_TELA / 2) - 11, "", bemVindo); // Mensagem centralizada
    printf("%*s*===========================*\n", (LARGURA_TELA / 2) - 11, ""); // Bordas
    printf("\n");
    // Palavra "HORTILOOK" em tamanho maior, centralizada
    printf("%*s\033[1;34m    HORTILOOK, o frescor que vai te surpreender.\033[0m\n", (LARGURA_TELA - 44) / 2, " "); // Centraliza HORTILOOK em azul


    printf("%*s*===========================*\n\n", (LARGURA_TELA / 2) - 11, "");
    printf("\033[0m\n"); // Reset de cor

    printf("\n\n");

    // Obter a data e hora atuais
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // Formatar a data e hora separadamente
    char data[30], hora[30];
    sprintf(data, ":: DATA: %02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    sprintf(hora, ":: HORA: %02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);

    // Imprimir a data e a hora do lado esquerdo
    printf("\033[1;34m"); // Cor azul para a data e hora
    printf("[%s]\n", data); // Data alinhada à esquerda
    printf("[%s]\n", hora);  // Hora alinhada à esquerda
    printf("\033[0m"); // Reset de cor
    printf("\n\n");
}



// Função para realizar o login
int realizarLogin() {
    char usuario[MAX_USUARIO];
    char senha[MAX_SENHA];
    char senhaCodificada[MAX_SENHA];
    char usuarioArmazenado[MAX_USUARIO];
    char senhaArmazenada[MAX_SENHA];
    char linha[100]; // Buffer para ler linhas do arquivo

    printf("\n");

    // Solicitar nome de usuário
    printf(COR_TITULO2 ">> Digite o nome de usuario: " COR_RESET);
    scanf("%s", usuario); // Captura o nome do usuário

    // Solicitar e capturar a senha de forma oculta
    obterSenhaOculta(senha, MAX_SENHA);

    // Codificar a senha
    codificarSenha(senha, senhaCodificada);

    // Abrir o arquivo de usuários
    FILE *file = fopen(ARQUIVO_USUARIOS, "r");
    if (!file) {
        printf(COR_ERRO2 "Erro ao abrir o arquivo de usuarios.\n" COR_RESET);
        return 0;
    }

    // Verificar se o usuário e a senha estão corretos
    while (fgets(linha, sizeof(linha), file)) {
        sscanf(linha, "%s %s", usuarioArmazenado, senhaArmazenada);
        if (strcmp(usuarioArmazenado, usuario) == 0 && strcmp(senhaArmazenada, senhaCodificada) == 0) {
            fclose(file);
            printf(COR_SUCESSO2 "Login realizado com sucesso!\n" COR_RESET);
            exibirBemVindo(); // Exibir boas-vindas após login
            return 1; // Login bem-sucedido
        }
    }

    fclose(file);
    printf(COR_ERRO2 "Usuario ou senha incorretos!\n" COR_RESET);
    return 0; // Falha no login
}


// Função para criar um novo usuário
int criarUsuario() {
    char usuario[MAX_LOGIN], senha[MAX_LOGIN], senhaCodificada[MAX_LOGIN];
     printf("\n");


    // Solicitar nome de usuário
    printf(COR_TITULO1 ">> Digite um novo usuario: " COR_RESET);
    scanf("%s", usuario);
    if (!verificarApenasLetrasOuNumeros(usuario, 2)) {
        printf(COR_ERRO "Usuario deve conter apenas letras!\n" COR_RESET);
        return 0;
    }

    // Solicitar senha
    printf(COR_TITULO1 ">> Digite uma nova senha: " COR_RESET);
    scanf("%s", senha);
    if (!verificarApenasLetrasOuNumeros(senha, 1)) {
        printf(COR_ERRO "Senha deve conter apenas numeros!\n" COR_RESET);
        return 0;
    }

    // Codificar a senha
    codificarSenha(senha, senhaCodificada);

    // Abrir o arquivo de usuários
    FILE *file = fopen(ARQUIVO_USUARIOS, "a+");
    if (!file) {
        printf(COR_ERRO "Erro ao abrir o arquivo de usuarios.\n" COR_RESET);
        return 0;
    }

    char linha[2 * MAX_LOGIN];
    while (fgets(linha, sizeof(linha), file)) {
        char* usuarioArmazenado = strtok(linha, " ");
        if (strcmp(usuarioArmazenado, usuario) == 0) {
            printf(COR_ERRO "Usuario ja existe!\n" COR_RESET);
            fclose(file);
            return 0;
        }
    }

    // Escrever o novo usuário no arquivo
    fprintf(file, "%s %s\n", usuario, senhaCodificada);
    fclose(file);

    // Confirmação de sucesso
    printf(COR_SUCESSO "Usuario criado com sucesso!\n" COR_RESET);
    return 1;
}


typedef struct {
    char nome[50];
    float preco;
    int quantidade_em_estoque;
    char categoria[30];
} Produtos;

// Declarações de arrays para armazenar produtos e itens do carrinho
Produto produto[MAX_PRODUTOS];  // Array para armazenar produtos
Produto carrinho[MAX_CARRINHO];   // Array para armazenar itens do carrinho

int numProdutos = 0;               // Total de produtos disponíveis
int numItensCarrinho = 0;          // Total de itens no carrinho

// Function declarations
void exibirInicio();
int realizarLogin();
void adicionarAoCarrinho();
void visualizarCarrinho();
float calcularTotal();
void exibirMenu1();


// Funções principais do sistema

// Função para limpar a tela
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
void exibirTituloMenu() {
    // Códigos de cor ANSI para diferentes cores
    char *red = "\033[38;5;196m";
    char *orange = "\033[38;5;202m";
    char *yellow = "\033[38;5;226m";
    char *blue = "\033[38;5;51m";
    char *reset = "\033[0m";

    // Exibindo "MENU" em formato ASCII colorido
    printf("|                           %sMM    MM%s   %sEEEEE%s   %sNN    NN%s  %sUU   UU%s                        |\n", red, reset, orange, reset, yellow, reset, blue, reset);
    printf("|                           %sMMM  MMM%s   %sEE    %s  %sNNN   NN%s  %sUU   UU%s                        |\n", red, reset, orange, reset, yellow, reset, blue, reset);
    printf("|                           %sMM MM MM%s   %sEEEEE%s   %sNNNN  NN%s  %sUU   UU%s                        |\n", red, reset, orange, reset, yellow, reset, blue, reset);
    printf("|                           %sMM    MM%s   %sEE    %s  %sNN  NNNN%s  %sUU   UU%s                        |\n", red, reset, orange, reset, yellow, reset, blue, reset);
    printf("|                           %sMM    MM%s   %sEEEEE%s   %sNN   NNN%s   %sUUUUU%s                         |\n", red, reset, orange, reset, yellow, reset, blue, reset);
}

void exibirMensagemSaida() {
    // Códigos de cor ANSI
    char *reset = "\033[0m";
    char *green = "\033[32m";
    char *yellow = "\033[33m";
    char *cyan = "\033[36m";
    
    printf("%s\n", cyan);
    printf("========================================================================================\n");
    printf("||                                                                                    ||\n");
    printf("||%s                       >> Obrigado pela visita na nossa loja! <<%s                    %s||\n", yellow, reset, cyan);
    printf("||%s                        Esperamos ve-lo novamente em breve!%s                         %s||\n", green, reset, cyan);
    printf("||                                                                                    ||\n");
    printf("||                       %s>> Hortilook - Sua loja de confianca! <<%s                     %s||\n", yellow, reset, cyan);
    printf("||                                                                                    ||\n");
    printf("========================================================================================\n");
    printf("%s\n", reset);
}

void exibirMenu1() {
    // Códigos de cor ANSI
    char *reset = "\033[0m";
    char *blue = "\033[34m";
    char *yellow = "\033[33m";
    char *cyan = "\033[36m";
    char *green = "\033[32m";

    // Exibindo o menu com cores e o título "MENU" maior
    printf("%s\n+::::::::::::::::::::::::::::-----------------------------------------------------------+\n", blue);
    printf("|                                                                                       |\n");
    printf("|                                                                                       |\n");

    // Exibindo o título "MENU" ampliado
    exibirTituloMenu();

    printf("|                                                                                       |\n");
    printf("+--------------------------------------------------------------:::::::::::::::::::::::::+\n");
    printf("|                                                                                       |\n");
    printf("|   %s(1). Gerenciar Carrinho%s                |        %s(2). Cancelar a Venda%s               |\n", green, blue, green, blue);
    printf("|                                                                                       |\n");
    printf("|                                                                                       |\n");
    printf("|   %s(3). Gerenciar Fornecedor%s              |        %s(4). Finalizar a Venda%s              |\n", green, blue, green, blue);
    printf("|                                                                                       |\n");
    printf("|                                                                                       |\n");
    printf("|   %s(5). Gerenciar Estoque%s                 |        %s(6). Voltar%s                         |\n", green, blue, green, blue);
    printf("|                                                                                       |\n");
    printf("|                                                                                       |\n");
    printf("|                                     %s(7) Sair%s                                          |\n", cyan, blue);
    printf("+---------------------------------------------------------------------------------------+\n%s", reset);
}


int main() {
    int opcao;
    Produto produtos[MAX_PRODUTOS]; // Defina MAX_PRODUTOS no seu cabeçalho de produtos
    Carrinho carrinho = { .numItens = 0 }; // Inicializa o carrinho
    int numProdutos = 0; // Inicializa o número de produtos

    // Loop principal
    while (1) {
        exibirInicio();
        if (scanf("%d", &opcao) != 1) {
            while(getchar() != '\n'); // Limpa o buffer de entrada
            printf("Entrada invalida! Tente novamente.\n");
            continue;
        }

        switch (opcao) {
            case 1:  // Login
                if (realizarLogin()) {
                    int opcaoMenu;

                    do {
                        exibirMenu1();
                        printf("\n\n\n");
                        printf(COR_TITULO ">> Escolha uma das opcao acima Desejada: " COR_RESET);
                        if (scanf("%d", &opcaoMenu) != 1) {
                        while (getchar() != '\n'); // Limpa o buffer de entrada
                        printf(COR_TITULO "Entrada invalida! Tente novamente.\n" COR_RESET);
                            continue;
                        }
                        

                        limparTela(); // Limpa a tela após a escolha da opção

                        switch (opcaoMenu) {
                            case 1:
                                menuCarrinho(&carrinho); 
                                break;
                            case 2:
                                cancelarVenda(&carrinho);
                                break;
                            case 4:
                                finalizar(&carrinho);
                                break;
                            case 5: 
                                menuProduto(); 
                                break;
                            case 3:
                                menuFornecedor();
                                break;
                             case 7:  // Sair
                                exibirMensagemSaida();
                                exit(0);
                                break;
                            default:
                                printf("Opcao invalida!\n");    
                            case 6:  //voltar
                                exibirInicio();
                                return 0;
                        }
                    } while (opcaoMenu != 10);
                }
                break;

            case 2:  // Criar usuário
                criarUsuario();
                break;

            case 3:  // Sair
                printf("Saindo...\n");
                exit(0);

            default:
                printf("Opcao invalida!\n");
        }
    }
    return 0; // Retornar 0 em caso de término normal do programa
}