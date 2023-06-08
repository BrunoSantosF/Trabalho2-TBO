#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Dados.h"
#include "Dijkstra.h"

//TODO: não precisa de um struct para isso aqui
struct dados {
  int N; // numero de vertices (1 a N)
  int M; // numero de arestas
  int S; // nó de origem
  int T; // nó de destino 
  int VeloInicial; //velocidade media inicial
  
  //TODO: trocar para double em todo o projeto
  double ** VetorArestas; //vetor que contém (vetice origem, vertice destino, distancia entre os nós)[3]
  
  int ** VetorTrafego; //vetor com informacoes do trafego ao longo da viagem(instante de tempo[0], aresta origem[1], aresta destino[2], velocidade media nova[3])
  int tamanhoVetorTrafego; // tamanho do vetor de trafego
};

//TODO: essa função tinha q ir pra main de alguma maneira
void imprimirDados(Dados * dados){
  
  int i, k=0;
  int tamanhoCaminho=0;
  int * caminho = calculaMenorCaminho(dados->VetorArestas, dados->M, dados->N, dados->S, dados->T, &tamanhoCaminho);

  int origem = dados->S;
  for(i=1;i<tamanhoCaminho;i++) {
    while(dados->VetorArestas[k][1]!=caminho[i]) k++;

    printf("passo %d: ir de %d até %d (%lf km a %lf km/h)\n", i, origem, caminho[i], dados->VetorArestas[k][2]/1000, dados->VetorArestas[k][3]);
    origem = caminho[i];
  }

  free(caminho);
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
  fscanf(arquivo, "%d\n",&dados->VeloInicial); //TODO: talvez de pra tirar essa variavel

  //alocando valores no vetor de arestas
  dados->VetorArestas = calloc(dados->M, sizeof(double *));
  
  int i;
  for (i = 0; i < dados->M; i++){
    dados->VetorArestas[i] = calloc(4,sizeof(double));
    fscanf(arquivo, "%lf;%lf;%lf\n",&dados->VetorArestas[i][0],&dados->VetorArestas[i][1],&dados->VetorArestas[i][2]);
    dados->VetorArestas[i][3] = dados->VeloInicial;
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

void liberaDados(Dados * dados) {
  int i;
  for (i = 0; i < dados->M; i++) free(dados->VetorArestas[i]);
  free(dados->VetorArestas);
  for (i = 0; i < dados->tamanhoVetorTrafego; i++) free(dados->VetorTrafego[i]);
  free(dados->VetorTrafego);
  free(dados);
}