#include "ListaSequencial.h"
#include <stdlib.h>

struct lista{
    int qtd;
    struct aluno dados[MAX];
};

Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if (li != NULL){
        li -> qtd = 0;
    }
    return li;
}

void libera_lista(Lista* li){
    free(li);
}

int tamanho_lista(Lista* li){
    if(li == NULL)
        return -1;
    return li->qtd;
}

int lista_cheia(Lista* li){
    if(li == NULL)
        return -1;
    return(li->qtd == MAX);
}

int lista_vazia(Lista* li){
    if(li == NULL)
        return -1;
    return(li->qtd == 0);
}

int insere_lista_final(Lista* li, struct aluno al){
    if(li == NULL || lista_cheia(li))
        return 0;
    li->dados[li->qtd] = al;
    li->qtd++;
    return 1;
}

int insere_lista_inicio(Lista* li, struct aluno al){
    if(li == NULL || lista_cheia(li))
        return 0;
    int i;
    for(i=li->qtd-1; i >= 0; i--){
        li->dados[i+1] = li->dados[i];
    }
    li->dados[0]= al;
    li->qtd++;
    return 1;
}

int insere_lista_meio(Lista* li, struct aluno al){
    if(li == NULL || lista_cheia(li))
        return 0;
    int i = 0, j;
    while(i< li->qtd && li->dados[i].matricula < al.matricula){
        i++;
    }
    for(j = li->qtd-1; j >= i; j--){
        li->dados[j+1] = li->dados[j];
    }
    li->dados[i] = al;
    li->qtd++;
    return 1;
}

int exibir_lista(Lista *li){
    if(lista_vazia(li)){
        printf("LISTA VAZIA\n");
        return 0;
    }
    int i = 0;
    for(i; i < li->qtd; i++){
        printf("ALUNO %d = %d\n", i, li->dados[i].matricula);
    }
    return 1;
}

int remove_lista_final(Lista* li){
    if(li == NULL || lista_vazia(li))
        return 0;
    li->qtd--;
    return 1;
}

int remove_lista_inicio(Lista* li){
    if(li == NULL || lista_vazia(li))
        return 0;
    int k = 0;
    for(k=0; k < li->qtd-1; k++)
        li->dados[k] = li->dados[k+1];
    li->qtd--;
    return 1;
}

int remove_lista(Lista* li, int mat){
    if(li == NULL || lista_vazia(li))
        return 0;
    int k, i = 0;
    while (i < li->qtd && li->dados[i].matricula != mat)
        i++;
    if(i == li->qtd)
        return 0;
    for(k=i; k < li->qtd-1; k++)
        li->dados[k] = li->dados[k+1];
    li->qtd--;
    return 1;
}

int consulta_lista_pos(Lista* li, int pos, struct aluno *al){
    if(li == NULL || pos <= 0 || pos > li -> qtd)
        return 0;
    *al = li->dados[pos-1];
    return 1;
}

int consulta_lista_mat(Lista* li, int mat, struct aluno *al){
    if(li == NULL)
        return 0;
    int k, i=0;
    while(i<li->qtd && li->dados[i].matricula != mat)
        i++;
    if(i == li->qtd)
        return 0;
    *al = li-dados[i];
    return 1;
}
