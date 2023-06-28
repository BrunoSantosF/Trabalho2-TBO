#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Dados.h"
#include "FilaPrioridade.h"
#include <time.h>


int main(int argc, char  ** argv){
  clock_t start = clock();
  
  if (argc != 3){
      printf("Erro: numero de argumentos invalido\n");
      return 1;
  }

  int N;              // numero de vertices (1 a N)
  int M;              // numero de arestas
  int S;              // nó de origem
  int T;              // nó de destino 

  double *** arestas;  // vetor que contém (vetice origem, vertice destino, distancia entre os nós)[3]
  int ** trafego;     // vetor com informacoes do trafego ao longo da viagem(instante de tempo[0], aresta origem[1], aresta destino[2], velocidade media nova[3])
  int tamanhoTrafego; // tamanho do vetor de trafego

  char * nomeArquivoEntrada = argv[1]; // nome do arquivo de entrada
  char * nomeArquivoSaida = argv[2];   // nome do arquivo de saidas
  
  // abrindo arquivos
  FILE * arquivoEntrada = fopen(nomeArquivoEntrada, "r");
  FILE * arquivoSaida = fopen(nomeArquivoSaida, "w");

  // contando o numero de linhas antes de começar a ler os conteudos
  int nmrLinhas = nmrLinhasArquivo(arquivoEntrada);
  
  clock_t t1 = clock();
  // populando os vetores de dados
  leituraParametros(arquivoEntrada, &N, &M, &S, &T);
  arestas = leituraArestas(arquivoEntrada, M, N);

  trafego = leituraTrafegos(arquivoEntrada, &tamanhoTrafego, nmrLinhas, M);
  fclose(arquivoEntrada);
  clock_t t2 = clock();
  printf("Tempo na leitura: %lf ms\n", ((((double)(t2-t1))/CLOCKS_PER_SEC) * 1000));

  // aplicando processamento do trabalho
  clock_t t3 = clock();
  processaDados(arquivoSaida, arestas, M, N, S, T, trafego, tamanhoTrafego);
  clock_t t4 = clock();
  printf("Tempo no processamento: %lf ms\n", ((((double)(t4-t3))/CLOCKS_PER_SEC) * 1000));
  fclose(arquivoSaida);
  
  liberaDados(arestas, N, trafego, tamanhoTrafego);

  clock_t end = clock();
  printf("Tempo total: %lf ms\n", ((((double)(end-start))/CLOCKS_PER_SEC) * 1000));
  return 0;
}