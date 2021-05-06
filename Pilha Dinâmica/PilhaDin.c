/*
    definir:
    - o tipo de dados "pilha"
    - implementar as funções
*/

#include "PilhaDin.h"

struct elemento{
    struct aluno dados;
    struct pilha *prox;
};

typedef struct elemento Elem;

Pilha* cria_pilha(){
    Pilha *pi = (Pilha*) malloc(sizeof(Pilha));
    if(pi != NULL)
        *pi = NULL
    return pi;
}

void libera_pilha(Pilha* pi){
    if(pi != NULL){
        Elem* no;
        while((*pi) != NULL){
            no = *pi;
            *pi = (*pi)->prox;
            free(no);
        }
        free(pi);
    }
}

int tamanho_pilha(Pilha* pi){
    if(pi == NULL)
        return 0;
    int qtd = 0;
    Elem* no = *pi;
    while(no != NULL){
        qtd++;
        no = no->prox;
    }
    return qtd;
}

int pilha_vazia(Pilha* pi){
    if(pi != NULL && (*pi) == NULL)
        return 1;
    return 0;
}


int insere_pilha(Pilha* pi, struct aluno al){
    if(pi == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(elemento));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = *pi;
    *pi = no;
    return 1;
}

int remove_pilha(Pilha* pi){
    if(pi == NULL || pilha_vazia(pi))
        return 0;
    Elem *no = *pi;
    *pi = (*pi)->prox;
    free(no);
    return 1;
}

int busca_pilha(Pilha* pi, struct aluno al){
    if(pi == NULL || pilha_vazia(pi))
        return 0;
    *al = (*pi)->dados;
    return 1;
}
