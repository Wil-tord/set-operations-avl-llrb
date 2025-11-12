#ifndef _ARVORE_BINARIA_AVL_H
#define _ARVORE_BINARIA_AVL_H

#include <stdbool.h>

// Definição de um valor para indicar erro em operações
#define ERRO -32000

// Definição da estrutura da árvore AVL (a estrutura é definida aqui de forma abstrata)
typedef struct avl AVL;

// Protótipos das funções para manipulação da árvore AVL

// Cria e inicializa uma árvore AVL vazia
AVL *avl_criar(void);

// Libera toda a memória usada pela árvore AVL
void avl_apagar(AVL **T);

// Insere uma chave (número inteiro) na árvore AVL, balanceando a árvore
bool avl_inserir(AVL *T, int chave);

// Busca uma chave na árvore AVL
bool avl_busca(AVL *T, int chave);

// Remove uma chave da árvore AVL, ajustando o balanceamento da árvore
bool avl_remover(AVL *T, int chave);

// Imprime a árvore AVL (usada para depuração)
void avl_imprimir(AVL *T);

// Verifica se a árvore AVL está vazia
bool avl_vazia(AVL *T);

// Cria uma cópia (clone) da árvore AVL
AVL *avl_clonar(AVL *A);

// Faz a união de duas árvores AVL, combinando todos os elementos
AVL *avl_uniao(AVL *A, AVL *B);

// Faz a interseção de duas árvores AVL, mantendo apenas os elementos em comum
AVL *avl_interseccao(AVL *A, AVL *B);

#endif
