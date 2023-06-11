#ifndef DIJSKTRA_H
#define DIJSKTRA_H
#include "Pilha.h"



/// @brief dados todos os nós e suas distâncias, obtém o menor caminho entre dois nós
/// @param distancias vetor com as distancias entre os nós
/// @param qtdDistancias tamanho do vetor de distancias
/// @param qtdNo quantidade de nós
/// @param origem nó de origem
/// @param destino nó de destino
/// @param tamanhoCaminho 
/// @return o menor caminho obtido


int * calculaMenorCaminho(double ** distancias, int qtdDistancias, int qtdNo,
                  int origem, int destino, int * tamanhoCaminho);

#endif