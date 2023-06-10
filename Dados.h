#ifndef DADOS_H
#define DADOS_H

typedef struct dados Dados;

Dados * leituraArquivoEntrada(char * entrada);
void imprimeTempo(double tempoEmSegundos);
void imprimeVertice(int vertice, int limite);
void imprimirDados(Dados * dados);
void liberaDados(Dados * dados);

#endif