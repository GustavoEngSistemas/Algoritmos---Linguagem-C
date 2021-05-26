/*Compressor orientado à caracteres.
O compressor deverá ser construído em camadas, baseando-se nas técnicas de mapa de bits e de meio byte.
Dado um arquivo texto fornecido pelo usuário, o programa deve, numa primeira camada, 
computar as frequências de cada caractere, tomando aquele mais frequente para a aplicação do compressor de mapa de bits. 
Em seguida, numa segunda camada, deve comprimir sequências numéricas. A melhor estratégia deve ser definida por você.*/


#include <stdio.h>
#include <string.h>

#define QUANT_LETRAS 95
//todos caracteres que são permitidos para leitura, o REPLIT SÓ ACEITA ESSES, no VS CODE aceita os 224 caracteres ** estamos utilizando a partir do caractere 32
//forma utilizada se for no REPLIT
unsigned char alfabeto[QUANT_LETRAS] = {' ', '!', '"', '#', '$', '%', '&', '\'',  '(', ')', '*', '+', ',', '-', '.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',  'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~'};

//forma utilizada em outro compilador
/*
#define QUANT_LETRAS 224
char alfabeto[QUANT_LETRAS] = {' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 
'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~', '⌂', 'Ç', 'ü', 'é', 'â', 'ä', 'à', 'å', 'ç', 'ê', 'ë', 'è', 'ï', 'î', 'ì', 'Ä', 'Å', 'É', 'æ', 'Æ', 'ô', 'ö', 'ò', 'û', 'ù', 'ÿ', 'Ö', 'Ü', 'ø', '£', 'Ø', '×', 'ƒ', 'á', 'í', 'ó', 'ú', 'ñ', 'Ñ', 'ª', 'º', '¿', '®', '¬', '½', '¼', '¡', '«', '»', '░', '▒', '▓', '│', '┤', 'Á', 'Â', 'À', '©', '╣', '║', '╗', '╝', '¢', '¥', '┐', '└', '┴', '┬', '├', '─', '┼', 'ã', 'Ã', '╚', '╔', '╩', '╦', '╠', '═', '╬', '¤', 'ð', 'Ð', 'Ê', 'Ë', 'È', 'ı', 'Í', 'Î', 'Ï', '┘', '┌', '█', '▄', '¦', 'Ì', '▀', 'Ó', 'ß', 'Ô', 'Ò', 'õ', 'Õ', 'µ', 'þ', 'Þ', 'Ú', 'Û', 'Ù', 'ý', 'Ý', '¯', '´', '­', '±', '‗', '¾', '¶', '§', '÷', '¸', '°', '¨', '·', '¹', '³', '²', '■'};*/


//definição do tipo Byte para ficar mais didático
typedef unsigned char byte;

//função para imprimir o mapa de bits de um char
void printBits(unsigned char valor){
  unsigned char i;
  unsigned mascara = (1<<7);
  for(i = 1; i <= 8; i++){
    putchar(valor & mascara? '1':'0');
    valor <<= 1;
  }
  putchar('\n');
}

//função para contar qual o caractere que mais se repete no texto
//retorna o caractere que mais se repete
char char_repet(FILE *arq){
  int quant[QUANT_LETRAS] = {0}, i, max[2];
  char letra;
  rewind(arq);
  while((letra = fgetc(arq)) != EOF){
    for(i = 0; i < QUANT_LETRAS; i++){
      if(letra == alfabeto[i]){
        quant[i]++;
      }
    }  
  }
  max[0] = quant[0];
  max[1] = 0;
  for(i = 1; i < QUANT_LETRAS; i++){
    if(quant[i] > max[0]){
      max[0] = quant[i];
      max[1] = i;
    }
  }
  rewind(arq);
  return alfabeto[max[1]];
}

//função para contar a quantidade de caracteres em um arquivo.
int quant_char(FILE *arq){
  int quant = 0;
  char letra;
  fseek(arq, 0, SEEK_END);
  quant = ftell(arq) / sizeof(char);
  rewind(arq);
  return quant;

}

//primeira camada de compressão utilizando mapa de bits
void compressao_char(FILE *arq, char letra){
  //deixei um caractere a mais para o \0
  char palavra[9];
  //variável auxiliar para controlar a execução
  int para = 0;
  
  rewind(arq);
  //cria o novo arquivo compactado
  FILE *comp = fopen("compactado.txt", "w");
  do{
    //cria um byte com o bitmap 0000 0000
    byte bitmap = 0; 
    int quant_letras = 0;
    int i;
    //lê 8 caracteres para formar um mapa de bit
    for(i = 0; i < 8; i++){
      palavra[i] = fgetc(arq);
      bitmap <<= 1;
      quant_letras++;
      if(palavra[i] == EOF){
        palavra[i] = '\0';
        para = 1;
        quant_letras--;
        break;
      }
      else{
        if(palavra[i] != letra){
          bitmap |= 1;
        }
      } 
    }
    //não chegamos ao final do arquivo.
    if(!para){
      //verifica se o bitmap = 1111 1111, caso seja, ele não tem a letra que estamos utilizando como base
      if(~bitmap != 0){
        //coloca o bitmap no arquivo
        fprintf(comp, "%c", bitmap);
        //tira a letra padrão e coloca as demais
        for(int j = 0; j < i; j++){
            if(palavra[j] != letra)
              fprintf(comp, "%c", palavra[j]);
        }
      }
      else{
          //como não tem a letra base, todas as letras serão deferentes, então podemos escrever a palavra toda e o bitmap
          fprintf(comp, "%c", bitmap);
          fprintf(comp, "%s", palavra);
        }
    }
    else{
      //chegamos ao final do arquivo
      //verifica se sobrou algo para escrever
      if(palavra[0] != EOF){
        fprintf(comp, "%c", bitmap);
        for(int j = 0; j < i; j++){
            if(palavra[j] != letra)
              fprintf(comp, "%c", palavra[j]);
        }
      }
    }
  }while(!para);
  fclose(comp);
  rewind(arq);
}

//segunda camada de compressão utilizando meio byte
void compressao_num(FILE *arq){
    char aux;
    int sequencia[16], i = 0;
    FILE *compact = fopen("compactado2.txt", "w");
    byte padrao = 0;
    padrao |= 16;
    padrao |= 1;
    //byte padrão será 00010001, que não é um caractere visivel
    while(fscanf(arq, "%c", &aux) != EOF){
        //verifica se o caractere é um número, está entre aspas pq o que estamos lendo sem caracteres 
        // de um arquivo de texto
        if(aux >= '0' && aux <= '9'){
            sequencia[i] = aux;
            i++;
            //verifica se completou uma sequencia de 16 caracteres (0 - 15), que é o máximo possível
            if(i == 15){
                //define um novo byte 0000 0000
                byte novo_byte = 0;
                
                //escreve o caractere padrão
                fwrite(&padrao, sizeof(byte), 1, compact);
                //faremos um OR com o 15, é será o número de caractere convertidos, já que esse if, é pra sequencia cheia
                novo_byte |= 15;
                //deslocando, o novo byte ficara, com os primeiro 4 bits sendo a quantidade;
                novo_byte <<= 4;
                //pegamos o primeiro valor da sequencia, pois ele dividirá o primeiro byte com a quant;
                //fazemos um AND com o 15, pois o mapa de bits dele é 00001111, assim, zeramos os primeiros 4 bits 
                sequencia[0] &= 15;
                //fazemos um OR para unir os 4 primeiros bits que são da quantidade registrada, e os 4 últimos que são do primeiro valor da sequencia
                novo_byte |= sequencia[0];
                //escrevemos o primeiro byte
                fwrite(&novo_byte, sizeof(byte), 1, compact);
                for(int j = 1; j < 15; j+= 2){
                  //faremos a mesma logica anterior, apenas agora pegamos os números de 2 em 2 e formamos um byte.
                  novo_byte = 0;
                  novo_byte |= sequencia[j];
                  novo_byte <<= 4;
                  sequencia[j+1] &= 15;
                  novo_byte |= sequencia[j+1];
                  fwrite(&novo_byte, sizeof(byte), 1, compact); 
                }
                //zeramos a sequencia armazeanda
                i = 0;
            }
        }
        //nesse caso o caractere lido não é um número
        else{
          //verificamos se na sequencia tem algum número para escrever
          //tem que ter pelo menos 5 para se convertido.
          if(i >= 5){
                //caso a quantidade de valores armazeandos seja par, acrescentamos um ao final para funcionar corretamente
                if(i % 2 == 0){
                    i++;
                    sequencia[i] = '0';
                }
                //utilizamos a mesma lógica de escrita anterior
                byte novo_byte = 0;
                byte byte_aux = 0;
                fwrite(&padrao, sizeof(byte), 1, compact);
                //a diferença está que agora a quantidade de números precisa ser referenciada
                novo_byte |= i;
                novo_byte <<= 4;
                sequencia[0] &= 15;
                novo_byte |= sequencia[0];
                fwrite(&novo_byte, sizeof(byte), 1, compact);
                for(int j = 1; j < i; j+= 2){
                    novo_byte = 0;
                    novo_byte |= sequencia[j];
                    novo_byte <<= 4;
                    sequencia[j+1] &= 15;
                    novo_byte |= sequencia[j+1];
                    fwrite(&novo_byte, sizeof(byte), 1, compact); 
                }
            }
            //se tiver números armazenados mas não forem pelo menos 5, não podemos comprensar eles 
            else if(i > 0){
                for(int j = 0; j < i; j++){
                    fwrite(&sequencia[j], sizeof(char), 1, compact);
                }
                

            }
            fwrite(&aux, sizeof(char), 1, compact);
            
            //zeramos os armazenados
            i = 0;
        }
    }
    //saimos do while
    //precisamos verificar novamente, pois, existe a possibilidade de lermos uma sequencia númerica, não atingir os 15
    //e chegarmos ao final do arquivo.
    if(i >= 5){
      if(i % 2 == 0){
          i++;
          sequencia[i] = '0';
      }
      byte novo_byte = 0;
      byte byte_aux = 0;
      fwrite(&padrao, sizeof(byte), 1, compact);
      novo_byte |= i;
      novo_byte <<= 4;
      sequencia[0] &= 15;
      novo_byte |= sequencia[0];
      fwrite(&novo_byte, sizeof(byte), 1, compact);
      for(int j = 1; j < i; j+= 2){
          novo_byte = 0;
          novo_byte |= sequencia[j];
          novo_byte <<= 4;
          sequencia[j+1] &= 15;
          novo_byte |= sequencia[j+1];
          fwrite(&novo_byte, sizeof(byte), 1, compact); 
      }
    }
    else if(i > 0){
      for(int j = 0; j < i; j++)
          fwrite(&sequencia[j], sizeof(char), 1, compact);
    }
    fclose(compact);
    
    rewind(arq);
}


void compressao_total(FILE *arq){
  char letra_mais;
  FILE *arq2, *arq3;
  letra_mais = char_repet(arq);
  printf("A letra mais repetida do arquivo é: '%c'\n", letra_mais);
  printf("O arquivo original tem: %d caracteres\n", quant_char(arq));
  compressao_char(arq, letra_mais);
  arq2 = fopen("compactado.txt", "r");
  printf("Após a primeira camada o arquivo tem: %d caracteres\n", quant_char(arq2));
  compressao_num(arq2);
  arq3 = fopen("compactado2.txt", "r");
  printf("Após a segunda camada o arquivo tem: %d caracteres\n", quant_char(arq3));
  fclose(arq2);
  fclose(arq3);
  remove("compactado.txt");
  rename("compactado2.txt", "texto_compactado.txt");
}

int main(void) {
  FILE *arq;
  arq = fopen("texto.txt", "r");
  if(arq != NULL){
    compressao_total(arq);
  }
  fclose(arq);
  return 0;
}
