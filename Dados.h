#ifndef DADOS_H
#define DADOS_H

void imprimeTempo(FILE * arquivo, double tempoEmSegundos);
void imprimeVertice(FILE * arquivo, int vertice, int limite);
int nmrLinhasArquivo(FILE * arquivo);
void leituraParametros(FILE * entrada, int * N, int * M, int * S, int * T);
void leituraArestas(FILE * entrada, double *** arestas, int qtd);
void leituraTrafegos(FILE * entrada, int *** trafego, int * qtd, int numLinhas, int numArestas);
void processaDados(FILE * saida, double ** arestas, int M, int N, int S, int T, int ** trafego, int tamanhoTrafego);
void liberaDados(double ** arestas, int M, int ** trafego, int tamanhoTrafego);

#endif