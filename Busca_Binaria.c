int busca_binaria(int *V, int N, int elem){
    int i, inicio, meio, final;
    inicio = 0;
    final = N-1;
    while (inicio <= final){
        meio = (inicio+final) / 2;
        if(elem < V[meio])
        final = meio - 1;
        else
            if(elem > V[meio])
                inicio = meio + 1;
            else
                return meio;
    }
    return -1;
}


void main(){
    int V[10] = {1, 2, 3, 4, 5, 6, 7, 8};
    int pos_enc = busca_binaria(V, 10, 4);
    printf("pos = %d, elemen = %d", pos_enc, V[pos_enc]);
}