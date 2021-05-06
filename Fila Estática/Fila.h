/* definir:
    - os protótipos das funções
    - o tipo de dado armazenado na fila
    - o ponteiro "fila"
    - tamanho do vetor usado na fila
*/

#define MAX 100

struct aluno{
    int matricula;
    char nome[30];
    float n1, n2, n3;
};

typedef struct fila Fila;

Fila* cria_fila();

void libera_fila(Fila* fi);


int tamanho_fila(Fila* fi);

int fila_cheia(Fila* fi);

int fila_vazia(Fila* fi);

int insere_fila(Fila*fi, struct aluno al);

int remove_fila(Fila* fi);
