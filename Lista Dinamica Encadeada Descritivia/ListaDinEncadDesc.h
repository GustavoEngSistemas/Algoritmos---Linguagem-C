/* Definir:
    - os prot�tipos das fun��es
    - o tipo de dado armazenado na lista
    - o ponteiro "Lista"
*/

struct aluno{
    int mat;
    char nome[30];
    float n1, n2, n3;
};

typedef struct descritor Lista;

Lista* cria_lista();

void libera_lista(Lista* li);

int tamanho_lista(Lista* li);

int lista_vazia(Lista* li);

int insere_lista_inicio(Lista* li, struct aluno al);

int insere_lista_final(Lista* li, struct aluno al)

int remove_lista_inicio(Lista* li);

int remove_lista_final(Lista* li);
