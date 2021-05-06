/*
    - Ideia básica: Dividir e conquistar
    - Um elemento é escolhido como pivô
    - Particionar: os dados são arranjados (valores menores do que o pivô são colcoados antes dele e os maiores, depois)
    - Recursivamente ordena as 2 partições
    - Performance: 
        * Melhor caso = (N log N)
        * Pior caso (raro) = (N ^ 2)
        * Estável: não altera a ordem de dados iguais
        * Desvantagens: como escolher o pivô??
*/


void quickSort(int *V, int inicio, int fim){
    int pivo;
    if(fim > inicio){
        pivo = particiona(V, inicio, fim);
        quickSort(V, inicio, pivo-1);
        quickSort(V, pivo+1, fim);
    }
}

int particiona(int *V, int inicio, int fim){
    int esq, dir, pivo, aux;
    esq = inicio;
    dir = fim;
    pivo = V[inicio];
    while (esq < dir){
        while(V[esq] <= pivo)
            esq++;
        while(V[dir] > pivo)
            dir--;
        if(esq < dir){
            aux = V[esq];
            V[esq] = V[dir];
            V[dir] = aux;
        }
    }
    V[inicio] = V[dir];
    V[dir] = pivo;
    return dir;
}