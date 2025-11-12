#include <stdio.h>
#include <stdlib.h>
#include "Conjunto.h"
#include "AVL.h"
#include "LLRB.h"

struct set {
    void *structure;   // Ponteiro para a estrutura interna (AVL ou LLRB)
    unsigned char tipo; // Tipo da estrutura (AVL ou LLRB)
};

// Função para criar o conjunto, usando AVL ou LLRB
SET *set_criar(unsigned char tipo) {
    SET *s = (SET *)malloc(sizeof(SET));
    if (!s) {
        fprintf(stderr, "Erro ao alocar memória para o conjunto.\n");
        return NULL;
    }

    s->tipo = tipo; // Define o tipo de estrutura (AVL ou LLRB)

    // Aloca a estrutura interna dependendo do tipo
    if (tipo == AVL_TYPE) {
        s->structure = avl_criar();  // Cria a árvore AVL
    } else if (tipo == LLRB_TYPE) {
        s->structure = llrb_criar(); // Cria a árvore LLRB
    } else {
        free(s); // Libera o espaço alocado caso o tipo seja inválido
        return NULL;
    }

    return s;
}

// Função para inserir um elemento no conjunto
bool set_inserir(SET *s, int elemento) {
    if (s == NULL) return false; // Retorna falso se o conjunto for nulo

    if (s->tipo == AVL_TYPE) {
        return avl_inserir(s->structure, elemento); // Chama a função de inserção na árvore AVL
    } else if (s->tipo == LLRB_TYPE) {
        return llrb_inserir(s->structure, elemento); // Chama a função de inserção na árvore LLRB
    }
    return false; // Retorna falso caso o tipo seja inválido
}

// Função para remover um elemento do conjunto
bool set_remover(SET *s, int elemento) {
    if (s == NULL) return false; // Retorna falso se o conjunto for nulo

    if (s->tipo == AVL_TYPE) {
        return avl_remover(s->structure, elemento); // Chama a função de remoção na árvore AVL
    } else if (s->tipo == LLRB_TYPE) {
        return llrb_remover(s->structure, elemento); // Chama a função de remoção na árvore LLRB
    }
    return false; // Retorna falso caso o tipo seja inválido
}

// Função para verificar se um elemento pertence ao conjunto
bool set_pertence(SET *A, int elemento) {
    if (A == NULL) return false; // Retorna falso se o conjunto for nulo

    if (A->tipo == AVL_TYPE) {
        return avl_busca(A->structure, elemento); // Busca o elemento na árvore AVL
    } else if (A->tipo == LLRB_TYPE) {
        return llrb_pertence(A->structure, elemento); // Busca o elemento na árvore LLRB
    }
    return false; // Retorna falso caso o tipo seja inválido
}

// Função para imprimir os elementos do conjunto
void set_imprimir(SET *s) {
    if (s == NULL || s->structure == NULL) {
        printf("Árvore vazia.\n"); // Informa que a árvore está vazia
        return;
    }

    if (s->tipo == AVL_TYPE) {
        avl_imprimir(s->structure);  // Chama a função de impressão específica da AVL
    } else if (s->tipo == LLRB_TYPE) {
        llrb_imprimir(s->structure);  // Chama a função de impressão específica da LLRB
    }
}

// Função para apagar o conjunto
void set_apagar(SET **s) {
    if (s == NULL || *s == NULL) return; // Verifica se o ponteiro é válido

    if ((*s)->tipo == AVL_TYPE) {
        avl_apagar((AVL **)&(*s)->structure); // Libera a árvore AVL
    } else if ((*s)->tipo == LLRB_TYPE) {
        llrb_apagar((LLRB **)&(*s)->structure); // Libera a árvore LLRB
    }

    free(*s); // Libera o conjunto
    *s = NULL; // Define o ponteiro como nulo para evitar acessos inválidos
}

// Função para realizar a união de dois conjuntos (AVL ou LLRB)
SET *set_uniao(SET *A, SET *B) {
    // Verifica se algum dos conjuntos é nulo
    if (!A || !B) return NULL;

    // Verifica se ambos os conjuntos têm o mesmo tipo (AVL ou LLRB)
    if (A->tipo != B->tipo) return NULL;

    // Cria um novo conjunto para armazenar o resultado da união
    SET *result = set_criar(A->tipo);
    if (!result) return NULL; // Verifica se a alocação do conjunto resultante falhou

    // União para árvores AVL (quando A->tipo == 0, indicando que A é uma árvore AVL)
    if (A->tipo == 0) {  // Caso A seja uma árvore AVL
        // Chama a função avl_uniao para realizar a união entre as árvores AVL
        result->structure = avl_uniao(A->structure, B->structure);  
    } else {  // Caso A seja uma árvore LLRB
        // Insere os elementos de A no conjunto resultante utilizando a operação LLRB
        llrb_inserir_em_conjunto((LLRB *)A->structure, result);
        // Insere os elementos de B no conjunto resultante utilizando a operação LLRB
        llrb_inserir_em_conjunto((LLRB *)B->structure, result);
    }

    // Retorna o conjunto resultante contendo a união dos dois conjuntos
    return result;
}

// Função para realizar a interseção de dois conjuntos
SET *set_interseccao(SET *A, SET *B) {
    if (A->tipo != B->tipo) return NULL; // Verifica se os conjuntos têm o mesmo tipo

    SET *result = malloc(sizeof(SET)); // Aloca memória para o conjunto resultante
    result->tipo = A->tipo; // Define o tipo com base nos conjuntos de entrada

    if (A->tipo == AVL_TYPE) {
        result->structure = avl_interseccao(A->structure, B->structure); // Interseção de árvores AVL
    } else if (A->tipo == LLRB_TYPE) {
        result->structure = llrb_interseccao(A->structure, B->structure); // Interseção de árvores LLRB
    }

    return result;
}
