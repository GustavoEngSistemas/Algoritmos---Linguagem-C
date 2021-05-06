#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncad.h"

int main()
{
    Lista *li;
    struct aluno alunos[5];
    li = cria_lista();
    alunos[0].matricula = 10;
    alunos[1].matricula = 20;
    alunos[2].matricula = 30;
    alunos[3].matricula = 40;
    alunos[4].matricula = 50;


    insere_lista_ordenada(li, alunos[2]);
    insere_lista_ordenada(li, alunos[0]);
    insere_lista_ordenada(li, alunos[3]);
    insere_lista_ordenada(li, alunos[1]);
    insere_lista_ordenada(li, alunos[4]);

    exibir_lista(li);
    libera_lista(li);
    return 1;
}
