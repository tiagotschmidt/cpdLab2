// Trabalho Laboratório 2 - Classificação e Pesquisa de Dados - Gabriel Castelo Branco Gomes e Tiago Torres Schmidt.
#include <stdio.h>//Bibliotecas utilizadas no projeto.
#include <time.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_ITEMS 1000000//Constantes utilizadas no projeto.
#define MAX_CHAR 10
#define DEFAULT_INPUT "entrada1.txt"
#define DEFAULT_OUTPUT1 "stats-mediana-hoare.txt"
#define DEFAULT_OUTPUT2 "stats-mediana-lomuto.txt"
#define DEFAULT_OUTPUT3 "stats-aleatorio-hoare.txt"
#define DEFAULT_OUTPUT4 "stats-aleatorio-lomuto.txt"

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

FILE* initializeFileR(FILE* input, char* name){
  if((input = fopen(name,"r")) == NULL){//Tenta abrir o arquivo de entrada,
    printf("Erro ao abrir arquivo %s \n",name);//Caso de falha.
  }
  return input;
}

FILE* initializeFileW(FILE* input, char* name){
  if((input = fopen(name,"w")) == NULL){//Tenta abrir o arquivo de entrada,
    printf("Erro ao abrir arquivo %s \n",name);//Caso de falha.
  }
  return input;
}

void swap(int* a,int *b){
  int buffer;

  buffer = *a;
  *a = *b;
  *b = buffer;
}

int qSLMPartition(int array[], int firstIndex, int lastIndex){
  int mid, pivot;
  int i,j;

  mid = (firstIndex + lastIndex)/2;

  if(array[mid] < array[firstIndex]){
    swap(&array[mid],&array[firstIndex]);
  }
  if(array[lastIndex] < array[firstIndex]){
    swap(&array[lastIndex],&array[firstIndex]);
  }
  if(array[mid] < array[lastIndex]){
    swap(&array[mid],&array[lastIndex]);
  }

  pivot = array[lastIndex];
  i = firstIndex - 1;

  /*printf("\nPivot:%d\n",pivot);
  prtArrayCLI(array,16);
  printf("\n");*/

  for(j=firstIndex; j < lastIndex;j++){
    if(array[j] <= pivot){
      i++;
      swap(&array[i],&array[j]);
    }
  }
  swap(&array[i+1],&array[lastIndex]);

  //prtArrayCLI(array,16);

  //puts("\n");

  return (i+1);
}

void quickSortLomutoMedian(int array[], int firstIndex, int lastIndex){
  int q;
  if(firstIndex < lastIndex){
    q = qSLMPartition(array, firstIndex, lastIndex);
    quickSortLomutoMedian(array,firstIndex,q-1);
    quickSortLomutoMedian(array,q+1,lastIndex);
  }
}

int qSLPartitionRandom(int array[], int firstIndex, int lastIndex){
  int randIndex,pivot;
  int i,j;

  srand(time(NULL));

  randIndex = firstIndex + rand() % (lastIndex+1 - firstIndex);

  swap(&array[randIndex],&array[lastIndex]);

  pivot = array[lastIndex];
  i = firstIndex - 1;

  /*printf("Pivot:%d\n",pivot);
  prtArrayCLI(array,16);
  printf("\n");*/

  for(j=firstIndex; j < lastIndex;j++){
    if(array[j] <= pivot){
      i++;
      swap(&array[i],&array[j]);
    }
  }
  swap(&array[i+1],&array[lastIndex]);

  //prtArrayCLI(array,16);

  //puts("\n");

  return (i+1);
}

void quickSortLomutoRandom(int array[], int firstIndex, int lastIndex){
  int q;
  if(firstIndex < lastIndex){
    q = qSLPartitionRandom(array, firstIndex, lastIndex);
    quickSortLomutoRandom(array,firstIndex,q-1);
    quickSortLomutoRandom(array,q+1,lastIndex);
  }
}

int qSHMPartition(int array[], int firstIndex, int lastIndex){
  int mid, pivot;
  int i,j;

  mid = (firstIndex + lastIndex)/2;

  //printf("Primeiro, ultimo e meio:%d %d %d\n",array[firstIndex],array[mid],array[lastIndex]);

  if(array[mid] > array[lastIndex]){
    swap(&array[mid],&array[lastIndex]);
  }
  if(array[lastIndex] < array[firstIndex]){
    swap(&array[lastIndex],&array[firstIndex]);
  }
  if(array[mid] > array[firstIndex]){
    swap(&array[mid],&array[lastIndex]);
  }

  pivot = array[firstIndex];
  i = firstIndex - 1;
  j = lastIndex;

  while(1){
    //printf("Pivot:%d %d %d\n",pivot, i, j);
    do{
      i++;
    }while(array[i]<pivot);
    do{
      j--;
    }while(array[j]>pivot);

    /*printf("I e J:%d e %d\n",i,j);
    prtArrayCLI(array,16);
    printf("\n");*/


    if(i >= j){
      return j;
    }
    swap(&array[i],&array[j]);
  }



  //prtArrayCLI(array,16);

  //puts("\n");
}

void quickSortHoareMedian(int array[], int firstIndex, int lastIndex){
  int q;
  if(firstIndex < lastIndex){
    /*printf("Primeiro e ultimo indice:%d %d\n",firstIndex,lastIndex);
    prtArrayCLI(array,16);
    printf("\n");*/
    q = qSHMPartition(array, firstIndex, lastIndex);
    quickSortHoareMedian(array,firstIndex,q);
    quickSortHoareMedian(array,q+1,lastIndex);
  }
}

int qSHPartitionRandom(int array[], int firstIndex, int lastIndex){
  int mid, pivot,randIndex;
  int i,j;

  srand(time(NULL));

  randIndex = firstIndex + rand() % (lastIndex+1 - firstIndex);

  swap(&array[randIndex],&array[firstIndex]);

  pivot = array[firstIndex];
  i = firstIndex - 1;
  j = lastIndex;

  while(1){
    //printf("Pivot:%d %d %d\n",pivot, i, j);
    do{
      i++;
    }while(array[i]<pivot);
    do{
      j--;
    }while(array[j]>pivot);

    /*printf("I e J:%d e %d\n",i,j);
    prtArrayCLI(array,16);
    printf("\n");*/


    if(i >= j){
      return j;
    }
    swap(&array[i],&array[j]);
  }
  //prtArrayCLI(array,16);

  //puts("\n");
}

void quickSortHoareRandom(int array[], int firstIndex, int lastIndex){
  int q;
  if(firstIndex < lastIndex){
    /*printf("Primeiro e ultimo indice:%d %d\n",firstIndex,lastIndex);
    prtArrayCLI(array,16);
    printf("\n");*/
    q = qSHPartitionRandom(array, firstIndex, lastIndex);
    quickSortHoareRandom(array,firstIndex,q);
    quickSortHoareRandom(array,q+1,lastIndex);
  }
}

int main(){//Função main. Executa os testes requisitados.
  setlocale(LC_ALL,"");
  int buffer[MAX_ITEMS];//Variáveis utilizadas nos testes.
  int bufferClone[MAX_ITEMS];//Buffer e BufferClone são os espaços de leitura dos vetores do .txt
  int nItems;//Quantifica quantos itens existem no array.
  int i,j,k;//Índices de uso geral.
  FILE* input;//Ponteiros para os arquivos.
  FILE* output1,*output2,*output3,*output4;
  char seqName[3][MAX_CHAR] = {"SHELL\n","KNUTH\n","CIURA\n"};
  char cName[MAX_CHAR];//Sistema para impressão da sequência atual.

  input = initializeFileR(input,DEFAULT_INPUT);
  output1 = initializeFileW(output1,DEFAULT_OUTPUT1);
  output2 = initializeFileW(output2,DEFAULT_OUTPUT2);
  output3 = initializeFileW(output3,DEFAULT_OUTPUT3);
  output4 = initializeFileW(output4,DEFAULT_OUTPUT4);

  while(feof(input)==0){//Enquanto não encontra o fim do arquivo de entrada.
    fscanf(input,"%d ",&nItems);//Resgata o número de itens no array.
    for(i=0;i<nItems;i++){//Para cada item no array, armazena um número lido.
      fscanf(input,"%d ",&buffer[i]);//Executa a leitura do .txt de entrada.
    }

    for(j=0;j<4;j++){//Para cada array lido do .txt, executa três variações do shell....
      for(k=0; k < MAX_ITEMS; k++) {//Copia o buffer para bufferClone.
        bufferClone[k] = buffer[k];
      }
      puts("Desorganizado:");
      prtArrayCLI(bufferClone,nItems);
      printf("\n");
      switch(j){//Varia entres os tipos de shell.
        case 0:
          quickSortLomutoMedian(bufferClone,0,nItems-1);
          puts("Organizado Lomuto - Mediana:");
          prtArrayCLI(bufferClone,nItems);
          break;
        case 1:
          quickSortLomutoRandom(bufferClone,0,nItems-1);
          puts("Organizado Lomuto - Aleatório:");
          prtArrayCLI(bufferClone,nItems);
          break;
        case 2:
          quickSortHoareMedian(bufferClone,0,nItems-1);
          puts("Organizado Hoare - Mediana:");
          prtArrayCLI(bufferClone,nItems);
          break;
        case 3:
          quickSortHoareMedian(bufferClone,0,nItems-1);
          puts("Organizado Hoare - Aleatório:");
          prtArrayCLI(bufferClone,nItems);
          break;
      }
      printf("\n");
    }
  }


  /*fclose(output);//Fecha os ponteiros de leitura.
  fclose(input);*/
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
