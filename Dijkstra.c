#include <stdlib.h>
#include <stdio.h>
#include "FilaPrioridade.h"
#include "Pilha.h"

static int compare(const void*a, const void *b){
  return (*(float**)a)[0] > (*(float**)b)[0];
}

void ordenarDistancias(float ** distancias, int qtdDistancias){
  // ordenação de distancias leva em conta apenas o primeiro no de cada aresta
  qsort(distancias, qtdDistancias, sizeof(float*), compare);
}

float menorDistancia(float ** distancias, int qtdDistancias, int origem, int destino, int veloInicial){
  int i;
  ordenarDistancias(distancias, qtdDistancias);
  // for(i=0;i<qtdDistancias;i++) printf("[%f][%f][%f]\n", distancias[i][0], distancias[i][1], distancias[i][2]);
  
  float * distanciaProxNoh = malloc(sizeof(float) * qtdDistancias);
  float * nohsVisitados = malloc(sizeof(float)* qtdDistancias);
  
  distanciaProxNoh[origem] = 0;
  fp * Q = PQ_init(qtdDistancias);

  for(i=0;i<qtdDistancias;i++) {
    if (i!=origem){
      distanciaProxNoh[i] = 10000000; // TODO: mudar representação de "infinito"
      nohsVisitados[i] = 0;
    }
    PQ_insert(Q, make_item(i+1, distancias[i][2])); // TODO: aqui talvez seja melhor não usar um vetor e sim uma struct para acessar a distancia
  }

  while (!PQ_empty(Q)) {
    Item * u = PQ_delmin(Q);

    for(i=0;i<qtdDistancias;i++) { //FIXME: talvez isso seja muito custoso (vários loops pelo vetor de distancias)
      // verificando se é vizinho de u
      if (distancias[i][0] == id(u)) {
        // calculando a distancia entre a origem e o vizinho
        float alt = distanciaProxNoh[id(u)] + distancias[i][2];
        
        // verificando se a distancia ate o vizinho é menor saindo da origem ou de u
        int v = distancias[i][1];
        // printf("dist da origem ate o %d: %f, dist de %d ate o %d: %f\n", v, distanciaProxNoh[v], id(u), v, alt);
        if (alt < distanciaProxNoh[v]) {

          distanciaProxNoh[v] = alt;
          nohsVisitados[v] = id(u);
          PQ_decrease_key(Q, v, alt);
        }
      }
    }
  }

  Pilha * pilha = criaPilhaVazia();
  printf("distancia origem->destino: %f\n", distanciaProxNoh[destino]);
  while (destino) {
    push(pilha, destino);
    destino = nohsVisitados[destino];
  }

  imprimePilha(pilha);
  destroiPilha(pilha);

  free(nohsVisitados);
  free(distanciaProxNoh);
}