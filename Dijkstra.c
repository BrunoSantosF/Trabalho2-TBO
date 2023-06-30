#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include "FilaPrioridade.h"
#include "Dijkstra.h"

#define INFINITY DBL_MAX

int * calculaMenorCaminho(Lista ** distancias, int qtdDistancias, int qtdNo, int origem, int destino, int * tamanhoCaminho){
  int i;
  
  // declarações de variáveis de controle e da heap para o algoritmo
  double * temposDePercurso = calloc(qtdNo+1, sizeof(double));
  int * verticesAnteriores = calloc(qtdNo+1, sizeof(int));  
  fp * Q = PQ_init(qtdNo);
  
  // populando a heap com os tempos de deslocamento (distancia * velocidade)
  for(i=1;i<qtdNo+1;i++) {
    if (i!=origem) temposDePercurso[i] = INFINITY;
    else temposDePercurso[origem] = 0.0;
    PQ_insert(Q, make_item(i, temposDePercurso[i])); 
  }

  // iterando pela heap para achar o melhor caminho
  while (!PQ_empty(Q)) {
    Item * u = PQ_delmin(Q);

    // Iterando pelos vizinhos do ponto e buscando o tempo de deslocamento ate eles
    int nmrVizinho = 0;
    double tempoVizinho = 0;
    while(true){
      tempoVizinho = getTempoVizinho(distancias[id(u)], nmrVizinho++);
      if (tempoVizinho<0) break;
      
      double alt = temposDePercurso[id(u)] + tempoVizinho;

      int destino = getDestinoVizinho(distancias[id(u)], nmrVizinho-1);
      
      // verificando se o caminho até o noh vizinho, passando pelo noh atual, é de fato o menor caminho possível ate entao
      if (alt < temposDePercurso[destino]) {
        // caso seja o menor caminho, atualize o caminho ate entao
        temposDePercurso[destino] = alt;
        verticesAnteriores[destino] = id(u);
        PQ_decrease_key(Q, destino, alt);
      }
    }

    free(u);
  }

  // criando o vetor de caminho
  i=1;
  int * caminhoInvertido = malloc(sizeof(int) * qtdDistancias);
  
  *tamanhoCaminho=1;
  while (destino) {
    caminhoInvertido[i++] = destino;
    destino = verticesAnteriores[destino];
    *tamanhoCaminho+=1;
  }
  
  int * caminho = malloc(sizeof(int) * qtdDistancias);
  for(int j=0;j<*tamanhoCaminho;j++,i--) caminho[j] = caminhoInvertido[i];

  // liberando memoria e retornando caminho
  free(verticesAnteriores);
  free(temposDePercurso); 
  PQ_finish(Q);

  return caminho;
}