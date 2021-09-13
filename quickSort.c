// Trabalho Laboratório 2 - Classificação e Pesquisa de Dados - Gabriel Castelo Branco Gomes e Tiago Torres Schmidt.
#include <stdio.h>//Bibliotecas utilizadas no projeto.
#include <time.h>

#define MAX_ITEMS 1000000//Constantes utilizadas no projeto.
#define MAX_CHAR 10
#define DEFAULT_INPUT "entrada1.txt"
#define DEFAULT_OUTPUT1 "stats-mediana-hoare.txt"
#define DEFAULT_OUTPUT2 "stats-mediana-lomuto.txt"
#define DEFAULT_OUTPUT3 "stats-aleatorio-hoare.txt"
#define DEFAULT_OUTPUT4 "stats-aleat ́orio-lomuto.tx"

void prtArray(int array[], int vectorLength, FILE* output){//Função prtArray. Printa a Array informada dentro do arquivo apontado por *output.
  int i;
  for(i=0;i<vectorLength;i++){//Iteração básica pelo tamanho do Array.
    fprintf(output,"%d ",array[i]);
  }
}

void prtArrayCLI(int array[], int vectorLength){//Função prtArrayCLI. Printa a Array informada dentro do console. Utilizado em DEV.
  int i;
  for(i=0;i<vectorLength;i++){//Iteração básica pelo tamanho do Array.
    printf("%d ",array[i]);
  }
}

File initializeFileR(File* input, char* name){
  if((input = fopen(DEFAULT_INPUT1,"r")) == NULL){//Tenta abrir o arquivo de entrada,
    printf("Erro ao abrir arquivo %s \n",name);//Caso de falha.
    break;
  }
  return input;
}

File initializeFileW(File* input, char* name){
  if((input = fopen(DEFAULT_INPUT1,"w")) == NULL){//Tenta abrir o arquivo de entrada,
    printf("Erro ao abrir arquivo %s \n",name);//Caso de falha.
    break;
  }
  return input;
}

void swap(int* a,int *b){
  int buffer;

  buffer = *a;
  *a = *b
  *b = buffer;
}

void quickSortLomutoMedian(int array[], int firstIndex, int lastIndex){
  int q;
  if(firstIndex < lastIndex){
    q = qSLMPartition(array, firstIndex, lastIndex);
    quickSortLomutoMedian(array,firstIndex,q-1);
    quickSortLomutoMedian(array,q+1,lastIndex);
  }
}

int qSLMPartition(int array[], int firstIndex, int lastIndex){
  int mid, pivot;
  int x,i,j;

  mid = (array[firstIndex] + array[lastIndex])/2;

  if(array[mid] < array[firstIndex]){
    swap(array[mid],array[firstIndex]);
  }
  if(array[lastIndex] < array[firstIndex]){
    swap(array[lastIndex],array[firstIndex]);
  }
  if(array[lastIndex] < array[mid]){
    swap(array[mid],array[lastIndex]);
  }

  x = array[mid];
  i = firstIndex - 1;

  for(j=firstIndex; j < mid-1;j++){
    if(a[j] <= x){
      i = i+1;
      swap(a[i],a[j])
    }
  }
  swap(a[i+1],a[lastIndex]);

  return i+1;
}

int main(){//Função main. Executa os testes requisitados.
  int buffer[MAX_ITEMS];//Variáveis utilizadas nos testes.
  int bufferClone[MAX_ITEMS];//Buffer e BufferClone são os espaços de leitura dos vetores do .txt
  int nItems;//Quantifica quantos itens existem no array.
  int i,j,k;//Índices de uso geral.
  FILE* input;//Ponteiros para os arquivos.
  FILE* output1,output2,output3,output4;
  char seqName[3][MAX_CHAR] = {"SHELL\n","KNUTH\n","CIURA\n"};
  char cName[MAX_CHAR];//Sistema para impressão da sequência atual.

  input = initializeFileR(input,DEFAULT_INPUT);
  output1 = initializeFileR(input,DEFAULT_OUTPUT1);
  output2 = initializeFileR(input,DEFAULT_OUTPUT2);
  output3 = initializeFileR(input,DEFAULT_OUTPUT3);
  output4 = initializeFileR(input,DEFAULT_OUTPUT4);

  while(feof(input)==0){//Enquanto não encontra o fim do arquivo de entrada.
    fscanf(input,"%d ",&nItems);//Resgata o número de itens no array.
    for(i=0;i<nItems;i++){//Para cada item no array, armazena um número lido.
      fscanf(input,"%d ",&buffer[i]);//Executa a leitura do .txt de entrada.
    }
    for(j=0;j<4;j++){//Para cada array lido do .txt, executa três variações do shell....
      for(k=0; k < MAX_ITEMS; k++) {//Copia o buffer para bufferClone.
        bufferClone[k] = buffer[k];
      }
      switch(j){//Varia entres os tipos de shell.
        case 0:
          shellSortBASE2T(bufferClone, nItems, output);
          break;
        case 1:
          shellSortKNUTHT(bufferClone, nItems, output);
          break;
        case 2:
          shellSortCIURAT(bufferClone, nItems, output);
          break;
        case 3:
          shellSortCIURAT(bufferClone, nItems, output);
          break;
      }
    }
  }

  fclose(output);//Fecha os ponteiros de leitura.
  fclose(input);
  return 0;
}


/*
void shellSortBASE2(int array[], int vectorLength, FILE* output){//Implementação do algoritmo shellSort, com base nos INCREMENTOS de base 2.
  int i,j,k,tmp;

  for(i=vectorLength/2;i>0;i=i/2){//Incremento atual.
    for(j=i;j<vectorLength;j++){//Percorre cada item de cada grupo formado pelo incremento.
      for(k=j-i;k>=0;k=k-1){//Percorre todos os grupos formados pelo incremento.
        if(array[k+i]>=array[k]){//Se o elemento já estiver ordenado, para.
          break;
        }else{//Se não:Executa troca,
          tmp = array[k];
          array[k] = array[k+i];
          array[k+i] = tmp;
        }
      }
    }
    prtArray(array,vectorLength,output);
    fprintf(output,"INCR=%d\n",i);
  }
}

void shellSortKNUTH(int array[], int vectorLength, FILE* output){//Implementação do algoritmo shellSort, com base nos INCREMENTOS de KNUTH.
  int i,j,k,tmp,initI;

  initI = 1;
  while((initI * 3 + 1) < vectorLength){//Definição do primeiro INCREMENTO utilizado, segundo a base de KNUTH.
    initI = initI * 3 + 1;
  }

  for(i=initI;i>0;i=i/3){//Incremento atual.
    for(j=i;j<vectorLength;j++){//Percorre cada item de cada grupo formado pelo incremento.
      for(k=j-i;k>=0;k=k-1){//Percorre todos os grupos formados pelo incremento.
        if(array[k+i]>=array[k]){//Se o elemento já estiver ordenado, para.
          break;
        }else{//Se não:Executa troca,
          tmp = array[k];
          array[k] = array[k+i];
          array[k+i] = tmp;
        }
      }
    }
    prtArray(array,vectorLength,output);
    fprintf(output,"INCR=%d\n",i);
  }
}

void shellSortCIURA(int array[], int vectorLength, FILE* output){//Implementação do algoritmo shellSort, com base nos INCREMENTOS de CIURA.
  int i,j,k,tmp,initI;
  int ciuraBASE[] = { 1,4,10,23,57,132,301,701,1577,3548,7983,17961,40412,90927,204585,460316};//Base de CIURA.
  int currentCiura;

  initI=0;
  while(vectorLength > ciuraBASE[initI+1]){//Define o incremento inicial, baseado na base de CIURA.
    initI++;
  }

  while(initI>=0){//Índice de incremento, roda até chegar ao 0.
    i = ciuraBASE[initI];//Incremento atual.
    for(j=i;j<vectorLength;j++){//Percorre cada item de cada grupo formado pelo incremento.
      for(k=j-i;k>=0;k=k-1){//Percorre todos os grupos formados pelo incremento.
        if(array[k+i]>=array[k]){//Se o elemento já estiver ordenado, para.
          break;
        }else{//Se não:Executa troca,
          tmp = array[k];
          array[k] = array[k+i];
          array[k+i] = tmp;
        }
      }
    }
    prtArray(array,vectorLength,output);
    fprintf(output,"INCR=%d\n",i);
    initI--;//Reduz o índice de Incremento.
  }
}

void shellSortBASE2T(int array[], int vectorLength, FILE* output){//Implementação do algoritmo shellSort, com base nos INCREMENTOS de base 2.
  int i,j,k,tmp;
  clock_t t;
  double cTime;

  t = clock();

  for(i=vectorLength/2;i>0;i=i/2){//Incremento atual.
    for(j=i;j<vectorLength;j++){//Percorre cada item de cada grupo formado pelo incremento.
      for(k=j-i;k>=0;k=k-1){//Percorre todos os grupos formados pelo incremento.
        if(array[k+i]>=array[k]){//Se o elemento já estiver ordenado, para.
          break;
        }else{//Se não:Executa troca,
          tmp = array[k];
          array[k] = array[k+i];
          array[k+i] = tmp;
        }
      }
    }
  }

  t = clock() - t;
  cTime = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
  fprintf(output,"SHELL,%d,%f\n",vectorLength,cTime);void shellSortBASE2(int array[], int vectorLength, FILE* output){//Implementação do algoritmo shellSort, com base nos INCREMENTOS de base 2.
  int i,j,k,tmp;

  for(i=vectorLength/2;i>0;i=i/2){//Incremento atual.
    for(j=i;j<vectorLength;j++){//Percorre cada item de cada grupo formado pelo incremento.
      for(k=j-i;k>=0;k=k-1){//Percorre todos os grupos formados pelo incremento.
        if(array[k+i]>=array[k]){//Se o elemento já estiver ordenado, para.
          break;
        }else{//Se não:Executa troca,
          tmp = array[k];
          array[k] = array[k+i];
          array[k+i] = tmp;
        }
      }
    }
    prtArray(array,vectorLength,output);
    fprintf(output,"INCR=%d\n",i);
  }
}

void shellSortKNUTH(int array[], int vectorLength, FILE* output){//Implementação do algoritmo shellSort, com base nos INCREMENTOS de KNUTH.
  int i,j,k,tmp,initI;

  initI = 1;
  while((initI * 3 + 1) < vectorLength){//Definição do primeiro INCREMENTO utilizado, segundo a base de KNUTH.
    initI = initI * 3 + 1;
  }

  for(i=initI;i>0;i=i/3){//Incremento atual.
    for(j=i;j<vectorLength;j++){//Percorre cada item de cada grupo formado pelo incremento.
      for(k=j-i;k>=0;k=k-1){//Percorre todos os grupos formados pelo incremento.
        if(array[k+i]>=array[k]){//Se o elemento já estiver ordenado, para.
          break;
        }else{//Se não:Executa troca,
          tmp = array[k];
          array[k] = array[k+i];
          array[k+i] = tmp;
        }
      }
    }
    prtArray(array,vectorLength,output);
    fprintf(output,"INCR=%d\n",i);
  }
}

void shellSortCIURA(int array[], int vectorLength, FILE* output){//Implementação do algoritmo shellSort, com base nos INCREMENTOS de CIURA.
  int i,j,k,tmp,initI;
  int ciuraBASE[] = { 1,4,10,23,57,132,301,701,1577,3548,7983,17961,40412,90927,204585,460316};//Base de CIURA.
  int currentCiura;

  initI=0;
  while(vectorLength > ciuraBASE[initI+1]){//Define o incremento inicial, baseado na base de CIURA.
    initI++;
  }

  while(initI>=0){//Índice de incremento, roda até chegar ao 0.
    i = ciuraBASE[initI];//Incremento atual.
    for(j=i;j<vectorLength;j++){//Percorre cada item de cada grupo formado pelo incremento.
      for(k=j-i;k>=0;k=k-1){//Percorre todos os grupos formados pelo incremento.
        if(array[k+i]>=array[k]){//Se o elemento já estiver ordenado, para.
          break;
        }else{//Se não:Executa troca,
          tmp = array[k];
          array[k] = array[k+i];
          array[k+i] = tmp;
        }
      }
    }
    prtArray(array,vectorLength,output);
    fprintf(output,"INCR=%d\n",i);
    initI--;//Reduz o índice de Incremento.
  }
}

void shellSortBASE2T(int array[], int vectorLength, FILE* output){//Implementação do algoritmo shellSort, com base nos INCREMENTOS de base 2.
  int i,j,k,tmp;
  clock_t t;
  double cTime;

  t = clock();

  for(i=vectorLength/2;i>0;i=i/2){//Incremento atual.
    for(j=i;j<vectorLength;j++){//Percorre cada item de cada grupo formado pelo incremento.
      for(k=j-i;k>=0;k=k-1){//Percorre todos os grupos formados pelo incremento.
        if(array[k+i]>=array[k]){//Se o elemento já estiver ordenado, para.
          break;
        }else{//Se não:Executa troca,
          tmp = array[k];
          array[k] = array[k+i];
          array[k+i] = tmp;
        }
      }
    }
  }

  t = clock() - t;
  cTime = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
  fprintf(output,"SHELL,%d,%f\n",vectorLength,cTime);
}

void shellSortKNUTHT(int array[], int vectorLength, FILE* output){//Implementação do algoritmo shellSort, com base nos INCREMENTOS de KNUTH.
  int i,j,k,tmp,initI;
  clock_t t;
  double cTime;

  t = clock();

  initI = 1;
  while((initI * 3 + 1) < vectorLength){//Definição do primeiro INCREMENTO utilizado, segundo a base de KNUTH.
    initI = initI * 3 + 1;
  }

  for(i=initI;i>0;i=i/3){//Incremento atual.
    for(j=i;j<vectorLength;j++){//Percorre cada item de cada grupo formado pelo incremento.
      for(k=j-i;k>=0;k=k-1){//Percorre todos os grupos formados pelo incremento.
        if(array[k+i]>=array[k]){//Se o elemento já estiver ordenado, para.
          break;
        }else{//Se não:Executa troca,
          tmp = array[k];
          array[k] = array[k+i];
          array[k+i] = tmp;
        }
      }
    }
  }

  t = clock() - t;
  cTime = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
  fprintf(output,"KNUTH,%d,%f\n",vectorLength,cTime);
}

void shellSortCIURAT(int array[], int vectorLength, FILE* output){//Implementação do algoritmo shellSort, com base nos INCREMENTOS de CIURA.
  int i,j,k,tmp,initI;
  int ciuraBASE[] = { 1,4,10,23,57,132,301,701,1577,3548,7983,17961,40412,90927,204585,460316};//Base de CIURA.
  int currentCiura;
  clock_t t;
  double cTime;

  t = clock();

  initI=0;
  while(vectorLength > ciuraBASE[initI+1]){//Define o incremento inicial, baseado na base de CIURA.
    initI++;
  }

  while(initI>=0){//Índice de incremento, roda até chegar ao 0.
    i = ciuraBASE[initI];//Incremento atual.
    for(j=i;j<vectorLength;j++){//Percorre cada item de cada grupo formado pelo incremento.
      for(k=j-i;k>=0;k=k-1){//Percorre todos os grupos formados pelo incremento.
        if(array[k+i]>=array[k]){//Se o elemento já estiver ordenado, para.
          break;
        }else{//Se não:Executa troca,
          tmp = array[k];
          array[k] = array[k+i];
          array[k+i] = tmp;
        }
      }
    }
    initI--;//Reduz o índice de Incremento.
  }

  t = clock() - t;
  cTime = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
  fprintf(output,"CIURA,%d,%f\n",vectorLength,cTime);
}
}

void shellSortKNUTHT(int array[], int vectorLength, FILE* output){//Implementação do algoritmo shellSort, com base nos INCREMENTOS de KNUTH.
  int i,j,k,tmp,initI;
  clock_t t;
  double cTime;

  t = clock();

  initI = 1;
  while((initI * 3 + 1) < vectorLength){//Definição do primeiro INCREMENTO utilizado, segundo a base de KNUTH.
    initI = initI * 3 + 1;
  }

  for(i=initI;i>0;i=i/3){//Incremento atual.
    for(j=i;j<vectorLength;j++){//Percorre cada item de cada grupo formado pelo incremento.
      for(k=j-i;k>=0;k=k-1){//Percorre todos os grupos formados pelo incremento.
        if(array[k+i]>=array[k]){//Se o elemento já estiver ordenado, para.
          break;
        }else{//Se não:Executa troca,
          tmp = array[k];
          array[k] = array[k+i];
          array[k+i] = tmp;
        }
      }
    }
  }

  t = clock() - t;
  cTime = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
  fprintf(output,"KNUTH,%d,%f\n",vectorLength,cTime);
}

void shellSortCIURAT(int array[], int vectorLength, FILE* output){//Implementação do algoritmo shellSort, com base nos INCREMENTOS de CIURA.
  int i,j,k,tmp,initI;
  int ciuraBASE[] = { 1,4,10,23,57,132,301,701,1577,3548,7983,17961,40412,90927,204585,460316};//Base de CIURA.
  int currentCiura;
  clock_t t;
  double cTime;

  t = clock();

  initI=0;
  while(vectorLength > ciuraBASE[initI+1]){//Define o incremento inicial, baseado na base de CIURA.
    initI++;
  }

  while(initI>=0){//Índice de incremento, roda até chegar ao 0.
    i = ciuraBASE[initI];//Incremento atual.
    for(j=i;j<vectorLength;j++){//Percorre cada item de cada grupo formado pelo incremento.
      for(k=j-i;k>=0;k=k-1){//Percorre todos os grupos formados pelo incremento.
        if(array[k+i]>=array[k]){//Se o elemento já estiver ordenado, para.
          break;
        }else{//Se não:Executa troca,
          tmp = array[k];
          array[k] = array[k+i];
          array[k+i] = tmp;
        }
      }
    }
    initI--;//Reduz o índice de Incremento.
  }

  t = clock() - t;
  cTime = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
  fprintf(output,"CIURA,%d,%f\n",vectorLength,cTime);
}
*/
