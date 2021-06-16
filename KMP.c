#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct {
	int * vetor, tamanho;
} vetor_de_inteiros;

void inserir_indice(vetor_de_inteiros * v, int indice){
	v->vetor = realloc(v->vetor, (v->tamanho + 1)*sizeof(int));
	v->vetor[v->tamanho] = indice;
	v->tamanho++;
}

vetor_de_inteiros * criar_vetor(){
	vetor_de_inteiros * v = malloc(sizeof(vetor_de_inteiros));
	v->vetor = malloc(sizeof(int));	//Aloca o vetor de inteiros para poder ser realocado posteriormente.
	v->tamanho = 0; //Inicializa o tamanho do vetor
	return v;
}

//Recebe o padrão,  tamanho do padrão e vetor que irá armazenar os padrões
void prefixoSufixo(char* pad, int M, int* auxiliar) {
	int j = 0;
	auxiliar[0] = 0;
	int i = 1; 
	while (i < M) {
		if (pad[i] == pad[j]) {
			j++;
			auxiliar[i] = j;
			i++;
		}
		else{
			if (j != 0)
				j = auxiliar[j - 1];
			else {
				auxiliar[i] = 0;
				i++;
			}
		}
	}
}


vetor_de_inteiros * KMP(char* texto, char* padrao) {
	//Vetor para armazenar os indices onde o padrão é encontrado
	vetor_de_inteiros * indices = criar_vetor();
	int M = strlen(padrao);
	int N = strlen(texto);
	//Vetor auxiliar que armazena os valores da função de prefixo
	int auxiliar[M];
	prefixoSufixo(padrao, M, auxiliar);

	//Percorre o texto
	int i = 0;
	//Percorre o padrão
	int j = 0;

	while (i < N) {
		//A letra lida corresponde a uma parte do padrão
		if (padrao[j] == texto[i]) {
			j++;
			i++;
		} 
		//Encontrou um padrão completo
		if (j == M) {
			inserir_indice(indices, i - j);
			j = auxiliar[j - 1];
		}
		else if (i < N && padrao[j] != texto[i]) {
			if (j != 0)
				j = auxiliar[j - 1];
			else
				i = i + 1;
		}
	}
	return indices;
}

int main() {

	FILE *stream;
	char nome_arq[50], padrao_procurado[50];
	int tam_arq;
	vetor_de_inteiros * indices;
	int i;


	printf("Qual arquivo deseja ler? ");
	scanf("%s", nome_arq);
	stream = fopen(nome_arq, "r");

	if(stream != NULL){
		printf("Arquivo aberto com sucesso...\n");
		fseek(stream, 0, SEEK_END);
		tam_arq = ftell(stream)/ sizeof(char);
		fseek(stream, 0, SEEK_SET);
	} 
	else{
		printf("Arquivo inexistente..\n");
		exit(1);
	}

	printf("Qual padrao voce deseja procurar? ");
	scanf("%s", padrao_procurado);
	char text[tam_arq+1];
	fread(&text, sizeof(char), tam_arq, stream);

	indices = KMP(text, padrao_procurado);

	//Imprimir o resultado 
	if(indices->tamanho == 0) {
		printf("O padrao nao foi encontrado.\n");
	}else if(indices->tamanho == 1) {
		printf("O padrao foi encontrado no indice %d.\n", indices->vetor[0]);
	} else {
		printf("O padrao foi encontrado %d vezes. Nos indices :", indices->tamanho);
		printf(" %d", indices->vetor[0]);
		for(i = 1; i < indices->tamanho-1; i++) {
			printf(", %d", indices->vetor[i]);
		}
		printf(" e %d.\n", indices->vetor[indices->tamanho-1]);
	}
	fclose(stream);
	return 0;
}