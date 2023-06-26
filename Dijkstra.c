#include <stdlib.h>
#include <stdio.h>
#include "FilaPrioridade.h"
#include "Pilha.h"
#include <float.h>

#define INFINITY DBL_MAX

int * calculaMenorCaminho(double *** distancias, int qtdDistancias, int qtdNo, int origem, int destino, int * tamanhoCaminho){
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

    for (i=1;i<qtdNo+1;i++){
      if (distancias[id(u)][i] == NULL) continue;

      // calculando o tempo de deslocamento entre a origem inicial e o vizinho, passando pelo noh atual
      double alt = temposDePercurso[id(u)] + ((distancias[id(u)][i][0]/1000) / distancias[id(u)][i][1]);
      
      // verificando se o caminho até o noh vizinho, passando pelo noh atual, é de fato o menor caminho possível ate entao
      if (alt < temposDePercurso[i]) {
        // caso seja o menor caminho, atualize o caminho ate entao
        temposDePercurso[i] = alt;
        verticesAnteriores[i] = id(u);
        PQ_decrease_key(Q, i, alt);
      }
    }

    free(u);
  }

  // agora basta usar uma pilha para fazer o "traverse" do caminho
  Pilha * pilha = criaPilhaVazia();
  *tamanhoCaminho=1;
  while (destino) {
    push(pilha, destino);
    destino = verticesAnteriores[destino];
    *tamanhoCaminho+=1;
  }

  // criando o vetor de caminho
  i=1;
  int * caminho = malloc(sizeof(int) * (*tamanhoCaminho));
  while(!pilhaVazia(pilha)) caminho[i++] = pop(pilha);

  // liberando memoria e retornando caminho
  free(verticesAnteriores);
  free(temposDePercurso); 
  destroiPilha(pilha);
  PQ_finish(Q);
  
  return caminho;
}