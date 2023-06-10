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
  double ** VetorArestas; //vetor que contém (vetice origem, vertice destino, distancia entre os nós)[3]
  int ** VetorTrafego; //vetor com informacoes do trafego ao longo da viagem(instante de tempo[0], aresta origem[1], aresta destino[2], velocidade media nova[3])
  int tamanhoVetorTrafego; // tamanho do vetor de trafego
};

//TODO: essa função tinha q ir pra main de alguma maneira
void imprimirDados(Dados * dados){
  
  int i=1, t=0, tamanhoCaminho=0;
  int * caminho = calculaMenorCaminho(dados->VetorArestas, dados->M, dados->N, dados->S, dados->T, &tamanhoCaminho);

  int origem = dados->S,  interrup=0;
  double tempo = 0.0, distancia = 0.0;

  for(i=1;i<tamanhoCaminho;i++) {
    
    if (caminho[i] == dados->S) {
      imprimeVertice(origem, dados->T);
      continue;
    }
    
    //TODO: procurar a distancia desse jeito pode ser muito ineficiente
    int k=0;
    while(dados->VetorArestas[k][0]!=origem || dados->VetorArestas[k][1]!=caminho[i]) k++;

    origem = caminho[i];
    imprimeVertice(origem, dados->T);

    // acumulando a distancia percorrida
    distancia += dados->VetorArestas[k][2]/1000;
    
    // calculando o tempo atual
    tempo+=((dados->VetorArestas[k][2]/1000) / dados->VetorArestas[k][3]) * 3600;

    // verificando se houve mudança no trafego no tempo atual
    while (t<dados->tamanhoVetorTrafego && tempo>=dados->VetorTrafego[t][0]) {

      // caso tenha ocorrido mudança, deve-se procurar a aresta que ocorreu a mudança
      int x=0;
      while (dados->VetorArestas[x][0] != dados->VetorTrafego[t][1] || dados->VetorArestas[x][1] != dados->VetorTrafego[t][2]) x++;
      //TODO: procurar a distancia desse jeito pode ser muito ineficiente

      // atualiza velocidade da aresta
      dados->VetorArestas[x][3] = dados->VetorTrafego[t][3];

      // recria o caminho
      free(caminho);
      caminho = calculaMenorCaminho(dados->VetorArestas, dados->M, dados->N, origem, dados->T, &tamanhoCaminho);
      i=1;
      
      t++;
    };
  }
  printf("%lf\n", distancia);
  imprimeTempo(tempo);
  free(caminho);
}

void imprimeTempo(double tempoEmSegundos){
  int horas = (int)(tempoEmSegundos/3600);
  int minutos = (int)(((int)(tempoEmSegundos)%3600)/60);
  double segundos = tempoEmSegundos - 60*minutos - 3600*horas;
  printf("%02d:%02d:%lf\n", horas, minutos, segundos);
}

void imprimeVertice(int vertice, int limite) {
  if (vertice!=limite) printf("%d;", vertice);
  else printf("%d\n", vertice);
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
  
  int VeloInicial;
  fscanf(arquivo, "%d\n",&VeloInicial); //TODO: talvez de pra tirar essa variavel

  //alocando valores no vetor de arestas
  dados->VetorArestas = calloc(dados->M, sizeof(double *));
  
  int i;
  for (i = 0; i < dados->M; i++){
    dados->VetorArestas[i] = calloc(4,sizeof(double));
    fscanf(arquivo, "%lf;%lf;%lf\n",&dados->VetorArestas[i][0],&dados->VetorArestas[i][1],&dados->VetorArestas[i][2]);
    dados->VetorArestas[i][3] = VeloInicial;
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