/*
    - A cada passo, procura o menor valor do array e o coloca na primeira posição do array
    - Descarta-se a primeira posição do array e repete-se o processo para a segunda posição
    - Isso é feito para todas as posições
    - Perfomance:
        * Melhor caso = (N^2)
        * Pior caso = (N^2)
        * Ineficiente para grandes conjuntos de dados
        * Estável: não altera a ordem de dados iguais.
*/

void selectionSort(int *V, int N){
    int i, j, menor, troca;
    for(i = 0; i < N-1; i++){
        menor = i;
        for(j = i+1; j < N; j++){
            if(V[j] < V[menor])
            menor = j;
        }
        if(i != menor){
            troca = V[i];
            V[i] = V[menor];
            V[menor] = troca;
        }
    }
}
