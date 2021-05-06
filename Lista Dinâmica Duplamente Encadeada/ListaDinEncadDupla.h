/* Definir:
    - os protótipos das funções
    - o tipo de dado armazenado na lista
    - o ponteiro "lista"
*/

struct aluno{
    int matricula;
    char nome[30];
    float n1, n2, n3;
};

typedef struct elemento* Lista;

Lista* cria_lista();

void libera_lista(Lista* li);

int tamanho_lista(Lista* li);

int lista_vazia(Lista* li);

int insere_lista_inicio(Lista* li, struct aluno al);

int insere_lista_fim(Lista* li, struct aluno al);

int insere_lista(Lista* li, struct aluno al);

int remove_lista_inicio(Lista* li);

int remove_lista_final(Lista* li);

int remove_lista_final(Lista* li, int mat);

int pesquisa_list_pos(Lista* li, int pos, struct aluno *al);

int pesquisa_list_mat(Lista* li, int mat, struct aluno *al);
