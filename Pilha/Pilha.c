/*
    definir:
    - o tipo de dados "pilha"
    - implementar as suas funções
*/

#include "Pilha.h"

struct pilha{
    int qtd;
    struct aluno dados[MAX];
};

Pilha* cria_pilha(){
    Pilha *pi = (Pilha*) malloc(sizeof(pilha));
    if(pi != NULL)
        pi->qtd = 0;
    return pi;
}

void libera_pilha(Pilha* pi){
    if(pi != NULL)
        free(pi);
}

int tamanho_pilha(Pilha* pi){
    if(pi == NULL)
        return -1;
    else
        return pi->qtd;
}

int pilha_vazia(Pilha *pi){
    if(pi == NULL)
        return -1;
    return(pi->qtd == 0);
}

int pilha_cheia(Pilha* pi){
    if(pi == NULL)
        return -1;
    return(pi->qtd == MAX);
}

int insere_pilha(Pilha* pi, struct aluno al){
    if(pi == NULL || pilha_cheia(pi))
        return 0;
    pi->dados[pi->qtd] = al;
    pi->qtd++;
    return 1;
}

int remove_pilha(Pilha *pi){
    if(pi == NULL || pilha_vazia(pi))
        return 0;
    pi->qtd--;
    return 1;
}

int busca_pilha(Pilha *pi, struct aluno al){
    if(pi == NULL || pilha_vazia(pi))
        return 0;
    *al = pi->dados[pi->qtd-1];
    return 1;
}
