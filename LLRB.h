#ifndef ARVORE_BINARIA_LLRB
    #define ARVORE_BINARIA_LLRB  // Previne múltiplas inclusões deste arquivo de cabeçalho

    #include <stdbool.h>  // Inclui o tipo booleano padrão 'bool', 'true' e 'false'
    #include "conjunto.h"  // Inclui o cabeçalho para a estrutura ou operações do 'SET

    // Tipos definidos para a Árvore Binária de Busca Vermelha e Esquerda (LLRB) e seus nós
    typedef struct arv_LLRB LLRB;  // Alias para a estrutura da árvore LLRB
    typedef struct no_ NO;  // Alias para a estrutura do nó, que representa os nós da árvore

    // Protótipos das funções:

    // Função para criar uma nova árvore LLRB vazia
    LLRB* llrb_criar(void);

    // Função para inserir uma chave ('chave') na árvore LLRB 'T'
    bool llrb_inserir(LLRB *T, int chave);

    // Função para verificar se uma chave ('chave') existe na árvore LLRB 'T'
    bool llrb_pertence(LLRB *T, int chave);

    // Função para remover uma chave ('chave') da árvore LLRB 'T'
    bool llrb_remover(LLRB *T, int chave);

    // Função para apagar a árvore inteira e liberar a memória
    void llrb_apagar(LLRB **T);

    // Função para calcular e retornar uma nova árvore LLRB contendo a interseção
    // dos elementos de duas árvores LLRB 'T1' e 'T2'
    LLRB* llrb_interseccao(LLRB *T1, LLRB *T2);

    // Função para inserir todos os elementos da árvore LLRB 'T' em um conjunto 's'
    void llrb_inserir_em_conjunto(LLRB *T, SET *s);

    // Função para imprimir os elementos da árvore LLRB 'T' de uma forma legível (provavelmente em ordem)
    void llrb_imprimir(LLRB *T);

    // Função para percorrer uma árvore com raiz 'raizA' (do tipo 'NO') e inserir os elementos
    // em duas outras árvores LLRB 'B' e 'C'. Esta função pode ser usada para mesclar árvores
    // ou redistribuir os elementos entre elas.
    void percorrer_e_inserir(NO* raizA, LLRB *B, LLRB *C);

#endif
