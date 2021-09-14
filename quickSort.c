// Trabalho Laboratório 2 - Classificação e Pesquisa de Dados - Gabriel Castelo Branco Gomes e Tiago Torres Schmidt.
#include <stdio.h>//Bibliotecas utilizadas no projeto.
#include <time.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_ITEMS 1000000//Constantes utilizadas no projeto.
#define DEFAULT_INPUT "entrada-quicksort.txt"
#define DEFAULT_OUTPUT1 "stats-mediana-hoare.txt"
#define DEFAULT_OUTPUT2 "stats-mediana-lomuto.txt"
#define DEFAULT_OUTPUT3 "stats-aleatorio-hoare.txt"
#define DEFAULT_OUTPUT4 "stats-aleatorio-lomuto.txt"

void prtInfo(int vectorLength, int swaps, int recursions, float time, FILE* output){//Função prtInfo. Printa informações requisitadas dentro do arquivo apontado por *output.
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

FILE* initializeFileR(FILE* input, char* name){//Função initializeFileR. Inicializa o ponteiro de leitura FILE. Em caso de erro, informa.
  if((input = fopen(name,"r")) == NULL){//Tenta abrir o arquivo de entrada,
    printf("Erro ao abrir arquivo %s \n",name);//Caso de falha.
  }
  return input;
}

FILE* initializeFileW(FILE* input, char* name){//Função initializeFileW. Inicializa o ponteiro de escrita FILE. Em caso de erro, informa.
  if((input = fopen(name,"w")) == NULL){//Tenta abrir o arquivo de saída,
    printf("Erro ao abrir arquivo %s \n",name);//Caso de falha.
  }
  return input;
}

void swap(int* a,int *b){//Função swap. Executa a troca de lugar de dois elementos do tipo int. Adaptado para elemento em vetor.
  int buffer;

  buffer = *a;
  *a = *b;
  *b = buffer;
}

int qSLMPartition(int array[], int firstIndex, int lastIndex,int *swaps){//Função qSLMPartition. Particionador da implementação Q.S Lomuto - Três Medianas.
  int mid, pivot;//Variáveis utilizadas na execução do particionador.
  int i,j;

  mid = (firstIndex + lastIndex)/2;//Define o índice do meio do array.

  if(array[mid] < array[firstIndex]){//Aqui estamos organizando os três itens: Primeiro elemento, elemento do meio e elemento final.
    swap(&array[mid],&array[firstIndex]);//O objetivo final é deixar, em ordem: O menor elemento(primeira posição);O maior elemento(posição média);0 elemento mediano(ultima posição=particionador);
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

  pivot = array[lastIndex];//Define o valor do particionardo:pivot.
  i = firstIndex - 1;//Define variável I, usada no for abaixo.

  for(j=firstIndex; j < lastIndex;j++){//Para j começando com o primeiro elemento, até o último elemento.
    if(array[j] <= pivot){//Se o elemento atual for menor / igual ao pivot.
      i++;//Aumenta o índice I.
      swap(&array[i],&array[j]);//Troca o elemento em I, com o elemento em J. Basicamente, estamos decantando o menores elementos do vetor para o início.
      *swaps = *swaps + 1;
    }
  }
  swap(&array[i+1],&array[lastIndex]);//Coloca o particionador na parte definitiva.
  *swaps = *swaps + 1;

  return (i+1);//Retorna o índice do particionador.
}

void quickSortLomutoMedian(int array[], int firstIndex, int lastIndex,int *swaps, int *recursions){//Função quickSortLomutoMedian. Q.S Lomuto - Três Medianas.
  int q;//Índice q.
  *recursions = *recursions + 1;
  if(firstIndex < lastIndex){//Se o primeiro índice for menor que o último, executa: (aqui temos uma condição de parada recursiva implícita. Leia-se, caso contrário: para recursividade)
    q = qSLMPartition(array, firstIndex, lastIndex,swaps);//Define o índice do particionador, além de particionar o vetor atual.
    quickSortLomutoMedian(array,firstIndex,q-1,swaps,recursions);//Recursividade dos menores que o pivot.
    quickSortLomutoMedian(array,q+1,lastIndex,swaps,recursions);//Recursividade dos maiores que o pivot.
  }
}

int qSLPartitionRandom(int array[], int firstIndex, int lastIndex,int *swaps){//Função qSLPartitionRandom. Particionador da implementação Q.S Lomuto - Aleatório.
  int randIndex,pivot;//Variáveis utilizadas na execução do particionador.
  int i,j;

  srand(time(NULL));

  randIndex = firstIndex + rand() % (lastIndex+1 - firstIndex);//Define o índice do particionador do array.

  swap(&array[randIndex],&array[lastIndex]);//Coloca o particionador no final.
  *swaps = *swaps + 1;

  pivot = array[lastIndex];//Define o valor do particionardo:pivot.
  i = firstIndex - 1;//Define variável I, usada no for abaixo.

  for(j=firstIndex; j < lastIndex;j++){//Para j começando com o primeiro elemento, até o último elemento.
    if(array[j] <= pivot){//Se o elemento atual for menor / igual ao pivot.
      i++;//Aumenta o índice I.
      swap(&array[i],&array[j]);//Troca o elemento em I, com o elemento em J. Basicamente, estamos decantando o menores elementos do vetor para o início.
      *swaps = *swaps + 1;
    }
  }
  swap(&array[i+1],&array[lastIndex]);//Coloca o particionador na parte definitiva.
  *swaps = *swaps + 1;

  return (i+1);//Retorna o índice do particionador.
}

void quickSortLomutoRandom(int array[], int firstIndex, int lastIndex,int *swaps,int *recursions){//Função quickSortLomutoRandom. Q.S Lomuto - Aleatório.
  int q;//Índice q.
  *recursions = *recursions + 1;
  if(firstIndex < lastIndex){//Se o primeiro índice for menor que o último, executa: (aqui temos uma condição de parada recursiva implícita. Leia-se, caso contrário: para recursividade)
    q = qSLPartitionRandom(array, firstIndex, lastIndex,swaps);//Define o índice do particionador, além de particionar o vetor atual.
    quickSortLomutoRandom(array,firstIndex,q-1,swaps,recursions);//Recursividade dos menores que o pivot.
    quickSortLomutoRandom(array,q+1,lastIndex,swaps,recursions);//Recursividade dos maiores que o pivot.
  }
}

int qSHMPartition(int array[], int firstIndex, int lastIndex,int *swaps){//Função qSHMPartition. Particionador da implementação Q.S Hoare - Três medianas.
  int mid, pivot;//Variáveis utilizadas na execução do particionador.
  int i,j;

  mid = (firstIndex + lastIndex)/2;//Define o índice do meio do array.

  if(array[mid] > array[lastIndex]){//Aqui estamos organizando os três itens: Primeiro elemento, elemento do meio e elemento final.
    swap(&array[mid],&array[lastIndex]);//O objetivo final é deixar, em ordem: O menor elemento(primeira posição);O maior elemento(posição média);0 elemento mediano(ultima posição=particionador);
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

  pivot = array[firstIndex];//Define o valor do particionardo:pivot.
  i = firstIndex - 1;//Define variável I, usada abaixo.
  j = lastIndex  + 1;//Define variável J, usada abaixo.

  while(1){//Loop infinito.
    do{//Aumenta o índice I, até que o elemento atual for maior ou igual ao pivo.
      i++;
    }while(array[i]<pivot);
    do{//Diminui o índice J, até que o elemento atual for menor ou igual ao pivo.
      j--;
    }while(array[j]>pivot);

    if(i >= j){//Se I for maior ou igual ao J, estamos com o particionador no lugar certo.
      return j;
    }
    swap(&array[i],&array[j]);//Se não, realizamos uma troca.
    *swaps = *swaps + 1;
  }
}

void quickSortHoareMedian(int array[], int firstIndex, int lastIndex,int *swaps,int *recursions){//Função quickSortHoareMedian. Q.S Hoare - Três Medianas.
  int q;
  *recursions = *recursions + 1;
  if(firstIndex < lastIndex){//Se o primeiro índice for menor que o último, executa: (aqui temos uma condição de parada recursiva implícita. Leia-se, caso contrário: para recursividade)
    q = qSHMPartition(array, firstIndex, lastIndex,swaps);//Define o índice do particionador, além de particionar o vetor atual.
    quickSortHoareMedian(array,firstIndex,q,swaps,recursions);//Recursividade dos menores que o pivot.
    quickSortHoareMedian(array,q+1,lastIndex,swaps,recursions);//Recursividade dos maiores que o pivot.
  }
}

int qSHPartitionRandom(int array[], int firstIndex, int lastIndex,int *swaps){//Função qSHPartitionRandom. Particionador da implementação Q.S Hoare - Aleatório.
  int mid, pivot,randIndex;//Variáveis utilizadas na execução do particionador.
  int i,j;

  srand(time(NULL));

  randIndex = firstIndex + rand() % (lastIndex+1 - firstIndex);//Define o índice do particionador do array.

  swap(&array[randIndex],&array[firstIndex]);//Coloca o particionador no final.
  *swaps = *swaps + 1;

  pivot = array[firstIndex];//Define o valor do particionardo:pivot.
  i = firstIndex - 1;//Define variável I, usada abaixo.
  j = lastIndex  + 1;//Define variável J, usada abaixo.

  while(1){//Loop infinito.
    do{//Aumenta o índice I, até que o elemento atual for maior ou igual ao pivo.
      i++;
    }while(array[i]<pivot);
    do{//Diminui o índice J, até que o elemento atual for menor ou igual ao pivo.
      j--;
    }while(array[j]>pivot);

    if(i >= j){//Se I for maior ou igual ao J, estamos com o particionador no lugar certo.
      return j;
    }
    swap(&array[i],&array[j]);//Se não, realizamos uma troca.
    *swaps = *swaps + 1;
  }
}

void quickSortHoareRandom(int array[], int firstIndex, int lastIndex,int *swaps,int *recursions){//Função quickSortHoareRandom. Q.S Hoare - Aleatório.
  int q;//Índice q.
  *recursions = *recursions + 1;
  if(firstIndex < lastIndex){//Se o primeiro índice for menor que o último, executa: (aqui temos uma condição de parada recursiva implícita. Leia-se, caso contrário: para recursividade)
    q = qSHPartitionRandom(array, firstIndex, lastIndex,swaps);//Define o índice do particionador, além de particionar o vetor atual.
    quickSortHoareRandom(array,firstIndex,q,swaps,recursions);//Recursividade dos menores que o pivot.
    quickSortHoareRandom(array,q+1,lastIndex,swaps,recursions);//Recursividade dos maiores que o pivot.
  }
}

int main(){//Função main. Executa os testes requisitados.
  setlocale(LC_ALL,"");//Ajusta as configurações de print para console. Usado em DEV.
  int buffer[MAX_ITEMS];//Variáveis utilizadas nos testes.
  int bufferClone[MAX_ITEMS];//Buffer e BufferClone são os espaços de leitura dos vetores do .txt
  int nItems;//Quantifica quantos itens existem no array.
  int i,j,k;//Índices de uso geral.
  int swaps, recursions;//Variáveis de contagem.
  FILE* input;//Ponteiros para os arquivos.
  FILE* output1,*output2,*output3,*output4;
  clock_t t;//Variáveis para controle de tempo.
  double cTime;

  input = initializeFileR(input,DEFAULT_INPUT);//Inicializa os arquivos .txt
  output1 = initializeFileW(output1,DEFAULT_OUTPUT1);
  output2 = initializeFileW(output2,DEFAULT_OUTPUT2);
  output3 = initializeFileW(output3,DEFAULT_OUTPUT3);
  output4 = initializeFileW(output4,DEFAULT_OUTPUT4);

  while(feof(input)==0){//Enquanto não encontra o fim do arquivo de entrada.
    fscanf(input,"%d ",&nItems);//Resgata o número de itens no array.
    for(i=0;i<nItems;i++){//Para cada item no array, armazena um número lido.
      fscanf(input,"%d ",&buffer[i]);//Executa a leitura do .txt de entrada.
    }

    for(j=0;j<4;j++){//Para cada array lido do .txt, executa as quatro variações do QuickSort.
      for(k=0; k < nItems; k++) {//Copia o buffer para bufferClone.
        bufferClone[k] = buffer[k];
      }
      swaps = 0;//Reseta variáveis de contagem.
      recursions = 0;

      switch(j){//Varia entres os tipos de QuickSort..
        case 0:
          t = clock();//Marca o início.
          quickSortLomutoMedian(bufferClone,0,nItems-1,&swaps,&recursions);//Executa o ordenamento.
          t = clock() - t;//Extrai o tempo total
          cTime = ((double)t)/CLOCKS_PER_SEC;//Cálculo do tempo decorrido.
          prtInfo(nItems,swaps,recursions,cTime,output2);//Printa as informações
          break;
        case 1:
          t = clock();//Marca o início
          quickSortLomutoRandom(bufferClone,0,nItems-1,&swaps,&recursions);//Executa o ordenamento.
          t = clock() - t;//Extrai o tempo total
          cTime = ((double)t)/CLOCKS_PER_SEC;//Cálculo do tempo decorrido.
          prtInfo(nItems,swaps,recursions,cTime,output4);//Printa as informações
          break;
        case 2:
          t = clock();//Marca o início
          quickSortHoareMedian(bufferClone,0,nItems-1,&swaps,&recursions);//Executa o ordenamento.
          t = clock() - t;//Extrai o tempo total
          cTime = ((double)t)/CLOCKS_PER_SEC;//Cálculo do tempo decorrido.
          prtInfo(nItems,swaps,recursions,cTime,output1);//Printa as informações
          break;
        case 3:
          t = clock();//Marca o início
          quickSortHoareRandom(bufferClone,0,nItems-1,&swaps,&recursions);//Executa o ordenamento.
          t = clock() - t;//Extrai o tempo total
          cTime = ((double)t)/CLOCKS_PER_SEC;//Cálculo do tempo decorrido.
          prtInfo(nItems,swaps,recursions,cTime,output3);//Printa as informações
          break;
      }
    }
  }


  fclose(output1);//Fecha os ponteiros de leitura e escrita..
  fclose(input);
  fclose(output2);
  fclose(output3);
  fclose(output4);
  return 0;
}
