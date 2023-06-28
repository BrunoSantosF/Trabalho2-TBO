#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Dados.h"
#include "Dijkstra.h"

int nmrLinhasArquivo(FILE * arquivo){
  char str[100];
  int qtd = 0;

  //capturando a quantidade de linhas do arquivo 
  while (!feof(arquivo)){
    qtd++;
    fscanf(arquivo,"%[^\n]\n",str); 
  }

  //voltando o buffer para início do arquivo e retornando o resultado
  fseek(arquivo, 0, SEEK_SET); 
  return qtd;
}

void leituraParametros(FILE * entrada, int * N, int * M, int * S, int * T) {
  fscanf(entrada, "%d;%d\n", N, M);
  fscanf(entrada, "%d;%d\n", S, T);
}


void leituraArestas(FILE * entrada, double *** arestas, int qtd){

  //alocando vetor de arestas onde cada item é um vetor com [origem, destino, distancia, velocidade]
  *arestas = calloc(qtd, sizeof(double *));
  
  int veloInicial;
  fscanf(entrada, "%d\n", &veloInicial); 

  int i;
  for (i = 0; i < qtd; i++){
    (*arestas)[i] = calloc(4,sizeof(double));
    fscanf(entrada, "%lf;%lf;%lf\n", &(*arestas)[i][0], &(*arestas)[i][1], &(*arestas)[i][2]);
    (*arestas)[i][3] = veloInicial;
  }
}

void leituraTrafegos(FILE * entrada, int *** trafego, int * qtd, int numLinhas, int numArestas) {
  
  //alocando vetor de trafego 
  *qtd = numLinhas - (3 + numArestas); //tamanho do vetor de trafego
  *trafego = calloc(*qtd, sizeof(int *));
  
  int i;
  for (i = 0; i < *qtd; i++){
    (*trafego)[i] = calloc(4,sizeof(int));
    fscanf(entrada,"%d;%d;%d;%d\n", &(*trafego)[i][0], &(*trafego)[i][1], &(*trafego)[i][2], &(*trafego)[i][3]);
  }
}

void processaDados(FILE * saida, double ** arestas, int M, int N, int S, int T, int ** trafego, int tamanhoTrafego) {
  
  int i=1, t=0, tamanhoCaminho=0, origem = S;
  int * caminho = calculaMenorCaminho(arestas, M, N, S, T, &tamanhoCaminho);

  double tempo = 0.0, distancia = 0.0;

  // iterando pelo caminho recem gerado
  for(i=1;i<tamanhoCaminho;i++) {
    if (caminho[i] == S) {
      imprimeVertice(saida, origem, T);
      continue;
    }
    
    // procurando a aresta que tem a atual origem e o atual destino (caminho[i])
    int k=0;
    while(arestas[k][0]!=origem || arestas[k][1]!=caminho[i]) k++;

    origem = caminho[i];
    imprimeVertice(saida, origem, T);

    // acumulando a distancia percorrida
    distancia += arestas[k][2]/1000;
    
    // calculando o tempo atual
    tempo+=((arestas[k][2]/1000) / arestas[k][3]) * 3600;

    // sinalização de que alguma aresta foi alterada
    int mudouCaminho = 0;

    // verificando se houve mudança no trafego no tempo atual
    while (t<tamanhoTrafego && tempo>=trafego[t][0]) {

      // caso tenha ocorrido mudança, deve-se procurar a aresta que ocorreu a mudança
      int x=0;
      while (arestas[x][0] != trafego[t][1] || arestas[x][1] != trafego[t][2]) x++;

      // atualiza velocidade da aresta
      arestas[x][3] = trafego[t][3];

      // sinalizando que mudou uma aresta
      mudouCaminho = 1;
      
      t++;
    }

    if (mudouCaminho) {
      // recria o caminho
      free(caminho);
      caminho = calculaMenorCaminho(arestas, M, N, origem, T, &tamanhoCaminho);
      i=1;
      
      mudouCaminho = 0;
    }
  }

  fprintf(saida, "%lf\n", distancia);
  imprimeTempo(saida, tempo);
  free(caminho);
}

void imprimeTempo(FILE * arquivo, double tempoEmSegundos){
  int horas = (int)(tempoEmSegundos/3600);
  int minutos = (int)(((int)(tempoEmSegundos)%3600)/60);
  double segundos = tempoEmSegundos - 60*minutos - 3600*horas;
  fprintf(arquivo, "%02d:%02d:%lf", horas, minutos, segundos);
}

void imprimeVertice(FILE * arquivo, int vertice, int limite) {
  if (vertice!=limite) fprintf(arquivo, "%d;", vertice);
  else fprintf(arquivo, "%d\n", vertice);
}

void liberaDados(double ** arestas, int M, int ** trafego, int tamanhoTrafego){
  int i;
  for(i=0;i<M;i++) free(arestas[i]);
  free(arestas);

  for(i=0;i<tamanhoTrafego;i++) free(trafego[i]);
  free(trafego);
}