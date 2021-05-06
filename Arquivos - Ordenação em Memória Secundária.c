//arquivo escrito por Gustavo Oliveira
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct{
    int num;
    char nome[30];
    char profissao[50];
}tipo;


void imprime_registros(FILE *fp){
    tipo aux;
    fseek(fp, 0, SEEK_SET);
    while (fread(&aux, 1, sizeof(tipo), fp) > 0)
    {
        printf("%d %s %s\n", aux.num, aux.nome, aux.profissao);
    }
}

tipo busca_binaria(FILE *fp, int N, int elem){
    int i, inicio, meio, final;
    tipo atual;
    inicio = 0;
    final = N-1;
    while (inicio <= final){
        meio = (inicio+final) / 2;
        fseek(fp, meio*sizeof(tipo), SEEK_SET);
        fread(&atual, sizeof(tipo), 1, fp);
        if(elem < atual.num)
            final = meio - 1;
        else
            if(elem > atual.num)
                inicio = meio + 1;
            else
                return atual;
    }
    atual.num = -1;
    return atual;
}


int main(){
    FILE *fp = fopen("nomes.bin", "r+b");
    size_t tam_dado = sizeof(tipo); // tamanho do tipo de dado armazenado
    int quant_dados; //quantidadade de dados registrados no arquivo
    tipo dados, dados_aux;
    int i, j, h;
    setlocale(LC_ALL, "Portuguese_Brazil");

    //verificando a abertura do arquivo
    if(fp == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    //encontrar o número de dados do arquivo
    fseek(fp, 0, SEEK_END);
    quant_dados = ftell(fp) / tam_dado;
    rewind(fp);

    //algoritmo shell sort - funciona comparando os valores por uma quantidade de passos inicial
    //e dividde à cada vez o número de passos pela metade, até que ele chegue à 1
    //o h se refere ao gap (ou número de saltos que o algoritmo dará)
    for(h = quant_dados/2; h > 0; h /= 2){
        //as variáveis i e j serão as responsáveis por demarcar as posições que deverão ser comparadas no passo
        for(i = h; i < quant_dados; i++){
            j = i;

            fseek(fp, i*tam_dado, SEEK_SET);
            fread(&dados_aux, tam_dado, 1, fp);
            rewind(fp);

            fseek(fp, (j-h)*tam_dado, SEEK_SET);
            fread(&dados, tam_dado, 1, fp);
            rewind(fp);

            //verifica se os dados precisam ser trocados, e faz a troca, como no insertion sort
            for(; j>= h && dados_aux.num < dados.num; j -= h){
                fseek(fp, j*tam_dado, SEEK_SET);
                fwrite(&dados, tam_dado, 1, fp);
                rewind(fp);

                fseek(fp,(j - 2*h)*tam_dado, SEEK_SET);
                fread(&dados, tam_dado, 1, fp);
                rewind(fp);
            }

            fseek(fp, j*tam_dado, SEEK_SET);
            fwrite(&dados_aux, tam_dado, 1, fp);
            rewind(fp);
        }
    }


    imprime_registros(fp);
    dados_aux = busca_binaria(fp, quant_dados, 17229);
    if(dados_aux.num != -1){
        printf("%d %s %s\n", dados_aux.num, dados_aux.nome, dados_aux.profissao);
    }
    fclose(fp);
    return 0;
}



