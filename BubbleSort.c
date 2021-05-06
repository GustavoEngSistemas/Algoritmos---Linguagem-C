/* 
    - Compara pares de elementos adjacentes e os troca de lugar se estiverem na ordem errada.
    - Esse processo se repete até que mais nenhuma troca seja necessáriia (elementos já ordenados)
    - Performace:
        * melhor caso = (N)
        * Pior caso = (N^2)
        * Não recomendado para grandes conjuntos de dados
*/

void bubbleSort(int *V, int N){
    int i, continua, aux, fim = N;
    do{
        continua = 0;
        for(i = 0; i < fim-1; i++){
            if(V[i] > V[i+1]){
                aux = V[i];
                V[i] = V[i+1];
                V[i+1] = aux;
                continua = i;
            }
        }
        fim--;
    }while(continua != 0);
}
