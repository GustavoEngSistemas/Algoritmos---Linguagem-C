/*
    - Similar a ordenação de cartas de baralho com as mãos
    - Pega-se uma carta de cada vez e a coloca em seu devido lugar, sempre deixando as cartas da mão em ordem
    - Perfomace:
        * Melhor caso = (N)
        * Puior caso = (N^2)
        * Edificiente para conjuntos pequenos de dados
        * Estável: não altera a ordem de dados iguais
        * Capaz de ordenar os dados a medida em que os recebe (tempo real)
*/

void insertionSort(int *V, int N){
    int i, j, aux;
    for(i = 1; i < N; i++){
        aux = V[i];
        for(j = i; (j>0) && (aux < V[j-1]); j--)
            V[j] = V[j-1];
        V[j] = aux ;
    }
}
