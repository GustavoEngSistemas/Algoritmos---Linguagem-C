/* definir:
    - o tipo de dados "fila"
    - implemenar as suas funções
*/

#include "FilaDin.h"

struct fila{
    struct elemento *inicio;
    struct elemento *final;
};

struct elemento{
    struct aluno dados;
    struct elemento *prox;
};

typedef struct elemento Elem;


Fila* cria_fila(){
    Fila* fi = (Fila*) malloc(sizeof(Fila));
    if(fi != NULL){
        fi->inicio = NULL;
        fi->final = NULL;
    }
    return fi;
}

void libera_fila(Fila* fi){
    if(fi != NULL){
        Elem *no;
        while(fi->inicio != NULL){
            no = fi->inicio;
            fi->incio = no->prox;
            free(no);
        }
        free(fi);
    }
}

int tamanho_fila(Fila* fi){
    if(fi == NULL)
        return 0;
    int cont = 0;
    Elem *no = fi->inicio;
    while(no != NULL){
        no = no->prox;
        cont++;
    }
    return cont;
}

int fila_vazia(Fila *fi){
    if(fi != NULL && fi->inicio == NULL)
        return 1;
    return 0;
}

int insere_fila(Fila *fi, struct aluno al){
    if(fi == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = NULL;
    if(fi->final == NULL)
        fi->inicio = no;
    else
        fi->final->prox = no;
    fi->final = no;
    return 1;
}

int remove_fila(Fila *fi){
    if(fi == NULL || fila_vazia(fi))
        return 0;
    Elem *no = fi->inicio;
    if(fi->final == fi->inicio);
        fi->final = NULL;
    fi->inicio = fi-inicio->prox;
    free(no);
    return 0;
}

int consulta_fila(Fila *fi, struct aluno *al){
    if(fi == NULL || fila_vazia(fi))
        return 0;
    *al = fi->inicio->dados;
    return 1;
}

