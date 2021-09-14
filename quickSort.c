// Trabalho Laboratório 2 - Classificação e Pesquisa de Dados - Gabriel Castelo Branco Gomes e Tiago Torres Schmidt.
#include <stdio.h>//Bibliotecas utilizadas no projeto.
#include <time.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_ITEMS 1000000//Constantes utilizadas no projeto.
#define MAX_CHAR 10
#define DEFAULT_INPUT "entrada-quicksort.txt"
#define DEFAULT_OUTPUT1 "stats-mediana-hoare.txt"
#define DEFAULT_OUTPUT2 "stats-mediana-lomuto.txt"
#define DEFAULT_OUTPUT3 "stats-aleatorio-hoare.txt"
#define DEFAULT_OUTPUT4 "stats-aleatorio-lomuto.txt"

void prtInfo(int vectorLength, int swaps, int recursions, float time, FILE* output){//Função prtArray. Printa a Array informada dentro do arquivo apontado por *output.
  fprintf(output,"TAMANHO ENTRADA %d\n",vectorLength);
  fprintf(output,"SWAPS #%d\n",swaps);
  fprintf(output,"RECURSOES #%d\n",recursions);
  fprintf(output,"TEMPO #%f\n",time);
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

int qSLMPartition(int array[], int firstIndex, int lastIndex,int *swaps){
  int mid, pivot;
  int i,j;

  mid = (firstIndex + lastIndex)/2;

  if(array[mid] < array[firstIndex]){
    swap(&array[mid],&array[firstIndex]);
    *swaps = *swaps + 1;
  }
  if(array[lastIndex] < array[firstIndex]){
    swap(&array[lastIndex],&array[firstIndex]);
    *swaps = *swaps + 1;
  }
  if(array[mid] < array[lastIndex]){
    swap(&array[mid],&array[lastIndex]);
    *swaps = *swaps + 1;
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
      *swaps = *swaps + 1;
    }
  }
  swap(&array[i+1],&array[lastIndex]);
  *swaps = *swaps + 1;

  //prtArrayCLI(array,16);

  //puts("\n");

  return (i+1);
}

void quickSortLomutoMedian(int array[], int firstIndex, int lastIndex,int *swaps, int *recursions){
  int q;
  *recursions = *recursions + 1;
  if(firstIndex < lastIndex){
    q = qSLMPartition(array, firstIndex, lastIndex,swaps);
    quickSortLomutoMedian(array,firstIndex,q-1,swaps,recursions);
    quickSortLomutoMedian(array,q+1,lastIndex,swaps,recursions);
  }
}

int qSLPartitionRandom(int array[], int firstIndex, int lastIndex,int *swaps){
  int randIndex,pivot;
  int i,j;

  srand(time(NULL));

  randIndex = firstIndex + rand() % (lastIndex+1 - firstIndex);

  swap(&array[randIndex],&array[lastIndex]);
  *swaps = *swaps + 1;

  pivot = array[lastIndex];
  i = firstIndex - 1;

  /*printf("Pivot:%d\n",pivot);
  prtArrayCLI(array,16);
  printf("\n");*/

  for(j=firstIndex; j < lastIndex;j++){
    if(array[j] <= pivot){
      i++;
      swap(&array[i],&array[j]);
      *swaps = *swaps + 1;
    }
  }
  swap(&array[i+1],&array[lastIndex]);
  *swaps = *swaps + 1;

  //prtArrayCLI(array,16);

  //puts("\n");

  return (i+1);
}

void quickSortLomutoRandom(int array[], int firstIndex, int lastIndex,int *swaps,int *recursions){
  int q;
  *recursions = *recursions + 1;
  if(firstIndex < lastIndex){
    q = qSLPartitionRandom(array, firstIndex, lastIndex,swaps);
    quickSortLomutoRandom(array,firstIndex,q-1,swaps,recursions);
    quickSortLomutoRandom(array,q+1,lastIndex,swaps,recursions);
  }
}

int qSHMPartition(int array[], int firstIndex, int lastIndex,int *swaps){
  int mid, pivot;
  int i,j;

  mid = (firstIndex + lastIndex)/2;

  //printf("Primeiro, ultimo e meio:%d %d %d\n",array[firstIndex],array[mid],array[lastIndex]);

  if(array[mid] > array[lastIndex]){
    swap(&array[mid],&array[lastIndex]);
    *swaps = *swaps + 1;
  }
  if(array[lastIndex] < array[firstIndex]){
    swap(&array[lastIndex],&array[firstIndex]);
    *swaps = *swaps + 1;
  }
  if(array[mid] > array[firstIndex]){
    swap(&array[mid],&array[lastIndex]);
    *swaps = *swaps + 1;
  }

  pivot = array[firstIndex];
  i = firstIndex - 1;
  j = lastIndex  + 1;

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
    *swaps = *swaps + 1;
  }



  //prtArrayCLI(array,16);

  //puts("\n");
}

void quickSortHoareMedian(int array[], int firstIndex, int lastIndex,int *swaps,int *recursions){
  int q;
  *recursions = *recursions + 1;
  if(firstIndex < lastIndex){
    /*printf("Primeiro e ultimo indice:%d %d\n",firstIndex,lastIndex);
    prtArrayCLI(array,16);
    printf("\n");*/
    q = qSHMPartition(array, firstIndex, lastIndex,swaps);
    quickSortHoareMedian(array,firstIndex,q,swaps,recursions);
    quickSortHoareMedian(array,q+1,lastIndex,swaps,recursions);
  }
}

int qSHPartitionRandom(int array[], int firstIndex, int lastIndex,int *swaps){
  int mid, pivot,randIndex;
  int i,j;

  srand(time(NULL));

  randIndex = firstIndex + rand() % (lastIndex+1 - firstIndex);

  swap(&array[randIndex],&array[firstIndex]);
  *swaps = *swaps + 1;

  pivot = array[firstIndex];
  i = firstIndex - 1;
  j = lastIndex  + 1;

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
    *swaps = *swaps + 1;
  }
  //prtArrayCLI(array,16);

  //puts("\n");
}

void quickSortHoareRandom(int array[], int firstIndex, int lastIndex,int *swaps,int *recursions){
  int q;
  *recursions = *recursions + 1;
  if(firstIndex < lastIndex){
    /*printf("Primeiro e ultimo indice:%d %d\n",firstIndex,lastIndex);
    prtArrayCLI(array,16);
    printf("\n");*/
    q = qSHPartitionRandom(array, firstIndex, lastIndex,swaps);
    quickSortHoareRandom(array,firstIndex,q,swaps,recursions);
    quickSortHoareRandom(array,q+1,lastIndex,swaps,recursions);
  }
}

int main(){//Função main. Executa os testes requisitados.
  setlocale(LC_ALL,"");
  int buffer[MAX_ITEMS];//Variáveis utilizadas nos testes.
  int bufferClone[MAX_ITEMS];//Buffer e BufferClone são os espaços de leitura dos vetores do .txt
  int nItems;//Quantifica quantos itens existem no array.
  int i,j,k;//Índices de uso geral.
  int swaps, recursions;
  FILE* input;//Ponteiros para os arquivos.
  FILE* output1,*output2,*output3,*output4;
  char seqName[3][MAX_CHAR] = {"SHELL\n","KNUTH\n","CIURA\n"};
  char cName[MAX_CHAR];//Sistema para impressão da sequência atual.
  clock_t t;
  double cTime;

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
      for(k=0; k < nItems; k++) {//Copia o buffer para bufferClone.
        bufferClone[k] = buffer[k];
      }

      swaps = 0;
      recursions = 0;

      /*puts("Desorganizado:");
      prtArrayCLI(bufferClone,nItems);
      printf("\n");*/
      switch(j){//Varia entres os tipos de shell.
        case 0:
          t = clock();
          quickSortLomutoMedian(bufferClone,0,nItems-1,&swaps,&recursions);
          t = clock() - t;
          cTime = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
          //puts("Organizado Lomuto - Mediana:");
          //printf("%d %d",swaps,recursions);
          prtInfo(nItems,swaps,recursions,cTime,output2);
          break;
        case 1:
          t = clock();
          quickSortLomutoRandom(bufferClone,0,nItems-1,&swaps,&recursions);
          t = clock() - t;
          cTime = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
          //puts("Organizado Lomuto - Aleatório:");
          prtInfo(nItems,swaps,recursions,cTime,output4);
          break;
        case 2:
          t = clock();
          quickSortHoareMedian(bufferClone,0,nItems-1,&swaps,&recursions);
          t = clock() - t;
          cTime = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
          //puts("Organizado Hoare - Mediana:");
          prtInfo(nItems,swaps,recursions,cTime,output1);
          break;
        case 3:
          t = clock();
          quickSortHoareMedian(bufferClone,0,nItems-1,&swaps,&recursions);
          t = clock() - t;
          cTime = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
          //puts("Organizado Hoare - Aleatório:");
          prtInfo(nItems,swaps,recursions,cTime,output3);
          break;
      }
      //printf("\n");
    }
  }


  fclose(output1);//Fecha os ponteiros de leitura.
  fclose(input);
  fclose(output2);
  fclose(output3);
  fclose(output4);
  return 0;
}
