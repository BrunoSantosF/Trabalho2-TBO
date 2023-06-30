#ifndef DADOS_H
#define DADOS_H

#include "Dijkstra.h"
#include "Lista.h"

void imprimeTempo(FILE * arquivo, double tempoEmSegundos);
void imprimeVertice(FILE * arquivo, int vertice, int limite);
int nmrLinhasArquivo(FILE * arquivo);
void leituraParametros(FILE * entrada, int * N, int * M, int * S, int * T);
Lista ** leituraArestas(FILE * entrada, int qtd, int qtdPontos);
int ** leituraTrafegos(FILE * entrada, int * qtd, int numLinhas, int numArestas);
void processaDados(FILE * saida, Lista ** arestas, int M, int N, int S, int T, int ** trafego, int tamanhoTrafego);
void liberaDados(Lista ** arestas, int N, int ** trafego, int tamanhoTrafego);
#endif