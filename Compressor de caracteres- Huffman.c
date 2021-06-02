/*
  Compressor de caracteres utilizando o algoritmo de Huffman
  Desenvolvido para transformar um arquivo .txt em um arquivo .bin
  O arquivo .bin contêm um cabeçalho para descompressão.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


//definição do tipo de dado utilizado
struct no{
  unsigned char caractere; //armazena a letra
  unsigned int frequencia; //armazena a quantidade de ocorrencia da letra no texto
  struct no *prox; //ponteiro para ordenação e manipulação
  struct no *esq, *dir; //ponteiro para criação da arvore
  char bitmap[1024]; //armazena o codigo binario do arquivo.
};


//Struct base para o cabecalho
struct cabecalho{
  int caracteres_diferentes;
  int caracteres_extras;
}typedef Cabecalho;

//struct utilizada pra colocar tabela de caracteres no arquivo final
struct tabela{
  char bitmap[1024];
  unsigned char caract;
}typedef Tabela;


//ponteiro para armazenar o incio da lista
typedef struct no* Lista;
//Defininição do nome do tipo de dado
typedef struct no Elem;
//definição do tipo byte = 1 caractere = 8 bits
typedef unsigned char byte;


//função criada apenas para fazer um delay na execução do programa.
void delay(unsigned int secs){
  unsigned int end = time(0) + secs;
  while(time (0) < end);
}

//recebe como parametro o arquivo à ser lido
//percorre ele contabilizando cada caractere e criando uma lista encadeada com os caracteres e os valores;
//retorna uma cabeça de lista
Lista* conta_char(FILE *arq){
  Lista* cabeca_lista = (Lista*) malloc(sizeof(Lista));
  *cabeca_lista = NULL;
  Elem *novo_elem = (Elem*) malloc(sizeof(Elem));
  byte letra;
  rewind(arq);
  letra = fgetc(arq);
  //cadastrar a primeira letra;
  novo_elem->frequencia = 1;
  novo_elem->caractere = letra;
  novo_elem->esq = NULL;
  novo_elem->dir = NULL;
  novo_elem->prox = NULL;
  *cabeca_lista = novo_elem;

  //lê caractere por caractere do arquivo
  while(fread(&letra, 1, 1, arq) >= 1){
    Elem *atual = *cabeca_lista, *ant;
    //procura o caractere lido na lista criada
    while(atual != NULL && atual->caractere != letra){
      ant = atual;
      atual = atual->prox;
    }
    //o caractere ainda não está cadastrado na lista, insere ele no final
    if(atual == NULL){
      novo_elem = (Elem*) malloc(sizeof(Elem));
      novo_elem->frequencia = 1;
      novo_elem->caractere = letra;
      novo_elem->esq = NULL;
      novo_elem->dir = NULL;
      novo_elem->prox = NULL;
      ant->prox = novo_elem;
    }
    //como achou o caractere cadastrado, apenas incrementa uma unidade na sua frequencia
    else{
      atual->frequencia++;
    }
  }
  rewind(arq);
  //retorna o endereço da cabeça da lista
  //obs: a lista não está ordenada
  return cabeca_lista;
}

//recebe como parametro a cabeça da lista
int imprime_quant(Lista* li){
  //verifica se a lista existe e se ela está vazia ou não
  if(li == NULL || (*li) == NULL)
    return 0;
  Elem *no = *li;
  //percorre o no auxiliar do incio ao final da lista
  for(; no != NULL; no = no->prox){
    //printa na tela a letra e a sua frequencia
    printf("Letra:'%c' | Frequencia: %d\n", no->caractere, no->frequencia);
  }
  return 1;
}

//Como a lista criada anteriormente não está ordenada, e precisaremos ordenar ela sempre, esta função ordena a lista.
//algoritmo de bubble sort
void ordena_lista(Lista* li){
  Elem *aux = *li, *troca;
  //variavel para guardar os elementos na hora da troca
  Elem *guarda = (Elem*) malloc(sizeof(Elem));
  while(aux != NULL){
    troca = aux->prox;
    while(troca != NULL){
      if(aux->frequencia > troca->frequencia){
        guarda->caractere = aux->caractere;
        guarda->frequencia = aux->frequencia;
        guarda->esq = aux->esq;
        guarda->dir = aux->dir;
        aux->caractere = troca->caractere;
        aux->frequencia = troca->frequencia;
        aux->esq = troca->esq;
        aux->dir = troca->dir;
        troca->caractere = guarda->caractere;
        troca->frequencia = guarda->frequencia;
        troca->esq = guarda->esq;
        troca->dir = guarda->dir;
      }
      troca = troca->prox;
    }
    aux = aux->prox;
  }
  free(guarda);
}

//Função que funciona para impressão do bitmap de um determinado Byte
void printBits(unsigned char valor){
  unsigned char i;
  unsigned mascara = (1<<7);
  for(i = 1; i <= 8; i++){
    putchar(valor & mascara? '1':'0');
    valor <<= 1;
  }
  //putchar('\n');
}

//função para criação da árvore de Huffman
void Huffman(Lista *lista){
  ordena_lista(lista); //antes de tudo ordena a lista recebida
  Elem *atual = (*lista); //recebe o primeiro elemento da lista = menor elemento
  Elem *prox = atual ->prox; //recebe o segundo elemento da lista = segundo menor elemento
  Elem *novo_no; //nó para criação da junção entre os dois outros nós
  //enquanto não chegar no ultimo no
  while(prox != NULL){
    //aloca a memória para o novo no
    novo_no = (Elem*) malloc(sizeof(Elem));
    //a direita referencia o segundo menor nó da lista
    novo_no->dir = prox;
    //a esquerda referencia o menor nó da lista
    novo_no->esq = atual;
    //o prox apontará para o terceiro menor nó da lista
    novo_no->prox = prox->prox;
    //a frequencia do novo nó será a soma da frequencia dos dois menores
    novo_no->frequencia = (atual->frequencia) + (prox->frequencia);
    //atribui um caractere qualquer para o novo nó
    novo_no->caractere = '-';
    //A cabeça da lista agora aponta para o novo nó
    *lista = novo_no;
    //ordena a lista novamente, para sempre termos os dois menores no incio
    ordena_lista(lista);
    //o atual novamente recebe o menor nó da lista
    atual = novo_no;
    //o prox novamente recebe o segundo menor nó da lista
    prox = atual->prox;
  }
  /*obs: o algoritmo criado não retorna uma nova lista ou árvore, ela recebe uma lista encadeada, e a transforma
  em uma árvore de Huffman */
}



/* 
  Função recursiva para criação do código binário que representa cada caractere dependendo do caminho para chegar até ele
  percorre a árvore de Huffman, preenchendo o buffer = armazenamento do código
  obs: foi utiliza uma função boleana para confirmar se encontrou ou não a letra;
  parametros, inicialmente, se passa o primeiro nó da árvore = Raiz, o caractere procurado, o buffer de armazenamento dos passos, e o tamanho do buffer já armazenado.
*/
bool pegaCodigo(Elem *no, byte c, char *buffer, int tamanho){
  /*caso base:
      Caso tenha encontrado o nó que armazena o caractere procurado, verifica se é um nó folha para não ocorrer erros.
  */
  if(!(no->esq || no->dir) && no->caractere == c){
    buffer[tamanho] = '\0';
    return true;
  }
  else{
    bool encontrado = false;
    //Se existir um nó à esquerda
    if(no->esq){
      //Passo para à esquerda  = adiciona '1' do buffer = caminho percorrido
      buffer[tamanho] = '1';
      encontrado = pegaCodigo(no->esq, c, buffer, tamanho + 1);
    }
    if(!encontrado && no->dir){
      //Passo para à direita = adiciona '0' do buffer = caminho percorrido
      buffer[tamanho] = '0';
      encontrado = pegaCodigo(no->dir, c, buffer, tamanho + 1);
    }
    if(!encontrado){
      buffer[tamanho] = '\0';
    }
    return encontrado;
  }
}

/*
  Recebe como parâmetro o primeiro parâmetro da lista encadeada
  percorre ela até achar a letra correspondente.
  Retorna o endereço de memória do elemento correspondente ao caractere
*/
Elem* busca_tabela(Elem *no, byte letra){
  Elem *aux = no;
  while(aux != NULL){
    if(!(aux->esq || aux->dir) && aux->caractere == letra){
      return aux;
    }
    aux = aux->prox;
  }
  return NULL;
}

/*
  Função para contar quantos caracteres distintos existem no arquivo lido.
*/
int distinct_char(Lista* li){
  Elem *no = *li;
  int quant = 0;
  while(no != NULL){
    quant++;
    no = no->prox;
  }
  return quant;
}

/*
  Função de compressão do arquivo, onde ocorrem são chamadas todas as outras funções.
  Recebe como parâmetro o ponteiro de um arquivo à ser comprimido.
*/
void compress(FILE *arq){
  Lista *caracteres; //lista encadeada que armazenara os caracteres
  Lista *nova_lista; //nova lista que armazenará  a árvore de Huffman
  
  printf("------------------------------------------------------------------------------------------\n");
  printf("Analisando arquivo");
  printf(".");
  delay(5);
  printf(".");
  delay(5);
  printf(".\n");
  delay(5);

  //ambas as listas são criadas, com a contagem total de caracteres do arquivo original
  caracteres = conta_char(arq);
  nova_lista = conta_char(arq);
  //ordenamos apenas a lista de caracteres, pois a lista da arvore é orenada na função de Huffman
  ordena_lista(caracteres);
  //manda a lista encadeada criada para ser convertida na árvore de Huffman
  Huffman(nova_lista);

  
  printf("------------------------------------------------------------------------------------------\n");
  printf("Total de caracteres: %d\n", (*nova_lista)->frequencia); //o todo da arvore de Huffman representa a quantidade total de caracteres do texto
  printf("------------------------------------------------------------------------------------------\n");
  delay(3);

  //nessa parte criaremos a tabela de conversao, que são os codigos de cada caractere
  Elem *no = *caracteres;
  printf("------------------------------------Tabela de conversao------------------------------------\n");
  printf("**OBS: Para a esquerda = 1, direita = 0\n");
  while(no != NULL){
    //criação de um buffer armazenando os passos temporariamente
    char buffer[1024] = {0};
    byte aux = 0;
    unsigned tamanho = 0;
    //percorre todas os nós da lista encadeada e imprime a sua letra, frequencia, código binario
    printf("Letra: %c | Freq: %d | Codigo binario: ", no->caractere, no->frequencia);
    /*chama a função pega código, passando a raiz da árvore de Huffman, o caractere do nó atual da lista encadeada, o buffer de armazenamento e o 0 que é o incio do nosso buffer */
    pegaCodigo(*nova_lista, no->caractere, buffer, 0);
    
    // Laço que percorre o buffer
    for (char *i = buffer; *i; i++)
    {
      printf("%c", *i);
      //armazena na lista encadeada o codigo de cada caractere
      no->bitmap[tamanho] = buffer[tamanho];  
      tamanho++;
    }
    printf("\n");
    no = no->prox;
  }
  byte letra;

  /*
    Aqui, faremos o seguinte esquema, criaremos um arquivo temporario, chamado binario.txt
    Ele irá armazenar os caracteres 0 e 1, que serão os caracteres do texto original convertidos pelo codigo gerado
  */
  rewind(arq);
  FILE *temp = fopen("binario.txt", "w");
  delay(3);
  Elem *aux;
  printf("------------------------------------------------------------------------------------------\n");
  printf("Convertendo os caracteres do arquivo para o codigo binario...\n");
  delay(3);
  //printf("Codificacao binaria do texto: \n");
  //lê cada letra do arquivo original
  while((fread(&letra, sizeof(byte), 1, arq)) >= 1){
    //armazena em uma variavel auxiliar o endereço de memoria na tabela (lista encadeada) representando o caractere lido
    aux = busca_tabela((*caracteres), letra);
    //percorre o bitmap ou código gerado do caractere e coloca ele no arquivo binario.txt
    for (char *i = aux->bitmap; *i; i++){
      fprintf(temp, "%c", *i);
      //imprime na tela para demostrar o funcionamento
      //printf("%c", *i);
    }
  }
  printf("\n");
  rewind(arq);
  fclose(temp);
  

  /*
    Nessa parte faremos a conversão dos varios caracteres 0 e 1 no arquivo binario.txt
    Juntando de 8 em 8, formando um byte, e escrevendo no arquivo final, texto_comprimido.bin
  */
  printf("Juntando os numeros binarios e formando caracteres...\n");
  delay(3);
  //lê o arquivo temporario criado para auxiliar
  temp = fopen("binario.txt", "r");
  //cria o arquivo binario para armazenamento final
  FILE *compressed_file = fopen("texto_comprimido.bin", "w+b");
  //cria o novo bitmap para armazenar os 8 bits referentes;
  byte novo_bm = 0;
  //variavel auxiliar para contar os caracteres lidos
  /*
    Criação do cabecalho temporio, pq ainda não temos a quantidade de bits extras necessarios
  */
  Cabecalho cab;
  cab.caracteres_diferentes = distinct_char(caracteres);
  cab.caracteres_extras = 8;
  //escreve o cabecalho temporario
  fwrite(&cab, sizeof(Cabecalho), 1, compressed_file);
  no = *caracteres;
  Tabela tab;
  /*
    Foi criado uma nova struct tabela, contendo apenas um unsigned char e um bitmap[1024];
    porque? Porque na transcrição da tabela para uso como cabecalho, não é necessario o uso dos 
    ponteiros criados na struct Elem.
    Para economizar espaço utilizamos uma nova struct
  */
  while(no != NULL){
    tab.caract = no->caractere;
    strcpy(tab.bitmap, no->bitmap);
    /* 
    Percorre a tabela de caracteres, converte para o novo formato de struct, e escreve no arquivo
    */
    fwrite(&tab, sizeof(Tabela), 1, compressed_file);
    no = no->prox;
  }
  

  int quant = 0;
  printf("------------------------------------------------------------------------------------------\n");
  //printf("Conversao da codificacao binaria em mapa de bits: \n");
  while((fread(&letra, sizeof(byte), 1, temp)) >= 1){
    //desloca para à esquerda o bitmap
    novo_bm <<= 1;
    /*
      Aqui para converter o 0 ou 1 e colocar dentro do bitmap, fazemos o seguinte
      o caractere de um número - '0' = o número próprio.
      fazemos um OR com o inteiro disso, assim colocamos o 0 ou 1 dentro do bitmap.
    */
    novo_bm |= (int)(letra - '0');
    //como foi adicionado um caractere ao bitmap, aumentamos a quantidade cadastrada.
    quant++;
    //caso o bitmap esteja completo = tenha 8 bits registrados
    if(quant == 8){
      //grava o bitmap no novo arquivo binário
      fwrite(&novo_bm, sizeof(byte), 1, compressed_file);
      //zera o contador e o bitmap
      quant = 0;
      novo_bm = 0;
    }
  }
  //verifica se sobrou algo no bitmap, que não tenha um bitmap completo. E precisa ser escrito
  if(quant > 0){
    //desloca para a esquerda quantos caracteres faltaram, acrescentando 0 ao final
    novo_bm <<= 8 - (quant);
    fwrite(&novo_bm, sizeof(byte), 1, compressed_file);
  }
  /*
    Agora temos os caracteres extras cadastrados.
    Podemos colocar o novo cabecalho definitivo.
  */
  cab.caracteres_extras = 8 - quant;
  fseek(compressed_file, 0, SEEK_SET);
  fwrite(&cab, sizeof(Cabecalho), 1, compressed_file);

  


  //exclui o arquivo binario.txt, já que ele não nos é útil*/
  fclose(temp);
  remove("binario.txt");


  /*
    Aqui só exibimos para o usuario algumas coisas sobre o arquivo comprimido.
  */
  printf("\n");
  printf("------------------------------------------------------------------------------------------\n");
  int tam;
  delay(3);
  fseek(arq, 0, SEEK_END);
  fseek(compressed_file, 0, SEEK_END);
  printf("O arquivo possui %d caracteres_distintos\n", cab.caracteres_diferentes);
  printf("Foram necessários %d caracteres extras\n", cab.caracteres_extras);
  printf("O arquivo original possui %lu caracteres\n", ftell(arq)/sizeof(char));
  fseek(compressed_file, 0, SEEK_END);
  printf("O arquivo comprimido possui %lu caracteres\n", ftell(compressed_file)/sizeof(char));
  printf("A redução foi de %.2f%%\n",  (float) 100.0 - (100 * (ftell(compressed_file)/sizeof(char)) / (ftell(arq)/sizeof(char))));
  printf("------------------------------------------------------------------------------------------\n");
  fclose(compressed_file);
  
}


int demostracao_cab(){
  FILE *tst = fopen("texto_comprimido.bin", "r+b");
  Cabecalho cab;
  Tabela tab;
  delay(3);
  fread(&cab, sizeof(Cabecalho), 1, tst);
  printf("------------------------------------Demonstracao da leitura do cabecalho------------------------------------\n");
  printf("[Caracteres diferentes: %d  | Caracteres extras: %d]\n", cab.caracteres_diferentes, cab.caracteres_extras);
  for(int i = 0; i < 4; i++){
    fread(&tab, sizeof(Tabela), 1, tst);
    printf("[Char: %c  | Código: %s]\n", tab.caract, tab.bitmap);
  }
  printf("...\n");
  return  0;
}


int main(){
  FILE *arq;
  char nome_arq[100] = "texto.txt";
  printf("Comprimindo o arquivo texto.txt\n");
  
  arq = fopen(nome_arq, "r");
  if(arq == NULL){
    printf("Arquivo invalido!\n");
    exit(1);
  }
  compress(arq);
  demostracao_cab();
  fclose(arq);
}
