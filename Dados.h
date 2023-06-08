#ifndef DADOS_H
#define DADOS_H

typedef struct dados Dados;

Dados * leituraArquivoEntrada(char * entrada);

void imprimirDados(Dados * dados);
void liberaDados(Dados * dados);

#endif