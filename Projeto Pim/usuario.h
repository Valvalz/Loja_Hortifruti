// usuario.h
#ifndef USUARIO_H
#define USUARIO_H

#define MAX_USUARIOS 100 // Defina o número máximo de usuários

typedef struct {
    int idUsuario;            // ID único do usuário
    char nome[100];          // Nome do usuário
    char senha[50];          // Senha do usuário
} Usuario;

// Funções para manipular usuários

/**
 * @brief Função para cadastrar um novo usuário
 */
void cadastrarUsuario();

/**
 * @brief Função para listar todos os usuários cadastrados
 */
void listarUsuarios();

/**
 * @brief Função para buscar um usuário pelo ID
 * @param id ID do usuário a ser buscado
 * @return Índice do usuário se encontrado, ou -1 se não for encontrado
 */
int buscarUsuario(int id);

/**
 * @brief Função para remover um usuário pelo ID
 * @param id ID do usuário a ser removido
 * @return 1 se o usuário foi removido com sucesso, ou 0 se não foi encontrado
 */
int removerUsuario(int id);

/**
 * @brief Função para editar as informações de um usuário
 * @param indice Índice do usuário no array
 */
void editarUsuario(int indice);

#endif // USUARIO_H
