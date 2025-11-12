#include<stdlib.h>
#include<stdio.h>
#include"LLRB.h"
#include"conjunto.h"

//Definição da estrutura da árvore Rubro negra(LLRB);
struct arv_LLRB{
    NO* raiz;
};

//Definição da estrutura do nó da árvore 
struct no_{
    int chave; //valor armazenado no nó
    NO* fesq; //ponteiro para filho esquerdo
    NO* fdir; //ponteiro para filho direito
    int cor; // 1 para vermelha, 0 para preta 
};

// Criação de uma nova árvore rubro-negra
LLRB* llrb_criar(void){
    LLRB *T = (LLRB*)malloc(sizeof(LLRB));
    if(T != NULL){
        T->raiz = NULL;
        return(T);
    }
    return(NULL);
}
// Função recursiva para apagar todos os nós da árvore
void llrb_apagar_no(NO *raiz) {
    if (raiz == NULL) return;

    // Apagar as subárvores esquerda e direita
    llrb_apagar_no(raiz->fesq);
    llrb_apagar_no(raiz->fdir);

    // Desalocar o nó atual
    free(raiz);
    raiz = NULL;
}


// Função para apagar a árvore inteira
void llrb_apagar(LLRB **T) {
    if (*T == NULL || (*T)->raiz == NULL) return;

    // Apagar a árvore recursivamente a partir da raiz
    llrb_apagar_no((*T)->raiz);

    // Desalocar a estrutura da árvore
    free(*T);
    *T = NULL;
}
// Função para criar um novo nó da árvore
NO* criar_no(int chave){
    NO* No = (NO*)malloc(sizeof(NO));
    if(No != NULL){
        No->chave = chave;
        No->fesq = NULL;
        No->fdir = NULL;
        No->cor = 1;
        return(No);
    }
    return(NULL);
}

// Verifica se um nó é vermelho(arresta)
int vermelha(NO *raiz){
    if(raiz == NULL){
        return 0; // Nó nulo é considerado preto(arresta)
    }
    return (raiz->cor == 1);
}
// Função de rotação à esquerda
NO* rodar_esquerda(NO* raiz){
    NO* b;
    b = raiz->fdir;
    raiz->fdir = b->fesq;
    b->fesq = raiz;

    b->cor = raiz->cor;
    raiz->cor = 1;
    return b;
}
// Função de rotação à direita
NO* rodar_direita(NO* raiz){
    NO* b;
    b = raiz->fesq;
    raiz->fesq = b->fdir;
    b->fdir = raiz;

    b->cor = raiz->cor;
    raiz->cor = 1;
    return b;
}
// Inverte a cor de um nó e seus filhos
NO* inverter_cor(NO *raiz){
    raiz->cor = !raiz->cor;
    if(raiz->fesq){
        raiz->fesq->cor = !raiz->fesq->cor;
    }
    if(raiz->fdir){
        raiz->fdir->cor = !raiz->fdir->cor;
    }
}
// Função para inserir um nó na árvore recursivamente
NO* llrb_inserir_no(NO* raiz,NO* novo_no){
    if(raiz == NULL){
        raiz = novo_no;// Caso base: árvore vazia, insere o novo nó
        return raiz;
    }
    if(novo_no->chave < raiz->chave){
        raiz->fesq = llrb_inserir_no(raiz->fesq, novo_no); //inseri a esquerda
    }
    if(novo_no->chave > raiz->chave){
        raiz->fdir = llrb_inserir_no(raiz->fdir, novo_no);//inseri a direita
    }

    //ajustando as cores e balanceamento
    if(vermelha(raiz->fdir) && !vermelha(raiz->fesq)){
        raiz = rodar_esquerda(raiz);// Caso de rotação à esquerda
    }
    if(vermelha(raiz->fesq) && vermelha(raiz->fesq->fesq)){
        raiz = rodar_direita(raiz);// Caso de rotação à direita
    }
    if(vermelha(raiz->fesq) && vermelha(raiz->fdir)){
        inverter_cor(raiz);// Inverte as cores dos nós
    }
    return raiz;
}

// Função para inserir um nó na árvore rubro-negra
bool llrb_inserir(LLRB *T, int chave){
    if(T == NULL){
        return(false);// Se a árvore for NULL, não é possível inserir
    }
    NO* novo_no = criar_no(chave);//criando novo no
    if(novo_no != NULL){
        T->raiz = llrb_inserir_no(T->raiz, novo_no);// Insere o nó na árvore
        T->raiz->cor = 0;// Garante que a raiz seja preta
        return(true);
    }
    return false;// Retorna false se a criação do nó falhar
   
}
// Função para verificar se um valor está presente na árvore
bool llrb_pertence(LLRB *T, int chave) {
    if (T == NULL || T->raiz == NULL) return false;  // Check if T or T->raiz is NULL

    NO *noAtual = T->raiz;
    while (noAtual != NULL) {
        if (chave < noAtual->chave) {
            noAtual = noAtual->fesq;  // Left child
        } else if (chave > noAtual->chave) {
            noAtual = noAtual->fdir;  // Right child
        } else {
            return true;  // Found the element
        }
    }
    return false;  // Element not found
}

//Esta função é responsável pela propagação de aresta vermelha na subárvore esquerda
NO* mover_aresta_esquerda(NO* raiz){
    inverter_cor(raiz);
    if (vermelha(raiz->fdir->fesq)) {
        raiz->fdir = rodar_direita(raiz->fdir);
        raiz = rodar_esquerda(raiz);
        inverter_cor(raiz);
    }
    return raiz;
}
//Esta função é responsável pela propagação de aresta vermelha na subárvore direita
NO* mover_aresta_direita(NO* raiz) {
    inverter_cor(raiz);
    if (vermelha(raiz->fesq->fesq)) {
        raiz = rodar_direita(raiz);
        inverter_cor(raiz);
    }
    return raiz;
}
//Esta função remove o nó com o valor mínimo da árvore rubro-negra.
NO* remover_minimo(NO* raiz) {
    if (raiz->fesq == NULL) {
        free(raiz);
        return NULL;
    }

    if (!vermelha(raiz->fesq) && !vermelha(raiz->fesq->fesq)) {
        raiz = mover_aresta_esquerda(raiz);
    }

    raiz->fesq = remover_minimo(raiz->fesq);

    // Ajustar após remoção
    if (vermelha(raiz->fdir)) {
        raiz = rodar_esquerda(raiz);
    }
    if (vermelha(raiz->fesq) && vermelha(raiz->fesq->fesq)) {
        raiz = rodar_direita(raiz);
    }
    if (vermelha(raiz->fesq) && vermelha(raiz->fdir)) {
        inverter_cor(raiz);
    }

    return raiz;
}

//Esta função busca o nó com o valor mínimo na árvore rubro-negra
NO* buscar_minimo(NO* raiz){
    if (raiz == NULL) return NULL;
    while (raiz->fesq != NULL) {
        raiz = raiz->fesq;
    }
    return raiz;
}

//Função auxiliar para remoção do nó na árvore
NO* llrb_remover_no(NO *raiz, int chave) {
    if (raiz == NULL) {
        return NULL; // Chave não encontrada
    }

    if (chave < raiz->chave) {
        // Remover na subárvore esquerda
        if (!vermelha(raiz->fesq) && !vermelha(raiz->fesq->fesq)) {
            raiz = mover_aresta_esquerda(raiz);
        }
        raiz->fesq = llrb_remover_no(raiz->fesq, chave);
    } else {
        // Caso especial: rodar para a direita se nó esquerdo for vermelho
        if (vermelha(raiz->fesq)) {
            raiz = rodar_direita(raiz);
        }

        if (chave == raiz->chave && raiz->fdir == NULL) {
            // Caso base: remover nó folha
            free(raiz);
            return NULL;
        }

        // Ajustar subárvore direita para remoção
        if (!vermelha(raiz->fdir) && !vermelha(raiz->fdir->fesq)) {
            raiz = mover_aresta_direita(raiz);
        }

        if (chave == raiz->chave) {
            // Substituir pelo sucessor
            NO* min = buscar_minimo(raiz->fdir);
            raiz->chave = min->chave;
            raiz->fdir = remover_minimo(raiz->fdir);
        } else {
            raiz->fdir = llrb_remover_no(raiz->fdir, chave);
        }
    }

    // Chamando diretamente as funções de balanceamento
    if (vermelha(raiz->fdir)) {
        raiz = rodar_esquerda(raiz);
    }
    if (vermelha(raiz->fesq) && vermelha(raiz->fesq->fesq)) {
        raiz = rodar_direita(raiz);
    }
    if (vermelha(raiz->fesq) && vermelha(raiz->fdir)) {
        inverter_cor(raiz);
    }

    return raiz;
}

//Função principal para remover um nó na árvore
bool llrb_remover(LLRB *T, int chave) {
    if (T == NULL || T->raiz == NULL) {
        return false; // Árvore vazia, não há o que remover
    }

    NO *original_root = T->raiz;

    // Realizar a remoção e ajustar a raiz para ser preta
    T->raiz = llrb_remover_no(T->raiz, chave);
    
    if (T->raiz != NULL) {
        T->raiz->cor = 0; // Preto
    }

    // Se a raiz foi modificada, retorno true
    return (original_root != T->raiz);
}

// Função para calcular a interseção de duas árvores rubro-negras
LLRB* llrb_interseccao(LLRB *A, LLRB *B) {
    if (!A || !B) return NULL;

    LLRB *C = llrb_criar();  // Cria um novo conjunto para armazenar a interseção

    // Percorre a árvore A e insere os elementos comuns em C
    percorrer_e_inserir(A->raiz, B, C);

    return C;
}

// Função para percorrer a árvore A e verificar se o elemento está em B
void percorrer_e_inserir(NO* raizA, LLRB *B, LLRB *C) {
    if (raizA == NULL) return;
    
    // Verifica se o elemento existe em B
    if (llrb_pertence(B, raizA->chave)) {
        // Se o elemento está presente em B, insere em C
        llrb_inserir(C, raizA->chave);
        printf("Elemento %d inserido na interseção!\n", raizA->chave);  // Para depuração
    }

    // Percorre a árvore A recursivamente
    percorrer_e_inserir(raizA->fesq, B, C);
    percorrer_e_inserir(raizA->fdir, B, C);
}
//Função auxiliar para inserir em conjunto
void llrb_inserir_em_conjunto_aux(NO *no, SET *s) {
    if (no != NULL) {
        // Inserir à esquerda
        llrb_inserir_em_conjunto_aux(no->fesq, s);
        
        // Inserir o nó atual no conjunto
        set_inserir(s, no->chave);

        // Inserir à direita
        llrb_inserir_em_conjunto_aux(no->fdir, s);
    }
}
//Função para inserir em conjunto
void llrb_inserir_em_conjunto(LLRB *T, SET *s) {
    if (T != NULL && T->raiz != NULL) {
        // Percorrer a subárvore esquerda
        llrb_inserir_em_conjunto_aux(T->raiz->fesq, s);
        
        // Inserir o valor na estrutura do conjunto
        // Aqui você precisa adaptar para adicionar a chave do nó no conjunto
        set_inserir(s, T->raiz->chave);

        // Percorrer a subárvore direita
        llrb_inserir_em_conjunto_aux(T->raiz->fdir, s);
    }
}

//Função auxiliar para imprimir o nó
void llrb_imprimir_no(NO *raiz) {
    if (raiz == NULL) return;
        
    llrb_imprimir_no(raiz->fesq);
    printf("%d ", raiz->chave);
    llrb_imprimir_no(raiz->fdir);    
}
//Função para imprimir os nós na árvore
void llrb_imprimir(LLRB *T){
    if(T != NULL || T->raiz != NULL){
        llrb_imprimir_no(T->raiz);
    }
    
}
