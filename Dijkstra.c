#include <stdlib.h>
#include <stdio.h>
#include "FilaPrioridade.h"
#include "Pilha.h"

static int compare(const void*a, const void *b){
  return (*(double**)a)[0] > (*(double**)b)[0];
}

void ordenarDistancias(double ** distancias, int qtdDistancias){
  // ordenação de distancias leva em conta apenas o primeiro no de cada aresta
  qsort(distancias, qtdDistancias, sizeof(double*), compare);
}

int * calculaMenorCaminho(double ** distancias, int qtdDistancias, int qtdNo, int origem, int destino, int * tamanhoCaminho){
  int i;

  // primeiramente se ordena as distancias, para que as arestas saindo do nó de origem inicial estejam no começo
  ordenarDistancias(distancias, qtdDistancias);

  // TODO: debug (retirar depois)
  // for(i=0;i<qtdDistancias;i++) printf("[%lf][%lf][%lf]\n", distancias[i][0], distancias[i][1], distancias[i][2]);

  // declarações de variáveis de controle e da heap para o algoritmo
  double * temposDePercurso = malloc(sizeof(double) * qtdDistancias);
  int * nohsVisitados = calloc(qtdNo, sizeof(int));  
  fp * Q = PQ_init(qtdDistancias);

  // populando a heap com os tempos de deslocamento (distancia * velocidade)
  //TODO: talvez esse loop nao precise começar em 0 mas sim em "origem" para cortar caminhos já percorridos
  for(i=0;i<qtdDistancias;i++) {
    if (i!=origem) temposDePercurso[i] = 10000000.0; // TODO: mudar representação de "infinito"
    else temposDePercurso[origem] = 0.0;
    
    // TODO: aqui talvez seja melhor não usar um vetor e sim uma struct para acessar distancia e velocidade
    PQ_insert(Q, make_item(i+1, distancias[i][2]/1000 * distancias[i][3])); 
  }

  // iterando pela heap para achar o melhor caminho
  while (!PQ_empty(Q)) {
    Item * u = PQ_delmin(Q);
    
    // loop para procurar o vizinhos (nós alcançáveis pelo nó atual)
    //TODO: talvez esse loop nao precise começar em 0 mas sim em "origem" para cortar caminhos já percorridos
    for(i=0;i<qtdDistancias;i++) { //TODO: talvez isso seja muito custoso (vários loops pelo vetor de distancias)

      // verificando se é vizinho de u
      if (distancias[i][0] == id(u)) {
        
        // calculando o tempo de deslocamento entre a origem inicial e o vizinho, passando pelo noh atual
        double alt = temposDePercurso[id(u)] + (distancias[i][2]/1000 * distancias[i][3]);
        
        // verificando se o caminho até o noh vizinho, passando pelo noh atual, é de fato o menor caminho possível ate entao
        int v = distancias[i][1];
        if (alt < temposDePercurso[v]) {
          // caso seja o menor caminho, atualize o caminho ate entao
          temposDePercurso[v] = alt;
          nohsVisitados[v] = id(u);
          // PQ_decrease_key(Q, v, alt);
        }
      }
    }

    free(u);
  }

  printf("\n");
  
  // agora basta usar uma pilha para fazer o "traverse" do caminho
  //TODO: talvez fazer uma implementação sem pilha (usando vetor)
  Pilha * pilha = criaPilhaVazia();
  while (destino) {
    push(pilha, destino);
    destino = nohsVisitados[destino];
    *tamanhoCaminho+=1;
  }

  // criando o vetor de caminho
  i=0;
  int * caminho = malloc(sizeof(int) * (*tamanhoCaminho));
  while(!pilhaVazia(pilha)) {
    caminho[i++] = pop(pilha);
  }

  // liberando memoria e retornando caminho
  free(nohsVisitados);
  free(temposDePercurso); 
  destroiPilha(pilha);
  PQ_finish(Q);
  return caminho;
}