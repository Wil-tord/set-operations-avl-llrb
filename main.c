#include <stdio.h>
#include <stdlib.h>
#include "Conjunto.h"  

int main(void) {
    SET *conjunto_A = NULL, *conjunto_B = NULL;  // Ponteiros para os conjuntos A e B
    unsigned char tipo;  // Tipo da estrutura de dados (0 para AVL, 1 para LLRB)
    int opcao;           // Código da operação escolhida pelo usuário
    int elemento;        // Elemento a ser inserido, removido ou verificado
    int n_A, n_B;        // Quantidade de elementos nos conjuntos A e B
    SET *resultado = NULL;  // Ponteiro para armazenar o conjunto resultante das operações

    // Lê o tipo de estrutura de dados (0 para AVL, 1 para LLRB)
    scanf("%hhu", &tipo);
    conjunto_A = set_criar(tipo);
    conjunto_B = set_criar(tipo);

    // Lê o número de elementos do conjunto A
    scanf("%d", &n_A); 
    
    // Lê o número de elementos do conjunto B
    scanf("%d", &n_B);

    // Adiciona elementos ao conjunto A
    for (int i = 0; i < n_A; i++) {
        scanf("%d", &elemento);
        set_inserir(conjunto_A, elemento);  // Insere cada elemento no conjunto A
    }

    // Adiciona elementos ao conjunto B
    for (int i = 0; i < n_B; i++) {
        scanf("%d", &elemento);
        set_inserir(conjunto_B, elemento);  // Insere cada elemento no conjunto B
    }

    // Lê a operação a ser realizada
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:  // Verifica se um elemento pertence ao conjunto A
            scanf("%d", &elemento);
            if (set_pertence(conjunto_A, elemento)) {
                printf("Pertence\n");
            } else {
                printf("Nao pertence\n");
            }
            break;

        case 2:  // Realiza a união dos conjuntos A e B
            resultado = set_uniao(conjunto_A, conjunto_B);  // União dos conjuntos
            set_imprimir(resultado);  // Imprime o conjunto resultante
            set_apagar(&resultado);  // Libera a memória do conjunto resultante
            break;

        case 3:  // Realiza a interseção dos conjuntos A e B
            resultado = set_interseccao(conjunto_A, conjunto_B);  // Interseção dos conjuntos
            set_imprimir(resultado);  // Imprime o conjunto resultante
            set_apagar(&resultado);  // Libera a memória do conjunto resultante
            break;

        case 4:  // Remove um elemento do conjunto A
            scanf("%d", &elemento);
            if (set_remover(conjunto_A, elemento)) {
                printf("Elemento %d removido do conjunto A.\n", elemento);
            } else {
                printf("Elemento %d nao encontrado no conjunto A.\n", elemento);
            }
            set_imprimir(conjunto_A);  // Imprime o conjunto A após a remoção
            break;

        default:  // Caso de opção inválida
            printf("Opcao invalida.\n");
            break;
    }

    // Libera a memória dos conjuntos A e B
    set_apagar(&conjunto_A);
    set_apagar(&conjunto_B);

    return 0;
}
