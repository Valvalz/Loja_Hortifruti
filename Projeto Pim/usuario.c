#include <stdio.h>
#include <string.h>
#include "usuario.h"

// Inicialização do array de usuários e contador
Usuario usuarios[MAX_USUARIOS];
int num_usuarios = 0;

// Função para cadastrar um novo usuário
void cadastrarUsuario() {
    if (num_usuarios < MAX_USUARIOS) {
        Usuario usuario;

        // Coleta informações do usuário
        printf("Nome: ");
        scanf(" %[^\n]", usuario.nome); // Lê até o final da linha
        printf("Senha: ");
        scanf(" %[^\n]", usuario.senha); // Lê até o final da linha

        // Atribui um ID único ao usuário
        usuario.idUsuario = num_usuarios + 1;

        // Armazena o usuário no array
        usuarios[num_usuarios++] = usuario;
        printf("Usuário cadastrado com sucesso!\n\n");
    } else {
        printf("Limite de usuários alcançado!\n");
    }
}

// Função para listar todos os usuários cadastrados
void listarUsuarios() {
    if (num_usuarios == 0) {
        printf("Nenhum usuário cadastrado.\n");
        return;
    }

    printf("Usuários:\n");
    for (int i = 0; i < num_usuarios; i++) {
        printf("%d. Nome: %s\n", usuarios[i].idUsuario, usuarios[i].nome);
    }
}

// Função para buscar um usuário pelo ID
int buscarUsuario(int id) {
    for (int i = 0; i < num_usuarios; i++) {
        if (usuarios[i].idUsuario == id) {
            return i; // Retorna o índice do usuário encontrado
        }
    }
    return -1; // Retorna -1 se não encontrado
}

// Função para remover um usuário pelo ID
int removerUsuario(int id) {
    int indice = buscarUsuario(id);
    if (indice != -1) {
        // Move todos os usuários após o índice encontrado uma posição para trás
        for (int i = indice; i < num_usuarios - 1; i++) {
            usuarios[i] = usuarios[i + 1];
        }
        num_usuarios--; // Decrementa o contador de usuários
        printf("Usuário removido com sucesso!\n");
        return 1; // Retorna 1 para sucesso
    }
    printf("Usuário não encontrado.\n");
    return 0; // Retorna 0 se não encontrado
}

// Função para editar as informações de um usuário
void editarUsuario(int indice) {
    if (indice >= 0 && indice < num_usuarios) {
        printf("Editar usuário %s:\n", usuarios[indice].nome);
        printf("Novo nome: ");
        scanf(" %[^\n]", usuarios[indice].nome);
        printf("Nova senha: ");
        scanf(" %[^\n]", usuarios[indice].senha);
        printf("Usuário editado com sucesso!\n");
    } else {
        printf("Usuário não encontrado.\n");
    }
}
