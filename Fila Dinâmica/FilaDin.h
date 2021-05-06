/* definir:
     - os protótipos das funções
     - o tipo de dado armazenado na lista
     - o ponteiro "fila"
*/

struct aluno{
    int matricula;
    char nome[30];
    float n1, n2, n3;
};

typedef struct fila Fila;

Fila* cria_fila();

void libera_fila(Fila* fi);

int tamanho_fila(Fila* fi);

int fila_vazia(Fila *fi);

int insere_fila(Fila *fi, struct aluno al);

int remove_fila(Fila *fi);

int consulta_fila(Fila *fi, struct aluno *al);
