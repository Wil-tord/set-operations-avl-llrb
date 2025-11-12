#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"

// Estrutura do nó da AVL
typedef struct no NO;
struct no {
    int chave;  // Chave do nó
    NO *esq;    // Filho esquerdo
    NO *dir;    // Filho direito
    int FB;     // Fator de balanceamento
    int altura; // Altura do nó
};

// Estrutura da árvore AVL
struct avl {
    NO *raiz;          // Raiz da árvore
    int profundidade;  // Profundidade máxima
};

//! Cria uma árvore AVL vazia
AVL *avl_criar(void) {
    AVL *T = (AVL *)malloc(sizeof(AVL)); // Aloca memória para a árvore
    if (T == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória.\n");  // Se a alocação falhar, imprime um erro
        return NULL;
    }
    T->raiz = NULL;          // Inicializa a raiz como NULL (a árvore começa vazia)
    T->profundidade = -1;    // Profundidade inicial é -1, pois não há nós
    return T;                // Retorna o ponteiro para a árvore criada
}

// Cria um nó com a chave fornecida
NO *avl_criar_no(int chave) {
    NO *no = (NO *)malloc(sizeof(NO)); // Aloca memória para o nó
    if (no) {
        no->chave = chave;             // Define a chave do nó
        no->esq = no->dir = NULL;      // Inicializa os filhos (esquerda e direita) como NULL
        no->FB = 0;                    // Inicializa o fator de balanceamento como 0
        no->altura = 0;                // Inicializa a altura do nó como 0
    }
    return no;  // Retorna o ponteiro para o nó criado
}

// Função recursiva para apagar todos os nós
void avl_apagar_aux(NO **raiz) {
    if (*raiz) {
        avl_apagar_aux(&(*raiz)->esq); // Apaga a subárvore esquerda
        avl_apagar_aux(&(*raiz)->dir); // Apaga a subárvore direita
        free(*raiz);                   // Libera a memória do nó atual
        *raiz = NULL;                  // Define o ponteiro para NULL para evitar referências pendentes
    }
}

//! Apaga a árvore AVL e libera a memória
void avl_apagar(AVL **T) {
    if (T && *T) {
        avl_apagar_aux(&(*T)->raiz);  // Apaga todos os nós da árvore
        free(*T);                     // Libera a memória alocada para a estrutura da árvore
        *T = NULL;                    // Define o ponteiro da árvore como NULL para evitar referências pendentes
    }
}

// Calcula a altura do nó
int avl_altura(NO *no) {
    if (no == NULL) return -1;  // Se o nó for NULL (inexistente), retorna -1
    int altura_esq = avl_altura(no->esq);  // Recursivamente, calcula a altura da subárvore esquerda
    int altura_dir = avl_altura(no->dir);  // Recursivamente, calcula a altura da subárvore direita
    // Retorna 1 (a altura do nó atual) + a maior altura entre a subárvore esquerda e a subárvore direita
    return 1 + (altura_esq > altura_dir ? altura_esq : altura_dir);
}

// Função para obter a altura de um nó
int avl_altura_no(NO *no) {
    // Se o nó não for NULL, retorna a altura armazenada no nó; caso contrário, retorna 0
    return no ? no->altura : 0;
}

// Função para calcular o fator de balanceamento
int fator_balanceamento(NO *raiz) {
    // Calcula o fator de balanceamento, que é a diferença entre as alturas das subárvores esquerda e direita
    // Se o nó for NULL, retorna 0
    return raiz ? avl_altura_no(raiz->esq) - avl_altura_no(raiz->dir) : 0;
}

// Realiza rotação simples à direita para balancear a árvore
NO *rodar_dir(NO *a) {
    // 'b' será o novo nó raiz da subárvore
    NO *b = a->esq;

    // Realiza a rotação à direita
    a->esq = b->dir; // A subárvore direita de 'b' passa a ser a subárvore esquerda de 'a'
    b->dir = a;      // 'a' se torna a subárvore direita de 'b'

    // Atualiza as alturas dos nós
    a->altura = 1 + (avl_altura_no(a->esq) > avl_altura_no(a->dir) ? avl_altura_no(a->esq) : avl_altura_no(a->dir));
    b->altura = 1 + (avl_altura_no(b->esq) > avl_altura_no(b->dir) ? avl_altura_no(b->esq) : avl_altura_no(b->dir));

    return b; // Retorna o novo nó raiz, que é 'b'
}

// Realiza rotação simples à esquerda para balancear a árvore
NO *rodar_esq(NO *a) {
    // 'b' será o novo nó raiz da subárvore
    NO *b = a->dir;

    // Realiza a rotação à esquerda
    a->dir = b->esq; // A subárvore esquerda de 'b' passa a ser a subárvore direita de 'a'
    b->esq = a;      // 'a' se torna a subárvore esquerda de 'b'

    // Atualiza as alturas dos nós
    a->altura = 1 + (avl_altura_no(a->esq) > avl_altura_no(a->dir) ? avl_altura_no(a->esq) : avl_altura_no(a->dir));
    b->altura = 1 + (avl_altura_no(b->esq) > avl_altura_no(b->dir) ? avl_altura_no(b->esq) : avl_altura_no(b->dir));

    return b; // Retorna o novo nó raiz, que é 'b'
}

// Realiza rotação dupla: esquerda-direita, necessário para balancear a árvore em alguns casos
NO *rodar_esquerda_direita(NO *a) {
    // Realiza uma rotação à esquerda na subárvore esquerda de 'a'
    a->esq = rodar_esq(a->esq);
    
    // Após a rotação à esquerda, realiza a rotação à direita
    return rodar_dir(a); 
}

// Realiza rotação dupla: direita-esquerda, necessário para balancear a árvore em alguns casos
NO *rodar_direita_esquerda(NO *a) {
    // Realiza uma rotação à direita na subárvore direita de 'a'
    a->dir = rodar_dir(a->dir);
    
    // Após a rotação à direita, realiza a rotação à esquerda
    return rodar_esq(a);
}

// Balanceia a árvore AVL após a inserção ou remoção de um nó
NO *avl_balancear(NO *raiz) {
    int FB = fator_balanceamento(raiz);  // Calcula o fator de balanceamento da árvore

    // Se o fator de balanceamento for -2, a árvore está desbalanceada para a direita
    if (FB == -2) {
        if (fator_balanceamento(raiz->dir) <= 0)
            raiz = rodar_esq(raiz); // Realiza uma rotação simples à esquerda
        else
            raiz = rodar_direita_esquerda(raiz); // Realiza uma rotação direita-esquerda (dupla)
    } 
    // Se o fator de balanceamento for 2, a árvore está desbalanceada para a esquerda
    else if (FB == 2) {
        if (fator_balanceamento(raiz->esq) >= 0)
            raiz = rodar_dir(raiz); // Realiza uma rotação simples à direita
        else
            raiz = rodar_esquerda_direita(raiz); // Realiza uma rotação esquerda-direita (dupla)
    }

    return raiz; // Retorna a árvore balanceada
}

// Função recursiva auxiliar que insere uma chave na árvore AVL
NO *avl_inserir_no(NO *raiz, int chave) {
    // Se a árvore estiver vazia, cria um novo nó com a chave
    if (raiz == NULL) {
        raiz = avl_criar_no(chave); // Cria um novo nó
    } else if (chave < raiz->chave) {
        raiz->esq = avl_inserir_no(raiz->esq, chave); // Insere a chave na subárvore esquerda
    } else if (chave > raiz->chave) {
        raiz->dir = avl_inserir_no(raiz->dir, chave); // Insere a chave na subárvore direita
    }

    // Após a inserção, balanceia a árvore
    raiz = avl_balancear(raiz);

    return raiz; // Retorna a raiz da árvore balanceada
}

//! Função pública para inserir uma chave na árvore AVL
bool avl_inserir(AVL *T, int chave) {
    if (T == NULL) return false; // Verifica se a árvore AVL é válida antes de tentar inserir

    T->raiz = avl_inserir_no(T->raiz, chave);  // Chama a função auxiliar para realizar a inserção
    return true; // Retorna verdadeiro indicando que a inserção foi bem-sucedida
}


// Função auxiliar recursiva que remove um nó substituindo-o pelo maior nó da subárvore esquerda
void troca_max_esq(NO *troca, NO *raiz, NO *ant) {
    if (troca->dir != NULL) {
        troca_max_esq(troca->dir, raiz, troca); // Vai até o maior nó da subárvore esquerda
        return;
    }

    // Ajusta o ponteiro do nó anterior para apontar para o filho esquerdo do nó a ser removido
    if (raiz == ant) {
        ant->esq = troca->esq;
    } else {
        ant->dir = troca->esq;
    }

    raiz->chave = troca->chave; // Atualiza a chave do nó removido com a chave do nó substituto
    free(troca);                // Libera a memória do nó que foi substituído
}

// Função auxiliar recursiva para remover um nó na árvore AVL
NO *avl_remover_aux(NO **raiz, int chave, bool *removido) {
    NO *temp;

    if (*raiz == NULL) return false; // Se a árvore estiver vazia, a chave não foi encontrada

    // Verifica se a chave é igual à chave do nó atual
    if (chave == (*raiz)->chave) {
        *removido = true; // Marca que o nó foi encontrado e será removido

        // Caso 1 e 2: O nó possui 0 ou 1 filho
        if ((*raiz)->esq == NULL || (*raiz)->dir == NULL) {
            temp = *raiz;
            if ((*raiz)->esq == NULL)
                *raiz = (*raiz)->dir; // Atualiza o nó com o filho direito (ou NULL)
            else
                *raiz = (*raiz)->esq; // Atualiza o nó com o filho esquerdo (ou NULL)

            free(temp); // Libera o nó
            temp = NULL;
        } 
        // Caso 3: O nó possui dois filhos
        else 
            troca_max_esq((*raiz)->esq, (*raiz), (*raiz)); // Substitui pelo maior nó da subárvore esquerda
    } 
    // Caso de busca na subárvore esquerda
    else if (chave < (*raiz)->chave) 
        (*raiz)->esq = avl_remover_aux(&(*raiz)->esq, chave, removido);

    // Caso de busca na subárvore direita
    else if (chave > (*raiz)->chave)
        (*raiz)->dir = avl_remover_aux(&(*raiz)->dir, chave, removido);

    // Após a remoção, a árvore precisa ser rebalanceada
    if (*raiz != NULL) 
        *raiz = avl_balancear(*raiz); // Chama a função de balanceamento

    return *raiz;
}

//! Função pública para remover uma chave da árvore AVL
bool avl_remover(AVL *T, int chave) {
    if (T == NULL) return false; // Se a árvore for vazia, retorna falso

    bool removido = false;
    T->raiz = avl_remover_aux(&T->raiz, chave, &removido); // Chama a função auxiliar para remover o nó
    return removido; // Retorna se a remoção foi realizada com sucesso
}

// Função auxiliar recursiva para buscar um nó na árvore AVL
bool avl_busca_aux(NO *raiz, int chave) {
    if (raiz == NULL) {
        return false; // Se a subárvore for vazia, a chave não foi encontrada
    }
    if (chave == raiz->chave) {
        return true; // Se a chave for igual à do nó atual, a chave foi encontrada
    }
    if (chave < raiz->chave) {
        return avl_busca_aux(raiz->esq, chave); // Se a chave for menor, busca na subárvore esquerda
    } else {
        return avl_busca_aux(raiz->dir, chave); // Se a chave for maior, busca na subárvore direita
    }
}

//! Função pública para buscar um nó pela chave na árvore AVL
bool avl_busca(AVL *T, int chave) {
    if (T == NULL || T->raiz == NULL) {
        return false; // Se a árvore for vazia ou inexistente, retorna falso
    }
    return avl_busca_aux(T->raiz, chave); // Chama a função auxiliar para realizar a busca
}

// Imprime os nós em pré-ordem (raiz, esquerda, direita)
void imprimir_preordem(NO *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->chave);  // Imprime a chave do nó atual
        imprimir_preordem(raiz->esq); // Chama a função recursivamente para a subárvore esquerda
        imprimir_preordem(raiz->dir); // Chama a função recursivamente para a subárvore direita
    }
}

//! Função pública para imprimir a árvore AVL em pré-ordem
void avl_imprimir(AVL *T) {
    if (T != NULL && T->raiz != NULL) {  // Verifica se a árvore não está vazia
        imprimir_preordem(T->raiz);      // Chama a função auxiliar de impressão
    } else {
        printf("Arvore vazia.\n"); // Se a árvore estiver vazia, imprime uma mensagem
    }
}

// Verifica se a árvore AVL está vazia
bool avl_vazia(AVL *T) {
    return T == NULL || T->raiz == NULL; // Retorna verdadeiro se a árvore for nula ou a raiz for nula
}

// Função auxiliar para clonar elementos de uma árvore AVL
void avl_clonar_elementos(NO *raiz, AVL *destino) {
    if (raiz != NULL) {
        avl_inserir(destino, raiz->chave); // Insere o valor da raiz na árvore destino
        avl_clonar_elementos(raiz->esq, destino); // Clona a subárvore esquerda
        avl_clonar_elementos(raiz->dir, destino); // Clona a subárvore direita
    }
}

//! Função principal para clonar uma árvore AVL
AVL *avl_clonar(AVL *A) {
    if (A == NULL || A->raiz == NULL) return avl_criar(); // Retorna árvore vazia se A for nula

    AVL *clone = avl_criar(); // Cria uma nova árvore AVL
    avl_clonar_elementos(A->raiz, clone); // Clona todos os elementos de A para o clone
    return clone; // Retorna o clone da árvore
}

//! Função para realizar a união de duas árvores AVL
AVL *avl_uniao(AVL *A, AVL *B) {
    if (A == NULL || A->raiz == NULL) return avl_clonar(B); // Se A for nula, clona B
    if (B == NULL || B->raiz == NULL) return avl_clonar(A); // Se B for nula, clona A

    AVL *uniao = avl_criar(); // Cria árvore para armazenar a união
    avl_clonar_elementos(A->raiz, uniao); // Clona elementos de A para a árvore de união
    avl_clonar_elementos(B->raiz, uniao); // Clona elementos de B para a árvore de união

    return uniao; // Retorna a árvore resultante da união
}

// Função auxiliar para verificar interseção de elementos
void avl_verificar_interseccao(NO *raiz, AVL *B, AVL *resultado) {
    if (raiz != NULL) {
        if (avl_busca(B, raiz->chave)) { // Verifica se o elemento está em B
            avl_inserir(resultado, raiz->chave); // Insere na árvore de resultado se houver interseção
        }
        avl_verificar_interseccao(raiz->esq, B, resultado); // Verifica subárvore esquerda
        avl_verificar_interseccao(raiz->dir, B, resultado); // Verifica subárvore direita
    }
}

//! Função para realizar a interseção de duas árvores AVL
AVL *avl_interseccao(AVL *A, AVL *B) {
    if (A == NULL || B == NULL || A->raiz == NULL || B->raiz == NULL) return avl_criar(); // Retorna árvore vazia se A ou B forem nulas

    AVL *interseccao = avl_criar(); // Cria árvore para armazenar a interseção
    avl_verificar_interseccao(A->raiz, B, interseccao); // Verifica os elementos comuns entre A e B

    return interseccao; // Retorna a árvore com a interseção dos elementos
}



