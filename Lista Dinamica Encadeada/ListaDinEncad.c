/*
    definir:
    - o tipo de dados "lista"
    - implementar as suas funções.
*/
#include "ListaDinEncad.h"
#include "stdlib.h"

struct elemento{
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li){
    if(li != NULL){
        Elem* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int tamanho_lista(Lista* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_vazia(Lista* li){
    if(li == NULL)
        return 0;
    if(*li == NULL)
        return 1;
    return 0;
}

int insere_lista_inicio(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = (*li);
    *li = no;
    return 1;
}

int insere_lista_fim(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));

    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = NULL;
    if((*li) == NULL)
        *li = no;
    else{
        Elem *aux = (*li);
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    if(lista_vazia(li)){
        no->prox = (*li);
        *li = no;
        return 1;
    }
    else{
        Elem *ant, atual = *li;
        while(atual != NULL && atual->dados.matricula < al.matricula){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){ //insere no incio
                no->prox = (*li);
                *li = no;
        }
        else{
            no->prox = ant->prox;
            ant->prox = no;
        }
    }
    return 1;
}

int remove_lista_inicio(Lista* li){
    if(li == NULL || lista_vazia(li))
        return 0;
    Elem *no = *li;
    *li = no->prox;
    free(no);
    return 1;
}

int exibir_lista(Lista* li){
    if(li == NULL || lista_vazia(li))
        return 0;
    Elem *no = *li;
    for(no; no != NULL; no = no->prox){
        printf("MATRICULA: %d\n", no->dados.matricula);
    }
    return 1;
}

int remove_lista_fim(Lista* li){
    if(li == NULL || lista_vazia(li))
        return 0;
    Elem *no = *li;
    if(no->prox == NULL){
        free(no);
        *li = NULL;
    }
    else{
        for(no; no->prox->prox != NULL; no=no->prox);
        free(no->prox);
        no->prox = NULL;
    }
    return 1;
}

int remove_lista(Lista* li, int mat){
    if(li == NULL || lista_vazia(li))
        return 0;
    Elem *ant, *no = *li;
    while(no != NULL && no->dados.matricula != mat){
        ant = no;
        no = no->prox;
    }
    if(no == NULL)
        return 0;
    if(no == *li)
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return 1;
}

int procura_lista_pos(Lista* li, int pos, struct aluno *al){
    if(li == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    while(no != NULL && i < pos){
        no = no->prox;
        i++;
    }
    if(no == NULL)
        return 0;
    else{
        *al = no->dados;
        return 1;
    }
}

int procura_lista_mat(Lista* li, int mat, struct aluno *al){
    if(li == NULL)
        return 0;
    Elem *no = *li;
    while(no != NULL && no->dados.matricula != mat){
        no = no->prox;
    }
    if(no == NULL)
        return 0;
    else{
        *al = no->dados;
        return 1;
    }
}
