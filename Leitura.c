#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Leitura.h"
#include "Dijkstra.h"


//TODO: não precisa de um struct para isso aqui
struct dados {
  int N; // numero de vertices (1 a N)
  int M; // numero de arestas
  int S; // nó de origem
  int T; // nó de destino 
  int VeloInicial; //velocidade media inicial
  
  //TODO: trocar para double em todo o projeto
  float ** VetorArestas; //vetor que contém (vetice origem, vertice destino, distancia entre os nós)[3]
  
  int ** VetorTrafego; //vetor com informacoes do trafego ao longo da viagem(instante de tempo[0], aresta origem[1], aresta destino[2], velocidade media nova[3])
  int tamanhoVetorTrafego; // tamanho do vetor de trafego
};

//TODO: essa função tem que ser apagada antes de entregar o trabalho (debug)
void ImprimirDados(Dados * dados){

  // printf("%d %d %d %d %d\n", dados->N,dados->M,dados->S,dados->T,dados->VeloInicial);

  // for (int i = 0; i < dados->M; i ++){
  //   printf("%.0f %.0f %.2f \n",dados->VetorArestas[i][0],dados->VetorArestas[i][1],dados->VetorArestas[i][2]);
  // }

  // for (int i = 0; i < dados->tamanhoVetorTrafego; i ++){
  //   printf("%d %d %d %d\n",dados->VetorTrafego[i][0],dados->VetorTrafego[i][1],dados->VetorTrafego[i][2],dados->VetorTrafego[i][3]);
  // }

  menorDistancia(dados->VetorArestas, dados->M, dados->S, dados->T, dados->VeloInicial);
}


Dados * leituraArquivoEntrada(char * entrada){
  Dados * dados = malloc(sizeof(Dados));

  FILE * arquivo = fopen(entrada,"r");
  char str[100];

  int qtd = 0;
  while (!feof(arquivo)){
    qtd++;
    fscanf(arquivo,"%[^\n]\n",str); //capturando tamanho de linha do arquivo 
  }
  fseek(arquivo, 0, SEEK_SET); //retorno para início do arquivo


  fscanf(arquivo, "%d;%d\n",&dados->N,&dados->M);
  fscanf(arquivo, "%d;%d\n",&dados->S,&dados->T);
  fscanf(arquivo, "%d\n",&dados->VeloInicial);

  //alocando valores no vetor de arestas
  dados->VetorArestas = calloc(dados->M, sizeof(float *));
  
  int i;
  for (i = 0; i < dados->M; i++){
    dados->VetorArestas[i] = calloc(3,sizeof(float));
    fscanf(arquivo, "%f;%f;%f\n",&dados->VetorArestas[i][0],&dados->VetorArestas[i][1],&dados->VetorArestas[i][2]);
  }

  //alocando vetor de trafego 
  dados->tamanhoVetorTrafego = qtd - (3 + dados->M); //tamanho do vetor de trafego
  dados->VetorTrafego = calloc(qtd, sizeof(int *));

  for (i = 0; i < dados->tamanhoVetorTrafego; i++){
    dados->VetorTrafego[i] = calloc(4,sizeof(int));
    fscanf(arquivo,"%d;%d;%d;%d\n",&dados->VetorTrafego[i][0],&dados->VetorTrafego[i][1],&dados->VetorTrafego[i][2],&dados->VetorTrafego[i][3]);
  }
  fclose(arquivo);

  return dados;
}