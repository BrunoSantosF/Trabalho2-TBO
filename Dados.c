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


double *** leituraArestas(FILE * entrada, int qtd, int qtdPontos){

  double *** arestas = calloc(qtdPontos+1, sizeof(double **));
  
  double veloInicial=0.0;
  fscanf(entrada, "%lf\n", &veloInicial); 

  int i;
  for (i = 0; i < qtd; i++){
    int origem=0, destino=0;
    double distancia=0.0;
    fscanf(entrada, "%d;%d;%lf\n", &origem, &destino, &distancia);
    if (!arestas[origem]) arestas[origem] = calloc(qtdPontos+1, sizeof(double*));
    
    double * aresta = malloc(sizeof(double) * 2);
    aresta[0] = distancia;
    aresta[1] = veloInicial;
    arestas[origem][destino] = aresta;
  }

  return arestas;
}

int ** leituraTrafegos(FILE * entrada, int * qtd, int numLinhas, int numArestas) {
  
  //alocando vetor de trafego 
  *qtd = numLinhas - (3 + numArestas); //tamanho do vetor de trafego
  int ** trafego = calloc(*qtd, sizeof(int *));
  
  int i;
  for (i = 0; i < *qtd; i++){
    trafego[i] = calloc(4,sizeof(int));
    fscanf(entrada,"%d;%d;%d;%d\n", &trafego[i][0], &trafego[i][1], &trafego[i][2], &trafego[i][3]);
  }

  return trafego;
}

void processaDados(FILE * saida, double *** arestas, int M, int N, int S, int T, int ** trafego, int tamanhoTrafego) {
  
  int i=1, t=0, tamanhoCaminho=0, origem = S, destino = S;
  int * caminho = calculaMenorCaminho(arestas, M, N, S, T, &tamanhoCaminho);
  double tempo = 0.0, distancia = 0.0;

  // iterando pelo vetor do caminho recem calculado
  for(i=1;i<tamanhoCaminho;i++) {
    
    // se for o primeiro vertice do caminho (origem), apenas imprima o vertice
    if (caminho[i] == S) {
      imprimeVertice(saida, origem, T);
      continue;
    }
    
    // atualizando destino
    destino = caminho[i];

    // acumulando a distancia percorrida
    distancia += (arestas[origem][destino][0])/1000;
    
    // calculando o tempo atual
    tempo += ((arestas[origem][destino][0]/1000) / arestas[origem][destino][1]) * 3600;

    // atualizando a nova origem e imprimindo
    origem = caminho[i];
    imprimeVertice(saida, origem, T);

    // variável que sinaliza alteração nas arestas
    int mudouCaminho = 0;
    
    // verificando se houve mudança no trafego no tempo atual
    while (t<tamanhoTrafego && tempo>=trafego[t][0]) {

      // atualização da nova velocidade de trafego
      int origemTrafego = trafego[t][1];
      int destinoTrafego = trafego[t][2];
      int velocidadeTrafego = trafego[t][3];
      arestas[origemTrafego][destinoTrafego][1] = velocidadeTrafego;

      // sinalizando que o caminho foi alterado
      mudouCaminho=1;
      
      // incremento no vetor de trafegos
      t++;
    }

    // caso tenha alterações, recalcule...
    if (mudouCaminho) {
      free(caminho);
      caminho = calculaMenorCaminho(arestas, M, N, origem, T, &tamanhoCaminho);
      i=1;
      mudouCaminho=0;
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

void liberaDados(double *** arestas, int N, int ** trafego, int tamanhoTrafego){
  int i, j;
  for(i=0;i<N+1;i++) {
    if (arestas[i] == NULL) continue;
    for(j=0;j<N+1;j++) if (arestas[i][j] != NULL) free(arestas[i][j]);
    free(arestas[i]);
  }
  free(arestas);

  for(i=0;i<tamanhoTrafego;i++) free(trafego[i]);
  free(trafego);
}