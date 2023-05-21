#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Dados.h"


int main(int argc, char  ** argv){
  
  if (argc != 3){
      printf("Erro: numero de argumentos invalido\n");
      return 1;
  }

  char *nomeArquivoEntrada = argv[1];
  char *nomeArquivoSaida = argv[2];

  Dados * dados = leituraArquivoEntrada(nomeArquivoEntrada);

  ImprimirDados(dados);

  return 0;
}