/*
    definir:
    - os protótipos das funções
    - o tipo de dado armazenado na pilha
    - o ponteiro "pilha"
    - o tamanho do vetor usado na pilha
*/
#define MAX 100

struct aluno{
    int matricula;
    char nome[30];
    float n1, n2, n3;
};

typedef struct pilha Pilha;

Pilha* cria_pilha();

void libera_pilha(Pilha* pi);

int tamanho_pilha(Pilha* pi);

int pilha_vazia(Pilha *pi);

int pilha_cheia(Pilha* pi);

int insere_pilha(Pilha* pi, struct aluno al);

int remove_pilha(Pilha *pi);

int busca_pilha(Pilha *pi, struct aluno al);
