#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int *adj;
    int tamanho;
}adjacentes;


typedef struct{
    adjacentes *fila;
    int frente;
    int tras;
}queue;

typedef struct{
    int v; //valor do vertice
    char cor; //b = blac, g = grey, w = white;
    int d; // distância;
    int pai;
    int f;
    adjacentes *adj;
} vertice;


typedef struct{
    int n; //quantidade de vértices(nós)  distintos
    vertice **vertices; //vetor para armazenar vértices
}grafo;


vertice* cria_vertice(int v) {
    vertice* novo_vertice = malloc(sizeof(vertice));
    novo_vertice->v = v;
    novo_vertice->cor = 'w';
    novo_vertice->d = 0;
    novo_vertice->pai = -1;
    novo_vertice->adj = malloc(sizeof(adjacentes));
    novo_vertice->adj->adj = malloc(sizeof(int));
    novo_vertice->adj->tamanho = 0;
    return novo_vertice;
}


grafo* cria_grafo(int quant_vertices){
    grafo* g = malloc(sizeof(grafo));
    g->n = quant_vertices;
    g->vertices = malloc(quant_vertices * sizeof(struct node*));
    int i;
    for (i = 0; i < quant_vertices; i++){
        g->vertices[i] = cria_vertice(i);
    }

    return g;
}


void adicionar_aresta(grafo* g, int origem, int dest) {
    g->vertices[origem]->adj->adj = realloc(g->vertices[origem]->adj->adj, (g->vertices[origem]->adj->tamanho + 1)*sizeof(int));
    g->vertices[origem]->adj->adj[g->vertices[origem]->adj->tamanho] = dest;
	g->vertices[origem]->adj->tamanho++;
}


void percorre_arq(FILE *ptr_arq, grafo *g){
    rewind(ptr_arq);
    char frase[5];
    //tira a primeira linha, que se refere ao
    fread(frase, sizeof(char), 4, ptr_arq);
    while(fread(frase, sizeof(char), 4, ptr_arq) > 0){
        int org, dest;
        //O - '0' serve para converter o caractere '1' por exemplo, no inteiro 1
        org = frase[0] - '0';
        dest = frase[2] - '0';
        adicionar_aresta(g, org, dest);
        
    }
}

void imprime_grafo(grafo *g){
    int i;
    for(i = 0; i < g->n; i++){
        //print([v, cor, pai, d]) - vizinhos
        printf("[ vertice: %d ]", g->vertices[i]->v);
        printf(" -> ");
        int j;
        for(j = 0;  j < g->vertices[i]->adj->tamanho; j++){
            if(j != g->vertices[i]->adj->tamanho -1)
                printf(" %d ->", g->vertices[i]->adj->adj[j]);
            else
                printf(" %d", g->vertices[i]->adj->adj[j]);
        }
        printf("\n");
    }
}

queue* criar_queue(int tam){
    queue* q = malloc(sizeof(queue));
    q->frente = -1;
    q->tras = -1;
    q->fila = malloc(sizeof(adjacentes));
    q->fila->adj = malloc(tam * (sizeof(int)));
    q->fila->tamanho = tam;
    return q;
}

int esta_vazia(queue* q) {
    if (q->tras == -1)
        return 1;
    else
        return 0;
}

void enqueue(queue* q, int valor) {
    if (q->tras == q->fila->tamanho - 1)
        printf("Fila Cheia!!\n");
    else{
        if (q->frente == -1)
        q->frente = 0;
        q->tras++;
        q->fila->adj[q->tras] = valor;
    }
}

int dequeue(queue* q){
    int item;
    if (esta_vazia(q)) {
        printf("A Fila está vazia\n");
        item = -1;
    } 
    else{
        item = q->fila->adj[q->frente];
        q->frente++;
        if (q->frente > q->tras){
            printf("Resetando fila...\n");
            q->frente = q->tras = -1;
        }
    }
    return item;
}

void exibir_queue(queue* q) {
    int i = q->frente;
    if (esta_vazia(q)) {
        printf("Fila Vazia");
    } 
    else {
        printf("\nA fila contem...\n");
        for (i = q->frente; i < q->tras + 1; i++) {
            printf("%d ", q->fila->adj[i]);
        }
        printf("\n");
    }
}


void BFS(grafo* g, int vertice_inicio) {
    for(int x = 0; x < g->n; x++){
        g->vertices[x]->cor = 'w';
        g->vertices[x]->d = '0';
        g->vertices[x]->pai = -1;
    }
    queue* q = criar_queue(g->n);
    g->vertices[vertice_inicio]->cor = 'g';
    g->vertices[vertice_inicio]->d = 0;
    g->vertices[vertice_inicio]->pai = -1;

    enqueue(q, vertice_inicio);
    while (!esta_vazia(q)) {
        exibir_queue(q);
        int vertice_atual = dequeue(q);
        printf("Visitado %d\n", vertice_atual);
        for(int i = 0; i < g->vertices[vertice_atual]->adj->tamanho; i++){
            if(g->vertices[g->vertices[vertice_atual]->adj->adj[i]]->cor == 'w'){
                g->vertices[g->vertices[vertice_atual]->adj->adj[i]]->cor = 'g';
                g->vertices[g->vertices[vertice_atual]->adj->adj[i]]->d = g->vertices[vertice_atual]->d + 1;
                g->vertices[g->vertices[vertice_atual]->adj->adj[i]]->pai = g->vertices[vertice_atual]->v;
                enqueue(q, g->vertices[g->vertices[vertice_atual]->adj->adj[i]]->v);
            }
        }
        g->vertices[vertice_atual]->cor = 'b';
        
    }
}


void imprime_distancias(grafo *g){
    int i;
    printf("\n\n");
    for(i = 0; i < g->n; i++){
        //print([v, cor, pai, d]) - vizinhos
        printf("[ vertice: %d | cor: %c | π: %d | distancia: %d]\n", g->vertices[i]->v,
                                                                     g->vertices[i]->cor,
                                                                     g->vertices[i]->pai,
                                                                     g->vertices[i]->d);
        
        
        printf("\n");
    }
}

void DFS_VISIT(grafo* g, vertice* u, int *tempo){
    ++*tempo;
    printf("Visitando Vertice: %d\n", u->v);
    u->d = *tempo;
    u->cor = 'g';
    for(int i = 0; i < u->adj->tamanho; i++){
        if(g->vertices[u->adj->adj[i]]->cor == 'w'){
            g->vertices[u->adj->adj[i]]->pai = u->v;
            DFS_VISIT(g, g->vertices[u->adj->adj[i]], tempo);
        }
    }
    u->cor = 'b';
    ++*tempo;
    u->f = *tempo;

}

void DFS(grafo* g, int vertice_origem){
    int i;
    for(i= 0; i < g->n; i++){
        g->vertices[i]->cor = 'w';
        g->vertices[i]->d = 0;
        g->vertices[i]->pai = -1;
        g->vertices[i]->f = 0;
     }
    int tempo = 0;
    int *ptr_tempo = &tempo;
    for(i= 0; i < g->n; i++){
        if(g->vertices[i]->cor == 'w'){
            
            DFS_VISIT(g, g->vertices[i], ptr_tempo);
        }
    }
    
}

void imprime_tempos(grafo *g){
    int i;
    printf("\n\n");
    for(i = 0; i < g->n; i++){
        //print([v, cor, pai, d]) - vizinhos
        printf("[ vertice: %d | cor:%c | π: %d | d: %d | f: %d]\n",  g->vertices[i]->v,
                                                                     g->vertices[i]->cor,
                                                                     g->vertices[i]->pai,
                                                                     g->vertices[i]->d,
                                                                     g->vertices[i]->f);
        
        printf("\n");
    }
}


int main(void) {
    FILE *ptr_arq;
    grafo *g;
    char cabecalho[4];
    int num_v;
    ptr_arq = fopen("arestas.txt", "r");
    fread(cabecalho, sizeof(char), 4, ptr_arq);
    //lê o número de vertices e converte em um inteiro
    num_v = cabecalho[0] - '0';
    
    //cria o gráfo
    g = cria_grafo(num_v);
    percorre_arq(ptr_arq, g);
    printf("--------------------------- Grafo e suas adjacências ---------------------------\n");
    imprime_grafo(g);
    printf("--------------------------------- Função de BFS --------------------------------\n");
    BFS(g, 0);
    printf("------------------------------- Distâncias Pós BFS ------------------------------\n");
    imprime_distancias(g);
    printf("--------------------------------- Função de DFS --------------------------------\n");
    DFS(g, 0);
    printf("--------------------------------- Tempos de DFS --------------------------------\n");
    imprime_tempos(g);

    fclose(ptr_arq);
    return 0;
    
}