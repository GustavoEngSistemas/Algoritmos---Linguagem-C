#include <stdio.h>
#include <stdlib.h>
#include "ListaSequencial.h"

int main()
{
    int tam;
    struct aluno al1, al2, al3;
    Lista *li = NULL;
    li = cria_lista();
    al1.matricula = 10;
    al2.matricula = 30;
    al3.matricula = 20;
    insere_lista_meio(li, al2);
    insere_lista_meio(li, al1);
    insere_lista_meio(li, al3);
    exibir_lista(li);
    tam = tamanho_lista(li);

    libera_lista(li);
    return 0;
}
