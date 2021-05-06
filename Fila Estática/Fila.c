/* definir:
    - o tipo de dados "fila"
    - implementar as funções
*/

#include "Fila.h"
#include <stdlib.h>

struct fila{
    int inicio, final, qtd;
    struct aluno dados[MAX];
};

Fila* cria_fila(){
    Fila *fi = (Fila*) malloc(sizeof(Fila));
    if(fi != NULL){
        fi->final = 0;
        fi->inicio = 0;
        fi->qtd = 0;
    }
    return fi;
}

void libera_fila(Fila* fi){
    free(fi);
}

int tamanho_fila(Fila* fi){
    if(fi != NULL)
        return fi->qtd;
    return -1;
}

int fila_cheia(Fila* fi){
    if(fi != NULL && fi->qtd == MAX)
        return 1;
    return 0;
}

int fila_vazia(Fila* fi){
    if(fi != NULL && fi->qtd == 0)
        return 1;
    return 0;
}

int insere_fila(Fila*fi, struct aluno al){
    if(fi == NULL || fila_cheia(fi))
        return 0;
    fi->dados[fi->final] = al;
    fi->final = (fi->final+1) % MAX;
    fi->qtd++;
    return 1;
}

int remove_fila(Fila* fi){
    if(fi == NULL || fila_vazia(fi))
        return 0;
    fi->inicio = (fi->inicio+1) % MAX;
    fi->qtd--;
    return 1;
}

int consulta_fila(Fila* fi, struct aluno *al){
    if(fi == NULL || fila_vazia(fi))
        return 0;
    *al = fi->dados[fi->inicio];
    return 1;
}
