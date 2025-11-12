#ifndef _CONJUNTO_H
#define _CONJUNTO_H

#include <stdbool.h> 

// Definição dos tipos de estruturas de dados suportadas
#define AVL_TYPE 0    // Representa o tipo AVL (Árvore Balanceada)
#define LLRB_TYPE 1   // Representa o tipo LLRB (Left-Leaning Red-Black Tree)

// Tipo abstrato para representar um conjunto
typedef struct set SET;

//! Operações básicas

// Cria um novo conjunto com o tipo especificado (AVL ou LLRB)
SET *set_criar(unsigned char tipo);

// Insere um elemento no conjunto, retorna true se a inserção for bem-sucedida
bool set_inserir(SET *s, int elemento);

// Remove todos os elementos do conjunto e libera a memória
void set_apagar(SET **s);

// Remove um elemento específico do conjunto, retorna true se for removido
bool set_remover(SET *s, int elemento);

// Imprime os elementos do conjunto em ordem crescente
void set_imprimir(SET *s);

//! Operações especiais

// Verifica se um elemento está presente no conjunto
bool set_pertence(SET *A, int elemento);

// Retorna um novo conjunto que representa a união de A e B
SET *set_uniao(SET *A, SET *B);

// Retorna um novo conjunto que representa a interseção de A e B
SET *set_interseccao(SET *A, SET *B);

#endif
