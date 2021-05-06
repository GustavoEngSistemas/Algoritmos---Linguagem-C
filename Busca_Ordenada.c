#include <stdio.h>
#include <stdlib.h>

int busca_ordenada(int *V, int N, int elem){
    int i;
    for(i = 0; i < N; i++){
        if(elem == V[i])
            return i;
        else
            if(elem < V[i])
                return -1;
    }
    return -1;
}


void main(){
    int V[10];
    for(int i = 0; i < 10; i++){
        V[i] = i+1;
    }
    int pos_enc = busca_ordenada(V, 10, 4);
    printf("pos = %d, elemen = %d", pos_enc, V[pos_enc]);
}