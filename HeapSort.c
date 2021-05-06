/*
    - Heap: vetor que simula uma árvore binária completa (exceção do último nível)
    - Todo elemento "Pai" do vetor possui dois elementos como "filhos"
    - "Pai" (i) -> "filhos": (2*i+1) e (2*i+2)
*/


void heapSort(int *V, int N){
    int i, aux;
    for(i = (N-1) /2; i >= 0; i--){
        criaHeap(V, i, N-1);
    }
    for(i = N-1; i >= 1; i--){
        aux = V[0];
        V[0] = V[i];
        V[i] = aux;
        criaHeap(V, 0, i - 1);
    }
}

void criaHeap(int *V, int inicio, int fim){
    int aux = V[inicio];
    int j = inicio * 2 + 1;
    while (j <= fim){
        if(j < fim){
            if(V[j] < V[j+1]){
                j = j + 1;
            }
        }
        if(aux < V[j]){
            V[inicio] = V[j];
            inicio = j;
            j = 2 * inicio * 1;
        }
        else{
            j = fim + 1;
        }
    }
    V[inicio] = aux;
}