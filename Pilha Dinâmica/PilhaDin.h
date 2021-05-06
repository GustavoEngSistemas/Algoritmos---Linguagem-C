/*
    definir:
    - os protótipos das funções
    - o tipo de dado armazenado na pilha
    - o ponteiro "Pilha"
*/


struct aluno{
    int matricula;
    char nome[30];
    float n1, n2, n3;
};

typedef struct elemento* Pilha;

Pilha* cria_pilha();

void libera_pilha(Pilha* pi);

int tamanho_pilha(Pilha* pi);

int pilha_vazia(Pilha* pi);

int insere_pilha(Pilha* pi, struct aluno al);

int remove_pilha(Pilha* pi);

int busca_pilha(Pilha* pi, struct aluno al);
